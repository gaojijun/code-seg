// http://hihocoder.com/problemset/problem/1040
// Key word: rectangle, macro, parallel, perpendicular, cross point

#include <stdio.h>

#define noLine(l) (l.x1==l.x2 && l.y1==l.y2)
#define PL(l1,l2) ( (l1.y1 - l1.y2) * (l2.x1 - l2.x2) == \
                    (l1.x1 - l1.x2) * (l2.y1 - l2.y2) ) // check if parallel
#define PE(l1,l2) ( (l1.y1 - l1.y2) * (l2.y1 - l2.y2) == \
                    (l1.x1 - l1.x2) * (l2.x1 - l2.x2) * (-1) )// check if perpendicular
#define PBL(l,x,y) ( (l.y2 - l.y1) * (x - l.x1) + (l.y1 - y) * (l.x2 - l.x1) ) // point below or above line

// Is there a cross point
#define CP(l1, l2) ( ( PBL(l1, l2.x1, l2.y1) * PBL(l1, l2.x2, l2.y2) <=0 ) && \
                     ( PBL(l2, l1.x1, l1.y1) * PBL(l2, l1.x2, l1.y2) <=0 ) )
// there are four cross points
#define FCP(l1, l2, l3, l4)   ( CP(l1, l3) && CP(l1, l4) && CP(l2, l3) && CP(l2, l4) )

typedef struct Line{
    int x1,y1,x2,y2;
}Line;

int is_rectangle(Line l[]){
    int i;
    for(i=1;i<5;i++) if ( noLine(l[i]) ) return 0;
    if      ( PL(l[1], l[2]) && PL(l[3], l[4]) && PE(l[1], l[3]) ) return FCP(l[1], l[2], l[3], l[4]);
    else if ( PL(l[1], l[3]) && PL(l[2], l[4]) && PE(l[1], l[2]) ) return FCP(l[1], l[3], l[2], l[4]);  
    else if ( PL(l[1], l[4]) && PL(l[2], l[3]) && PE(l[1], l[2]) ) return FCP(l[1], l[4], l[2], l[3]);  
    else return 0;
}

int main() {
    int T, i;
    Line lines[5], *l;
    scanf("%d", &T);
    while(T--) {
        for(i=1;i<=4;i++) {
            l = &lines[i];
            scanf("%d%d%d%d", &l->x1, &l->y1, &l->x2, &l->y2); 
        }
        if ( is_rectangle(lines) ) printf("YES\n");
        else printf("NO\n");
    }
}
