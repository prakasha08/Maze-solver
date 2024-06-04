//#include "picoFF.h"

#include <Wire.h>
#include <SparkFun_VL6180X.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_TB6612.h>

#define AIN1 18
#define BIN1 20
#define AIN2 17
#define BIN2 21
#define PWMA 16
#define PWMB 22
#define STBY 19

Motor motor1 = Motor(AIN1, AIN2, PWMA, 1, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, 1, STBY);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define VL6180X_ADDRESS 0x29
#define NEWVL6180X_ADDRESS_1  0x30
#define NEWVL6180X_ADDRESS_2  0x31
#define Fsensor 9     // Sensor 1
#define Rsensor 13     // Sensor 2
#define Lsensor 11      // Sensor 3

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

VL6180xIdentification identification;
VL6180x sensor3(VL6180X_ADDRESS);
VL6180x sensor2(VL6180X_ADDRESS); 
VL6180x sensor1(VL6180X_ADDRESS);
int Front, Right, Left;
char word1 = 'A';
int wallError;

/***********************************HEADER***************************************/

char dir = 'N';
bool hasLwall;
bool hasFwall;
bool hasRwall;
int curXcordinate = 0;
int curYcordinate = 0;
int xCordinate;
int yCordinate;
int xprev=20;
int yprev=20;


int cells[16][16] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

int maze[16][16] = { { 14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14 },
                     { 13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13 },
                     { 12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12 },
                     { 11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11 },
                     { 10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10 },
                     { 9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9 },
                     { 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8 },
                     { 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7 },
                     { 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7 },
                     { 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8 },
                     { 9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9 },
                     { 10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10 },
                     { 11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11 },
                     { 12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12 },
                     { 13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13 },
                     { 14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14 } };

int flood[16][16] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

void updateDir(int changeVal) {
  
  if (changeVal == 1) {
    if (dir == 'N')
      dir = 'E';
    else if (dir == 'E')
      dir = 'S';
    else if (dir == 'S')
      dir = 'W';
    else if (dir == 'W')
      dir = 'N';
  }

  if (changeVal == 2) {
    if (dir == 'N')
      dir = 'W';
    else if (dir == 'W')
      dir = 'S';
    else if (dir == 'S')
      dir = 'E';
    else if (dir == 'E')
      dir = 'N';
  }
  
}

void updateCord() {

  if (dir == 'N')
    curXcordinate += 1;
  if (dir == 'W')
    curYcordinate -= 1;
  if (dir == 'S')
    curXcordinate -= 1;
  if (dir == 'E')
    curYcordinate += 1;
  
  //cout<<curXcordinate<<"  "<<curYcordinate;
}

void hasWall(int L,int R,int F) {
  if (L < 100)
    hasLwall = true;
  else
    hasLwall = false;

  if (F < 100)
    hasFwall = true;
  else
    hasFwall = false;

  if (R < 100)
    hasRwall = true;
  else
    hasRwall = false;
}

void updateWalls(int x, int y, int orient, bool L, bool R, bool F) {
  if (L && R && F) {
    if (orient == 'S') {
      cells[y][x] = 11;
    } else if (orient == 'E') {
      cells[y][x] = 12;
    } else if (orient == 'W') {
      cells[y][x] = 13;
    } else {
      cells[y][x] = 14;
    }
  } else if (L && R && !F) {
    if (orient == 'E' || orient == 'W') {
      cells[y][x] = 9;
    } else if (orient == 'N' || orient == 'S') {
      cells[y][x] = 10;
    }
  } else if (L && F && !R) {
    if (orient == 'W') {
      cells[y][x] = 5;
    } else if (orient == 'N') {
      cells[y][x] = 6;
    } else if (orient == 'E') {
      cells[y][x] = 7;
    } else {
      cells[y][x] = 8;
    }
  } else if (R && F && !L) {
    if (orient == 'S') {
      cells[y][x] = 5;
    } else if (orient == 'W') {
      cells[y][x] = 6;
    } else if (orient == 'N') {
      cells[y][x] = 7;
    } else {
      cells[y][x] = 8;
    }
  } else if (F) {
    if (orient == 'W') {
      cells[y][x] = 1;
    } else if (orient == 'S') {
      cells[y][x] = 2;
    } else if (orient == 'E') {
      cells[y][x] = 3;
    } else {
      cells[y][x] = 4;
    }
  } else if (L) {
    if (orient == 'N') {
      cells[y][x] = 1;
    } else if (orient == 'W') {
      cells[y][x] = 2;
    } else if (orient == 'S') {
      cells[y][x] = 3;
    } else {
      cells[y][x] = 4;
    }
  } else if (R) {
    if (orient == 'S') {
      cells[y][x] = 1;
    } else if (orient == 'E') {
      cells[y][x] = 2;
    } else if (orient == 'N') {
      cells[y][x] = 3;
    } else {
      cells[y][x] = 4;
    }
  } else {
    cells[y][x] = 15;
  }
}

bool isAccessible(int x, int y, int x1, int y1){
  if (x == x1 && y == y1) {
    return true;
  }
  if (x != x1 && y != y1) {
    return false;
  }
  

  if (x == x1) {
    if(y==(y1-1)){
      if (cells[y][x] == 1 || cells[y][x] == 2 || cells[y][x] == 4 || cells[y][x] == 5 || cells[y][x] == 6 || cells[y][x] == 9 || cells[y][x] == 13 || cells[y1][x1] == 2 || cells[y1][x1] == 3 || cells[y1][x1] == 4 || cells[y1][x1] == 7 || cells[y1][x1] == 8 || cells[y1][x1] == 9 || cells[y1][x1] == 12 || cells[y][x] == 15 || cells[y1][x1] == 15) {
        return true;
      }
      else if(cells[y][x] == 0 && cells[y1][x1] == 0){
        return true;
      }
      else{
        return false;
      }
    }
    else if(y==(y1+1)){
      if (cells[y][x] == 2 || cells[y][x] == 3 || cells[y][x] == 4 || cells[y][x] == 7 || cells[y][x] == 8 || cells[y][x] == 9 || cells[y][x] == 12 || cells[y1][x1] == 1 || cells[y1][x1] == 2 || cells[y1][x1] == 4 || cells[y1][x1] == 5 || cells[y1][x1] == 6 || cells[y1][x1] == 9 || cells[y1][x1] == 13 || cells[y][x] == 15 || cells[y1][x1] == 15) {
        return true;
      }
      else if(cells[y][x] == 0 && cells[y1][x1] == 0){
        return true;
      }
      else{
        return false;
      }
    }
    else{
      return false;
    }
  }
  else if (y == y1) {
    if(x==(x1-1)){
    if (cells[y][x] == 1 || cells[y][x] == 2 || cells[y][x] == 3 || cells[y][x] == 5 || cells[y][x] == 8 || cells[y][x] == 10 || cells[y][x] == 11 || cells[y1][x1] == 1 || cells[y1][x1] == 3 || cells[y1][x1] == 4 || cells[y1][x1] == 6 || cells[y1][x1] == 7 || cells[y1][x1] == 10 || cells[y1][x1] == 14 || cells[y][x] == 15 || cells[y1][x1] == 15) {
      return true;
    }
    else if(cells[y][x] == 0 && cells[y1][x1] == 0){
        return true;
      }
    else{
      return false;
    }
    }
    else if(x==(x1+1)){
      if (cells[y][x] == 1 || cells[y][x] == 3 || cells[y][x] == 4 || cells[y][x] == 6 || cells[y][x] == 7 || cells[y][x] == 10 || cells[y][x] == 14 || cells[y1][x1] == 1 || cells[y1][x1] == 2 || cells[y1][x1] == 3 || cells[y1][x1] == 5 || cells[y1][x1] == 8 || cells[y1][x1] == 10 || cells[y1][x1] == 11 || cells[y][x] == 15 || cells[y1][x1] == 15) {
      return true;
    }
    else if(cells[y][x] == 0 && cells[y1][x1] == 0){
        return true;
      }
    else{
      return false;
    }
    }
    else{
      return false;
  }
 }
 return false;
}

int getSurrounds(int x, int y) {
   int x3 = x - 1;
   int y3 = y;
   int x0 = x;
   int y0 = y +1;
   int x1 = x + 1;
   int y1 = y;
   int x2 = x;
   int y2 = y - 1;
   if (x1 >= 16)
      x1 = -1;
   if (y0 >= 16)
      y0 = -1;
  return (x0, y0, x1, y1, x2, y2, x3, y3);
}

void floodFill() {
    int front=0;
    int rear=0;
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      maze[i][j] = 0;
    }
  }

  int queue[520];
  maze[7][7] = 1;
  maze[8][7] = 1;
  maze[7][8] = 1;
  maze[8][8] = 1;
  queue[rear++] = 7;
  queue[rear++] = 7;
  queue[rear++] = 8;
  queue[rear++] = 7;
  queue[rear++] = 7;
  queue[rear++] = 8;
  queue[rear++] = 8;
  queue[rear++] = 8;
  while (front < rear) {
    int yrun = queue[front++];
    int xrun = queue[front++];
    int x3 = xrun - 1;
    int y3 = yrun;
    int x0 = xrun;
    int y0 = yrun +1;
    int x1 = xrun + 1;
    int y1 = yrun;
    int x2 = xrun;
    int y2 = yrun - 1;
    if (x1 >= 16)
        x1 = -1;
    if (y0 >= 16)
        y0 = -1;
    
    if(x0>=0 && y0>=0 && (isAccessible(xrun,yrun,x0,y0))){
      if (maze[y0][x0]==0){
        maze[y0][x0]=maze[yrun][xrun]+1;
        queue[rear++] = y0;
        queue[rear++] = x0;
      }
    }

    if(x1>=0 && y1>=0 && (isAccessible(xrun,yrun,x1,y1))){
      if (maze[y1][x1]==0){
        maze[y1][x1]=maze[yrun][xrun]+1;
        queue[rear++] = y1;
        queue[rear++] = x1;
      }
    }

    if(x2>=0 && y2>=0 && (isAccessible(xrun,yrun,x2,y2))){
      if (maze[y2][x2]==0){
        maze[y2][x2]=maze[yrun][xrun]+1;
        queue[rear++] = y2;
        queue[rear++] = x2;
      }
    }
    if(x3>=0 && y3>=0 && (isAccessible(xrun,yrun,x3,y3))){
      if (maze[y3][x3]==0){
        maze[y3][x3]=maze[yrun][xrun]+1;
        queue[rear++] = y3;
        queue[rear++] = x3;
      }
    }
  }
}

char nextCell(){
  int out[4]={1000,1000,1000,1000};
  int yrun = curYcordinate;
  int xrun = curXcordinate;
  int x3 = xrun - 1;
  int y3 = yrun;
  int x0 = xrun;
  int y0 = yrun +1;
  int x1 = xrun + 1;
  int y1 = yrun;
  int x2 = xrun;
  int y2 = yrun - 1;
  if (x1 >= 16)
    x1 = -1;
  if (y0 >= 16)
    y0 = -1;
  
  if ((x0>=0)&&(y0>=0)&&(isAccessible(xrun,yrun,x0,y0))&&maze[y0][x0]<maze[yrun][xrun]){
    if (!((xprev==x0)&&(yprev==y0))){
      out[0]=maze[y0][x0];
    }else{
      out[0]=999;
    }
  }
  if ((x1>=0)&&(y1>=0)&&(isAccessible(xrun,yrun,x1,y1))&&maze[y1][x1]<maze[yrun][xrun]){
    if (!((xprev==x1)&&(yprev==y1))){
      out[1]=maze[y1][x1];
    }else{
      out[1]=999;
    }
  }
  if ((x2>=0)&&(y2>=0)&&(isAccessible(xrun,yrun,x2,y2))&&maze[y2][x2]<maze[yrun][xrun]){
    if (!((xprev==x2)&&(yprev==y2))){
      out[2]=maze[y2][x2];
    }else{
      out[2]=999;
    }
  }
  if ((x3>=0)&&(y3>=0)&&(isAccessible(xrun,yrun,x3,y3))&&maze[y3][x3]<maze[yrun][xrun]){
    if (!((xprev==x3)&&(yprev==y3))){
      out[3]=maze[y3][x3];
    }else{
      out[3]=999;
    }
  }

  int min=1001;
  int minCell;
  for (int i=0 ; i<4 ; i++ ){
    if ( out[i] < min ){
      min = out[i];
      minCell = i;
    }
  }
  
  if (dir=='N')
  {
    if (minCell==0){
      return 'R';
    }else if (minCell==1){
      return 'F';
    }else if (minCell==2){
      return 'L';
    }else{
      return 'B';
    }
  }else if (dir=='E')
  {
    if (minCell==0){
      return 'F';
    }else if (minCell==1){
      return 'L';
    }else if (minCell==2){
      return 'B';
    }else{
      return 'R';
    }
  }else if (dir=='S')
  {
    if (minCell==0){
      return 'L';
    }else if (minCell==1){
      return 'B';
    }else if (minCell==2){
      return 'R';
    }else{
      return 'F';
    }
  }else if (dir=='W')
  {
    if (minCell==0){
      return 'B';
    }else if (minCell==1){
      return 'R';
    }else if (minCell==2){
      return 'F';
    }else{
      return 'L';
    }
  }
  return 'N';
}


void rightTurn(){
  motor1.drive(100);
  motor2.drive(-100);
  delay(100);
  updateDir(1);
}
void leftTurn(){
  motor1.drive(-100);
  motor2.drive(100);
  delay(100);

  updateDir(2);
}
void forwardMove(){
      wallCentre();
      motor1.drive(100+wallError);
      motor2.drive(100-wallError);


  updateCord();
  flood[curYcordinate][curXcordinate]+=1;
}

void OLEDdisp(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.cp437(true);
  display.write("L:");
  display.print(Left);
  display.write("  F:");
  display.print(Front);
  display.write("  R:");
  display.print(Right);

  display.setCursor(0, 8);
  display.write("D: ");
  display.print(dir);
  display.write("  Cord:");
  display.print(curXcordinate);
  display.write("  ");
  display.print(curYcordinate);

  display.setCursor(0, 16);
  display.write("Next Cell:");
  display.print(word1);
  display.display();
}
void wallCentre(){
  Right=sensor2.getDistance();
  Left=sensor3.getDistance();
  if(Left < 100 && Right < 100){
    wallError = (Right - Left);
  }else if(Left < 100){
    wallError = 100 - Left;;
  }else if(Right < 100){
    wallError = Right - 100;
  }else
    wallError = 0;

  if (wallError >25)
    wallError=25;
  if (wallError < -25)
    wallError=-25;
}

/***********************************HEADER***************************************/



void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  Serial.println("HI");
  pinMode(Fsensor, OUTPUT);
  pinMode(Rsensor, OUTPUT);
  pinMode(Lsensor, OUTPUT);
  Wire.begin();
  delay(100);
  digitalWrite(Fsensor, HIGH);
  digitalWrite(Rsensor, LOW);
  digitalWrite(Lsensor, LOW);
  sensor1.getIdentification(&identification);
  if (sensor1.VL6180xInit() != 0) {
    Serial.println("FAILED TO INITALIZE FRONT");}
  sensor1.VL6180xDefautSettings();
  delay(500);
  sensor1.changeAddress(VL6180X_ADDRESS, NEWVL6180X_ADDRESS_1);

  digitalWrite(Rsensor, HIGH);
  sensor2.getIdentification(&identification);
  if (sensor2.VL6180xInit() != 0) {
    Serial.println("FAILED TO INITALIZE RIGHT");}
  sensor2.VL6180xDefautSettings();
  delay(500);
  sensor2.changeAddress(VL6180X_ADDRESS, NEWVL6180X_ADDRESS_2);
  digitalWrite(Lsensor, HIGH);
  sensor3.getIdentification(&identification);
  if (sensor3.VL6180xInit() != 0) {
    Serial.println("FAILED TO INITALIZE LEFT");}
  sensor3.VL6180xDefautSettings();
  delay(500);

  Front=sensor1.getDistance();
  Right=sensor2.getDistance();
  Left=sensor3.getDistance();
  delay(1000);
  Front=sensor1.getDistance();
  Right=sensor2.getDistance();
  Left=sensor3.getDistance();
  delay(1000);
  Front=sensor1.getDistance();
  Right=sensor2.getDistance();
  Left=sensor3.getDistance();
  delay(1000);
}

void loop() {/*
  Front=sensor1.getDistance();
  delay(5);
  Right=sensor2.getDistance();
  delay(5);
  Left=sensor3.getDistance();
  delay(5);
  Front=sensor1.getDistance();
  delay(5);
  Right=sensor2.getDistance();
  delay(5);
  Left=sensor3.getDistance();
  delay(5);
  Serial.print("Right(mm)= ");
  Serial.println(Right); 
  Serial.print("Left(mm) = ");
  Serial.println(Left);
  Serial.print("Front(mm)= ");
  Serial.println(Front);


  hasWall(Left,Right,Front);
  updateWalls(curXcordinate,curYcordinate,dir,hasLwall,hasRwall,hasFwall);
  floodFill();
  Serial.print("curXcordinate:   ");
  Serial.println(curXcordinate);
  Serial.print("curYcordinate:   ");
  Serial.println(curYcordinate);
  Serial.print("dir:   ");
  Serial.println(dir);
  Serial.print("hasLwall:   ");
  Serial.println(hasLwall);
  Serial.print("hasRwall:   ");
  Serial.println(hasRwall);
  Serial.print("hasFwall:   ");
  Serial.println(hasFwall);
  

  word1=nextCell();
  Serial.print("nextCell:   ");
  Serial.println(word1);
  OLEDdisp();
  if (word1=='R'){
    rightTurn();
    forwardMove();
  }else if (word1=='F')
  {
    forwardMove();
  }else if (word1=='L')
  {
    leftTurn();
    forwardMove();
  }else if (word1=='B')
  {
    rightTurn();
    rightTurn();
    forwardMove();
  }
  for (int i = 0; i < 16; i++) {
     for (int j = 0; j < 16; j++) {
      Serial.print(cells[i][j]);
      Serial.print("  ");
    }
    Serial.println();
}

for (int i = 0; i < 16; i++) {
     for (int j = 0; j < 16; j++) {
      Serial.print(maze[i][j]);
      Serial.print("  ");
    }
    Serial.println();
}*/
Front=sensor1.getDistance();
  delay(5);
  Right=sensor2.getDistance();
  delay(5);
  Left=sensor3.getDistance();
  delay(5);
  Front=sensor1.getDistance();
  delay(5);
  Right=sensor2.getDistance();
  delay(5);
  Left=sensor3.getDistance();
  delay(5);
  if(Front > 80){
    forwardMove();
  }else if (Right > 50) {
    rightTurn();
  }else {
  leftTurn();
  }/*
rightTurn();
brake(motor1, motor2);
delay(1000);
leftTurn();
brake(motor1, motor2);
delay(1000);
forwardMove();
Serial.println(wallError);*/
}