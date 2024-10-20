//------------------------YouTube-3DSage----------------------------------------
//Full video: https://www.youtube.com/watch?v=gYRrGTC7GtA 
//WADS to move player.

#include <stdlib.h>
#include </usr/include/GL/gl.h>
#include </usr/include/GL/glu.h>
#include </usr/include/GL/glut.h>
#include <math.h>
#define M_PI 3.14159265358979323846 

//-----------------------------MAP----------------------------------------------
#define mapX  8      //map width
#define mapY  8      //map height
#define mapS 64      //map cube size
int map[]=           //the map array. Edit to change level but keep the outer walls
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
};

void drawMap2D()
{
 int x,y,xo,yo;
 for(y=0;y<mapY;y++)
 {
  for(x=0;x<mapX;x++)
  {
   if(map[y*mapX+x]==1){ glColor3f(1,1,1);} else{ glColor3f(0,0,0);}
   xo=x*mapS; yo=y*mapS;
   glBegin(GL_QUADS); 
   glVertex2i( 0   +xo+1, 0   +yo+1); 
   glVertex2i( 0   +xo+1, mapS+yo-1); 
   glVertex2i( mapS+xo-1, mapS+yo-1);  
   glVertex2i( mapS+xo-1, 0   +yo+1); 
   glEnd();
  } 
 } 
}//-----------------------------------------------------------------------------


//------------------------PLAYER------------------------------------------------
float degToRad(int a) { return a*M_PI/180.0;}
int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}

float px,py,pdx,pdy,pa;

void drawPlayer2D()
{
 glColor3f(1,1,0);   
 glPointSize(8);    
 glLineWidth(4);
 glBegin(GL_POINTS); 
 glVertex2i(px,py); 
 glEnd();
 glBegin(GL_LINES);  glVertex2i(px,py); glVertex2i(px+pdx*20,py+pdy*20); glEnd();
}

void Buttons(unsigned char key,int x,int y)
{
 /*if(key=='a'){ pa+=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));} 	
 if(key=='d'){ pa-=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));} 
 if(key=='w'){ px+=pdx*5; py+=pdy*5;}
 if(key=='s'){ px-=pdx*5; py-=pdy*5;}*/
 if (key=='a') { pa-=0.1; if (pa<0) { pa+=2*M_PI; } pdx=cos(pa)*5; pdy=sin(pa)*5;} 
 if (key=='d'){ pa+=0.1; if (pa>2*M_PI) { pa-=2*M_PI; } pdx=cos(pa) *5; pdy=sin(pa) *5;}
 if (key=='w') { px+=pdx; py+=pdy;}
 if (key=='s') { px-=pdx; py-=pdy;}
 glutPostRedisplay();
}//-----------------------------------------------------------------------------


//---------------------------Draw Rays and Walls--------------------------------
float distance(ax,ay,bx,by,ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}

/*void drawRays2D()
{
 glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(526,  0); glVertex2i(1006,  0); glVertex2i(1006,160); glVertex2i(526,160); glEnd();	
 glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(526,160); glVertex2i(1006,160); glVertex2i(1006,320); glVertex2i(526,320); glEnd();	 	
	
 int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
 
 ra=FixAng(pa+30);                                                              //ray set back 30 degrees
 
 for(r=0;r<60;r++)
 {
  //---Vertical--- 
  dof=0; side=0; disV=100000;
  float Tan=tan(degToRad(ra));
       if(cos(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
  else if(cos(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
  else { rx=px; ry=py; dof=8;}                                                  //looking up or down. no hit  

  while(dof<8) 
  { 
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  vx=rx; vy=ry;

  //---Horizontal---
  dof=0; disH=100000;
  Tan=1.0/Tan; 
       if(sin(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up 
  else if(sin(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
  else{ rx=px; ry=py; dof=8;}                                                   //looking straight left or right
 
  while(dof<8) 
  { 
   mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
   if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
   else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  } 
  
  glColor3f(0,0.8,0);
  if(disV<disH){ rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}                  //horizontal hit first
  glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
    
  int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
  int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
  int lineOff = 160 - (lineH>>1);                                               //line offset
  
  glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineOff);glVertex2i(r*8+530,lineOff+lineH);glEnd();//draw vertical wall  

  ra=FixAng(ra-1);                                                              //go to next ray
 }
}*/

void drawRays2D()
{
    int r,mx, my, mp, dof; float rx, ry, ra, xo, yo;
    ra = pa;
    for (r = 0; r<1; r++)
    {
    //---Check Horizontal Lines---
    dof=0;
    float aTan=-1/tan (ra);
    if (ra>M_PI) { ry=(((int) py>>6) <<6)-0.0001; rx=(py-ry)*aTan+px; yo=-64; xo=-yo*aTan; }//looking up 
    if (ra<M_PI) { ry=(((int) py>>6) <<6)+64; rx=(py-ry)*aTan+px; yo=64; xo=-yo*aTan;}//looking down
    if (ra==0 || ra==M_PI) { rx=px; ry=py; dof=8;}//looking straight left or right 
    while (dof<8)
    {
        mx= (int) (rx)>>6; 
        my=(int) (ry) >>6; 
        mp = my*mapX+mx;
        if (mp<mapX*mapY && map[mp]==1){ dof=8;}//hit vall
        else {rx+=xo; ry+=yo; dof+=1;}//next line
    }
    glColor3f (0,1,0); glLineWidth (10); glBegin (GL_LINES); glVertex2i (px, py); glVertex2i (rx, ry); glEnd();
    /*//---Check Vertical Lines---
    dof=0;
    float nTan-tan (za);
    if (ra>P2 && ra<P3) { rx=(((int) px>>6) <<6)-0.0001; ry- (px-rx) *nTan+py; xo=-64; yo=-xo nTan;}//looking left if (ra<P2 || ra>P3) { rx-(((int) px>>6)<<6)+64; ry- (px-xx) *nTan+py; xo 64; yo=-xo*nTan; }//looking right
    if (ra || ra--PI) ( xx-px; xy-py: dof-8://looking straight up or down while (dof<8)
    (
    mx= (int) (xx)>>6; my-(int) (ry) >>6; mp my mapX+mx;
    if (mp<mapX*mapy && map [mp]=-1){ dof-;}//hit vall else{ xx+xo; xy+-yo; dof+-1; }*/
    }
}







//-----------------------------------------------------------------------------


void init()
{
 glClearColor(0.3,0.3,0.3,0);
 gluOrtho2D(0,1024,510,0);
 //px=150; py=400; pa=90;
 //pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa)); 
 px = 300;
 py = 300; 
 pdx = cos(pa)*5;
 pdy = sin(pa)*5;
}

void display()
{   
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 drawMap2D();
 drawPlayer2D();
 drawRays2D();
 glutSwapBuffers();  
}

int main(int argc, char* argv[])
{ 
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 glutInitWindowSize(1024,510);
 glutCreateWindow("YouTube-3DSage");
 init();
 glutDisplayFunc(display);
 glutKeyboardFunc(Buttons);
 glutMainLoop();
}
