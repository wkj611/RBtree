#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct node *link;
struct node{
    int key;
    link l,r;
    int cl;
};
link NODE(int key,link l,link r,int cl){
    link root = malloc(sizeof(struct node));
    root->l = l;
    root->r = r;
    root->key = key;
    root->cl = cl;
    return root;
    
}
link null;
link init_null(){
    null = NODE(0,NULL,NULL,0);
    null->l = null;
    null->r = null;
    return null;
}
link rotL(link root){
    link x = root->r;
    root->r = x->l;
    x->l = root;
    x->cl = root->cl;
    root->cl = 1;
    return x;
}
link rotR(link root){
    link x = root->l;
    root->l = x->r;
    x->r = root;
    x->cl = root->cl;
    root->cl = 1;
    return x;
}
link  changecl(link root){
    root->l->cl = 0;
    root->r->cl = 0;
    root->cl = 1;
    return root;

}
link insert_node(link root,int key){
    if(root==null){
        return NODE(key,null,null,1);
    }
    if(key<root->key)
        root->l = insert_node(root->l,key);
    else 
        root->r = insert_node(root->r,key);
    if(!root->l->cl&&root->r->cl)root = rotL(root);
    if(root->l->cl&&root->l->l->cl)root = rotR(root);
    if(root->l->cl&&root->r->cl)root = changecl(root);
    return root;
}
link RB_insert(link root,int key){
    root = insert_node(root,key);
    root->cl = 0;
    return root;
}

void RB_display(link root){
    if(root!=null){
        RB_display(root->l);
        printf("%d  ",root->key);
        RB_display(root->r);
    }
}
#define N 16
void main(){
    link root;
    int i;
    srand(time(NULL));
    root = init_null();
    for(i=0;i<N;i++){
        root = RB_insert(root,rand()%100);
    }
    RB_display(root);
}
