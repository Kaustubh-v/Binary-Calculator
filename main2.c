#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bc_che_functions.h"

int main()
{

    // conversion of the given expression to postfix:
    char *infix = NULL;
    char *postfix;

    printf("Enter infix expression: ");
    scanf("%m[^\n]1000%c", &infix);

    int strlength = strlen(infix);
    postfix = (char *)malloc(sizeof(char) * (2*strlength));

    infixtopostfix(infix, postfix, strlength);

    int size = strlen(postfix);
    printf("postfix is %s\n", postfix);
    free(infix);
    // given infix expression converted to postfix.


    // evaluation of the postfix expression:
    stack s;
    initstack(&s);

    list l,l1,l2;
    l1.head = NULL;
    l2.head = NULL;
    int i;
    for (i = 0; i < size; i++)
    {
        if (isdigit(postfix[i]))
        {
            l.head = NULL;
            while (isdigit(postfix[i]))
            {
                insertnumpostfix(postfix[i]-'0',&l);
                i++;
            }
            push(&l, &s); // adding all the digits of a number into list and pushing it into stack
            i--;
        }
        else if (postfix[i] == ' ')
        {
            continue;
        }
        else if (isoperator(postfix[i])) // if character is operator pop two lists from stack  and perform the required operation
        {
            l1.head = pop(&s);
            l2.head = pop(&s);
            switch (postfix[i])
            {
            case '+':
                list l3;
                l3 = add(&l2, &l1);
                push(&l3, &s);
                break;
            case '-':
                list l4;
                l4.head = NULL;
                l4 = subtract(&l2, &l1);
                push(&l4, &s);
                break;
            case '*':
                list l5;
                l5.head = NULL;
                l5 = multiply(&l2, &l1);
                push(&l5, &s);
                break;
            case '/':
                list l6;
                l6.head = NULL;
                l6 = divide(&l2, &l1);
                push(&l6, &s);
                break;
            default:
                break;
            }
        }
    }
    free(postfix);
    printf("given expression is equivalent to: ");
    displaynum(pop(&s));
    return 0;
}