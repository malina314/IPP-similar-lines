/**
 * Author:  Mateusz Malinowski
 * Date:    March 2021
 */

#include "line.h"
#include "vector.h"

Line *LineNew(int nr) {
    Line *obj = malloc(sizeof (Line));
    if (obj == NULL) {
        exit(1);
    }

    obj->ullv = ULLVectorNew();
    obj->llv = LLVectorNew();
    obj->dv = DVectorNew();
    obj->sv = SVectorNew();
    obj->nr = nr;

    return obj;
}

void LineFree(Line *self) {
    ULLVectorFree(&self->ullv);
    LLVectorFree(&self->llv);
    DVectorFree(&self->dv);
    SVectorFree(&self->sv);
}