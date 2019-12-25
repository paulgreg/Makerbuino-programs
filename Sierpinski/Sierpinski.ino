#include <SPI.h>
#include <Gamebuino.h>
#include <math.h>
Gamebuino gb;

void setup()
{
  gb.begin();
  gb.titleScreen(F("Sierpinski"));
}

void input()
{
  if(gb.buttons.pressed(BTN_C))
    gb.titleScreen(F("Sierpinski"));
}

void update()
{
}

void mid(int p1[], int p2[], int pp[]) {
  pp[0] = (int) round((p1[0] + p2[0]) / 2);
  pp[1] = (int) round((p1[1] + p2[1]) / 2);
}

void triangle(int color, int p1[], int p2[], int p3[]) {
  gb.display.setColor(color);
  gb.display.fillTriangle(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1]);  
}


void Sierpinski(int depth, int p1[], int p2[], int p3[]) 
{ 
  int pp1[2], pp2[2], pp3[2];
  mid(p1, p2, pp1);
  mid(p1, p3, pp2);
  mid(p2, p3, pp3);

  triangle(WHITE, pp1, pp2, pp3);

  if (depth == 0) return;

  Sierpinski(depth - 1, pp1, p2, pp3);
  Sierpinski(depth - 1, p1, pp1, pp2);
  Sierpinski(depth - 1, pp2, pp3, p3);
} 

boolean drawn = false;

void draw()
{
  gb.display.persistence = true;
  if (!drawn) {
    int depth = 2;
    int p1[] = { (int) round(LCDWIDTH / 2), 0 };
    int p2[] = { 0, LCDHEIGHT };
    int p3[] = { LCDWIDTH, LCDHEIGHT };

    triangle(BLACK, p1, p2, p3);

    Sierpinski(depth, p1, p2, p3);
    drawn = true;
  }
}


void loop()
{
  if (gb.update()){
    input();
    update();
    draw();
  }
}
