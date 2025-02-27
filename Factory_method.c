#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    void(*draw)();
}shape;

typedef struct
{
    shape base;
}circle;
void draw_circle()
{
    printf("draw the circle\n");
}
circle* create_circle()
{
    circle *circle1=(circle*)malloc(sizeof(circle));
    circle1->base.draw=draw_circle;
    return circle1;
}

typedef struct
{
    shape base;
}square;
void draw_square()
{
    printf("draw the sqaure\n");
};
square* create_square()
{
    square *square1=(square*)malloc(sizeof(square));
    square1->base.draw=draw_square;
    return square1;
}

int main()
{
    circle *circle1=create_circle();
    circle1->base.draw();
    square *square1=create_square();
    square1->base.draw();
}