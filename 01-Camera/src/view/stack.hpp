
#pragma once
#define MAX_SIZE 32

#include "../../include/vmath.h"

class TransformationStack {
private:
    vmath::mat4 transformationStack[MAX_SIZE];
    int top;

public:
    TransformationStack() : top(-1) {}

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == MAX_SIZE - 1;
    }

    void pushMatrix(const vmath::mat4& matrix) {
        if (!isFull()) {
            transformationStack[++top] = matrix;
        }
    }

    vmath::mat4 popMatrix() {
        if (!isEmpty()) {
            return transformationStack[top--];
        }
        // Handle error for popping from an empty stack
        return vmath::mat4(); // return an identity matrix or throw an exception
    }
};