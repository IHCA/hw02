struct tnode{
    int num;
    struct tnode *left;
    struct tnode *right;
};
void bst_find(struct tnode *arr, int key);
struct tnode *bst_insert(struct tnode *arr, int key);
void bst(int repeat, int make);
