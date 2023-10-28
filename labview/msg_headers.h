#include <rabbitmq-c/amqp.h>
#include "extcode.h"

#ifndef MSG_HEADERS_H
#define MSG_HEADERS_H

/**
 * This function takes an AMQP table containing headers and converts them into
 * a string format where the headers' keys and values are concatenated together.
 * Key-value pairs are separated by '=' and multiple headers are separated by
 * ';'.
 */
void parseHeaders(amqp_table_t* table, const uint8_t* headerBuffer, uint64_t headerBufferLen);

/**
 * This function parses a string representation of headers and populates an AMQP
 * table with the parsed header entries. The headers in the string are expected
 * to be in a specific format where key-value pairs are separated by '=' and
 * multiple headers are separated by ';'.
 *
 * @note The `table` parameter should be a initialized `amqp_table_t` structure.
 *       The `headerBuffer` should point to a null-terminated C string.
 *       The function modifies the `table` structure in place with the parsed
 * entries.
 */
void headersToString(amqp_table_t *table, LStrHandle concatenatedHeaders);

#endif
