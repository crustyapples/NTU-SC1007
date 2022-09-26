#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
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
}

void swapBrackets(char *s) {
    int i=0;
    while (s[i] != '\0') {
        if (s[i] == '(') {
            s[i] = ')';
        } else if (s[i] == ')') {
            s[i] = '(';
        }
        i++;
    }
}

int checkPrecedence(char operator)
{
    if (operator == '/' || operator == '*')
    {
        return 2;
    }
    else if (operator == '+' || operator == '-')
    {
        return 1;
    }
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{
    //Write your code here
    reverseString(infix);
    swapBrackets(infix);

    // reverse the infix string and then convert it into a postfix expression

    char postfix[SIZE];
    Stack s;
    s.head = NULL;
    s.size = 0;

    int operand = 0;
    int i = 0;
    int n = 0;
    int k = 0;
    int length = strLen(infix);

    for (int i = 0; i < length; i++){
        int j=0;
        char holdingStr[SIZE] = " ";

        if (infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '(' && infix[i] != ')'){ 
            postfix[k] = infix[i];
            k++;
            n = i;
            while (infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '(' && infix[i] != ')') {
                holdingStr[j] = infix[i];
                j++;
                i++;
            }
            i = n+1;
            // reverse the digits before passing them into the node
            
            reverseString(holdingStr);
            operand = atof(holdingStr);
            insertNode(inExpLL, operand, OPERAND);
        }

        else if(infix[i] == ')'){  
            while (peek(s) != '('){
                postfix[k] = peek(s);
                insertNode(inExpLL, peek(s), OPT);
                k++;
                pop(&s);
            }
            pop(&s); 
        }

        else if(infix[i] == '('){ 
            push(&s, infix[i]);
        }

        else{
            while(s.size != 0 && peek(s) != '(' && checkPrecedence(peek(s) >= checkPrecedence(infix[i]))){
                    postfix[k] = peek(s);
                    insertNode(inExpLL, peek(s), OPT);
                    k++;
                    pop(&s);
            }
            push(&s, infix[i]);
        }
    }

    while(s.size!=0){
        postfix[k] = peek(s);
        insertNode(inExpLL, peek(s), OPT);
        k++;
        pop(&s);
    }

    postfix[k] = '\0';

    // insert the postfix of the reversed string at the start of the linkedlist to reverse  it once

    // int operand = 0;
    // int len = strLen(postfix);
    // i = 0;

    // while (i<len) {
    //     int j = 0;
    //     char holdingStr[SIZE] = " ";

    //     if (postfix[i] == '+' | postfix[i] == '-' | postfix[i] == '/' | postfix[i] == '*' | postfix[i] == ')' | postfix[i] == '(') {
    //         insertNode(inExpLL, postfix[i], OPT);
    //         i++;
    //     } 
        
    //     else {
    //         while (postfix[i] != '+' && postfix[i] != '-' && postfix[i] != '*' && postfix[i] != '/' && postfix[i] != '(' && postfix[i] != ')') {
    //             holdingStr[j] = postfix[i];
    //             j++;
    //             i++;
    //         }

    //         // reverse the digits before passing them into the node
    //         reverseString(holdingStr);
    //         operand = atof(holdingStr);
    //         insertNode(inExpLL, operand, OPERAND);
    //     }

    // }

}

