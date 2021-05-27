int input[1000000];
int find[100000];
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/time.h>
#include"ll.h"
#include"arr.h"
#include"hash.h"
#include"bst.h"
#include"bs.h"
struct  timeval start;
struct  timeval end;
unsigned  long diff;
void array_find(int num[1000000], int k, int time){
    for(int i=0;i<time;i++){
        if(input[k]==num[i]){
            return;
        }
    }
}
void arr(int repeat, int make){
    int i, num[1000000];
    gettimeofday(&start, NULL);
    for(i=0;i<repeat;i++){
        num[i]=input[i];
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);
    gettimeofday(&start, NULL);
    for(i=0;i<make;i++){
        array_find(num, i, repeat);
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n\n", diff / 1000000.0);
}
void link_find(struct lnode *arr, int key){
    struct lnode *p=arr;
    while(p){
        if(p->num==key){
            return;
        }
        else p=p->next;
    }
}
struct lnode* link_insert(struct lnode*arr,int key){
    struct lnode* p;
    p=(struct lnode*)malloc(sizeof(struct lnode));
    p->num=key;
    if(arr==NULL){
        p->next=NULL;
    }
    else{
        p->next=arr;
    }
    return p;
}
void link(int repeat, int make){
    int i;
    struct lnode*arr=NULL;
    gettimeofday(&start, NULL);
    for(i=0;i<repeat;i++){
        arr=link_insert(arr,input[i]);
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);
    gettimeofday(&start, NULL);
    for(i=0;i<make;i++){
        link_find(arr, find[i]);
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n\n", diff / 1000000.0);
}
struct dnode *l_insert(struct dnode *L, int word){
    struct dnode *p;
    p=(struct dnode *)malloc(sizeof(struct dnode));
    p->key=word;
    p->next=L;
    return p;
}
void l_find(struct dnode *L, int word){
    struct dnode *p;
    if(L==NULL)return;
    p=L;
    while(p){
        if(p->key==word){
            return;
        }
        p=p->next;
    }
    return;
}
void hash_insert(struct dnode**hTab, int maxHash, int key){
    unsigned int hv;
    struct dnode *dptr;
    hv=key;
    hv=hv%maxHash;
    dptr=hTab[hv];
    hTab[hv]=l_insert(dptr, key);
}
void hash_find(struct dnode**hTab, int maxHash, int key){
    unsigned int hv;
    struct dnode *dptr;
    hv=key;
    hv=hv%maxHash;
    dptr=hTab[hv];
    l_find(dptr, key);
}
void hash(int repeat, int make){
    int i;
    struct dnode **hTab;
    int maxHash=1<<20;
    hTab=(struct dnode **)malloc(sizeof(struct dnode*)*maxHash);
    for(int i=0;i<maxHash;i++){
        hTab[i]=NULL;
    }
    gettimeofday(&start, NULL);
    for(i=0;i<repeat;i++){    
        hash_insert(hTab, maxHash, input[i]);
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);
    gettimeofday(&start, NULL);
    for(i=0;i<make;i++){
        hash_find(hTab, maxHash, find[i]);
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n\n", diff / 1000000.0);
}
void bst_find(struct tnode *arr, int key){
    if(arr==NULL)return;
    else if(key==arr->num){
        return;
    }
    else if(arr->num>key)bst_find(arr->left, key);
    else bst_find(arr->right, key);
}
struct tnode *bst_insert(struct tnode *arr, int key){
    struct tnode *p;
    if(arr==NULL){
        p=(struct tnode*)malloc(sizeof(struct tnode));
        p->num=key;
        p->left=NULL;
        p->right=NULL;
        return p;
    }
    else if(key<arr->num){
        arr->left=bst_insert(arr->left,key);
    }
    else{
        arr->right=bst_insert(arr->right,key);
    }
    return arr;
}
void bst(int repeat, int make){
    int i;
    struct tnode*arr=NULL;
    gettimeofday(&start, NULL);
    for(i=0;i<repeat;i++){
        arr=bst_insert(arr,input[i]);
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);
    gettimeofday(&start, NULL);
    for(i=0;i<make;i++){
        bst_find(arr, find[i]);
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n\n", diff / 1000000.0);
}
void binary_find(int num[1000000], int input, int repeat){
    int low=0, high=repeat, mid=repeat/2;
    while(low<=high){
        if(input==num[mid]){
            return;
        }
        else if(input>num[mid]){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
        mid=(low+high)/2;
    }
}
void binary(int repeat, int make){
    int num[1000000], j, i, tmp;
    gettimeofday(&start, NULL);
    for(i=0;i<repeat;i++){
        num[i]=input[i];
    }
    for(i=0;i<repeat;i++){
        for(j=0;j<repeat/2-1;j++){
            if(num[j]>num[j+1]){
                tmp=num[j];
                num[j]=num[j+1];
                num[j+1]=tmp;
            }
        }
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("building time: %f sec\n", diff / 1000000.0);
    gettimeofday(&start, NULL);
    for(i=0;i<make;i++){
        binary_find(num, find[i], repeat);
    }
    gettimeofday(&end, NULL);
    diff = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("query time: %f sec\n\n", diff / 1000000.0);
}
int main(int argc,char **argv){
    int i,repeat,make;
    srand(1);
    if(strcmp(argv[2],"1e4")==0){
        repeat=10000;
        for(i=0;i<10000;i++){
            input[i]=rand();
        }
    }
    else if(strcmp(argv[2],"1e5")==0){
        repeat=100000;
        for(i=0;i<100000;i++){
            input[i]=rand();
        }
    }
    else{
        repeat=1000000;
        for(i=0;i<1000000;i++){
            input[i]=rand();
        }
    }
    if(strcmp(argv[4],"1e3")==0){
        make=1000;
        for(i=0;i<1000;i++){
            find[i]=rand();
        }
    }
    else if(strcmp(argv[4],"1e4")==0){
        make=10000;
        for(i=0;i<10000;i++){
            find[i]=rand();
        }
    }
    else{
        make=100000;
        for(i=0;i<100000;i++){
            find[i]=rand();
        }
    }
    for(i=5;i<argc;i++){
        if(strcmp(argv[i],"-bst")==0){
            printf("bst:\n");
            bst(repeat, make);
        }
        if(strcmp(argv[i],"-bs")==0){
            printf("bs:\n");
            binary(repeat, make);
        }
        if(strcmp(argv[i],"-arr")==0){
            printf("arr:\n");
            arr(repeat, make);
        }
        if(strcmp(argv[i],"-ll")==0){
            printf("ll:\n");
            link(repeat, make);
        }
        if(strcmp(argv[i],"-hash")==0){
            printf("hash:\n");
            hash(repeat, make);
        }
    }
}
