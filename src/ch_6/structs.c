
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

#define max(a,b) ( ((a) > (b)) ? (a) : (b) )
#define min(a,b) ( ((a) < (b)) ? (a) : (b) )

struct point {
    int x;
    int y;
};
struct rect {
    struct point pt1;
    struct point pt2;
};
struct rect screen;

struct point makepoint(int, int);
struct point addpoint(struct point, struct point);
int pt_in_rect(struct point, struct rect);
void canonrect(struct rect);


struct point makepoint(int x, int y) {
    
    struct point pt;
    pt.x = x;
    pt. y = y;
    return pt;
}


struct point addpoint(struct point pt1, struct point pt2) {
    
    struct point pt;
    pt.x = pt1.x + pt2.x;
    pt.y = pt2.x + pt2.y;
    return pt;
}


int pt_in_rect(struct point pt, struct rect rt) {
// Checks whether a point is in a rectangle

    int within_x, within_y;

    within_x = pt.x >= rt.pt1.x  && pt.x < rt.pt2.x;
    within_y = pt.y >= rt.pt1.y  && pt.y < rt.pt2.y;
    return (within_x && within_y);
}


void canonrect (struct rect rt) {
// Canonicalizes coordinates of a `rt`

    rt.pt1.x = min(rt.pt1.x, rt.pt2.x);
    rt.pt1.y = min(rt.pt1.y, rt.pt2.y);
    rt.pt2.x = max(rt.pt1.x, rt.pt2.x);
    rt.pt2.y = max(rt.pt1.y, rt.pt2.y);
}


int main() {
   
    struct point pt;
    pt.x = 2;

    struct rect rt, *p_rt;
    p_rt = &rt;
    p_rt->pt1.x = 2;
    p_rt->pt2.x = 1;
    p_rt->pt1.y = 2;
    p_rt->pt2.y = 1;
    canonrect(*p_rt);

}