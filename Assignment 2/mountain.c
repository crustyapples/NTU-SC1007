#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode
{
    int  item;
	struct _dbllistnode *next;
	struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist{
   int size;
   CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);

int main()
{
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i,cases;
    int numP;
    scanf("%d",&cases);
    for(i=0; i<cases; i++)
    {
        while(scanf("%d",&item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n",numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value){
      //create a new node
      CDblListNode* newNode;
      newNode = (CDblListNode *) malloc(sizeof(CDblListNode));
      newNode->item = value;

      if(ptrCDLL->size==0) //first node
      {
          newNode->next = newNode;
          newNode->pre = newNode;
          ptrCDLL->head = newNode;
      }
      else{
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; //update last node next link;
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
      }
      ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL){

    if(CDLL.head==NULL) return;

    CDblListNode* temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head){
        printf("%d ", temp->item);
        temp = temp->next;

    }
    printf("%d\n",temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL){
    if(ptrCDLL->head==NULL) return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next!= ptrCDLL->head) {
        temp=cur->next;
        free(cur);
        cur=temp;
    }

    free(cur);
    ptrCDLL->head =NULL;
    ptrCDLL->size =0;

}


int numMountainPairs(CDblLinkedList CDLL)
{
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail

    if (CDLL.size == 1 || CDLL.size == 0) {
        return 0;
    }

    int nonAdjacentPairsF = 0;
    CDblListNode *cur, *temp;
    int store = 0;
    cur = CDLL.head;
 
    int i=1; int j=1; int k=0; int n = 0;
    int *counterF = (int*) calloc(CDLL.size * 40, sizeof(int));
    
    do {
        temp = cur->next;
        store = 0;
        j=1;
        while (temp != cur->pre) {
            if (temp->item>store) {
                store = temp->item;
            }
            if (cur->item >= store && temp->next->item >= store && temp->next != cur->pre) {
                k = i+j+1;
                if (k>CDLL.size) {
                    k = i+j+1 - CDLL.size;
                }
                for (int l=0; l<n+1; l++) {
                    if (counterF[l] == i && counterF[l-1] == k && (l % 2 == 1)) {

                        nonAdjacentPairsF--;
                        break;
                    }
                }
                counterF[n] = i; n++;
                counterF[n] = k; n++;
                nonAdjacentPairsF++;
            }
            j++;
            temp = temp->next;
        }
        
        if (cur==CDLL.head && nonAdjacentPairsF > (CDLL.size - 3)) {
            nonAdjacentPairsF = CDLL.size - 3;
        }

        i++;
        cur = cur->next;
    } while (cur != CDLL.head);

    free(counterF);

    return nonAdjacentPairsF + CDLL.size;
}
