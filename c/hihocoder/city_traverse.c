// http://hihocoder.com/problemset/problem/1041
// Key word: Tree traverse

#include <stdio.h>
#include <stdlib.h>

#define white 0
#define red 1
#define black 2
#define OK 0
#define FAIL 1

typedef struct Node {
    int city;
    int color;
    struct Node *parent, *firstChild, *lastChild, *sibling;
} Node, *Tree;

Tree newNode(int city) {
    Tree t = (Tree)malloc(sizeof(Node)*1);
    t->city = city;
    t->color = white;
    t->parent = t->firstChild = t->lastChild = t->sibling = NULL;
    return t;
}

void addChild(Tree a, Tree b) {
    if ( !a->firstChild ) {
        a->firstChild = a->lastChild = b;
    } else {
        a->lastChild->sibling = b;
        a->lastChild = b;
    }
    b->parent = a;
}

void traverse(Tree p) {
    Tree q;
    for ( q=p->firstChild; q; q=q->sibling ) {
        traverse(q);
    }
    p->color = black;
    // printf("City %d becomes black!\n", p->city);
}

int process(Tree *cities, int city) {
    if ( cities[city]->color != white ) return FAIL;
    Tree p, q, pre;
    for ( p=cities[city]; p && p->color == white; p=p->parent ) {
        p->color = red;
        // printf("City %d becomes red!\n", p->city);
        pre = p;
    }
    if ( !p ) return OK;
    if ( p->color == black ) return FAIL;
    // p->color == red
    for ( q=p->firstChild; q; q=q->sibling ) {
        if ( q != pre && q->color == red ) traverse(q);
    }
    return OK;
}

int main(){
    int T, cityNum, i, citya, cityb, cityc, m, flag;
    Tree *cities;
    scanf("%d", &T);
    while(T--) {
        
        // build the city tree
        scanf("%d", &cityNum);
        cities = (Tree *)malloc(sizeof(Tree *)*(cityNum+1));
        for ( i=1; i<=cityNum; i++) {
            cities[i] = NULL;
        }
        for ( i=1; i<cityNum; i++) {
            scanf("%d%d", &citya, &cityb);
            if ( !cities[citya] ) cities[citya] = newNode(citya);
            if ( !cities[cityb] ) cities[cityb] = newNode(cityb);
            addChild(cities[citya], cities[cityb]);
        }

        // travel through cities
        scanf("%d", &m);
        flag = OK;
        while(m--) {
             scanf("%d", &cityc);
             if ( flag == OK && FAIL == process(cities, cityc) ) {
                 flag = FAIL;
             }
        }

        if ( flag == OK ) printf("YES\n");
        else printf("NO\n");

        for ( i=1; i<=cityNum; i++) {
            free(cities[i]);
        }
        free(cities);
    }
    return 0;
}
