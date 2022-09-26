#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode{
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode** node, char* preO, char* postO);
void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main()
{
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s",preO);
    scanf("%s",postO);

    BTNode* root=NULL;
    buildTree(&root,preO,postO);
    if(root==NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}
void inOrder(BTNode *cur){
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c",cur->id);
    inOrder(cur->right);
}
void preOrder(BTNode *cur){
    if (cur == NULL)
        return;

    printf("%c",cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}
void postOrder(BTNode *cur){
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c",cur->id);
}
int i = 0; int j = 0;

int stringLength(char* string) {
    int len = 0;
    while (string[len] != '\0') {
        len++;
    }
    return len;
}

void insertBTNode(BTNode* cur, char id){
	BTNode* node = (BTNode*) malloc(sizeof(BTNode));
	node->id = id;
	node->left = node->right = NULL;
}

void buildTree(BTNode** node, char* preO, char* postO)
{
    (*node) = (BTNode*) malloc(sizeof(BTNode));
    BTNode* newNode = *node;
    newNode->id = preO[i];

    if (stringLength(preO) == 0 || stringLength(postO) == 0) {
        return;
    }

    if (newNode->id != postO[j]) {
        printf("newnode: %c, postO: %c, preO: %c \n", newNode->id, postO[j], preO[i]);
        newNode->id = preO[i];
        newNode->left = (BTNode*) malloc(sizeof(BTNode));
        i++;
        buildTree(&newNode->left, preO, postO);
    }

    if (newNode->id != postO[j]) {
        printf("newnode: %c, postO: %c, preO: %c \n", newNode->id, postO[j], preO[i]);
        newNode->id = preO[i];
        newNode->right = (BTNode*) malloc(sizeof(BTNode));
        i++;
        buildTree(&newNode->right, preO, postO);
    }

    j++;
    return;
}