#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    int *visited; //store the visited vertices
    int **matrix;
}Graph;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} Stack;

// You should not change the prototypes of these functions
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
////////////////////////////////////////////

void DFS_I (Graph , int );

int main()
{
    Graph g;
    int i,j;
    

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;
	
	g.visited = (int *) malloc(sizeof(int)*g.V);
    for(i=0;i<g.V;i++) g.visited[i] = 0;
    
    
    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter a start vertex for DFS:\n");
    scanf("%d", &i);
    
    printGraphMatrix(g);
    DFS_I(g,i);

    return 0;
}

// 7
// 1 2
// 1 3
// 2 3
// 2 4
// 3 5
// 3 6
// 6 7
// a
// 1

void DFS_I (Graph g, int v)
{
    // Stack s;
    // s.head = NULL;
    // s.size = 0;

    // int w;
    // int stopNode = 0;
    // push(&s,v);
    // g.visited[v-1] = 1;
    // printf("%d",v);

    // // while the stack is not empty
    // while(isEmptyStack(s)==0) {
    //     w = peek(s);
    //     stopNode = 0;

    //     // loop through all adjacent vertices to look for unvisited node
    //     for (int i=0; i<g.V;i++) {
    //         if (g.matrix[w-1][i] == 1 && g.visited[i] == 0) {
    //             // push found node to stack and print
    //             push(&s, i+1);
    //             printf("%d",i+1);
    //             // mark as visited
    //             g.visited[i] = 1;

    //             // stopNode set to 1 as node has been found
    //             stopNode=1;
    //             break;
    //         }
    //     }

    //     // when there are no unvisited nodes, stopNode would be 0, and we stack backtracking
    //     if (stopNode == 0) {
    //         pop(&s);
    //     }
    // }

    Stack s;
    s.head = NULL;
    s.size = 0;

    push(&s, v);
    printf("%d", v);
    g.visited[v-1] = 1;
    
    while (isEmptyStack(s)==0) {
        int currentNode = peek(s);
        int stopNode = 0;
        for (int i=0; i<g.V; i++) {
            if (g.matrix[currentNode-1][i] && g.visited[i]==0) {
                stopNode = 1;
                g.visited[i] = 1;
                printf("%d", i+1);
                push(&s,i+1);
                break;
            }
        }
        if (stopNode == 0) {
            pop(&s);
        }
        
    }


    // Write your code here
}

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
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

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
