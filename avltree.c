#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"



int height(Node N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
Node newNode(char* key)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    strcpy(node->key,key);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    return(node);
}
 
Node rightRotate(Node y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    return x;
}
 
Node leftRotate(Node x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    return y;
}
 
int getBalance(Node N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
Node insert(Node node, char* key)
{
    int balance;
    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    node->height = max(height(node->left), height(node->right)) + 1;
    balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
Node minValueNode(Node node)
{
    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
Node deleteNode(Node root, char* key)
{
    int balance;
    if (root == NULL)
        return root;
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct node *temp = root->left ? root->left : root->right;
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else 
             *root = *temp; 
            free(temp);
        }
        else
        {
            struct node* temp = minValueNode(root->right);
            strcpy(root->key,temp->key);
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (root == NULL)
      return root;
    root->height = max(height(root->left), height(root->right)) + 1;
    balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}
 
void preOrder(Node root)
{
    if(root != NULL)
    {
        printf("%s ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
 
/* Drier program to test above function*/
/*int main()
{
    Node root = NULL;
    root = insert(root, "XN111");
    root = insert(root, "xn22");
    root = insert(root, "asf");
    root = insert(root, "ola");
    root = insert(root, "asf");
    root = insert(root, "asfa");
    root = insert(root, "jasnfkjasnf");
    root = insert(root, "KJHABFJHASDBF");
    root = insert(root, "kjahsdf");
    printf("Pre order traversal of the constructed AVL tree is \n");
    preOrder(root);
    printf("\nPre order traversal after deletion of 10 \n");
    preOrder(root);
    return 0;
}*/