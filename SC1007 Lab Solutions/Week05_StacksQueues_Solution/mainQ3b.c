#include <stdio.h>
#include <stdlib.h>

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

double exePrefix(char*);

int main()
{
    char prefix[SIZE];

    printf("Enter a prefix expression:\n");
    scanf("%[^\n]%*c",prefix);

    printf("The answer is %.2lf.\n",exePrefix(prefix));

    return 0;
}

int strLen(char s[]) {
    int i=0;
    for (i=0; s[i] != '\0'; ++i);
    return i;
}

void reverseString(char *s)  
{  
    int i,t;  
    int len = strLen(s); 
      
    for (i = 0; i < len/2; i++)  
    {  
        t = s[i];  
        s[i] = s[len - i - 1];  
        s[len - i - 1] = t;  
    }  

    s[len] = '\0';
}

double exePrefix(char* postfix)
{
    Stack s;
    s.head = NULL;
    s.size = 0;

    int i=strLen(postfix)-1;
    double op1, op2;
    char c;
    double result;
    // reverseString(postfix);
    
    while(postfix[i]!='\0')
    {
        c = postfix[i--];
        if(c=='*' || c=='/' || c=='+' || c=='-')
        {

            op1 = peek(s); pop(&s);
            op2 = peek(s); pop(&s);

            switch(c)
            {
            case '*':
                push(&s, op1*op2);
                break;
            case '/':
                push(&s, op1/op2);
                break;
            case '+':
                push(&s, op1+op2);
                break;
            case '-':
                push(&s, op1-op2);
            }
        }
        else
            push(&s, (c-'0')) ;

    }

   result = peek(s); pop(&s);
   return result;

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
