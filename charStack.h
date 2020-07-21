// C program for array implementation of char stack
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// A structure to represent a stack
typedef struct charStack
{
    int top;
    unsigned capacity;
    char *array;
} charStack;

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct charStack *createCharStack(unsigned capacity)
{
    struct charStack *stack = (struct charStack *)malloc(sizeof(struct charStack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char *)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Stack is full when top is equal to the last index
int chIsFull(struct charStack *stack)
{
    return stack->top == stack->capacity - 1;
}

// Stack is empty when top is equal to -1
int chIsEmpty(struct charStack *stack)
{
    return stack->top == -1;
}

// Function to add an item to stack. It increases top by 1
void chPush(struct charStack *stack, char item)
{
    if (chIsFull(stack))
    {
        printf("Error: Full stack");
        return;
    }
    stack->top++;
    stack->array[stack->top] = item;
    //printf("%d pushed to stack\n", item);
}

// Function to remove an item from stack. It decreases top by 1
char chPop(struct charStack *stack)
{
    if (chIsEmpty(stack))
    {
        printf("Error: Empty Stack\n");
        return 0;
    }
    //printf("popped %d\n", stack->array[stack->top]);
    return stack->array[stack->top--];
}

char chTop(struct charStack *stack)
{
    return stack->array[stack->top];
}

// Function to return the top from stack without removing it
int chPeek(struct charStack *stack)
{
    if (chIsEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}
