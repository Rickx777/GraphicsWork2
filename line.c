#include "line.h"



int main(){
  screen a;
  pixel def;
  
  def.r = 255; def.g = 255; def.b = 255;  
  newdisplay(a,def); //set array to this.

  def.r = 53; def.g = 88; def.b = 200;
  drawheart(a, def);
  
  FILE *newim = fopen("image.ppm","w");
  tofile(a,newim);
  
  printf("Line created!\n");
  return 0;
}

void pix(pixel c, char* buff){
  strcpy(buff,"");
  snprintf(buff,64,"%d %d %d ", c.r, c.g, c.b);
}

void tofile(screen c, FILE* newim){
  int x;
  int y = height - 1;
  char buff[64];
  
  snprintf(buff,64,"P3 %d %d %d ",width,height,maxcolor);
  fprintf(newim,buff);

  while (y >= 0){
    x = 0;
    while (x < width){
      pix(c[x][y],&buff);
      fprintf(newim,buff);
      x++;
    }
    y--;
  }
  fprintf(newim,"\n");
}

void newdisplay(screen c, pixel b){
  int x = 0;
  int y = 0;
  while (y < height){
    x = 0;
    while(x < width){
      c[x][y] = b;
      x++;
    }
    y++;
  }
}

void drawline(int x0, int y0, int x1, int y1, screen c, pixel b) {  
  int x = x0; int y = y0;
  int Ah = y1 - y0;
  int Bh = -(x1 - x0);
  int d;

  if (x1 < x0 || (y1 < y0 && x1 == x0)){ //x1 < x0
    x = x1; y = y1; //change x and y to y1 vals    
    x1 = x0; y1 = y0; //change x1 to x0 and y1 to y0 vals
    Ah = y1 - y; //adjust values
    Bh = -(x1 - x);
    //printf("Ah: %d Bh: %d\n", Ah, Bh);
  }

  if(Ah == 0){
    while (x <= x1){
      c[x][y] = b;
      x++;
    }
  }
  
  else if(Bh == 0){    
    //printf("Ah: %d Bh: %d\n", Ah, Bh);
    while (y <= y1){
      c[x][y] = b;
      y++;
    }
  }
  
  else if( (Ah/(-Bh)) == 0 && Ah > 0){ //I
    d = 2*Ah + Bh;
    
    while (x <= x1){
      c[x][y] = b;
      if (d > 0){
	y++;
	d+= 2*Bh;
      }
      x++;
      d += 2*Ah;
    }
  }

  else if ( (Ah/(-Bh)) > 0 && Ah > 0){ //II
    d = 2*Bh + Ah;
    
    while (y <= y1){
      c[x][y] = b;
      if (d < 0){	
	x++;
	d += 2*Ah;
      }
    y++;
    d += 2*Bh;
    }
  }

  else if ( (Ah/(-Bh)) == 0 && Ah < 0){ //VIII
    d = -2*Ah + Bh;

    while (x <= x1){
      c[x][y] = b;
      if (d < 0){
	y--;
	d -= 2*Bh; 
      }
      x++;
      d += 2*Ah;
    }    
  }

  else{ //VII
    d = -2*Bh + Ah;

    while(y > y1){
      c[x][y] = b;
      if (d > 0){
	x++;
	d += 2*Ah;
      }
      y--;
      d -= 2*Bh;
    }
  }
}

void drawheart(screen c, pixel b){
  int heart[] = {60,140,40,160,30,160,10,150,0,130,0,100,10,80,30,60,60,30,90,60,110,80,120,100,120,130,110,150,90,160,80,160,60,140,40,160,60,140};
  int ctr = 0;
  int adj = 0;
  
  while (ctr < (sizeof(heart)/sizeof(heart[0]))){
    if (ctr % 2) heart[ctr] += 30;
    if (!(ctr % 2)) heart[ctr] += 20;
    heart[ctr] *= 2;
    ctr++; 
  }  
  drawmultiple(heart,c,b,sizeof(heart)/sizeof(heart[0]));

  ctr = 0;
  while (ctr < 20){
    adj = 0;
    while (adj < (sizeof(heart)/sizeof(heart[0]))){
      heart[adj] += 1;
      adj++;
    }
    drawmultiple(heart,c,b,sizeof(heart)/sizeof(heart[0]));
    ctr++;
  }
  
}

void drawmultiple(int* a,screen c, pixel b, int size){
  int first[2];
  int ctr;
  int x0; int y0; int x1; int y1;
  
  if (size % 2) {
    printf("Odd number of coordinates! This can't do!\n");
    return;
  }

  ctr = 0;
  size -= 2;
  while (ctr < size){
    x0 = a[ctr]; y0 = a[ctr + 1];
    x1 = a[ctr + 2]; y1 = a[ctr + 3];
    //printf("%d %d %d %d\n",x0,y0,x1,y1);
    //printf("ctr: %d n: %d\n",ctr,size);    
    drawline(x0,y0,x1,y1,c,b);    
    ctr += 2;
  }
}
