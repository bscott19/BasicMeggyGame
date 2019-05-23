
//4x4 etch a sketch for meggy with 3 duplicate kaleidoscope tiles . 

#include <MeggyJrSimple.h>

int x, y, mX, mY, color;

void setup() 
{
  MeggyJrSimpleSetup();

  x = 0;
  y = 4;
  mX = 0,
  color=1;
  Tone_Start(17500,300);
  delay(350);
  Tone_Start(17500,500);
  delay(500);
  Tone_Start(13000,800);
}

void loop()
{
  delay(150);
  DrawPx(x,y,color);
  CheckButtonsDown();
  MovePlayer();
  check();
  changecolor();
  DisplaySlate();
  clearslate();
  mirrorslate();
}

// -------------------------------

void MovePlayer()
{
  if(Button_Left)
  {
    x--;
  }
  if(Button_Right)
  {
    x++;
  }
  if(Button_Up)
  {
    y++;
  }
  if(Button_Down)
  {
    y--;
  }
}

void check()
{
  if(x < 0)
  {
    x = 0;
  }
  if(x > 3)
  {
  x = 3;
  }
  if (y > 7)
  {
    y = 7;
  }
  if (y < 4)
  {
    y = 4;
  }
}

void changecolor()
{
  if (Button_A)
  {
    color++;
    Tone_Start(1500,100);
    delay(110);
    Tone_Start(1300,80);
  }
  if (color>14)
  {
    color=1;
  }
  if (color<1)
  {
    color=14;
  }
}

void clearslate()
{
  if (Button_B)
  {
    ClearSlate();
    Tone_Start(18182,150);
    delay(150);
    Tone_Start(20000,125);
    delay(125);
    Tone_Start(30000,250);
  }
}

void mirrorslate()
{
  
}
