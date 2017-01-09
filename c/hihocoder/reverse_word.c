// http://hihocoder.com/problemset/problem/1366
// Key word: reverse word, hash table

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MULT 31
#define HASHSIZE 50021
typedef unsigned int uint;

typedef struct Node{
    char *s;
    struct Node *next;
}Node, *List;

uint hashv(char *s){
    uint h=0;
    while ( *s )
        h = h * MULT + *s++;
    return h % HASHSIZE;
}

char *trans(char *s){
    int n = strlen(s);
    char *A = (char *)malloc(sizeof(char)*(n+1));
    char *p=s, *q=s+n-1, *pa=A;
    while ( *p==*q ) {
        *pa++ = *p++;
        q--;
    }
    if ( *p < *q )
        while( *p ) *pa++ = *p++;
    else{
        while( s<q ) *pa++ = *q--;
        *pa++ = *q;
    }
    *pa = '\0';
    return A;
}

int lookup(List hash[], char *s){
    uint h = hashv(s);
    List p, q, l;
    for ( p=hash[h]; p!=NULL; q=p, p=p->next ) {
        if ( strcmp(s, p->s) == 0 )
            break;
    }
    if ( p == NULL ) {
        l = (List)malloc(sizeof(Node));
        l->s = s;
        l->next = hash[h];
        hash[h] = l;
        return 0;
    } else {
        if ( p == hash[h] ) hash[h] = p->next;
        else q->next = p->next;
        free(s);
        free(p->s);
        free(p);
        return 1;
    }
}


int main() {
    int N, ans=0, i;
    List hash[HASHSIZE];
    for (i=0;i<HASHSIZE;i++) hash[i]=NULL;
    char s[17];
    scanf("%d", &N);
    while ( N-- ) {
        scanf("%s", s);
        // printf("%s\n%s\n", s, trans(s));
        if ( lookup(hash, trans(s)) ) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
