#ifndef AVL_H_
#define AVL_H_

typedef struct avl_node_s avl_node_t;
typedef struct avl_tree_s avl_tree_t;

/* Create a new AVL tree. */
avl_tree_t *avl_create();

/* Balance a given tree */
void avl_balance( avl_tree_t *tree );

/* Insert a new node. */
void avl_insert( avl_tree_t *tree, char* value );

/* Find the node containing a given value */
avl_node_t *avl_find( avl_tree_t *tree, char* value );

/* Do a depth first traverse of a node. */
void avl_traverse_node_dfs( avl_node_t *node, int depth );

/* Print in order */
void preorder (avl_node_t *t);


#endif