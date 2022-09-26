#include <stdio.h>
#include <stdlib.h>

struct _listnode
{
    int item;
    struct _listnode *next;
};

typedef struct _listnode ListNode;

ListNode *findNode(ListNode* cur, int i)
{
    if (cur==NULL || i<0)
        return NULL;
        while(i>0){
            cur=cur->next;
            if (cur==NULL)
            return NULL;
            i--;
        }
    return cur;
}

int insertNode (ListNode **ptrHead , int i , int item ){
    ListNode *pre , *newNode ;
    // If empty list or inserting first node , update head pointer
    if (i == 0) {
        newNode = (ListNode *) malloc (sizeof(ListNode));
        newNode->item = item ;
        newNode->next = *ptrHead ;
        *ptrHead = newNode ;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((pre = findNode (*ptrHead , i-1) ) != NULL ){
        newNode = (ListNode *) malloc (sizeof(ListNode));
        newNode->item = item ;
        newNode->next = pre->next ;
        pre->next = newNode ;
        return 1;
    }
    return 0;
 }

void printList(ListNode* cur){
    while (cur != NULL){
        printf("%d\n", cur->item);
        cur = cur->next;
    }
}

int main(void)
{
    ListNode *head = NULL, *temp;

    int num;
    printf("Enter a list of numbers, terminated by the value -1\n");
    scanf("%d",&num);

    while (num != -1) {
        if(head == NULL) {
            head = malloc(sizeof(ListNode));
            temp = head;
        } else {
            temp->next = malloc(sizeof(ListNode));
            temp = temp->next;
        }

        temp->item = num;
        temp->next = NULL;

        scanf("%d",&num);
    }

    printf("current list: ");
    temp = findNode(head,3);
    
    printf("%d",temp->item);
    printList(head);

    // clear memory taken by linked list
    while (head != NULL) {
        ListNode *temp = head->next;
        free(head);
        head = temp;
    }

    return 0;
}

