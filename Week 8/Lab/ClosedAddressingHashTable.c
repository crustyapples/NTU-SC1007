#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{ //Linkedlist with key and link to next node as data
    int key;
    struct _listnode *next; 
} ListNode;

typedef struct _linkedlist{ //Linkedlist with head and size, called HashTableNode (each node of a hash table is a LinkedList)
   int size;
   ListNode *head;
} HashTableNode;

typedef struct _hashTable{
   int hSize; //size of hash table (number of LinkedLists)
   int nSize; //number of inserted keys
   HashTableNode *Table; //pointer pointing to the next node, can use indexing
} HashTable;

int Hash(int,int); 

ListNode* HashSearch(HashTable, int);
int HashInsert(HashTable *, int);

//In Practice, we will not do it
void HashPrint(HashTable);

int main()
{
    int opt;
    int size;

    int i;
    int key;

    //Create a HashTable
    HashTable Q3Hash;
    Q3Hash.hSize = 0; 
    Q3Hash.nSize = 0; 
    Q3Hash.Table = NULL;

    printf("============= Hash Table ============\n");
    printf("|1. Create a hash table             |\n");
    printf("|2. Insert a key to the hash table  |\n");
    printf("|3. Search a key in the hash table  |\n");
    printf("|4. Print the hash table            |\n");
    printf("|5. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt); //opt decideds function to carry out in the hash table
    while(opt>=1 && opt <=4){
        switch(opt){
        case 1:
            printf("Enter the size of hash table:\n");
            scanf("%d",&Q3Hash.hSize); //number of LinkedLists in the hashtable

            Q3Hash.nSize = 0; //inital number of keys = 0;

            Q3Hash.Table = (HashTableNode *) malloc(sizeof(HashTableNode)*(Q3Hash.hSize)); //New table

            for(i=0;i<Q3Hash.hSize;i++){ //creating empty linked list in each hashtable nodes
               Q3Hash.Table[i].head = NULL;
               Q3Hash.Table[i].size = 0;
            }
            printf("HashTable is created.\n"); //A hastable with n linkedlists which are empty are created
            break;
        case 2: //Insertion
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);

            if(HashInsert(&Q3Hash,key)) // return 1 if key insertion is successful
                printf("%d is inserted.\n",key);
            else
                printf("%d is a duplicate. No key is inserted.\n",key); // return 0 if duplicate key is inserted
            break;
        case 3: //Search
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            ListNode* node = HashSearch(Q3Hash, key); //return node that is found

            if(node!=NULL)
                printf("%d is found.\n",key);
            else
                printf("%d is not found.\n",key);
            break;
        case 4:
            HashPrint(Q3Hash);
            break;
        }

    printf("Enter selection: ");
    scanf("%d",&opt);
    }

    for(i=0;i<Q3Hash.hSize;i++)
    {
        while(Q3Hash.Table[i].head)
        {
            ListNode *temp;
            temp = Q3Hash.Table[i].head;
            Q3Hash.Table[i].head = Q3Hash.Table[i].head->next;
            free(temp);
        }
    }
    free(Q3Hash.Table);

    return 0;

}
// Hash Function is used to determine the index of (inserted key) in the hash table
int Hash(int key,int hSize)
{
    return key%hSize;
}

ListNode* HashSearch(HashTable Q3Hash, int key)
{

    if(Q3Hash.hSize <= 0){
        return NULL;
    }


    int index;

    index = hash(key, Q3Hash.hSize);

    ListNode *temp = Q3Hash.Table[index].head;

    while(temp != NULL){
        if(temp -> key == key){
            return temp;
        }

        else{
            temp = temp -> next;
        }
    }

    return NULL;

    // //write your code here
    // int index;
    // ListNode *temp;

    // if(Q3Hash.hSize != 0){
    //     index = Hash(key, Q3Hash.hSize); //with hash we found the index of the linkedlistn where key is stored
    // }
    // else{
    //     return NULL;
    // }

    // temp = Q3Hash.Table[index].head; //temp points to the head of the linkedlist

    // while(temp != NULL){
    //     if(temp -> key == key){
    //         return temp; //return temp when found
    //     }
    //     else{
    //         temp = temp -> next;
    //     }
    // }
    // return NULL;
}



int HashInsert(HashTable* Q3HashPtr, int key)
{

    if(Q3HashPtr -> hSize <= 0){
        return 0;
    }

    if(HashSearch(*Q3HashPtr,key) != NULL){ //only insert if key does not already exist
        return 0;
    }
    
    
    int index;

    index = hash(key, Q3HashPtr->hSize);
    
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));

    temp -> key = key;

    temp -> next = Q3HashPtr ->Table[index].head;

    Q3HashPtr ->Table[index].head = temp;

    Q3HashPtr ->hSize ++;

    Q3HashPtr -> nSize ++;
    
    return 1;
    
    
    //write your code here
    // int index;
    // ListNode *newnode;

    // if (HashSearch(*Q3HashPtr, key) != NULL){ //return 0 if the key already exists in the hashtable
    //     return 0;
    // }

    // if(Q3HashPtr -> hSize != 0){
    //     index = Hash(key, Q3HashPtr -> hSize);
    // }

    // //The key is inserted from the front
    // //Initialise a node containing the key first

    // newnode = (ListNode *) malloc(sizeof(ListNode)); //new node has to be created
    // newnode -> key = key;
    // newnode -> next = Q3HashPtr -> Table[index].head; //insert this newnode at the head
    // Q3HashPtr -> Table[index].head = newnode; //set the head

    // Q3HashPtr -> Table[index].size++; //update size of both
    // Q3HashPtr -> nSize++;

    // return 1;
}

void HashPrint(HashTable Q3Hash)
{
    int i;
    ListNode *temp;
    for(i=0;i<Q3Hash.hSize;i++)
    {
        temp =Q3Hash.Table[i].head;
        printf("%d:  ",i);
        while(temp !=NULL)
        {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}