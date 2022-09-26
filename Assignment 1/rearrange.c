#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList{
    ListNode *head;
    int size;
}LinkedList;

void printList(LinkedList ll);
void deleteList(LinkedList* llptr);

LinkedList rearrange (LinkedList ll);

int main()
{
    LinkedList ll;

    ll.head = NULL;
    ll.size = 0;
    ListNode* temp;

	int i = 0;

	while (scanf("%d", &i)){
		if (ll.head == NULL){
			ll.head = (ListNode*) malloc(sizeof(ListNode));
			temp = ll.head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
		ll.size++;
	}
	temp->next = NULL;

	ll=rearrange(ll);

	printList(ll);
    deleteList(&ll);
	return 0;
}

void printList(LinkedList ll){
    ListNode* temp = ll.head;

    while(temp !=NULL){
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");
}
void deleteList(LinkedList* llptr){
    ListNode *cur = llptr->head;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	llptr->head=NULL;
	llptr->size =0;
}

LinkedList rearrange (LinkedList ll){
	// divide into two Lists. ListOne and ListTwo
    LinkedList firstList;
    LinkedList secondList;
    LinkedList fullList;
    firstList.head = ll.head;
    secondList.head = ll.head;

    ListNode *cur, *firstTemp, *secondTemp;
	int size = ll.size;

	if (size == 1) {
		return ll;
	}
    
	int firstSize = size/2;
	int secondSize = firstSize + 1;

    cur = firstList.head;
    int i=0;
    
    // creating first half list
    while (cur!=NULL && i<firstSize-1) {
        cur=cur->next;
        i++;
    }
    firstTemp = cur;
    secondTemp = cur->next;

    // breaking the first half
    cur->next = NULL;
    

    // start of second list after end of first half
    secondList.head = secondTemp;
    cur = secondTemp;
    while (cur!=NULL && firstSize<secondSize-1) {
        cur=cur->next;
        firstSize++;
    }
    secondTemp = cur;

    // firstlist and secondlist are now created, we must link the two at alternating nodes
    ListNode *curFirst, *curSecond, *pre, *nextFirst, *nextSecond;
    curFirst = firstList.head;
    curSecond = secondList.head;
    pre = NULL;
    nextFirst = NULL;
    nextSecond = NULL;

    while (curFirst!=NULL) {
        nextSecond = curSecond->next;
        curSecond->next = curFirst;
        nextFirst = curFirst->next;
        curFirst->next = nextSecond;
        curSecond = nextSecond;
        curFirst = nextFirst;
    }

    // second arrangement starts here

    firstList.head = secondList.head;
    firstSize = size/2;
    secondSize = firstSize + 1;
    cur = firstList.head;

    i=0;

    // creating first half list
    while (cur!=NULL && i<firstSize-1) {
        cur=cur->next;
        i++;
    }
    firstTemp = cur;
    secondTemp = cur->next;

    // breaking the first half
    cur->next = NULL;
    

    // start of second list after end of first half
    secondList.head = secondTemp;
    cur = secondTemp;
    while (cur!=NULL && firstSize<secondSize-1) {
        cur=cur->next;
        firstSize++;
    }
    secondTemp = cur;

    // we link the two again
    
    curFirst = secondList.head;
    curSecond = firstList.head;
    pre = NULL;
    nextFirst = NULL;
    nextSecond = NULL;

    while (curFirst!=NULL && curSecond != NULL) {
        nextSecond = curSecond->next;
        curSecond->next = curFirst;
        nextFirst = curFirst->next;
        curFirst->next = nextSecond;
        curSecond = nextSecond;
        curFirst = nextFirst;
    }

    cur = firstList.head;
    while (1) {
        cur = cur->next;
        if (cur->next == NULL) {
            cur->next = curFirst;
            break;
        }
    }

    fullList.head = firstList.head;
    return fullList;
// Write your code here
}
