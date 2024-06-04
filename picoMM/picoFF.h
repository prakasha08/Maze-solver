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
  
  updateDir(1);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.cp437(true);
  display.write("Front:");
  display.print(Front);
  display.write("\nLeft:");
  display.print(Left);
  display.write("\nRight:");
  display.print(Right);
  display.display();
}
void leftTurn(){
  updateDir(2);
}
void forwardMove(){
  updateCord();
  flood[curYcordinate][curXcordinate]+=1;
}