#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bc_che_functions.h"



// functions for infix to postfix

int isEmpty(infixstack s)
{
    return s.top == -1;
}

int isFull(infixstack s)
{
    return s.top == s.size - 1;
}

// void initinfixstack(infixstack *s)
// {
//     s->A = (int*)malloc(sizeof(int) * (s->size));
//     s->top = -1;
// }

void pushinfix(infixstack *s, int key)
{
    if (isFull(*s))
    {
        printf("Stack Overflow");
        return;
    }
    else
    {

        s->top = (s->top) + 1;
        s->A[s->top] = key;
    }
}

char popinfix(infixstack *s)
{
    char value;
    if (isEmpty(*s))
    {
        printf("Stack Underflow");
        return -1;
    }
    else
    {
        value = s->A[s->top];
        (s->top)--;
    }
    return value;
}

void display(infixstack s)
{
    int i;
    for (i = 0; i <= s.top; i++)
    {
        printf("%d\t", s.A[i]);
    }
    printf("\n");
}

int isoperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '/' || ch == '*');
}

int precedence(char ch)
{
    if (ch == '+' || ch == '-')
    {
        return 1;
    }
    else if (ch == '/' || ch == '*')
    {
        return 2;
    }
    else
    {
        return -1;
    }
}

void infixtopostfix(char *infix, char *postfix, int strlength)
{
    infixstack s;
    s.A = (char *)malloc(sizeof(char) * strlength);
    s.size = strlength;
    s.top = -1;

    int i;
    int j = 0;
    for (i = 0; i < strlength; i++)
    {
        if (infix[i] == ' ' || infix[i] == '\t')
        {
            postfix[j] = infix[i];
            j++;
        }
        else if (isalnum(infix[i]))
        {
            postfix[j] = infix[i];
            j++;
        }
        else if (infix[i] == '(')
        {
            pushinfix(&s, infix[i]);
        }
        else if (infix[i] == ')')
        {
            postfix[j] = ' ';
            j++;
            while (s.top > -1 && s.A[s.top] != '(')
            {
                postfix[j] = popinfix(&s);
                j++;
            }
            if (s.top > -1 && s.A[s.top] != '(')
                return NULL;
            else
                s.top--;
        }
        else if (isoperator(infix[i]))
        {
            postfix[j] = ' ';
            j++;
            if (isEmpty(s))
            {
                pushinfix(&s, infix[i]);
            }
            else
            {
                if (precedence(infix[i]) > precedence(s.A[s.top]))
                {
                    pushinfix(&s, infix[i]);
                }
                else
                {
                    while (!isEmpty(s) && precedence(infix[i]) <= precedence(s.A[s.top]))
                    {
                        postfix[j] = ' ';
                        j++;
                        postfix[j] = popinfix(&s);
                        j++;
                    }
                    pushinfix(&s, infix[i]);
                }
            }
        }
    }
    while (!isEmpty(s))
    {
        postfix[j] = ' ';
        j++;
        postfix[j] = popinfix(&s);
        j++;
    }
    postfix[j] = '\0';
}




// functions of pointer stack containing pointers to list


void initlist(list *l)
{
    l->head = NULL;
    return;
}

void insertnum(int num, list *l)
{
    node *nn;
    nn = (node *)malloc(sizeof(node));
    nn->next = NULL;
    nn->num = num;
    if (l->head == NULL)
    {
        l->head = nn;
    }
    else
    {
        node *temp = l->head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = nn;
    }
}

void insertnumpostfix(int num, list *l)
{
    node *nn;
    nn = (node *)malloc(sizeof(node));
    nn->next = NULL;
    nn->num = num;
    if (l->head == NULL)
    {
        l->head = nn;
    }
    else
    {
        nn->next = l->head;
        l->head = nn;
    }
}

void initstack(stack *s)
{
    s->listpointer_top = NULL;
    return;
}

int isempty(stack s)
{
    if (s.listpointer_top == NULL)
        return 1;
    else{
        return 0;
    }
}

void push(list *l, stack *s)
{
    snode *nn;
    nn = (snode *)malloc(sizeof(snode));
    nn->listpointer = l->head;
    nn->next = NULL;
    if (isempty(*s))
    {
        s->listpointer_top = nn;
        return;
    }
    nn->next = s->listpointer_top;
    s->listpointer_top = nn;
    return;
}

node *pop(stack *s)
{
    if (isempty(*s))
    {
        return NULL;
    }
    snode *temp = s->listpointer_top;
    s->listpointer_top = temp->next;
    list *l;
    l = (list *)malloc(sizeof(list));
    initlist(l);
    l->head = temp->listpointer;
    free(temp);
    return l->head;
}

// all the bc operations

int count(list l)
{
    node *temp = l.head;
    int count = 0;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

void displaynum(node *head)
{
    if (head == NULL)
    {
        printf("\n");
        return;
    }

    displaynum(head->next);
    printf("%d", head->num);
}

node *reverse(list *l1)
{
    node *p;
    node *q;
    node *r;
    p = q = r = l1->head;
    while (r)
    {
        r = r->next;
        q->next = p;
        p = q;
        q = r;
    }
    l1->head->next = NULL;
    l1->head = p;
    return l1->head;
}

int isGreater(list *l1, list *l2)
{
    if (count(*l1) > count(*l2))
    {
        return 1;
    }
    else if (count(*l1) < count(*l2))
    {
        return 0;
    }
    else
    {
        node *temp1 = reverse(l1);
        node *temp2 = reverse(l2);
        while (temp1 != NULL && temp2 != NULL)
        {
            if (temp1->num > temp2->num)
            {
                l1->head = reverse(l1);
                l2->head = reverse(l2);
                return 1;
            }
            else if (temp1->num < temp2->num)
            {
                l1->head = reverse(l1);
                l2->head = reverse(l2);
                return 0;
            }
            else
            {
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
        }
        return 1;
    }
}

node *duplicate(list *l1, list *l2)
{
    l1->head = NULL;
    node *temp2 = l2->head;
    node *temp1 = l1->head;
    while (temp2 != NULL)
    {
        node *nn = (node *)malloc(sizeof(node));
        nn->num = temp2->num;
        nn->next = NULL;
        if (temp1 == NULL)
        {
            l1->head = nn;
            temp1 = nn;
        }
        else
        {
            temp1->next = nn;
            temp1 = nn;
        }
        temp2 = temp2->next;
    }
    return l1->head;
}

list add(list *l1, list *l2)
{
    list l3;
    initlist(&l3);
    int carry = 0;
    int sum;
    node *temp1 = l1->head;
    node *temp2 = l2->head;
    while (temp1 != NULL && temp2 != NULL)
    {
        insertnum((temp1->num + temp2->num + carry) % 10, &l3);
        carry = (temp1->num + temp2->num + carry) / 10;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    while (temp1 != NULL)
    {
        insertnum((temp1->num + carry) % 10, &l3);
        carry = (temp1->num + carry) / 10;
        temp1 = temp1->next;
    }
    while (temp2 != NULL)
    {
        insertnum((temp2->num + carry) % 10, &l3);
        carry = (temp2->num + carry) / 10;
        temp2 = temp2->next;
    }
    if (temp1 == NULL && temp2 == NULL && carry == 1)
    {
        insertnum(1, &l3);
    }
    return l3;
}

list subtract(list *l1, list *l2)
{
    list l3;
    initlist(&l3);
    node *temp1 = l1->head;
    node *temp2 = l2->head;
    if (count(*l1) < count(*l2))
    {
        list l4;
        l4 = subtract(l2, l1);
        node *temp3 = l4.head;
        while (temp3->next != NULL)
        {
            temp3 = temp3->next;
        }
        temp3->num = (-1) * (temp3->num);
        return l4;
    }
    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->num < temp2->num)
        {
            node *borrow = temp1->next;
            if (borrow == NULL)
            {
                insertnum(temp1->num - temp2->num + 10, &l3);
                list l4;
                initlist(&l4);
                for (int i = 1; i <= count(l3); i++)
                {
                    insertnum(0, &l4);
                }
                insertnum(1, &l4);
                list l5 = subtract(&l4, &l3);
                node *tempo = l5.head;
                while (tempo->next->next != NULL)
                {
                    tempo = tempo->next;
                }
                tempo->num = (-1) * (tempo->num);
                tempo->next = NULL;
                return l5;
            }
            while (borrow->num == 0)
            {
                borrow->num += 9;
                borrow = borrow->next;
            }
            borrow->num = borrow->num - 1;
            insertnum(temp1->num - temp2->num + 10, &l3);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else
        {
            insertnum(temp1->num - temp2->num, &l3);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    while (temp1 != NULL)
    {
        insertnum(temp1->num, &l3);
        temp1 = temp1->next;
    }
    node *alpha = reverse(&l3);

    while (alpha->num == 0 && alpha->next!= NULL)
    {
        node *beta = alpha;
        alpha = alpha->next;
        l3.head = alpha;
        beta->next = NULL;
        free(beta);
    }
    // l3.head = alpha;
    if (alpha == NULL)
    {
        list l5;
        initlist(&l5);
        insertnum(0, &l5);
        return l5;
    }
    reverse(&l3);
    return l3;
}

list multiply(list *l1, list *l2)
{
    list *l3;
    l3 = (list *)malloc(sizeof(list) * count(*l2));
    for (int k = 0; k < count(*l2); k++)
    {
        initlist(&l3[k]);
    }
    list ans;
    initlist(&ans);
    insertnum(0, &ans);
    // long long int sum =0;

    node *temp2 = l2->head;
    int carry = 0;
    int i = 0;
    while (temp2 != NULL)
    {
        node *temp1 = l1->head;
        for (int j = 0; j < i; j++)
        {
            insertnum(0, &l3[i]);
        }
        while (temp1 != NULL)
        {
            insertnum(((temp2->num) * (temp1->num) + carry) % 10, &l3[i]);
            carry = ((temp2->num) * (temp1->num) + carry) / 10;
            temp1 = temp1->next;
        }
        if (temp1 == NULL && carry != 0)
        {
            insertnum(carry, &l3[i]);
        }
        temp2 = temp2->next;
        ans = add(&ans, &l3[i]);
        i++;
    }
    return ans;
}

list divide(list *l1, list *l2)
{
    list ans;
    initlist(&ans);
    insertnum(0, &ans);

    list count;
    initlist(&count);
    insertnum(1, &count);

    list division;
    initlist(&division);
    insertnum(0, &division);
    if (isGreater(l1, l2))
    {
        division = add(&division, &count);
        ans = add(&ans, l2);
    }
    while (isGreater(l1, &ans))
    {
        division = add(&division, &count);
        ans = add(&ans, l2);
    }
    division = subtract(&division, &count);
    return division;
}


