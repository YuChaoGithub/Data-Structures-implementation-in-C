#include <stdio.h>
#include <stdlib.h>

typedef int T;

typedef struct {
    T* arr;
    int maxSize;
    int currSize;
} Vector;

Vector* initVector(int maxSize) {
    Vector* vec = malloc(sizeof(Vector));
    vec->arr = malloc(sizeof(T) * maxSize);
    vec->maxSize = maxSize;
    vec->currSize = 0;
    return vec;
}

void freeVector(Vector* vec) {
    free(vec->arr);
    free(vec);
}

Vector* resizeVector(Vector* vec, int newSize) {
    Vector* temp = initVector(newSize);
    temp->currSize = vec->currSize;

    int i;
    for (i = 0; i < vec->currSize; i++)
        temp->arr[i] = vec->arr[i];
    
    freeVector(vec);
    return temp;
}

Vector* pushBack(Vector* vec, int num) {
    if (vec->currSize == vec->maxSize)
        vec = resizeVector(vec, vec->maxSize * 2);
    
    vec->arr[vec->currSize] = num;
    vec->currSize++;
    return vec;
}

void popBack(Vector* vec) {
    if (vec->currSize != 0) {
        vec->currSize--;
    }
}

int back(Vector* vec) {
    if (vec->currSize == 0) {
        puts("Empty.");
        return -1;
    }

    return vec->arr[vec->currSize - 1];
}

int getIndex(Vector* vec, int i) {
    if (vec->currSize <= i || i < 0) {
        puts("Out of bounds.");
        return -1;
    }

    return vec->arr[i];
}

void print(Vector* vec) {
    int i;
    for (i = 0; i < vec->currSize; i++)
        printf("%d ", vec->arr[i]);
    
    putchar('\n');
}

int main(void) {
    Vector* vec = initVector(5);
    vec = pushBack(vec, 1);
    vec = pushBack(vec, 2);
    vec = pushBack(vec, 3);
    vec = pushBack(vec, 4);
    vec = pushBack(vec, 5);
    vec = pushBack(vec, 6);
    vec = pushBack(vec, 7);
    print(vec);
    printf("The back is %d.\n", back(vec));
    popBack(vec);
    popBack(vec);
    popBack(vec);
    pushBack(vec, 10);
    print(vec);
    freeVector(vec);
    return 0;
}