#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000 //The limit of expression length

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

void in2Post(char*, char*);

int main()
{
    char infix[SIZE];
    char postfix[SIZE];

    printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    in2Post(infix,postfix);
    printf("The postfix expression is \n");
    printf("%s\n",postfix);
    return 0;
}

void push(Stack *sPtr, char item){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void in2Post(char* infix, char* postfix)
{
 //Write your code here
    Stack s;
    s.head = NULL;
    s.size = 0;

    int length = strlen(infix);
    int k = 0;

    for(int i = 0; i < length; i++){
        if(infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '(' && infix[i] != ')'){ // take out numbers and put them in postfix accordingly
            postfix[k] = infix[i];
            k++;
        }

        else if(infix[i] == ')'){  // sends everything from open bracket to close bracket to postfix, since this is more priority
            while (peek(s) != '('){
                postfix[k] = peek(s);
                k++;
                pop(&s);
            }
            pop(&s); //pop out the open bracket from the stack
        }

        else if(infix[i] == '('){ //when there is a open bracket, send it to the stack first and let the programme run until close brakcet is seen and the previous scenario is executed
            push(&s, infix[i]);
        }

        else{
            while(s.size != 0 && peek(s) != '('){
                if(peek(s) == '*' || peek(s) == '/' || peek(s) == '-' && infix[i] == '-' || peek(s) == '-' && infix[i] == '+' || peek(s) == '+' && infix[i] == '+' || peek(s) == '+' && infix[i] == '-'){ //if peek(S) is times or divide its precedence will be higher regardless
                    postfix[k] = peek(s);
                    k++;
                    pop(&s);
                }
                else{
                    break;
                }
            }

            push(&s, infix[i]);
        }
    }

    while(s.size!=0){ //empty out stack
        postfix[k] = peek(s);
        k++;
        pop(&s);
    }

    postfix[k] = 0;
}



// a+b*c-d*(e/f)
// postfix: a
// postfix: a, s: +
// postfix: ab, s: +
// postfix: ab