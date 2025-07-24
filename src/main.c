// Copyright (c) 2025, London Sheard
// Licensed under the 3-Clause Sheard License
// See the LICENSE file in project root for details.
//
// Created by London Sheard on 23/07/25.
//
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "libread.h"

#define CMAKELIST "CMakeLists.txt"

char* PROJECT_NAME = NULL;
char* MIN_CMAKE_VERSION = NULL;
char* C_STANDARD = NULL;
char* SOURCE_FILE = NULL;

int check_exists() {
    FILE* check = fopen(CMAKELIST, "r");
    if (check) {
        printf("CMakeLists.txt already exists in current directory, overwrite? (Y/n): ");

        char input[16];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            return 1;
        }
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline if 'return'

        char ovrwrtOption;
        if (input[0] == '\0') {
            ovrwrtOption = 'Y';
        } else {
            ovrwrtOption = toupper((unsigned char)input[0]);
        }

        switch (ovrwrtOption) {
            case 'Y': break;
            case 'N': return 1;
            default:
                fprintf(stderr, "Invalid option, quitting");
                return 1;
        }
    }
    return 0;
}

int gen_file() {
    FILE* file = fopen(CMAKELIST, "w");
    if (!file) {
        perror("Could not open CMakeLists.txt");
        return 1;
    }
    fprintf(file, "set(PROJECT_NAME %s)\n", PROJECT_NAME);
    fprintf(file, "set(SOURCES\n");
    fprintf(file, "\t%s\n", SOURCE_FILE);
    fprintf(file, ")\n\n");
    fprintf(file, "cmake_minimum_required(VERSION %s)\n", MIN_CMAKE_VERSION);
    fprintf(file, "project(${PROJECT_NAME} C)\n\n");
    fprintf(file, "set(CMAKE_C_STANDARD %s)\n\n", C_STANDARD);
    fprintf(file, "add_executable(${PROJECT_NAME}\n");
    fprintf(file, "\t\"${SOURCES}\"\n");
    fprintf(file, ")\n");

}

int main(int argc, char* argv[]) {
    if ((check_exists() == 1)) {
        return 1;
    }
    printf("Enter project name: ");
    readlnm(&PROJECT_NAME);
    printf("Enter main source file (ex. main.c): ");
    readlnm(&SOURCE_FILE);
    printf("Enter minimum CMake version (sugg. 3.20): ");
    readlnm(&MIN_CMAKE_VERSION);
    printf("Enter C standard (sugg. 11): ");
    readlnm(&C_STANDARD);

    gen_file();
    freeall(2, &PROJECT_NAME, &SOURCE_FILE);
    return 0;
}