/**
 * Author:  Mateusz Malinowski
 * Date:    March 2021
 *
 * Summary of File:
 *
 *   This file implements conversion string to line object as it is described in
 *   header file and auxiliary functions.
 */

#include "parse.h"

#include "line.h"

#include <ctype.h>
#include <errno.h>

// finds first whitespace in given string and sets it to '\0'
static char *findEndOfWord(char *p) {
    while (!isspace(*p))
        p++;
    *p = '\0';
    return p;
}

// tries convert word to unsigned long long and push it into line
// on ERANGE push it into line as a string
// sets next to the first char of input after converted part
// returns 1 if converted, 0 otherwise
static int parseULL(char *input, Line *line, char **next, int base) {
    errno = 0;

    char *end = NULL;
    unsigned long long ullValue = strtoull(input, &end, base);

    if (errno == ERANGE) {
        // ERANGE means that we cannot read it as unsigned long long, so
        // we should read it as string.
        end = findEndOfWord(end);
        SVectorPush(&line->sv, input);
    }
    else if (isspace(*end)) { // whole word was correctly converted
        ULLVectorPush(&line->ullv, ullValue);
    }
    else { // there are some chars which are not valid digit
        return 0;
    }

    *next = end + 1;

    return 1;
}

// tries convert word to long long and push it into line
// on ERANGE push it into line as a string
// sets next to the first char of input after converted part
// returns 1 if converted, 0 otherwise
static int parseLL(char *input, Line *line, char **next) {
    errno = 0;

    char *end = NULL;
    long long llValue = strtoll(input, &end, 10);

    if (errno == ERANGE) {
        // ERANGE means that we cannot read it as long long, so
        // we should read it as string.
        end = findEndOfWord(end);
        SVectorPush(&line->sv, input);
    }
    else if (isspace(*end)) { // whole word was correctly converted
        if (llValue == 0)
            ULLVectorPush(&line->ullv, 0);
        else
            LLVectorPush(&line->llv, llValue);
    }
    else { // there are some chars which are not valid digit
        return 0;
    }

    *next = end + 1;

    return 1;
}

// checks if word could be an octal number and tries convert it
// returns 1 if converted, 0 otherwise
static int parseOct(char *input, Line *line, char **next) {
    if (input[0] != '0')
        return 0;

    return parseULL(input, line, next, 8);
}

// checks if word could be an hexadecimal number and tries convert it
// returns 1 if converted, 0 otherwise
static int parseHex(char *input, Line *line, char **next) {
    if (!(input[0] == '0' && input[1] == 'x'))
        return 0;

    // as it was said on the forum, "0x" is number, but for strtoull it's not
    if (isspace(input[2])) {
        ULLVectorPush(&line->ullv, 0);
        *next = input + 3;
        return 1;
    }

    return parseULL(input, line, next, 16);
}

// tries convert word as decimal number
// returns 1 if converted, 0 otherwise
static int parseDec(char *input, Line *line, char **next) {
    if (input[0] == '-')
        return parseLL(input, line, next);
    else
        return parseULL(input, line, next, 10);
}

// checks edge cases form the forum
// returns 1 if given word is not valid double
static int edgeCases(const char *s) {
    return (s[0] == 'n' && s[1] == 'a' && s[2] == 'n') ||
        ((s[0] == '+' || s[0] == '-') && s[1] == 'n' && s[2] == 'a' &&
            s[3] == 'n') ||
        ((s[0] == '+' || s[0] == '-') && s[1] == '.' && s[2] == 'e') ||
        (s[0] == '0' && s[1] == 'x') ||
        ((s[0] == '+' || s[0] == '-') && s[1] == '0' && s[2] == 'x');
}

// tries convert word to double and push it into line
// if number can be represented as unsigned long long or long long,
// it is converted and pushed into line as corresponding type
// on ERANGE push it into line as a string
// sets next to the first char of input after converted part
// returns 1 if converted, 0 otherwise
static int parseDouble(char *input, Line *line, char **next) {
    if (edgeCases(input))
        return 0;

    errno = 0;

    char *end = NULL;
    double dValue = strtod(input, &end);

    if (errno == ERANGE) {
        // ERANGE means that we cannot read it as double, so
        // we should read it as string.
        end = findEndOfWord(end);
        SVectorPush(&line->sv, input);
    }
    else if (isspace(*end)) { // whole word was correctly converted
        if (dValue >= 0) {
            unsigned long long ullValue = (unsigned long long)dValue;
            if ((double)ullValue == dValue)
                ULLVectorPush(&line->ullv, ullValue);
            else
                DVectorPush(&line->dv, dValue);
        }
        else {
            long long llValue = (long long)dValue;
            if ((double)llValue == dValue)
                LLVectorPush(&line->llv, llValue);
            else
                DVectorPush(&line->dv, dValue);
        }
    }
    else { // there are some chars which are not valid digit
        return 0;
    }

    *next = end + 1;

    return 1;
}

static int parseString(char *input, Line *line, char **next) {
    *next = findEndOfWord(input) + 1;
    SVectorPush(&line->sv, input);

    return 1;
};

static void parseWord(char *input, Line *line, char **next) {
    // skip whitespaces
    while (isspace(*input)) {
        input++;
    }

    if (*input == '\0') {
        *next = input;
        return;
    }

    // Hex always begins with "0x", oct with "0", so parseHex should be called
    // before parseOct.
    // All correct octal number could be parsed as decimal, but not the other
    // way around, so parseOct should be called before parseDec.
    // All correct decimal numbers could be parsed as double, but not the
    // other way around, so parseDec should be called before parseDouble.
    (void)(parseHex(input, line, next) ||
           parseOct(input, line, next) ||
           parseDec(input, line, next) ||
           parseDouble(input, line, next) ||
           parseString(input, line, next));
}

void parseLine(char *input, Line *line) {
    while (*input != '\0') {
        parseWord(input, line, &input);
    }
}