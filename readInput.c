/**
 * Author:  Mateusz Malinowski
 * Date:    March 2021
 *
 * Summary of File:
 *
 *   This file implements reading lines from stdin operations.
 */

#include "readInput.h"

#include "line.h"
#include "lineVector.h"
#include "parse.h"

#include <stdio.h>
#include <ctype.h>

typedef enum {
    READ_OK,
    READ_ERROR,
    READ_END,
    READ_COMMENT,
    READ_EMPTY_LINE,
    UNDEFINED
} readStatus;

// reads all chars to '\n' or EOF and discard them
static void skipLine() {
    char c;
    while ((c = (char)getchar()) != EOF && c != '\n');
}

// returns 0 if given string contains only whitespaces, non-zero otherwise
static int isEmpty(char *str) {
    while (isspace(*str)) {
        str++;
    }
    return *str == '\0';
}

// reads line, checks if it is comment or contains illegal characters
// sets read status
// returns pointer to buffer in which are read characters
static char *getline(readStatus *status) {
    char c = (char)getchar();

    if (feof(stdin)) {
        *status = READ_END;
        return NULL;
    }

    if (c == '#') {
        skipLine();
        *status = READ_COMMENT;
        return NULL;
    }

    CVector input = CVectorNew();

     do {
        if (isspace(c) || (c >= 33 && c <= 126)) {
            CVectorPush(&input, (char)tolower(c));
        } else {
            *status = READ_ERROR;
            CVectorFree(&input);
            skipLine();
            return NULL;
        }
    } while (c != '\n' && (c = (char)getchar()) != EOF);

    if (c != '\n') {
        CVectorPush(&input, '\n');
    }

    CVectorPush(&input, '\0');

    if (isEmpty(input.items)) {
        *status = READ_EMPTY_LINE;
        CVectorFree(&input);
        return NULL;
    }

    return input.items;
}

// reads line and convert it
static int readLine(Line *line) {
    readStatus status = UNDEFINED;
    char *input = getline(&status);

    if (status != UNDEFINED)
        return status;

    parseLine(input, line);

    free(input);

    return READ_OK;
}

// read input line by line, converts them to proper object and pushes them into
// line vector.
void readInput(LineVector *lv) {
    int nr = 0;

    while (1) {
        Line *line = LineNew(++nr);
        int status = readLine(line);

        switch (status) {
            case READ_OK:
                LineVectorPush(lv, *line);
                free(line);
                break;
            case READ_ERROR:
                fprintf(stderr, "ERROR %d\n", line->nr);
                LineFree(line);
                free(line);
                break;
            case READ_EMPTY_LINE:
            case READ_COMMENT:
                LineFree(line);
                free(line);
                break;
            case READ_END:
                LineFree(line);
                free(line);
                return;
        }
    }
}