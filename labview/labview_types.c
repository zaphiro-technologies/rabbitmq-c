#include <string.h>

#include "extcode.h"

/**
 * This function copies the contents of a C string into a LabVIEW LStrHandle,
 * resizing the handle if necessary.
 */
MgErr copyStringToLStrHandle(char *cpString, LStrHandle LVString) {
  int32 len = strlen(cpString);
  MgErr err = NumericArrayResize(uB, 1, (UHandle *)&LVString, len);
  if (!err) {
    strncpy((*LVString)->str, cpString,
            len);            // copying the string into the handle
    (*LVString)->cnt = len;  // telling the Handle what string size to expect
  }

  return err;
}

/**
 * This function copies the contents of a binary buffer into a LabVIEW
 * LStrHandle, resizing the handle if necessary. The function is designed for
 * handling binary data.
 */
MgErr copyBufferToLStrHandle(const void *buffer, int len, LStrHandle LVString) {
  MgErr err = NumericArrayResize(uB, 1, (UHandle *)&LVString, len);
  if (!err) {
    memcpy((*LVString)->str, buffer,
           len);             // copying the string into the handle
    (*LVString)->cnt = len;  // telling the Handle what string size to expect
  }

  return err;
}

/**
 * This function searches for a specified character within a binary buffer and
 * returns a pointer to the first occurrence of the character, starting from the
 * given offset.
 */
char *findInBuffer(const uint8_t *buffer, uint32_t len, uint32_t offset,
                   char toFind) {
  uint32_t i = offset;
  for (i; i < len; i++) {
    if (buffer[i] == toFind) {
      return buffer + i;
    }
  }
  return NULL;
}

/**
 * Split a string into an array of tokens based on a delimiter.
 * Memory is allocated for the token array, and the caller is responsible for
 * freeing the memory when it's no longer needed.
 */
char **splitString(char *input, int *count, char delimiter) {
  char **tokens = NULL;
  char *token = strtok(input, &delimiter);
  *count = 0;

  while (token != NULL) {
    tokens = (char **)realloc(tokens, ((*count) + 1) * sizeof(char *));
    if (tokens == NULL) {
      perror("Memory allocation error");
      exit(1);
    }

    tokens[(*count)] = strdup(token);
    (*count)++;
    token = strtok(NULL, &delimiter);
  }

  return tokens;
}

/**
 * This function frees the memory allocated for an array of tokens created by
 * 'splitString'.
 */
void freeTokens(char **tokens, int count) {
  if (tokens == NULL) {
    return;  // Handle NULL input.
  }

  for (int i = 0; i < count; i++) {
    free(tokens[i]);  // Free memory for each token.
  }

  free(tokens);  // Free memory for the token array itself.
}
