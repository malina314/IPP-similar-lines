/**
 * Author:  Mateusz Malinowski
 * Date:    March 2021
 *
 * Summary of File:
 *
 *   This file implements basic line vector functions.
 */

#include "lineVector.h"

#include "line.h"

#include <stdio.h>

LineVector LineVectorNew() {
    LineVector obj = {NULL, 0, 0};
    return obj;
}

void LineVectorFree(LineVector *self) {
    for (size_t i = 0; i < self->size; ++i) {
        LineFree(&self->items[i]);
    }
    free(self->items);
}

void LineVectorPush(LineVector *self, Line line) {
    size_t typeSize = sizeof line;
    if (self->allocated == 0) {
        self->items = malloc(typeSize);
        if (self->items == NULL) {
            exit(1);
        }
        self->allocated = 1;
    } else if (self->size == self->allocated) {
        self->items = realloc(self->items, self->allocated * 2 * typeSize);
        if (self->items == NULL) {
            exit(1);
        }
        self->allocated *= 2;
    }

    self->items[self->size++] = line;
}