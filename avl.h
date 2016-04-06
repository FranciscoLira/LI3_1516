#ifndef AVL_H_  
#define AVL_H_

typedef struct avl_node_s avl_node_t;
typedef struct avl_tree_s avl_tree_t;

/* Create a new AVL tree. */
avl_tree_t *avl_create();
/* Initialize a new node. */
int avl_node_height( avl_node_t *node ) ;
/* Insert a new node. */
void avl_insert( avl_tree_t *tree, int value );
/* Find the node containing a given value */
avl_node_t *avl_find( avl_tree_t *tree, int value );

#endif 

