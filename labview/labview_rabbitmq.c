#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>
#include <amqp_framing.h>
#include <string.h>
#include "utils.h"
#include "extcode.h"
#include "labview_rabbitmq.h"
#include <assert.h>
#include <sys/time.h>
#include <stdio.h>


MgErr copyStringToLStrHandle(char *cpString, LStrHandle LVString)
{
	int32 len = strlen(cpString);
	MgErr err = NumericArrayResize(uB, 1, (UHandle*) &LVString, len);
	if (!err)
	{
		strncpy((*LVString)->str, cpString, len);	// copying the string into the handle
		(*LVString)->cnt = len;	// telling the Handle what string size to expect
	}

	return err;
}

MgErr copyBufferToLStrHandle(const void *buffer, int len, LStrHandle LVString)
{
	MgErr err = NumericArrayResize(uB, 1, (UHandle*) &LVString, len);
	if (!err)
	{
		memcpy((*LVString)->str, buffer, len);	// copying the string into the handle
		(*LVString)->cnt = len;	// telling the Handle what string size to expect
	}

																	
			 
	 
																					
																				
	 
	return err;
}

// Function to split a string into multiple strings based on the ";" separator
char **splitString(char *input, int *count)
{
	char **tokens = NULL;
	char *token = strtok(input, ";");
	*count = 0;

	while (token != NULL)
	{
		tokens = (char **) realloc(tokens, ((*count) + 1) *sizeof(char*));
		if (tokens == NULL)
		{
			perror("Memory allocation error");
			exit(1);
		 
										 
				   
								  
		}

		tokens[(*count)] = strdup(token);
		(*count) ++;
		token = strtok(NULL, ";");
	}

	return tokens;
}

void getConcatenatedMessageHeaders(amqp_table_t *table, LStrHandle cheaders_key, LStrHandle cheaders_value)
{
	// Calculate required buffer size for concatenated headers keys and values,
	// following strings will be separated by ";". Buffer will be finished with Null-terminate the C string.
	// Init counters with num of elements-1 (number of separators) + 1 ('\0')
	int required_buffer_size_keys = (table->num_entries - 1) + 1;
	int required_buffer_size_values = (table->num_entries - 1) + 1;
	for (int i = 0; i < table->num_entries; i++)
	{
		required_buffer_size_keys += table->entries[i].key.len;
		switch (table->entries[i].value.kind) {
			case AMQP_FIELD_KIND_I8:
				required_buffer_size_values += 1;
				break;
			case AMQP_FIELD_KIND_I64:
				required_buffer_size_values += 8;
				break;
			case AMQP_FIELD_KIND_UTF8:
				required_buffer_size_values += table->entries[i].value.value.bytes.len;
				break;
			default:
				required_buffer_size_values += 0;
				break;
		}
	}

	// Allocate memory for temp strings
	char *keys = (char*) malloc(required_buffer_size_keys* sizeof(char));
	char *values = (char*) malloc(required_buffer_size_values* sizeof(char));

	char *byteArray;
	int keys_offset = 0;
	int values_offset = 0;
	for (int i = 0; i < table->num_entries; i++)
	{
		memcpy(keys + keys_offset, table->entries[i].key.bytes, table->entries[i].key.len);
		keys_offset += table->entries[i].key.len;
		keys[keys_offset] = ';';
		keys_offset++;
		
		switch (table->entries[i].value.kind) {
			case AMQP_FIELD_KIND_I8:
				values[values_offset]=table->entries[i].value.value.i8; //check if not zero!
				values_offset++;
				break;
			case AMQP_FIELD_KIND_I64:
				byteArray=&(table->entries[i].value.value.i64);
				memcpy(values + values_offset, byteArray, 8);
				values_offset+=8;
				break;
			case AMQP_FIELD_KIND_UTF8:
				memcpy(values + values_offset, table->entries[i].value.value.bytes.bytes, table->entries[i].value.value.bytes.len);
				values_offset+=table->entries[i].value.value.bytes.len;
				break;
			default:
				required_buffer_size_values += 0;
				break;
		}
		values[values_offset] = ';';
		values_offset++;
	}

	// add Null-terminate the C string
	keys[keys_offset - 1] = '\0';
	values[values_offset -1] = '\0';

	copyStringToLStrHandle(keys, cheaders_key);
	//copyStringToLStrHandle(values, cheaders_value);
	copyBufferToLStrHandle(values, required_buffer_size_values, cheaders_value);

	free(keys);
	free(values);
}

char *amqpBytesToString(amqp_bytes_t input)
{
	// Allocate memory for the C string and a null terminator
	char *result = (char*) malloc(input.len + 1);

	if (result == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	// Copy the data from amqp_bytes_t to the C string
	memcpy(result, input.bytes, input.len);

	// Null-terminate the C string
	result[input.len] = '\0';

	return result;
}

LABVIEW_PUBLIC_FUNCTION
char *lv_rabbitmq_version(void)
{
	char *VERSION = "0.0.1";
	return VERSION;
}

/*This function is a modified version of the `die_on_amqp_error` function used in examples,
enhanced with LabVIEW string support.*/
int lv_report_amqp_error(amqp_rpc_reply_t x, char
	const *context, LStrHandle error_description)
{
	unsigned char temp_str[MAX_ERROR_DESCRIPTION_LENGTH];
	int err;
	switch (x.reply_type)
	{
		case AMQP_RESPONSE_NORMAL:
			return _AMQP_RESPONSE_NORMAL;

		case AMQP_RESPONSE_NONE:
			snprintf(temp_str, MAX_ERROR_DESCRIPTION_LENGTH, "%s: missing RPC reply type!", context);
			err = copyStringToLStrHandle(temp_str, error_description);
			if (err)
			{
				return err;
			}

			return _AMQP_RESPONSE_NONE;

		case AMQP_RESPONSE_LIBRARY_EXCEPTION:
			snprintf(temp_str, MAX_ERROR_DESCRIPTION_LENGTH, "%s: %s ", context, amqp_error_string2(x.library_error));
			err = copyStringToLStrHandle(temp_str, error_description);
			if (err)
			{
				return err;
			}

			return _AMQP_RESPONSE_LIBRARY_EXCEPTION;

		case AMQP_RESPONSE_SERVER_EXCEPTION:
			switch (x.reply.id)
			{
				case AMQP_CONNECTION_CLOSE_METHOD:
					{
						amqp_connection_close_t *m =
						(amqp_connection_close_t*) x.reply.decoded;
						snprintf(temp_str, MAX_ERROR_DESCRIPTION_LENGTH, "%s: server connection error %uh, message: %.*s ",
							context, m->reply_code, (int) m->reply_text.len,
							(char*) m->reply_text.bytes);
						err = copyStringToLStrHandle(temp_str, error_description);
						if (err)
						{
							return err;
						}

						return _AMQP_RESPONSE_SERVER_EXCEPTION;
					}

				case AMQP_CHANNEL_CLOSE_METHOD:
					{
						amqp_channel_close_t *m = (amqp_channel_close_t*) x.reply.decoded;
						snprintf(temp_str, MAX_ERROR_DESCRIPTION_LENGTH, "%s: server channel error %uh, message: %.*s ",
							context, m->reply_code, (int) m->reply_text.len,
							(char*) m->reply_text.bytes);
						err = copyStringToLStrHandle(temp_str, error_description);
						if (err)
						{
							return err;
						}

						return _AMQP_RESPONSE_SERVER_EXCEPTION;
					}

				default:
					snprintf(temp_str, MAX_ERROR_DESCRIPTION_LENGTH, "%s: unknown server error, method id 0x%08X ",
						context, x.reply.id);
					err = copyStringToLStrHandle(temp_str, error_description);
					if (err)
					{
						return err;
					}

					return _AMQP_RESPONSE_SERVER_EXCEPTION;
			}

   
			break;
	}
}


LABVIEW_PUBLIC_FUNCTION
int64_t lv_amqp_new_connection()
{
	// conn is an opaque struct pointer
	amqp_connection_state_t conn = amqp_new_connection();
	// cast to int64_t so LabVIEW will receive it as 
	// a 64-bit integer transfered by value
	int64_t conn_intptr = (int64_t) conn;
	return conn_intptr;
}


LABVIEW_PUBLIC_FUNCTION
int lv_amqp_close_connection(int64_t conn_intptr, LStrHandle error_description)
{
	// cast back to amqp_connection_state_t opaque struct pointer
	amqp_connection_state_t conn = (amqp_connection_state_t) conn_intptr;
	return lv_report_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Connection close", error_description);
}


LABVIEW_PUBLIC_FUNCTION
void lv_amqp_destroy_connection(int64_t conn_intptr)
{
	amqp_connection_state_t conn = (amqp_connection_state_t) conn_intptr;
	amqp_destroy_connection(conn);
}


LABVIEW_PUBLIC_FUNCTION
int lv_amqp_channel_open(int64_t conn_intptr, uint16_t channel, LStrHandle error_description)
{
	amqp_connection_state_t conn = (amqp_connection_state_t) conn_intptr;
	amqp_channel_open(conn, channel);
	return lv_report_amqp_error(amqp_get_rpc_reply(conn), "Opening channel", error_description);
}


LABVIEW_PUBLIC_FUNCTION
int lv_amqp_channel_close(int64_t conn_intptr, uint16_t channel, LStrHandle error_description)
{
	amqp_connection_state_t conn = (amqp_connection_state_t) conn_intptr;
	return lv_report_amqp_error(amqp_channel_close(conn, channel, AMQP_REPLY_SUCCESS), "Closing channel", error_description);
}


LABVIEW_PUBLIC_FUNCTION
int lv_amqp_exchange_declare(int64_t conn_intptr, uint16_t channel, char *exchange, char *exchangetype, LStrHandle error_description)
{
	amqp_connection_state_t conn = (amqp_connection_state_t) conn_intptr;

	amqp_boolean_t PASSIVE = 0;
	amqp_boolean_t DURABLE = 0;
	amqp_boolean_t AUTO_DELETE = 0;
	amqp_boolean_t INTERNAL = 0;
	amqp_exchange_declare(conn, channel, amqp_cstring_bytes(exchange),
		amqp_cstring_bytes(exchangetype), PASSIVE, DURABLE, AUTO_DELETE, INTERNAL,
		amqp_empty_table);

	return lv_report_amqp_error(amqp_get_rpc_reply(conn), "Exchange declare", error_description);
}


LABVIEW_PUBLIC_FUNCTION
int lv_amqp_login(int64_t conn_intptr, char *host, int port, int timeout_sec, char *username, char *password, LStrHandle error_description)
{
	int status;
	amqp_socket_t *socket = NULL;
	amqp_connection_state_t conn = (amqp_connection_state_t) conn_intptr;

	struct timeval tval;
	tval.tv_sec = timeout_sec;
	tval.tv_usec = 0;

	socket = amqp_tcp_socket_new(conn);
	if (!socket)
	{
		return _CREATING_TCP_SOCKET;
	}

	status = amqp_socket_open_noblock(socket, host, port, &tval);
	if (status < 0)
	{
		return _OPENING_TCP_SOCKET;
	}

	/*Code explanation:
	socket is set/stored in the connection state,
	so we dont need to destroy this socket because
	it will be destroyed along with connection state destroy function*/

	char
	const *VHOST = "/";	// the virtual host to connect to on the broker. The default on most brokers is "/"
	int
	const CHANNEL_MAX = 0;	// the limit for number of channels for the connection. 0 means no limit.
	int
	const FRAME_MAX = 131072;	// the maximum size of an AMQP frame. 131072 is the default. 
	// 4096 is the minimum size, 2^31-1 is the maximum, a good default is 131072 (128KB),
	int
	const HEARTBEAT = 0;	// the number of seconds between heartbeat frames to request of the broker. A value of 0 disables heartbeats.

	return lv_report_amqp_error(amqp_login(conn, VHOST, CHANNEL_MAX, FRAME_MAX, HEARTBEAT, AMQP_SASL_METHOD_PLAIN, username, password), "Logging in", error_description);
}


LABVIEW_PUBLIC_FUNCTION
int lv_amqp_basic_publish(int64_t conn_intptr, uint16_t channel, char *exchange, char *routingkey, char *cheaders_key, char *cheaders_value, char *messagebody, LStrHandle error_description)
{
	amqp_connection_state_t conn = (amqp_connection_state_t) conn_intptr;
	amqp_basic_properties_t props;
	props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
	props.content_type = amqp_cstring_bytes("text/plain");
	props.delivery_mode = 2; /*persistent delivery mode */

	int count, count2;
	char **headers_key = splitString(cheaders_key, &count);
	char **headers_value = splitString(cheaders_value, &count2);
	if (headers_key != NULL)
	{
		// Update flags to use custom headers
		props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG | AMQP_BASIC_HEADERS_FLAG;
		// Allocate memory for custom headers
		amqp_table_t *table = &props.headers;
		props.headers.num_entries = count;
		props.headers.entries = calloc(props.headers.num_entries, sizeof(amqp_table_entry_t));
		// update headers content
		for (int i = 0; i < count; i++)
		{ (table->entries[i]).key = amqp_cstring_bytes(headers_key[i]);
			((table->entries[i]).value).kind = AMQP_FIELD_KIND_BYTES;
			((table->entries[i]).value).value.bytes = amqp_cstring_bytes(headers_value[i]);
		}
	}

	int error_code = error_code = amqp_basic_publish(conn, channel, amqp_cstring_bytes(exchange), amqp_cstring_bytes(routingkey), 0, 0, &props, amqp_cstring_bytes(messagebody));

	// Dereference headers
	if (headers_key != NULL)
	{
		for (int i = 0; i < count; i++)
		{
			free(headers_key[i]);
			free(headers_value[i]);
		}

		free(headers_key);
		free(headers_value);
	}

	return error_code;
	//this function returns amqp_status_enum thats different from amqp_rpc_reply_t
}


LABVIEW_PUBLIC_FUNCTION
int lv_amqp_create_queue(int64_t conn_intptr, uint16_t channel, LStrHandle queue_name_out, LStrHandle error_description)
{
	amqp_connection_state_t conn = (amqp_connection_state_t) conn_intptr;
	int status;
	amqp_bytes_t queuename;

	amqp_boolean_t PASSIVE = 0;
	amqp_boolean_t DURABLE = 0;
	amqp_boolean_t EXCLUSIVE = 0;
	amqp_boolean_t AUTO_DELETE = 1;
	amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, channel, amqp_empty_bytes, PASSIVE, DURABLE, EXCLUSIVE, AUTO_DELETE, amqp_empty_table);

	status = lv_report_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue", error_description);
	copyBufferToLStrHandle(r->queue.bytes, r->queue.len, queue_name_out);
	return status;
}

LABVIEW_PUBLIC_FUNCTION
int lv_amqp_bind_queue(int64_t conn_intptr, uint16_t channel, char *exchange, char *queuename, char *bindingkey, LStrHandle error_description)
{
	amqp_connection_state_t conn = (amqp_connection_state_t) conn_intptr;
	int status;

	amqp_queue_bind(conn, channel, amqp_cstring_bytes(queuename), amqp_cstring_bytes(exchange), amqp_cstring_bytes(bindingkey), amqp_empty_table);
	status = lv_report_amqp_error(amqp_get_rpc_reply(conn), "Binding queue", error_description);
	if (status != 1)
	{
		return status;
	}

	amqp_boolean_t NO_LOCAL = 0;
	amqp_boolean_t NO_ACK = 1;
	amqp_boolean_t EXCLUSIVE2 = 0;
	amqp_basic_consume(conn, channel, amqp_cstring_bytes(queuename), amqp_empty_bytes, NO_LOCAL, NO_ACK, EXCLUSIVE2, amqp_empty_table);
	/*amqp_basic_consume is used to register a consumer on the queue,
	 so that the broker will start delivering messages to it.*/
	status = lv_report_amqp_error(amqp_get_rpc_reply(conn), "Basic consume", error_description);
	return status;
}


LABVIEW_PUBLIC_FUNCTION
int lv_amqp_consume_message(int64_t conn_intptr, int timeout_sec, LStrHandle output, LStrHandle cheaders_key, LStrHandle cheaders_value, LStrHandle error_description)
{
	amqp_connection_state_t conn = (amqp_connection_state_t) conn_intptr;

	int status;
	struct timeval tval;
	tval.tv_sec = timeout_sec;
	tval.tv_usec = 0;
	amqp_rpc_reply_t res;
	amqp_envelope_t envelope;

	//amqp_maybe_release_buffers(conn);

	status = lv_report_amqp_error(amqp_consume_message(conn, &envelope, &tval, 0), "Consuming message", error_description);
	if (status != 1)
	{
		return status;
	}

	if (envelope.message.body.len > 0)
	{
		copyBufferToLStrHandle(envelope.message.body.bytes, envelope.message.body.len, output);
	}

	// Check message headers
	amqp_table_t *headers = &envelope.message.properties.headers;
	if (headers->num_entries > 0)
	{
		getConcatenatedMessageHeaders(headers, cheaders_key, cheaders_value);
	}

	amqp_destroy_envelope(&envelope);
	return status;
}

