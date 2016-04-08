#ifndef AVL_H_
#define AVL_H_


typedef int TreeKey;
typedef char TreeInfo;
typedef struct treenode *Tree;

Tree newAvl();
Tree insertTree(Tree t, TreeKey e, TreeInfo *i, int *cresceu);
Tree rotateRight(Tree t);
Tree insertRight(Tree t, TreeKey e, TreeInfo *i, int *cresceu);
Tree balanceRight(Tree t);
Tree rotateLeft(Tree t);
Tree insertLeft(Tree t, TreeKey e, TreeInfo *i, int *cresceu);
Tree balanceLeft(Tree t);
void preorder(Tree t);

#endif
