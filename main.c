/**
 * Author:  Mateusz Malinowski
 * Date:    March 2021
 *
 * Summary of File:
 *
 *   This file contains main function which finds similar lines and prints
 *   result. Idea of the algorithm is to sort all lines. After that similar
 *   lines are next to each other, so we can easily group them. Then we sort
 *   groups of line numbers and print it.
 *   Complexity of this solution is O(n*log(n)*cmp_t), where n is number of
 *   lines and cmp_t is comparison time which is proportional to length of
 *   compared lines.
 */

#include "compare.h"
#include "lineVector.h"
#include "readInput.h"
#include "vector.h"

#include <stdio.h>

static void printAnswer(ULLVectorVector *v) {
    for (size_t i = 0; i < v->size; ++i) {
        // in order to not print space at end of line
        printf("%llu", v->items[i].items[0]);
        for (size_t j = 1; j < v->items[i].size; ++j) {
            printf(" %llu", v->items[i].items[j]);
        }
        printf("\n");
    }
}

int main() {
    LineVector lines = LineVectorNew();

    readInput(&lines);

    sortLineVector(&lines);

    if (lines.size > 0) {
        ULLVectorVector answer = ULLVectorVectorNew();
        ULLVector similarLines = ULLVectorNew();
        Line *lastLine = NULL;

        ULLVectorPush(&similarLines, lines.items[0].nr);
        lastLine = &lines.items[0];

        for (size_t i = 1; i < lines.size; ++i) {
            if (isSimilar(lastLine, &lines.items[i]) == 0) {
                ULLVectorPush(&similarLines, lines.items[i].nr);
            }
            else {
                ULLVectorVectorPush(&answer, similarLines);
                similarLines = ULLVectorNew();
                ULLVectorPush(&similarLines, lines.items[i].nr);
                lastLine = &lines.items[i];
            }
        }
        ULLVectorVectorPush(&answer, similarLines); // push last group

        sortULLVectorVector(&answer);

        printAnswer(&answer);

        ULLVectorVectorFree(&answer);
    }

    LineVectorFree(&lines);

    return 0;
}
