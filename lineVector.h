/**
 * Author:  Mateusz Malinowski
 * Date:    March 2021
 *
 * Summary of File:
 *
 *   This header provides line vector structure and basic functions.
 */

#ifndef SIMILAR_LINES_LINEVECTOR_H
#define SIMILAR_LINES_LINEVECTOR_H

#include "line.h"

typedef struct {
    Line *items;
    size_t size;
    size_t allocated;
} LineVector;

LineVector LineVectorNew();
void LineVectorFree(LineVector *self);
void LineVectorPush(LineVector *self, Line line);

#endif //SIMILAR_LINES_LINEVECTOR_H
