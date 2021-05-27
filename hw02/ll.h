struct lnode{
    int num;
    struct lnode*next;
};
void link_find(struct lnode *arr, int key);
struct lnode* link_insert(struct lnode*arr,int key);
void link(int repeat, int make);
