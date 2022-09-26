#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void triPartition(ListNode** head, int pivot);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int pivot = 0;

	scanf("%d",&pivot);

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


	triPartition(&head, pivot);
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



void triPartition(ListNode** head, int pivot){
    ListNode *trav = *head;
    ListNode *pivotTemp = NULL;
    ListNode *pivotHead = NULL;
    ListNode *bigTemp = NULL;
    ListNode *bigHead = NULL;
    ListNode *smallTemp = NULL;
    ListNode *smallHead = NULL; 

    while (trav!=NULL) {

        if (trav->item == pivot) {
            if (pivotTemp == NULL) { 
                pivotTemp = trav;
                pivotHead = pivotTemp;
            } else {
                pivotTemp->next = trav;
                pivotTemp = trav;
            }
        }

        if (trav->item > pivot) {
            if (bigTemp == NULL) { 
                bigTemp = trav;
                bigHead = bigTemp;
            } else {
                bigTemp->next = trav;
                bigTemp = trav;
            }
        }

        if (trav->item < pivot) {
            if (smallTemp == NULL) { 
                smallTemp = trav;
                smallHead = smallTemp;
            } else {
                smallTemp->next = trav;
                smallTemp = trav;
            }
        }
        trav=trav->next;
    }

    if (bigTemp != NULL) {
        bigTemp = bigHead;
        while (bigTemp->next != NULL) {
            if (bigTemp->next->item <= pivot) {
                bigTemp->next = NULL;
                break;
            }
            bigTemp = bigTemp->next;
        }
    }

    if (smallTemp != NULL) {
        smallTemp = smallHead;
        while (smallTemp->next != NULL) {
            if (smallTemp->next->item >= pivot) {
                smallTemp->next = NULL;
                break;
            }
            smallTemp = smallTemp->next;
        }
    }

    if (smallHead != NULL && bigHead != NULL && pivotTemp == NULL) {
        smallTemp->next = bigHead;
    } else if (smallHead != NULL && bigHead != NULL && pivotHead != NULL) {
        smallTemp->next = pivotHead;
        pivotTemp->next = bigHead;
    } 

    if (smallHead != NULL) {
        *head = smallHead;
    } else {
        *head = pivotHead;
    }
// Write your code here
}