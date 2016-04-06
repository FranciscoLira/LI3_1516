#ifndef AVL_H_  
#define AVL_H_

typedef struct node *Node;
struct node
{
    char key[10];
    struct node *left;
    struct node *right;
    int height;
};
int height(Node N);
 
int max(int a, int b);

Node newNode(char* key);
 
Node rightRotate(Node y);
 
Node leftRotate(Node x);

 
int getBalance(Node N);
 
Node insert(Node node, char* key);
 

Node minValueNode(Node node);
 
Node deleteNode(Node root, char* key);
 
void preOrder(Node root);




#endif 

