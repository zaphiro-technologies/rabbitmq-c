#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>
//#include <amqp_private.h>
#include <amqp_framing.h>
#include <string.h>
#include "utils.h"
#include "extcode.h"
#include "labview_rabbitmq.h"


LABVIEW_PUBLIC_FUNCTION
char lv_rabbitmq_version(void) {
	char version = "0.0.1";
	return version;
}


amqp_bytes_t queuename;
struct lv_timeval {
	long    tv_sec;
	long	tv_usec;
};


int lv_die_on_amqp_error(amqp_rpc_reply_t x, char const *context) {
	switch (x.reply_type) {
	case AMQP_RESPONSE_NORMAL:
		return 1;

	case AMQP_RESPONSE_NONE:
		return 2;

	case AMQP_RESPONSE_LIBRARY_EXCEPTION:
		return 3;

	case AMQP_RESPONSE_SERVER_EXCEPTION:
		switch (x.reply.id) {
		case AMQP_CONNECTION_CLOSE_METHOD: {
			amqp_connection_close_t *m =
				(amqp_connection_close_t *)x.reply.decoded;
			return 4;
		}
		case AMQP_CHANNEL_CLOSE_METHOD: {
			amqp_channel_close_t *m = (amqp_channel_close_t *)x.reply.decoded;
			return 5;
		}
		default:
			return 6;
		}
		break;
	}

}


char *lv_die_on_amqp_error2(amqp_rpc_reply_t x, char const *context, char *des) {

	char *r1 = "1";
	char *r2 = "2";
	char *r3 = "3";
	char *r4 = "4";
	char *r5 = "5";
	char *r6 = "6";

	switch (x.reply_type) {
	case AMQP_RESPONSE_NORMAL:
		des = r1;
		return des;

	case AMQP_RESPONSE_NONE:
		des = r2;
		return des;

	case AMQP_RESPONSE_LIBRARY_EXCEPTION:
		return amqp_error_string2(x.library_error);

	case AMQP_RESPONSE_SERVER_EXCEPTION:
		switch (x.reply.id) {
		case AMQP_CONNECTION_CLOSE_METHOD: {
			amqp_connection_close_t *m =
				(amqp_connection_close_t *)x.reply.decoded;
			des = r4;
			return des;
		}
		case AMQP_CHANNEL_CLOSE_METHOD: {
			amqp_channel_close_t *m = (amqp_channel_close_t *)x.reply.decoded;
			des = r5;
			return des;
		}
		default:
			des = r6;
			return des;
		}
		break;
	}

}



int lv_amqp_dump(size_t len) {
	int count = 0;
	size_t i;

	for (i = 0; i < len; i++) {
		count++;
	}
	return count;
}






struct amqp_connection_state_t* lv_int_to_pointer(int *conn_int) {
	amqp_connection_state_t *x;
	x = (amqp_connection_state_t*)conn_int;
	return *x;
}


//Reviewed
LABVIEW_PUBLIC_FUNCTION
void* lv_amqp_new_connction() {
	// TO DO: incorrect vaiable assigement
	/* The amqp_new_connection() function returns a pointer to
	 a new amqp_connection_state_t struct, so it should be:
	 amqp_connection_state_t *conn; */
	amqp_connection_state_t conn;
	conn = amqp_new_connection();
	return conn; //LabVIEW will receive it as Int64
}


//Reviewed
LABVIEW_PUBLIC_FUNCTION
int lv_amqp_close_connection(int *conn_int) {
	amqp_connection_state_t *x;
	x = (amqp_connection_state_t*)conn_int;
	int r = lv_die_on_amqp_error(amqp_connection_close(*x, AMQP_REPLY_SUCCESS),"Connection close");
	return r;
}


//Reviewed
LABVIEW_PUBLIC_FUNCTION
void lv_amqp_destroy_connection(int *conn_int) {
	amqp_connection_state_t *x;
	x = (amqp_connection_state_t*)conn_int;
	amqp_destroy_connection(*x);
}


//Reviewed
LABVIEW_PUBLIC_FUNCTION
void lv_amqp_channel_open(int *conn_int) {
	amqp_connection_state_t *x;
	x = (amqp_connection_state_t*)conn_int;
	amqp_channel_open(*x, 1);
}
// TO DO: channel is set constant to 1, should be a parameter
// TO DO: add amqp_get_rpc_reply function
/* to get the status there is always amqp_get_rpc_reply function
that collects it, I think there is no need to split them for LabVIEW
so it should be integrated into this function*/


//Reviewed
LABVIEW_PUBLIC_FUNCTION
int lv_amqp_channel_close(int *conn_int) {
	amqp_connection_state_t *x;
	x = (amqp_connection_state_t*)conn_int;
	int r = lv_die_on_amqp_error(amqp_channel_close(*x, 1, AMQP_REPLY_SUCCESS), "Closing channel");
	return r;
}
// TO DO: channel is set constant to 1, should be a parameter


// This functions should be removed
LABVIEW_PUBLIC_FUNCTION
int lv_amqp_get_rpc_reply(int *conn_int, char *operation) {
	amqp_connection_state_t *x;
	x = (amqp_connection_state_t*)conn_int;
        int r =	lv_die_on_amqp_error(amqp_get_rpc_reply(*x), "aaa");
       return r;
}


//Reviewed
LABVIEW_PUBLIC_FUNCTION
int lv_amqp_exchange_declare(int *conn_int, char *exchange, char *exchangetype ) {
	amqp_connection_state_t *x;
	x = (amqp_connection_state_t*)conn_int;
	amqp_exchange_declare(*x, 1, amqp_cstring_bytes(exchange),
		amqp_cstring_bytes(exchangetype), 0, 0, 0, 0,
		amqp_empty_table);
        return 1;
}
// TO DO : add the amqp_get_rpc_reply function
// This function will be used for examples only

LABVIEW_PUBLIC_FUNCTION
char *name(char *res) {
	char *char_temp = "hahaha2";
	res = char_temp;
	return res;

};


//Reviewed
LABVIEW_PUBLIC_FUNCTION
void lv_amqp_login(int *conn_int, char *host, int port, char *username, char *password, char *des) {

	// TO DO: check the type
	/* the lv_amqp_new_connction returns a void pointer that is 
	stored as Int64 in LabVIEW, this is not coherent with 
	*conn_int input for this function */
	amqp_connection_state_t *x;
	x = (amqp_connection_state_t*)conn_int;

	int status;
	amqp_socket_t *socket = NULL;
	socket = amqp_tcp_socket_new(*x);
	// TO DO: if socket is NULL, LabVIEW will crash
	status = amqp_socket_open(socket, host, port);
	// TO DO: if status is not 0, LabVIEW will crash
	/*Code explanation:
	socket is set/stored in the connection state, so I beleve
	it will be destroyed along with connection state destroy function*/  

	char *r;
	r = lv_die_on_amqp_error2(amqp_login(*x, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN,
		username, password),
		"Logging in", "");
	//char *char_temp = "1";
	// TO DO: why char is used here?
	/* Create a additional file that containes enum with error codes
	that can be "copied" in LabVIEW, use the enum instead of char*/
	
	// TO DO: the constants used in the function are not defined
	// however, they are the same like in original code example
	// It woudl make sens to describe them

	// TO DO: the function doesn't return anything
}






//Reviewed
LABVIEW_PUBLIC_FUNCTION
void lv_amqp_basic_publish(int *conn_int, char *exchange, char *routingkey, char *messagebody) {
	amqp_connection_state_t *x;
	x = (amqp_connection_state_t*)conn_int;
	amqp_basic_properties_t props;
	props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
	props.content_type = amqp_cstring_bytes("text/plain");
	props.delivery_mode = 2; /* persistent delivery mode */
	die_on_error(amqp_basic_publish(*x, 1, amqp_cstring_bytes(exchange),
		amqp_cstring_bytes(routingkey), 0, 0,
		&props, amqp_cstring_bytes(messagebody)),
		"Publishing");
	// TO DO: labview will crash in case of error here
}








//Reviewed
LABVIEW_PUBLIC_FUNCTION
int lv_amqp_consume_message1(int *conn_int, char *exchange, char *bindingkey) {
	amqp_connection_state_t *x;
	x = (amqp_connection_state_t*)conn_int;

        
	amqp_queue_declare_ok_t *r = amqp_queue_declare(
		*x, 1, amqp_empty_bytes, 0, 0, 0, 1, amqp_empty_table);
        int a =	lv_die_on_amqp_error(amqp_get_rpc_reply(*x), "Declaring queue");
	// TO DO: if error - > retrun it
	queuename = amqp_bytes_malloc_dup(r->queue);
	if (queuename.bytes == NULL) {
		//fprintf(stderr, "Out of memory while copying queue name");
		//return "Out of memory while copying queue name";
		return 0;
		// TO DO return error code to LabVIEW
	}


	amqp_queue_bind(*x, 1, queuename, amqp_cstring_bytes(exchange),
		amqp_cstring_bytes(bindingkey), amqp_empty_table);
	int b = lv_die_on_amqp_error(amqp_get_rpc_reply(*x), "Binding queue");
	// TO DO: if error - > retrun it
	amqp_basic_consume(*x, 1, queuename, amqp_empty_bytes, 0, 1, 0,
		amqp_empty_table);
	/* amqp_basic_consume is used to register a consumer on the queue,
	 so that the broker will start delivering messages to it.*/
	int c = lv_die_on_amqp_error(amqp_get_rpc_reply(*x), "Consuming");

        return 1;
}



//Reviewed
LABVIEW_PUBLIC_FUNCTION
char *lv_amqp_consume_message2(int *conn_int, int *e, int *number, char *des) {
	

         
        char  *aaa;
	amqp_connection_state_t *x;
	x = (amqp_connection_state_t*)conn_int;

	struct lv_timeval lv_timeval1;
	lv_timeval1.tv_sec = 0;
	lv_timeval1.tv_usec = 100000;

		amqp_rpc_reply_t res;
		amqp_envelope_t envelope;
		amqp_maybe_release_buffers(*x);
		res = amqp_consume_message(*x, &envelope, &lv_timeval1, 0);

		if (envelope.message.body.len > 0) {
			//TO DO: no idea what is this
			*number = lv_amqp_dump(envelope.message.body.len);
			*e = &envelope;

			//amqp_destroy_envelope(&envelope);
			aaa = envelope.message.body.bytes;

			//return envelope.message.body.bytes;
			return aaa;
		}
		else {
			return "null";
		}
		//amqp_destroy_envelope(&envelope);
           	
           char *b = "abcd";
           des = aaa;
           return des;
	// TO DO: returning pointer from string can be done more elegant

	//TO DO: memory leak here
	//amqp_destroy_envelope(&envelope) is not triggered
	// probably because it will delete received message string
	// best way to do it is to get string from LabVIEW and 
	// copy the content of the message to it, so LabVIEW will take
	// care of the memory allocation
}



LABVIEW_PUBLIC_FUNCTION
void lv_amqp_destroy_envelope(int envelope) {
	//amqp_envelope_t *x;
	//x = (amqp_envelope_t*)envelope;
	amqp_destroy_envelope(envelope);
}


// Following function are not used in the code 

/* Handle "cnt" field is int32 so max length is INT32_MAX. */
#define MaxHandleStringLength INT32_MAX

LABVIEW_PUBLIC_FUNCTION
void LVLStrHandle(int *conn_int, int *number, LStrHandle input, LStrHandle output)
{
	int32 len;
	uInt32 i, j, stringLength;
	uInt32 temp;
	temp = 50;


	char  *aaa;
	amqp_connection_state_t *x;
	x = (amqp_connection_state_t*)conn_int;
	//设置获取数据的超时时间
	struct lv_timeval lv_timeval1;
	lv_timeval1.tv_sec = 0;
	lv_timeval1.tv_usec = 100000;

	amqp_rpc_reply_t res;
	amqp_envelope_t envelope;
	amqp_maybe_release_buffers(*x);
	res = amqp_consume_message(*x, &envelope, &lv_timeval1, 0);

	if (envelope.message.body.len > 0) {
		*number = lv_amqp_dump(envelope.message.body.len);

		//amqp_destroy_envelope(&envelope);
		aaa = envelope.message.body.bytes;

		//return envelope.message.body.bytes;






		len = (*input)->cnt;
		/* If we really have a handle, make sure it has enough room.. */
		
			stringLength = len * 2;
			if (stringLength > MaxHandleStringLength) {
				stringLength = MaxHandleStringLength;
			}

			
				/* Adjust the handle size to hold everything we want to put in it */
			
			

			
				strncpy((*output)->str, (*input)->str, len);
				/* Reverse "i" characters. */
				/*
				for ( i = len, j = 0; ( i > 0 ) && ( j < ( stringLength - len )); j++ )
				{
				(*output)->str[j + len] = (*input)->str[--i];
				}
				*/
				char *bbb = "labview";
				//bbb = envelope.message.body.bytes;
				int l = strlen(bbb);
				if (l > 0) {
					for (i = 0; i < l; i++) {
						(*output)->str[i] = bbb[i];
					}
				}
				(*output)->cnt = l;
			
		



	}
	else {
            int fff;
            fff = 0;
	}
	
	
	//amqp_destroy_envelope(&envelope);


}

