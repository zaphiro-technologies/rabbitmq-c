#include "extcode.h"

#ifndef LABVIEW_TYPES_H
#define LABVIEW_TYPES_H

/**
 * This function copies the contents of a C string into a LabVIEW LStrHandle,
 * resizing the handle if necessary.
 */
MgErr copyStringToLStrHandle(char *cpString, LStrHandle LVString);

/**
 * This function copies the contents of a binary buffer into a LabVIEW
 * LStrHandle, resizing the handle if necessary. The function is designed for
 * handling binary data.
 */
MgErr copyBufferToLStrHandle(const void *buffer, int len, LStrHandle LVString);

/**
 * This function searches for a specified character within a binary buffer and
 * returns a pointer to the first occurrence of the character, starting from the
 * given offset.
 */
char* findInBuffer(const uint8_t* headerBuffer, uint32_t headerBufferLen, uint32_t offset, char toFind);

/**
 * Split a string into an array of tokens based on a delimiter.
 * Memory is allocated for the token array, and the caller is responsible for
 * freeing the memory when it's no longer needed.
 */
char **splitString(char *input, int *count, char delimiter);

/**
 * This function frees the memory allocated for an array of tokens created by
 * 'splitString'.
 */
void freeTokens(char** tokens, int count);

#endif
