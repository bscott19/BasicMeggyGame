
//Etch a Sketch for meggy with clear slate and color changing capabilities

//Scrolling font intro derived from: MeggyJr_Font by Mark White
//Scrolling font intro a work in progress



#include <MeggyJrSimple.h>

int x, y, color;

unsigned long TimeNow, HoldTime;
int WaitTime;

boolean ScrollYes;
byte ColorBack, ColorFore;

int ScrollX;
byte BottomY, SpaceLen;
int ScrLen;

unsigned int ma[40];
unsigned int mm[25];
char Message[21];
byte ThisMess;

void setup() 
{
  MeggyJrSimpleSetup();

  //for scrolling intro text:

  LoadFont();
  ThisMess = 0;
  TranslateMessage();
  
  ScrollX = 1;
  ScrollYes = true;
  BottomY = 2;
  SpaceLen = 1;
      
  WaitTime = 130;
  HoldTime = millis();
  
  ScrollMessage();
  delay(200);

  //game setup:

  x = 7;
  y = 4;
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
  if(x > 7)
  {
  x = 7;
  }
  if (y > 7)
  {
    y = 7;
  }
  if (y < 0)
  {
    y = 0;
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


//-----------  Scrolling font intro derived from: MeggyJr_Font by Mark White . All code below this line ----------- 

void ScrollMessage() // scrolls message, paints game slate, updates screen
{
  unsigned int mmMask;
  byte i, j;
  int ScrollMax, CharNow, LineNow;
    
  ScrollMax = ((ScrLen * (SpaceLen + 3)-8));
  
  for (i=0;i<8;i++)
  {
    CharNow = int((ScrollX + i)/ (SpaceLen + 3));
    LineNow = (ScrollX + i) % (SpaceLen + 3);
    mmMask = ma[mm[CharNow]];
    
    switch (LineNow)  // I tried everything but could never get "pow()" to work here, so I used brute force
    {
      case 1:
        if (mmMask & 1) {DrawPx(i,0 + BottomY,ColorFore);} else {DrawPx(i,0 + BottomY,ColorBack);}
        if (mmMask & 2) {DrawPx(i,1 + BottomY,ColorFore);} else {DrawPx(i,1 + BottomY,ColorBack);}
        if (mmMask & 4) {DrawPx(i,2 + BottomY,ColorFore);} else {DrawPx(i,2 + BottomY,ColorBack);}
        if (mmMask & 8) {DrawPx(i,3 + BottomY,ColorFore);} else {DrawPx(i,3 + BottomY,ColorBack);}
        if (mmMask & 16) {DrawPx(i,4 + BottomY,ColorFore);} else {DrawPx(i,4 + BottomY,ColorBack);}
        break;
      case 2:
        if (mmMask & 32) {DrawPx(i,0 + BottomY,ColorFore);} else {DrawPx(i,0 + BottomY,ColorBack);}
        if (mmMask & 64) {DrawPx(i,1 + BottomY,ColorFore);} else {DrawPx(i,1 + BottomY,ColorBack);}
        if (mmMask & 128) {DrawPx(i,2 + BottomY,ColorFore);} else {DrawPx(i,2 + BottomY,ColorBack);}
        if (mmMask & 256) {DrawPx(i,3 + BottomY,ColorFore);} else {DrawPx(i,3 + BottomY,ColorBack);}
        if (mmMask & 512) {DrawPx(i,4 + BottomY,ColorFore);} else {DrawPx(i,4 + BottomY,ColorBack);}
        break;
      case 3:
        if (mmMask & 1024) {DrawPx(i,0 + BottomY,ColorFore);} else {DrawPx(i,0 + BottomY,ColorBack);}
        if (mmMask & 2048) {DrawPx(i,1 + BottomY,ColorFore);} else {DrawPx(i,1 + BottomY,ColorBack);}
        if (mmMask & 4096) {DrawPx(i,2 + BottomY,ColorFore);} else {DrawPx(i,2 + BottomY,ColorBack);}
        if (mmMask & 8192) {DrawPx(i,3 + BottomY,ColorFore);} else {DrawPx(i,3 + BottomY,ColorBack);}
        if (mmMask & 16384) {DrawPx(i,4 + BottomY,ColorFore);} else {DrawPx(i,4 + BottomY,ColorBack);}
        break;  
      default:
        for (j=0;j<5;j++) {DrawPx(i,j + BottomY,ColorBack);}
        break;
    }
  }
  ScrollX++;
  if (ScrollX > ScrollMax){ScrollX = 1;}
  DisplaySlate();
}

void TranslateMessage() // reads the message string and translates it into usable font
{
  byte j, i;
  
  switch (ThisMess) {
    case 0:
      strcpy(Message, "etch a sketch");
      ScrLen = 11; 
      ColorBack = Dark;
      ColorFore = Red;
      break;
  }
    
  mm[0] = 38;
  mm[1] = 38;
  mm[ScrLen + 1] = 38;
  mm[ScrLen + 2] = 38;
  mm[ScrLen + 3] = 38;
  
  i=0;
  while (i<ScrLen)
  {
    j = Message[i];
    mm[i + 2] = 39;
    if (j == 32){mm[i + 2] = 38;}
    if ((j>47) && (j<58)){mm[i + 2] = j-48;}
    if ((j>64) && (j<91)){mm[i + 2] = j-55;}    
    if ((j>96) && (j<123)){mm[i + 2] = j-87;}    
    i++;  
  }
  ScrLen += 4;
  DrawBox(0,0,8,8,ColorBack);
}

void SetChar(byte CI, boolean P1, boolean P2, boolean P3, boolean P4, boolean P5, boolean P6, boolean P7, boolean P8, boolean P9, boolean P10, boolean P11, boolean P12, boolean P13, boolean P14, boolean P15)
{  // sets each bit in an integer to represent a character
  
  ma[CI] = 0;
  if (P1) {ma[CI] = ma[CI] | 16;}
  if (P2) {ma[CI] = ma[CI] | 512;}
  if (P3) {ma[CI] = ma[CI] | 16384;}
  if (P4) {ma[CI] = ma[CI] | 8;}
  if (P5) {ma[CI] = ma[CI] | 256;}
  if (P6) {ma[CI] = ma[CI] | 8192;}
  if (P7) {ma[CI] = ma[CI] | 4;}
  if (P8) {ma[CI] = ma[CI] | 128;}
  if (P9) {ma[CI] = ma[CI] | 4096;}
  if (P10) {ma[CI] = ma[CI] | 2;}
  if (P11) {ma[CI] = ma[CI] | 64;}
  if (P12) {ma[CI] = ma[CI] | 2048;}
  if (P13) {ma[CI] = ma[CI] | 1;}
  if (P14) {ma[CI] = ma[CI] | 32;}
  if (P15) {ma[CI] = ma[CI] | 1024;}
}

void LoadFont() // defines the bits to be set in each character
{
  SetChar(0, 1,1,1, 1,0,1, 1,0,1, 1,0,1, 1,1,1); // "0"
  SetChar(1, 0,1,0, 1,1,0, 0,1,0, 0,1,0, 1,1,1); // "1"
  SetChar(2, 0,1,0, 1,0,1, 0,0,1, 0,1,0, 1,1,1); // "2"
  SetChar(3, 1,1,1, 0,0,1, 1,1,0, 0,0,1, 1,1,1); // "3"
  SetChar(4, 1,0,1, 1,0,1, 1,1,1, 0,0,1, 0,0,1); // "4"
  SetChar(5, 1,1,1, 1,0,0, 1,1,0, 0,0,1, 1,1,1); // "5"
  SetChar(6, 1,0,0, 1,0,0, 1,1,1, 1,0,1, 1,1,1); // "6"
  SetChar(7, 1,1,1, 0,0,1, 0,0,1, 0,0,1, 0,0,1); // "7"
  SetChar(8, 1,1,1, 1,0,1, 1,1,1, 1,0,1, 1,1,1); // "8"
  SetChar(9, 1,1,1, 1,0,1, 1,1,1, 0,0,1, 0,0,1); // "9"
  
  SetChar(10, 0,1,0, 1,0,1, 1,0,1, 1,1,1, 1,0,1); // "A"
  SetChar(11, 1,1,0, 1,0,1, 1,1,0, 1,0,1, 1,1,0); // "B"
  SetChar(12, 0,1,1, 1,0,0, 1,0,0, 1,0,0, 0,1,1); // "C"
  SetChar(13, 1,1,0, 1,0,1, 1,0,1, 1,0,1, 1,1,0); // "D"
  SetChar(14, 1,1,1, 1,0,0, 1,1,0, 1,0,0, 1,1,1); // "E"
  SetChar(15, 1,1,1, 1,0,0, 1,1,1, 1,0,0, 1,0,0); // "F"
  SetChar(16, 0,1,1, 1,0,0, 1,1,1, 1,0,1, 0,1,1); // "G"
  SetChar(17, 1,0,1, 1,0,1, 1,1,1, 1,0,1, 1,0,1); // "H"
  SetChar(18, 1,1,1, 0,1,0, 0,1,0, 0,1,0, 1,1,1); // "I"
  SetChar(19, 0,0,1, 0,0,1, 0,0,1, 1,0,1, 1,1,1); // "J"
  SetChar(20, 1,0,1, 1,1,0, 1,1,0, 1,0,1, 1,0,1); // "K"
  SetChar(21, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,1,1); // "L"
  SetChar(22, 1,0,1, 1,1,1, 1,1,1, 1,0,1, 1,0,1); // "M"
  SetChar(23, 1,1,0, 1,0,1, 1,0,1, 1,0,1, 1,0,1); // "N"
  SetChar(24, 1,1,1, 1,0,1, 1,0,1, 1,0,1, 1,1,1); // "O"
  SetChar(25, 1,1,1, 1,0,1, 1,1,1, 1,0,1, 1,0,1); // "P"
  SetChar(26, 1,1,1, 1,0,1, 1,1,1, 1,1,1, 0,0,1); // "Q"
  SetChar(27, 1,1,0, 1,0,1, 1,1,0, 1,0,1, 1,0,1); // "R"
  SetChar(28, 0,1,1, 1,0,0, 0,1,0, 0,0,1, 1,1,0); // "S"
  SetChar(29, 1,1,1, 0,1,0, 0,1,0, 0,1,0, 0,1,0); // "T"
  SetChar(30, 1,0,1, 1,0,1, 1,0,1, 1,0,1, 1,1,1); // "U"
  SetChar(31, 1,0,1, 1,0,1, 1,0,1, 1,1,1, 0,1,0); // "V"
  SetChar(32, 1,0,1, 1,0,1, 1,1,1, 1,1,1, 1,0,1); // "W"
  SetChar(33, 1,0,1, 1,0,1, 0,1,0, 1,0,1, 1,0,1); // "X"
  SetChar(34, 1,0,1, 1,0,1, 0,1,0, 0,1,0, 0,1,0); // "Y"
  SetChar(35, 1,1,1, 0,0,1, 0,1,0, 1,0,0, 1,1,1); // "Z"
  
  SetChar(38, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0); // " "
  SetChar(39, 1,1,1, 1,1,1, 1,1,1, 1,1,1, 1,1,1); // " "
  
//SetChar(1, 0,0,0, 1,0,0, 1,1,0, 1,0,0, 1,0,0); // "1"
}

// Draw a box of pixels
void DrawBox (byte ThisX, byte ThisY, byte ThisW, byte ThisH, byte ThisColor)
{
  byte i, iW, j, jH;
  i = ThisX;
  iW = (i + ThisW);
     
   while (i < iW){
      j = ThisY;
      jH = (j + ThisH);
        while ( j < jH){
          DrawPx(i,j,ThisColor);
          j++;
        }
   i++;
   }
}
