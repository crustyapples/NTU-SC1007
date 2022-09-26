#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void reverseKNodes(ListNode** head, int K);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int K = 0;

	scanf("%d",&K);

	while (scanf("%d", &i)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
	}
	temp->next = NULL;


	reverseKNodes(&head, K);
	printList(head);
    deleteList(&head);
	return 0;
}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%d ",head->item);
        head = head->next;
    }
    printf("\n");
}
void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
}

ListNode *findNode(ListNode *cur, int index) {
	
	if (!cur || index<0) {
		return NULL;
	}

	for (int i = 0; i < index; i++) {
		cur = cur->next;
	}

	return cur;
}

ListNode *reverseSegment(ListNode* head, int start, int end)
{
	ListNode *startNode,*endNode,*endNextNode,*beforeStartNode = NULL;
	ListNode *cur = head;

	for (int i=0; i<=end; i++) {
	    if (cur!=NULL) {
	        if (i == start) {
	            startNode = cur;
	        }
	        else if (i == start-1) {
	            beforeStartNode = cur;
	        }
	    }
	    endNode = cur;
	    cur = cur->next;
	}
	
	endNextNode = endNode->next;
	cur = startNode;
	endNode->next = NULL;
	
	ListNode *pre,*next = NULL;
	while (cur) {
		next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	endNode = pre;

	if (beforeStartNode != NULL) {
		beforeStartNode->next = endNode;
	} else {
		head = endNode;
	}

	startNode->next = endNextNode;
	return head;
// Write your code here
}


void reverseKNodes (ListNode **head, int K) {
	if (head == NULL) {
		return;
	}
	ListNode *cur = *head;
	int index;
	int size=0;

	while(cur!=NULL) {
		cur=cur->next;
		size++;
	}

	cur=*head;


	for (int i=0; i<size+1;i++) {
		if (K <= 0) {
			break;
		}

		if(i%K == 0 && i != 0) {
			index = i-1;
			if (i==K) {
				*head = reverseSegment(*head, 0, index);
			} else {
				*head = reverseSegment(*head, index-K+1, index);
			}
			
		}
		if (cur) {
			cur = cur->next;
		}
	}
}