#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

BTNode* insertBSTNode(BTNode* cur, int item);
void printBTNode(BTNode *root, int space,int left);
void deleteTree(BTNode **root);
int removeBSTNode(BTNode **nodePtr, int item);

int main()
{
    BTNode* root=NULL;
    int item;

    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        root = insertBSTNode(root, item);
    scanf("%*s");

    printf("The Binary Search Tree:\n");
    printBTNode(root,0,0);

    printf("Enter an integer to be removed from the tree:\n");
    scanf("%d",&item);

    if(removeBSTNode(&root,item))
       printf("%d was removed\n",item);

    else
       printf("%d is not in the tree.\n",item);

    printf("The Binary Search Tree:\n");
    printBTNode(root,0,0);

    deleteTree(&root);
    root=NULL;
    return 0;
}

BTNode* insertBSTNode(BTNode* cur, int item){
    if (cur == NULL){
        BTNode* node = (BTNode*) malloc(sizeof(BTNode));
    	node->item = item;
    	node->left = node->right = NULL;
    	return node;
	}
    if (item < cur->item)
        cur->left  = insertBSTNode (cur->left, item);
    else if (item > cur->item)
        cur->right = insertBSTNode (cur->right, item);
    else
        printf("Duplicated Item: %d\n",item);

    return cur;
}

void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->item);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

void deleteTree(BTNode **root){
    if (*root != NULL)
	{
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}

// BTNode* findSmallest(BTNode *node){
//     printf("right tree %d \n", node->item);
//     if (node->left == NULL) return node;
//     findSmallest(node->left);

// }

// BTNode* findLargest(BTNode *node){
//     printf("left tree %d \n", node->item);
//     if (node->right == NULL) return node;
//     findLargest(node->right);
// }

int removeBSTNode(BTNode **nodePtr, int item){
    //Write Your Code Here
    // consider 3 cases:
    // 1. node has no children
    // 2. node has one child node
    // 3. node has two child nodes

    BTNode *node = *nodePtr;
    BTNode *temp;

    if (node == NULL) return 0;

    if (node->left && node->item > item) {
        removeBSTNode(temp->left,item);
    }
    if (node->right && node->item < item) {
        removeBSTNode(node->right,item);
    }
    else {
        if (node->right != NULL && node->left != NULL) {
            temp = node->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            node->item = temp->item;
            return removeBSTNode(node->left,temp->item);
        }
        else {
            temp = node;
            if (node->left) {
                node = node->left;
            } else {
                node = node->right;
            }
            free(temp);
            return 1;
        }
    }
    
}
