#include <stdio.h>
#include <stdlib.h>

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation with ADJ_MATRIX and ADJ_LIST as types

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode; //Linkedlist Node with data vertex and pointer to next node

union GraphForm{  //union is user defined data type where all memebers share the same memory location
    int **matrix;
    ListNode **list;
};

typedef struct _graph{
    int V;
    int E;
    enum GraphType type;
    union GraphForm adj;
}Graph;

void printGraphMatrix(Graph );
void adjM2adjL(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph,int *);
void printDegreeV(int *,int );

int main()
{
    Graph g; //declare a new graph
    int i,j;

    int* degreeV;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
        for(j=0;j<g.V;j++)
            g.adj.matrix[i][j] = 0; //initialise matrix to be a 0 matrix
    g.type = ADJ_MATRIX; //it is an adjacency matrix

    degreeV = (int *) malloc(g.V*sizeof(int));
    for(i=0;i<g.V;i++)
        degreeV[i]=0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other: (enter a to stop)\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++; //add edges
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other: (enter a to stop)\n");
    }


    printGraphMatrix(g);
    
    adjM2adjL(&g);
    
    printGraphList(g);

    calDegreeV(g,degreeV);
    
    printDegreeV(degreeV,g.V);

    return 0;
}

void printGraphMatrix(Graph g)
{
    int i,j;
    printf("Print graph matrix \n");
    if(g.type == ADJ_LIST) {printf("Error"); return;}
    
    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.adj.matrix[i][j]);
        printf("\n");
    }
    printf("\n");

}

void adjM2adjL(Graph *g)
{

    if(g->type == ADJ_LIST){
        return;
    }

    if(g->V <= 0){
        return;
    } 

    //define an adjaceny list to be an array of linkedlist, use double pointer

    ListNode ** list = (ListNode **)malloc(g->V *sizeof(ListNode *)); 
    
    //initialise each linkeldlist to be null
    
    for(int i = 0; i < g->V; i++){
        list[i] = NULL;
    }
    
    ListNode *temp;
    
    for(int r = 0; r < g->V; r++){
        for(int c = 0; c < g->V; c++){
            if(g->adj.matrix[r][c] == 1){ 

                if(list[r] == NULL){
                    list[r] = (ListNode *)malloc(sizeof(ListNode));
                    list[r] ->vertex = c + 1;
                    list[r] -> next = NULL;
                    temp = list[r];
                }

                else{
                    temp -> next = (ListNode *)malloc(sizeof(ListNode));
                    temp -> next -> vertex = c + 1;
                    temp -> next ->next = NULL;
                    temp = temp -> next;
                }
            }
        }
    }

    g->type = ADJ_LIST;

    //free adj matrix

    g->adj.list = list;
}


void printGraphList(Graph g){
    int i;
    ListNode* temp;
    printf("Print graph list \n");
    if(g.type == ADJ_MATRIX) {printf("Error"); return;}

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.adj.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("\n");
}

void calDegreeV(Graph g, int *degreeV)
{
    
    for(int i = 0; i < g.V; i++){
        degreeV[i] = 0;
        ListNode *temp = g.adj.list[i];

        while(temp != NULL){
            degreeV[i]++;
            temp = temp -> next;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    // Question 3
    // Write your code here
    // int i,j;
    // ListNode *temp = NULL;

	// for(i=0;i<g.V;i++){ //add size of their linkedlist in adjaceny list for each of the Vertices
	// 	degreeV[i]=0;
	// 	ListNode *temp = g.adj.list[i];
	// 	while(temp != NULL){
	// 		degreeV[i]++;
	// 		temp = temp->next; //traverse through the linkedlist and keep adding 1 every time a next temp exists
	// 	}
	// }
}

void printDegreeV(int *degreeV,int V)
{
    int i;
    for(i=0;i<V;i++)
        printf("%d: %d degree\n",i+1,degreeV[i]);
}