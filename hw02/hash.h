struct dnode{
    int key;
    struct dnode *next;
};
struct dnode *l_insert(struct dnode *L, int word);
void l_find(struct dnode *L, int word);
void hash_insert(struct dnode**hTab, int maxHash, int key);
void hash_find(struct dnode**hTab, int maxHash, int key);
void hash(int repeat, int make);
