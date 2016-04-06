#ifndef AVL_H_
#define AVL_H_

struct avl_node_s {
    struct avl_node_s *left;
    struct avl_node_s *right;
    char value[10];
};

typedef struct avl_node_s avl_node_t;

struct avl_tree_s {
    struct avl_node_s *root;
};

typedef struct avl_tree_s avl_tree_t;


/* Create a new AVL tree. */
avl_tree_t *avl_create();

/* Initialize a new node. */
avl_node_t *avl_create_node();

/* Find the height of an AVL node recursively */
int avl_node_height( avl_node_t *node );


/* Find the balance of an AVL node */
int avl_balance_factor( avl_node_t *node );

/* Left Left Rotate */
avl_node_t *avl_rotate_leftleft( avl_node_t *node );

/* Left Right Rotate */
avl_node_t *avl_rotate_leftright( avl_node_t *node );

/* Right Left Rotate */
avl_node_t *avl_rotate_rightleft( avl_node_t *node );

/* Right Right Rotate */
avl_node_t *avl_rotate_rightright( avl_node_t *node );

/* Balance a given node */
avl_node_t *avl_balance_node( avl_node_t *node );

/* Balance a given tree */
void avl_balance( avl_tree_t *tree );

/* Insert a new node. */
void avl_insert( avl_tree_t *tree, char* value );

/* Find the node containing a given value */
avl_node_t *avl_find( avl_tree_t *tree, char* value );

/* Do a depth first traverse of a node. */
void avl_traverse_node_dfs( avl_node_t *node, int depth );

/* Do a depth first traverse of a tree. */
void avl_traverse_dfs( avl_tree_t *tree );
void preorder (avl_node_t *t);


#endif