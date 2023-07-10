// structs for infix to postfix, linked list and stack of pointers

typedef struct infixstack
{
    int top;
    char *A;
    int size;
} infixstack;

typedef struct snode
{
    struct node *listpointer;
    struct snode *next;

} snode;

typedef struct node
{
    int num;
    struct node *next;

} node;

typedef struct list
{
    struct node *head;
} list;

typedef struct stack
{
    struct snode *listpointer_top;
} stack;





// functions for infix to postfix

int isEmpty(infixstack s);
int isFull(infixstack s);
void pushinfix(infixstack *s, int key);
char popinfix(infixstack *s);
void display(infixstack s);
int isoperator(char ch);
int precedence(char ch);
void infixtopostfix(char *infix, char *postfix, int strlength);


// functions of pointer stack containing pointers to list
void initlist(list *l);
void insertnum(int num, list *l);
void insertnumpostfix(int num, list *l);
void initstack(stack *s);
int isempty(stack s);
void push(list *l, stack *s);
node *pop(stack *s);



// all the bc operations
int count(list l);
void displaynum(node *head);
node *reverse(list *l1);
int isGreater(list *l1, list *l2);
node *duplicate(list *l1, list *l2);
list add(list *l1, list *l2);
list subtract(list *l1, list *l2);
list multiply(list *l1, list *l2);
list divide(list *l1, list *l2);