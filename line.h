/**
 * Author:  Mateusz Malinowski
 * Date:    March 2021
 *
 * Summary of File:
 *
 *   This header provides Line structure and basic functions to create and
 *   delete object of this structure.
 */

#ifndef SIMILAR_LINES_LINE_H
#define SIMILAR_LINES_LINE_H

#include "vector.h"

typedef struct {
    ULLVector ullv;
    LLVector llv;
    DVector dv;
    SVector sv;
    int nr;
} Line;

Line *LineNew(int nr);
void LineFree(Line *self);

#endif //SIMILAR_LINES_LINE_H
