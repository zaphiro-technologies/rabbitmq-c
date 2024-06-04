#include <rabbitmq-c/amqp.h>
#include <stdlib.h>

#include "extcode.h"
#include "labview_types.h"


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


amqp_field_value_t createFieldValue(int32_t dataType, LStrHandle value)
{
  amqp_field_value_t fieldValue;
  fieldValue.kind = dataType;

  switch (fieldValue.kind) {
        case AMQP_FIELD_KIND_UTF8:
        case AMQP_FIELD_KIND_BYTES:
          fieldValue.value.bytes.bytes = (void *)(*value)->str;
          fieldValue.value.bytes.len = (*value)->cnt;
          break;
        case AMQP_FIELD_KIND_I8:
          fieldValue.value.i8 = *((int8_t*)(*value)->str);
          break;
        case AMQP_FIELD_KIND_U8:
          fieldValue.value.u8 = *((uint8_t*)(*value)->str);
          break;
        case AMQP_FIELD_KIND_I16:
          fieldValue.value.i16 = *((int16_t*)(*value)->str);
          break;
        case AMQP_FIELD_KIND_U16:
          fieldValue.value.u16 = *((uint16_t*)(*value)->str);
          break;
        case AMQP_FIELD_KIND_I32:
          fieldValue.value.i32 = *((int32_t*)(*value)->str);
          break;
        case AMQP_FIELD_KIND_U32:
          fieldValue.value.u32 = *((uint32_t*)(*value)->str);
          break;
        case AMQP_FIELD_KIND_I64:
          fieldValue.value.i64 = *((int64_t*)(*value)->str);
          break;
        case AMQP_FIELD_KIND_U64:
        case AMQP_FIELD_KIND_TIMESTAMP:
          fieldValue.value.u64 = *((uint64_t*)(*value)->str);
          break;
        case AMQP_FIELD_KIND_F32:
          fieldValue.value.f32 = *((float*)(*value)->str);
          break;
        case AMQP_FIELD_KIND_F64:
          fieldValue.value.f64 = *((double*)(*value)->str);
          break;
        default:
          // Unsupported kind, ignore this header
          break;
  }
  return fieldValue;
}

/**
 * This function parses a C representation of array of clusters and populates an AMQP
 * table with the parsed header entries. 
 *
 * @note The `table` parameter should be a initialized `amqp_table_t` structure.
 *       The `KeyValuePairArrHdl` should be a handler to C structure generated by LabVIEW.
 *       The function modifies the `table` structure in place with the parsed entries.
 */
void buildHeaders(amqp_table_t* table, KeyValuePairArrHdl headers)
{
  amqp_table_entry_t* entries = malloc(sizeof(amqp_table_entry_t) * (*headers)->dimSize);

  int32_t i = 0;
  KeyValuePairRec *p = (*headers)->elt;
	for (; i < (*headers)->dimSize; i++, p++)
  {
    amqp_field_value_t value;
    LStrPtr keyPtr = *p->key;

    entries[i].key.bytes = (void *)keyPtr->str;
    entries[i].key.len = keyPtr->cnt;
    entries[i].value = createFieldValue(p->dataType, p->value);
  }

		// Set the entries to the headers table
  table -> entries = entries;
  table -> num_entries = (*headers)->dimSize;
  
}