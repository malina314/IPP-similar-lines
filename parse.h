/**
 * Author:  Mateusz Malinowski
 * Date:    March 2021
 *
 * Summary of File:
 *
 *   This header provides function which convert string to line object.
 *   All numbers which can be represented as unsigned long long are converted
 *   to unsigned long long. If number can't be converted to unsigned long long
 *   algorithm tries convert it to long long if possible. If not algorithm tries
 *   convert it to double. If it fails that means it's not-number and should be
 *   stored as string.
 */

#ifndef SIMILAR_LINES_PARSE_H
#define SIMILAR_LINES_PARSE_H

#include "line.h"

// converts all numbers from input into corresponding types and pushes them
// into line, also pushes non-words
void parseLine(char *input, Line *line);

#endif //SIMILAR_LINES_PARSE_H
