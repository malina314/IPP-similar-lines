/**
 * Author:  Mateusz Malinowski
 * Date:    March 2021
 *
 * Summary of File:
 *
 *   This header provides functions to compare lines and sort line vector and
 *   vector of unsigned long long vectors.
 */

#ifndef SIMILAR_LINES_COMPARE_H
#define SIMILAR_LINES_COMPARE_H

#include "line.h"
#include "lineVector.h"
#include "vector.h"

// checks if two lines are similar
int isSimilar(const Line* a, const Line* b);

void sortLineVector(LineVector *lv);

void sortULLVectorVector(ULLVectorVector *v);

#endif //SIMILAR_LINES_COMPARE_H
