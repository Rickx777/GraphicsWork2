#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define width 500
#define height 500
#define maxcolor 255

typedef struct pixel {
  int r;
  int g;
  int b;
} pixel;

typedef struct pixel screen[width][height];

void pix(pixel,char*);
void tofile(screen, FILE* );
void newdisplay(screen, pixel);
void drawline(int,int,int,int,screen,pixel);
void drawheart(screen,pixel);
void drawmultiple(int*, screen,pixel,int);
