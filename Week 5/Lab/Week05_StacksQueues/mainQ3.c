#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000 //The limit of expression length

typedef struct _stackNode{
    double item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, double item);
int pop(Stack *sPtr);
double peek(Stack s);
int isEmptyStack(Stack s);

double exePostfix(char*);

int main()
{
    char postfix[SIZE];

    printf("Enter a postfix expression:\n");
    scanf("%[^\n]%*c",postfix);

    printf("The answer is %.2lf.\n",exePostfix(postfix));

    return 0;
}

void push(Stack *sPtr, double item){
    StackNode *newNode;
    newNode = (StackNode *) malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

double peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

double exePostfix(char* postfix)
{
 //Write your code here
    Stack s;
    s.head = NULL;
    s.size = 0;

    double operand, operand1, operand2;

    int len = strlen(postfix);

    for (int i=0; i < len; i++) {
        if (postfix[i] == '+' | postfix[i] == '-' | postfix[i] == '/' | postfix[i] == '*') {
            operand1 = peek(s);
            pop(&s);
            operand2 = peek(s);
            pop(&s);

            if (postfix[i] == '+') {
                push(&s, operand2 + operand1);
            }
            if (postfix[i] == '-') {
                push(&s, operand2 - operand1);
            }
            if (postfix[i] == '*') {
                push(&s, operand2 * operand1);
            }
            if (postfix[i] == '/') {
                push(&s, operand2 / operand1);
            }

        } else { 
            char a = postfix[i];
            char *str = &a;
            operand = atof(str);
            push(&s, operand);
        }
    }

    return peek(s);




}
