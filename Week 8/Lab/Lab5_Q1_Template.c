#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{
    int key;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} HashTableNode;

typedef struct _hashTable{
   int hSize; //size of hash table
   int nSize; //number of inserted keys
   HashTableNode *Table;
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
    scanf("%d",&opt);
    while(opt>=1 && opt <=4){
        switch(opt){
        case 1:
            printf("Enter the size of hash table:\n");
            scanf("%d",&Q3Hash.hSize);

            Q3Hash.nSize = 0;

            Q3Hash.Table = (HashTableNode *) malloc(sizeof(HashTableNode)*(Q3Hash.hSize));

            for(i=0;i<Q3Hash.hSize;i++){
               Q3Hash.Table[i].head = NULL;
               Q3Hash.Table[i].size = 0;
            }
            printf("HashTable is created.\n");
            break;
        case 2: //Insertion
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);

            if(HashInsert(&Q3Hash,key))
                printf("%d is inserted.\n",key);
            else
                printf("%d is a duplicate. No key is inserted.\n",key);
            break;
        case 3: //Search
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            ListNode* node = HashSearch(Q3Hash, key);

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

int Hash(int key,int hSize)
{
    return key%hSize;
}

ListNode* HashSearch(HashTable Q3Hash, int key)
{
    //write your code here
    int size = Q3Hash.hSize;
    int value = Hash(key,size);

    ListNode *cur = Q3Hash.Table[value].head;

    return cur;

}

int HashInsert(HashTable* Q3HashPtr, int key)
{
    // //write your code here

    // // key is taken as input -> run hash function -> output key 

    // // create a node 
    // ListNode *newNode = malloc(sizeof(ListNode));
    // newNode->next = NULL;
    // newNode->key = 0;

    // // calculate the hash key
    // int size = Q3HashPtr->hSize;
    // int value = Hash(key,size);

    // if ((*Q3HashPtr).Table[value].size == 0) {
    //     newNode->key = key;
    //     (*Q3HashPtr).Table[value].head = newNode;
    //     (*Q3HashPtr).Table[value].size++;
    //     Q3HashPtr->nSize++;
    // } 
    
    // else {
    //     ListNode *cur = (*Q3HashPtr).Table[value].head;
    //     newNode->key = key;
    //     (*Q3HashPtr).Table[value].head = newNode;
    //     (*Q3HashPtr).Table[value].size++;
    //     Q3HashPtr->nSize++;
    //     (*Q3HashPtr).Table[value].head->next = cur;
    // }

// -----------------------------------------------------------------
    int tableSize = Q3HashPtr->hSize;
    int index = Hash(key, tableSize);

    // intialise a new node

    ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
    newNode->key = key;

    //insert this node into the hashtable

    newNode->next = Q3HashPtr->Table[index].head;
    Q3HashPtr->Table[index].head = newNode;

    Q3HashPtr->Table[index].size++; Q3HashPtr->nSize++;


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