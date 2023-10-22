#ifndef LABVIEW_RABBITMQ_H
#define LABVIEW_RABBITMQ_H

#if defined(__GNUC__) 
#define LABVIEW_PUBLIC_FUNCTION __attribute__((visibility("default")))
#define LABVIEW_PUBLIC_VARIABLE __attribute__((visibility("default"))) extern
#define LABVIEW_CALL
#else
#define LABVIEW_PUBLIC_FUNCTION
#define LABVIEW_PUBLIC_VARIABLE extern
#define LABVIEW_CALL
#endif

#define MaxHandleStringLength INT32_MAX
#define MAX_ERROR_DESCRIPTION_LENGTH 1000

enum error_code_enum_ {
    _AMQP_RESPONSE_NONE = 0,
    _AMQP_RESPONSE_NORMAL,
    _AMQP_RESPONSE_LIBRARY_EXCEPTION,
    _AMQP_RESPONSE_SERVER_EXCEPTION,
    _STR_LEN_OVER_INT32MAX,
    _CREATING_TCP_SOCKET,
    _OPENING_TCP_SOCKET,
    _OUT_OF_MEMORY,
    _LSTRHANDLE_IS_NULL
};

char* lv_rabbitmq_version(void);

int lv_report_amqp_error(amqp_rpc_reply_t x, char const* context, LStrHandle error_description);

int64_t lv_amqp_new_connection();

int lv_amqp_close_connection(int64_t conn_intptr, LStrHandle error_description);

void lv_amqp_destroy_connection(int64_t conn_intptr);

int lv_amqp_channel_open(int64_t conn_intptr, uint16_t channel, LStrHandle error_description);

int lv_amqp_channel_close(int64_t conn_intptr, uint16_t channel, LStrHandle error_description);

int lv_amqp_exchange_declare(int64_t conn_intptr, uint16_t channel, char* exchange, char* exchangetype, LStrHandle error_description);

int lv_amqp_login(int64_t conn_intptr, char* host, int port, int timeout_sec, char* username, char* password, LStrHandle error_description);

int lv_amqp_basic_publish(int64_t conn_intptr, uint16_t  channel, char *exchange, char *routingkey, char *cheaders_key, char *cheaders_value, char *messagebody, LStrHandle error_description);

int lv_amqp_create_queue(int64_t conn_intptr, uint16_t channel, char* exchange, char* bindingkey, LStrHandle error_description);

int lv_amqp_consume_message(int64_t conn_intptr, int timeout_sec, LStrHandle output, LStrHandle cheaders_key, LStrHandle cheaders_value, LStrHandle error_description);


#endif /* LABVIEW_RABBITMQ_H */
