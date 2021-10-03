/**
 * Author:  Mateusz Malinowski
 * Date:    March 2021
 *
 * Summary of File:
 *
 *   This file implements functions to compare lines and sort line vector and
 *   vector of unsigned long long vectors and their auxiliary functions.
 *   To compare lines, their elements are sorted.
 *   To sorting is used qsort algorithm from standard library.
 */

#include "compare.h"

#include "line.h"
#include "lineVector.h"
#include "vector.h"

#include <stdlib.h>
#include <string.h>

static int cmpULL(const void* a, const void* b)
{
    unsigned long long arg1 = *(const unsigned long long *)a;
    unsigned long long arg2 = *(const unsigned long long *)b;

    if (arg1 > arg2) return 1;
    if (arg1 < arg2) return -1;
    return 0;
}

static int cmpLL(const void* a, const void* b)
{
    long long arg1 = *(const long long *)a;
    long long arg2 = *(const long long *)b;

    if (arg1 > arg2) return 1;
    if (arg1 < arg2) return -1;
    return 0;
}

static int cmpD(const void* a, const void* b)
{
    double arg1 = *(const double *)a;
    double arg2 = *(const double *)b;

    if (arg1 > arg2) return 1;
    if (arg1 < arg2) return -1;
    return 0;
}

static int cmpS(const void* a, const void* b)
{
    const char *arg1 = *(const char **)a;
    const char *arg2 = *(const char **)b;

    return strcmp(arg1, arg2);
}

// sorts each component vector of given line
static void sortElementsOfLine(const Line *line) {
    qsort(line->ullv.items, line->ullv.size, sizeof (unsigned long long),
        cmpULL);
    qsort(line->llv.items, line->llv.size, sizeof (long long), cmpLL);
    qsort(line->dv.items, line->dv.size, sizeof (double), cmpD);
    qsort(line->sv.items, line->sv.size, sizeof (char *), cmpS);
}

static inline size_t min(size_t a, size_t b) {
    return a < b ? a : b;
}

static int cmpULLVector(const void* a, const void* b)
{
    ULLVector *v1 = (ULLVector *)a;
    ULLVector *v2 = (ULLVector *)b;

    size_t end = min(v1->size, v2->size);

    for (size_t i = 0; i < end; ++i) {
        if (v1->items[i] > v2->items[i]) return 1;
        if (v1->items[i] < v2->items[i]) return -1;
    }

    if (v1->size > v2->size) return 1;
    if (v1->size < v2->size) return -1;
    return 0;
}

static int cmpLLVector(const void* a, const void* b)
{
    LLVector *v1 = (LLVector *)a;
    LLVector *v2 = (LLVector *)b;

    size_t end = min(v1->size, v2->size);

    for (size_t i = 0; i < end; ++i) {
        if (v1->items[i] > v2->items[i]) return 1;
        if (v1->items[i] < v2->items[i]) return -1;
    }

    if (v1->size > v2->size) return 1;
    if (v1->size < v2->size) return -1;
    return 0;
}

static int cmpDVector(const void* a, const void* b)
{
    DVector *v1 = (DVector *)a;
    DVector *v2 = (DVector *)b;

    size_t end = min(v1->size, v2->size);

    for (size_t i = 0; i < end; ++i) {
        if (v1->items[i] > v2->items[i]) return 1;
        if (v1->items[i] < v2->items[i]) return -1;
    }

    if (v1->size > v2->size) return 1;
    if (v1->size < v2->size) return -1;
    return 0;
}

// compare string's arrays size n
static int cmpStringsArray(char **v1, char **v2, size_t n) {
    int res = 0;

    for (size_t i = 0; i < n && res == 0; ++i) {
        res = strcmp(*v1++, *v2++);
    }

    return res;
}

static int cmpSVector(const void* a, const void* b)
{
    SVector v1 = *(SVector *)a;
    SVector v2 = *(SVector *)b;

    int res = cmpStringsArray(v1.items, v2.items, min(v1.size, v2.size));

    if (res == 0) {
        if (v1.size > v2.size) return 1;
        if (v1.size < v2.size) return -1;
        return 0;
    }

    return res;
}

// compares sorted lines
// if lines are similar, greater is line with greater number
static int cmpLine(const void* a, const void* b)
{
    Line line1 = *(Line *)a;
    Line line2 = *(Line *)b;

    int res = 0;

    res = cmpULLVector(&line1.ullv, &line2.ullv);
    if (res != 0) return res;

    res = cmpLLVector(&line1.llv, &line2.llv);
    if (res != 0) return res;

    res = cmpDVector(&line1.dv, &line2.dv);
    if (res != 0) return res;

    res = cmpSVector(&line1.sv, &line2.sv);
    if (res != 0) return res;

    if (line1.nr > line2.nr) return 1;
    if (line1.nr < line2.nr) return -1;
    return 0;
}

// sorts elements of each line in order to be able to compare, then sorts lines
void sortLineVector(LineVector *lv) {
    for (size_t i = 0; i < lv->size; ++i) {
        sortElementsOfLine(&lv->items[i]);
    }

    qsort(lv->items, lv->size, sizeof (Line), cmpLine);
}

void sortULLVectorVector(ULLVectorVector *v) {
    qsort(v->items, v->size, sizeof (ULLVector), cmpULLVector);
}

int isSimilar(const Line* a, const Line* b)
{
    int res = 0;

    res = cmpULLVector(&a->ullv, &b->ullv);
    if (res != 0) return res;

    res = cmpLLVector(&a->llv, &b->llv);
    if (res != 0) return res;

    res = cmpDVector(&a->dv, &b->dv);
    if (res != 0) return res;

    res = cmpSVector(&a->sv, &b->sv);
    if (res != 0) return res;

    return 0;
}