//
// Created by London Sheard on 21/07/25.
//

#ifndef LIBREAD_H
#define LIBREAD_H
#include <stddef.h>

int readln(char* string, size_t size);

int readlnm(char** string);

int freeall(const int count, ...);

#endif //LIBREAD_H
