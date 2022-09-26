#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queuenode{
    BTNode* node;
    struct _queuenode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space,int left);
//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * node);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2);

int main()
{
    BTNode* root = (BTNode*) malloc(sizeof(BTNode));

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    BTNode* node;
    enqueue(&q,root);

    int nodeV;
    char opL, opR;

    while(!isEmptyQueue(q)){
            scanf("%d %c %c",&nodeV,&opL,&opR);
            node = getFront(q);dequeue(&q);
            node->nodeV = nodeV;

            if(opL != '@'){
                node->left = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->left);
            }
            else node->left =NULL;
            if(opR != '@'){
                node->right = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->right);
            }
            else
                node->right = NULL;
    }

    int v1,v2;
    scanf("%d %d",&v1,&v2);
    int cost = twoNodesCost(root,v1,v2);

    printBTNode(root,0,0);

    printf("Distance is %d\n",cost);
    return 0;
}

void enqueue(Queue *qPtr, BTNode *node){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

BTNode* getFront(Queue q){
    return q.head->node;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}
void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->nodeV);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

void printQueue(Queue q) {
    BTNode* node = getFront(q);
    while (q.size != 0) {
        node = getFront(q);
        printf("%d", node->nodeV);
    }
}

Queue q1; 
Queue q2; 
Queue q3; 
Queue q4;


void forV1(BTNode* node, int nodeV1) {
    if (node == NULL) return;
    printf("%d \n", node->nodeV);
    forV1(node->left, nodeV1);
    forV1(node->right, nodeV1);
    
    if (node->left == NULL) {
        if (node->right == NULL) {
            return;
        }
    }

    if ((node->left != NULL && node->left->nodeV == nodeV1) || (node->right !=NULL && node->right->nodeV == nodeV1)) {
        enqueue(&q1, node);
        enqueue(&q2, node);
        printf("q1: %d \n", getFront(q1)->nodeV);
        printf("q2: %d \n", node->nodeV);
        return;
    }

    if (q1.size != 0) {
        printf("q1: %d \n", getFront(q1)->nodeV);
        printf("node left: %d \n", node->left->nodeV);
        if ((node->left != NULL && node->left->nodeV == getFront(q1)->nodeV) || (node->right !=NULL && node->right->nodeV == getFront(q1)->nodeV)) {
            dequeue(&q1);
            enqueue(&q1, node);
            enqueue(&q2, node);
            printf("q1: %d \n", getFront(q1)->nodeV);
            printf("q2: %d \n", node->nodeV);
            return;
        }
    }

    return;
}

void forV2(BTNode* node, int nodeV1) {
    if (node == NULL) return;
    printf("%d \n", node->nodeV);
    forV2(node->left, nodeV1);
    forV2(node->right, nodeV1);
    
    if (node->left == NULL) {
        if (node->right == NULL) {
            return;
        }
    }

    if ((node->left != NULL && node->left->nodeV == nodeV1) || (node->right !=NULL && node->right->nodeV == nodeV1)) {
        enqueue(&q3, node);
        enqueue(&q4, node);
        printf("q3: %d \n", getFront(q3)->nodeV);
        printf("q4: %d \n", node->nodeV);
        return;
    }

    if (q3.size != 0) {
        printf("q3: %d \n", getFront(q3)->nodeV);
        printf("node left: %d \n", node->left->nodeV);
        if ((node->left != NULL && node->left->nodeV == getFront(q3)->nodeV) || (node->right !=NULL && node->right->nodeV == getFront(q3)->nodeV)) {
            dequeue(&q3);
            enqueue(&q3, node);
            enqueue(&q4, node);
            printf("q3: %d \n", getFront(q3)->nodeV);
            printf("q4: %d \n", node->nodeV);
            return;
        }
    }

    return;
}


int twoNodesCost(BTNode* node, int nodeV1,int nodeV2)
{
    if (nodeV1 == nodeV2) {
        return nodeV1;
    }
    
    forV1(node, nodeV1);
    forV2(node, nodeV2);

    // comparing q2 and q4
    int distance = nodeV1 + nodeV2;
    int len = 0;

    if (q2.size > q4.size) {
        len = q2.size;

    } else if (q4.size > q2.size) {
        len = q4.size;

    } else {
        len = q2.size;
    }

    for (int i=0; i<len; i++) {
        if ((getFront(q2)->nodeV == getFront(q4)->nodeV)) {
            distance += getFront(q2)->nodeV;
            dequeue(&q2);
            dequeue(&q4);
            break;
        } else if (q2.size > q4.size){
            distance += getFront(q2)->nodeV;
            dequeue(&q2);
        } else if (q4.size > q2.size) {
            distance += getFront(q4)->nodeV;
            dequeue(&q4); 
        } else {
            distance += getFront(q2)->nodeV;
            distance += getFront(q4)->nodeV;
            dequeue(&q2);
            dequeue(&q4);
        }
    }


    return distance;
}
// 