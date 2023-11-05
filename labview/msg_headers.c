#include <rabbitmq-c/amqp.h>

#include "extcode.h"
#include "labview_types.h"

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
void stringToHeaders(amqp_table_t* table, const uint8_t* headerBuffer,
                     uint64_t headerBufferLen) {
  amqp_table_entry_t* entries = NULL;
  int numEntries = 0;
  int finished = FALSE;
  int index = 0;

  while (finished == 0) {
    // Find the delimiter ';'
    char* delimiter = findInBuffer(headerBuffer, headerBufferLen, index, 0x3B);
    if (delimiter == NULL) {
      delimiter =
          headerBuffer +
          headerBufferLen;  // If no delimiter found, use the end of the string
    }
    if (delimiter == headerBuffer + headerBufferLen) {
      finished = TRUE;
    }
    // Find the equal_char '='
    char* equal_char = findInBuffer(headerBuffer, headerBufferLen, index, 0x3D);

    if (equal_char != NULL && equal_char < delimiter) {
      // Add the entry to the entries array
      amqp_table_entry_t* newEntries =
          realloc(entries, (numEntries + 1) * sizeof(amqp_table_entry_t));
      if (newEntries == NULL) {
        // Error handling for memory allocation failure
        perror("Memory allocation failed");
        free(entries);
        return table;
      }
      entries = newEntries;
      amqp_field_value_t value;

      // Get the kind (first byte)
      value.kind = headerBuffer[index];
      index++;  // Move to the next character

      // Parse the key
      entries[numEntries].key.bytes = headerBuffer + index;
      entries[numEntries].key.len = equal_char - ((char*)headerBuffer + index);

      // Init and parse the value
      char valueTempBuffer[8];
      int valueLength = delimiter - equal_char - 1;
      memcpy(valueTempBuffer, equal_char + 1, valueLength);

      // Parse the value based on the kind
      switch (value.kind) {
        case AMQP_FIELD_KIND_UTF8:
        case AMQP_FIELD_KIND_BYTES:
          value.value.bytes.bytes = equal_char + 1;  // fist char after "="
          value.value.bytes.len = valueLength;
          break;
        case AMQP_FIELD_KIND_I8:
          value.value.i8 = (int8_t)valueTempBuffer[0];
          break;
        case AMQP_FIELD_KIND_U8:
          value.value.u8 = (uint8_t)valueTempBuffer[0];
          break;
        case AMQP_FIELD_KIND_I16:
          value.value.i16 = *((int16_t*)valueTempBuffer);
          break;
        case AMQP_FIELD_KIND_U16:
          value.value.u16 = *((uint16_t*)valueTempBuffer);
          break;
        case AMQP_FIELD_KIND_I32:
          value.value.i32 = *((int32_t*)valueTempBuffer);
          break;
        case AMQP_FIELD_KIND_U32:
          value.value.u32 = *((uint32_t*)valueTempBuffer);
          break;
        case AMQP_FIELD_KIND_I64:
          value.value.i64 = *((int64_t*)valueTempBuffer);
          break;
        case AMQP_FIELD_KIND_U64:
        case AMQP_FIELD_KIND_TIMESTAMP:
          value.value.u64 = *((uint64_t*)valueTempBuffer);
          break;
        case AMQP_FIELD_KIND_F32:
          value.value.f32 = *((float*)valueTempBuffer);
          break;
        case AMQP_FIELD_KIND_F64:
          value.value.f64 = *((double*)valueTempBuffer);
          break;
        default:
          // Unsupported kind, ignore this header
          break;
      }

      entries[numEntries].value = value;
      numEntries++;
    }

    // Move to the next header (skip the delimiter ';')
    index = delimiter - (char*)headerBuffer + 1;
  }

  // Assign the entries to the table
  table->num_entries = numEntries;
  table->entries = entries;
}

/**
 * This function takes an AMQP table containing headers and converts them into
 * a string format where the headers' keys and values are concatenated together.
 * Key-value pairs are separated by '=' and multiple headers are separated by
 * ';'.
 */
void headersToString(amqp_table_t* table, LStrHandle concatenatedHeaders) {
  // Calculate required string (char buffer) size
  int required_buffer_size = 0;
  for (int i = 0; i < table->num_entries; i++) {
    required_buffer_size++;  // character that indicates a type
    required_buffer_size += table->entries[i].key.len;  // key
    required_buffer_size++;                             // '=' separator

    switch (table->entries[i].value.kind) {
      case AMQP_FIELD_KIND_I8:
        required_buffer_size += 1;
        break;
      case AMQP_FIELD_KIND_I64:
        required_buffer_size += 8;
        break;
      case AMQP_FIELD_KIND_UTF8:
      case AMQP_FIELD_KIND_BYTES:
        required_buffer_size += table->entries[i].value.value.bytes.len;
        break;
      case AMQP_FIELD_KIND_U8:
        required_buffer_size += 1;
        break;
      case AMQP_FIELD_KIND_I16:
        required_buffer_size += 2;
        break;
      case AMQP_FIELD_KIND_U16:
        required_buffer_size += 2;
        break;
      case AMQP_FIELD_KIND_I32:
        required_buffer_size += 4;
        break;
      case AMQP_FIELD_KIND_U32:
        required_buffer_size += 4;
        break;
      case AMQP_FIELD_KIND_U64:
        required_buffer_size += 8;
        break;
      case AMQP_FIELD_KIND_TIMESTAMP:
        required_buffer_size += 8;
        break;
      case AMQP_FIELD_KIND_F32:
        required_buffer_size += 4;
        break;
      case AMQP_FIELD_KIND_F64:
        required_buffer_size += 8;
        break;
      default:
        required_buffer_size += 0;  // Unsupported kind, ignore
        break;
    }

    required_buffer_size++;  // ';' separator 
  }

  // Allocate memory for temp buffer
  char* headers = (char*)malloc(required_buffer_size * sizeof(char));
  float f32_value;
  double f64_value;

  int index = 0;
  for (int i = 0; i < table->num_entries; i++) {
    headers[index] = table->entries[i].value.kind;  // Character that indicates a type
    index++;

    memcpy(headers + index, table->entries[i].key.bytes, table->entries[i].key.len);
    index += table->entries[i].key.len;
    headers[index] = '=';  // Separator
    index++;

    switch (table->entries[i].value.kind) {
      case AMQP_FIELD_KIND_I8:
        headers[index] = table->entries[i].value.value.i8;
        index++;
        break;
      case AMQP_FIELD_KIND_I64:
        for (int j = 0; j < 8; j++) {
          headers[index + j] = (table->entries[i].value.value.i64 >> (j * 8)) & 0xFF;
        }
        index += 8;
        break;
      case AMQP_FIELD_KIND_UTF8:
      case AMQP_FIELD_KIND_BYTES:
        memcpy(headers + index, table->entries[i].value.value.bytes.bytes, table->entries[i].value.value.bytes.len);
        index += table->entries[i].value.value.bytes.len;
        break;
      case AMQP_FIELD_KIND_U8:
        headers[index] = table->entries[i].value.value.u8;
        index++;
        break;
      case AMQP_FIELD_KIND_I16:
        headers[index] = table->entries[i].value.value.i16 & 0xFF;
        headers[index + 1] = (table->entries[i].value.value.i16 >> 8) & 0xFF;
        index += 2;
        break;
      case AMQP_FIELD_KIND_U16:
        headers[index] = table->entries[i].value.value.i16 & 0xFF;
        headers[index + 1] = (table->entries[i].value.value.i16 >> 8) & 0xFF;
        index += 2;
        break;
      case AMQP_FIELD_KIND_I32:
        for (int j = 0; j < 4; j++) {
          headers[index + j] = (table->entries[i].value.value.i32 >> (j * 8)) & 0xFF;
        }
        index += 4;
        break;
      case AMQP_FIELD_KIND_U32:
        for (int j = 0; j < 4; j++) {
          headers[index + j] = (table->entries[i].value.value.u32 >> (j * 8)) & 0xFF;
        }
        index += 4;
        break;
      case AMQP_FIELD_KIND_U64:
      case AMQP_FIELD_KIND_TIMESTAMP:
        for (int j = 0; j < 8; j++) {
          headers[index + j] = (table->entries[i].value.value.u64 >> (j * 8)) & 0xFF;
        }
        index += 8;
        break;
      case AMQP_FIELD_KIND_F32:
        f32_value = table->entries[i].value.value.f32;
        memcpy(headers + index, &f32_value, 4);
        index += 4;
        break;
      case AMQP_FIELD_KIND_F64:
        f64_value = table->entries[i].value.value.f64;
        memcpy(headers + index, &f64_value, 8);
        index += 8;
        break;
      default:
        break;  // Unsupported kind, ignore
    }

    headers[index] = ';';  // Separator
    index++;
  }

  // Copy the resulting string to the LStrHandle
  copyBufferToLStrHandle(headers, required_buffer_size, concatenatedHeaders);

  // Free the temporary buffer
  free(headers);
}