#include "stack.h"     // My custom Stack for int values
#include "charStack.h" // My custom Stack for char values
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void convertToPostfix(char *exp, int len);       // Converts an infix string to postfix
int isOperator(char ch);                         // Checks if character is an operator
int performOperation(int op1, int op2, char op); // Performs + _ / * arithmethics
int precedence(char op);                         // Checks the precedence of operators

// Driver program
int main()
{
    char exp[1000], buffer[15];
    int error; //flags errors
    char infix = 'y';
    int i, op1, op2, len, j, x;
    FILE *input;

    printf("is this an infix calculation? Enter 'y' for yes and 'n' for postfix:  ");
    scanf("%s", &infix);
    if (infix == 'y')
    {
        input = fopen("infix.txt", "r"); // Gets default infix.txt file
    }
    else
    {
        input = fopen("postfix.txt", "r"); // Gets default postfix.txt file
    }
    if (input == NULL) // Checks if file was uploaded successfully
        exit(EXIT_FAILURE);

    memset(exp, ' ', 1000);
    printf("\nRESULTS OF DATASET\n--------\n");
    while (fgets(exp, sizeof(exp), input))
    {
        error = 0; // Flags errors
        struct Stack *s = createStack(100);
        len = sizeof(exp) / sizeof(char);

        if (infix == 'y')
        {
            //Converts to postfix expression
            printf("Infix Expression: %s", exp);
            convertToPostfix(exp, len);
        }

        printf("Postfix Expression: %s\n", exp);

        j = 0;
        for (i = 0; i < len; i++)
        {
            if (exp[i] == ' ')
            {
                // skips when a space is encountered
                continue;
            }
            else if (exp[i] == '\0' || exp[i] == '\n')
            {
                //Breaks at the end of the string (expression)
                break;
            }
            else if (exp[i] >= '0' && exp[i] <= '9')
            {
                buffer[j++] = exp[i];
                // Converts character to int and stores in stack
                push(s, exp[i] - '0');
            }
            else if (isOperator(exp[i]))
            {
                if (s->top >= 1)
                {
                    op1 = top(s);
                    pop(s);
                    op2 = top(s);
                    pop(s);
                    push(s, performOperation(op1, op2, exp[i]));
                }
                else // ERROR CHECK- Empty stack operand pops will be caught here
                {
                    printf("Error: invalid expression (ran out of operands in stack)\n");
                    error = 1; // Error flag
                    break;
                }
            }
            else // ERROR CHECK - Invalid characters will be caught here
            {
                printf("Error: an invalid character was encountered : '%c'\n", exp[i]);
                error = 1; // Error flag
                break;
            }
        }
        if (!error) // If there is no prior error
        {
            //Checks to see that stack has only one item
            if (s->top == 0)
                printf("The value of the expression is %d\n", top(s));
            else // ERROR CHECK - Incomplete calculations will be caught here
            {
                printf("Error: invalid expression (incomplete expression)\n");
                printf("\n");
                continue;
                //return 1;
            }
        }
        //free(s);
        printf("\n-------------------------------------------------------\n");
    } //End while loop
    fclose(input);
    return 0;
}

/** OTHER FUNCTIONS */
int isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        return 1;
    else
        return 0;
}

int performOperation(int op1, int op2, char op)
{
    int ans;
    switch (op)
    {
    case '+':
        ans = op2 + op1;
        break;
    case '-':
        ans = op2 - op1;
        break;
    case '*':
        ans = op2 * op1;
        break;
    case '/':
        ans = op2 / op1;
        break;
    }
    return ans;
}

int precedence(char op)
{
    switch (op)
    {
    case '+':
        return 0;
    case '-':
        return 0;
    case '*':
        return 1;
    case '/':
        return 1;
    }
    return -1;
}
void convertToPostfix(char *exp, int len)
{
    int i, j;
    char postFixExp[1000];
    charStack *stk = createCharStack(100);

    for (i = 0, j = 0; i < len; i++)
    {
        if (exp[i] == ' ')
        {
            // skips when a blank space is encountered
            continue;
        }
        else if (exp[i] == '\0' || exp[i] == '\n')
        {
            //Breaks at the end of the string (expression)
            break;
        }
        else if (exp[i] >= '0' && exp[i] <= '9')
        {
            //Add the digit to the postfix expression
            postFixExp[j++] = exp[i];
        }
        else if (exp[i] == '(')
        {
            //Save '(' on a stack
            chPush(stk, exp[i]);
        }
        else if (exp[i] == ')')
        {
            while (chTop(stk) != '(')
            {
                postFixExp[j++] = chTop(stk);
                chPop(stk);
            }
            chPop(stk); // Remove the open parentheses
        }
        else if (isOperator(exp[i]))
        {
            while (!chIsEmpty(stk) && chTop(stk) != '(' && precedence(exp[i]) <= precedence(chTop(stk)))
            {
                postFixExp[j++] = chTop(stk);
                chPop(stk);
            }
            chPush(stk, exp[i]);
        }
    } // End for loop

    while (stk->top >= 0)
    {
        //pop/print out the rest of the values
        postFixExp[j++] = chTop(stk);
        chPop(stk);
    }
    postFixExp[j] = '\0';
    strcpy(exp, postFixExp);
} // end convertToPostfix
