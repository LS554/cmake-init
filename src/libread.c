// Copyright (c) 2025, London Sheard
// Licensed under the 3-Clause Sheard License
// See the LICENSE file in project root for details.
//
// Created by London Sheard on 21/07/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/**
 * Reads a line from stdin into `string`.
 * Removes the trailing newline if present.
 *
 * Usage:
 * char buffer[1024];
 * if (read(buffer, sizeof(buffer))) {
 *     // use buffer
 * }
 * @param string Char array buffer to store input.
 * @param size Size of the buffer.
 * @return 0 on success, 1 on error.
 */
int readln(char* string, const size_t size) {
    if (fgets(string, size, stdin) == NULL) {
        return 1;
    }
    const size_t len = strlen(string);

    if (len > 0 && string[len -1] == '\n') {
        string[len -1] = '\0';
    }
    return 0;
}

/**
 * Reads a line from stdin into a dynamically allocated buffer.
 * Removes the trailing newline if present.
 *
 * Usage:
 * char* buffer;
 * if (readm(&buffer)) {
 *     // use buffer
 *     free(buffer);
 * }
 * @warning MUST FREE
 * @param string Pointer to a char* that will hold the allocated string.
 * @return 0 on success, 1 on error.
 */
int readlnm(char** string) {
    size_t size = 128;
    size_t len = 0;
    char* buffer = malloc(size);
    if (!buffer)
        return 1;

    while (1) {
        // Read into the buffer starting at offset 'len'
        if (fgets(buffer + len, size - len, stdin) == NULL) {
            free(buffer);
            return 1;
        }

        // Determine length of the newly read chunk and update len.
        size_t chunk_len = strlen(buffer + len);
        len += chunk_len;

        // If the last character is newline, replace it with a null terminator and break.
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
            break;
        }

        // If no newline, it means that the input line is longer than the available space.
        // Double the buffer size to read more.
        size_t new_size = size * 2;
        char* new_buffer = realloc(buffer, new_size);
        if (!new_buffer) {
            free(buffer);
            return 1;
        }
        buffer = new_buffer;
        size = new_size;
    }

    // Optionally, shrink the buffer to fit the string exactly.
    char* final_str = realloc(buffer, len + 1);
    if (final_str)
        buffer = final_str;
    *string = buffer;
    return 0;
}

/**
 * Frees all provided pointers (sets them to NULL after freeing)
 *
 * Usage:
 * char* a = malloc(100);
 * char* b = malloc(100);
 * freeall(2, &a, &b);
 * @param count Number of provided pointers.
 * @param ... pointers to pointers (e.g., &a, &b).
 * @return 0 on success, 1 on error.
 */
int freeall(const int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        void **ptr = va_arg(args, void **);
        if (ptr && *ptr) {
            free(*ptr);
            *ptr = NULL;
        }
    }
    va_end(args);
    return 0;
}