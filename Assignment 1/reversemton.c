
#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    float item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode *reverseSegment(ListNode* head, int start, int end);

int main()
{
    ListNode *head = NULL, *temp;
	float f = 0.0;
	int S, E;

	scanf("%d %d",&S, &E);

	while (scanf("%f", &f)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = f;
	}
	temp->next = NULL;

	head = reverseSegment(head,S,E);
	printList(head);
	deleteList(&head);
	return 0;

}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%.2f ",head->item);
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
	ListNode *startNode,*endNode,*endNextNode,*beforeStartNode;
	ListNode *cur = head;

	int size=0;
	while (cur) {
		cur=cur->next;
		size++;
	}

	if (start < 0 || start > size || end < 0 || end > size || end < start) {
		return head;
	}

	cur = head;
	startNode = findNode(cur, start);
	endNode = findNode(cur, end);
	beforeStartNode = findNode(cur, start-1);
	endNextNode = findNode(cur, end+1);

	endNextNode = endNode->next;
	endNode->next = NULL;

	cur = startNode;
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