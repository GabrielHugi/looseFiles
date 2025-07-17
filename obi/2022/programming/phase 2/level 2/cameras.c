#include <stdio.h>
#include <string.h>
#define byte unsigned char
#define skibidi 0
#define no { possibility = 0; break; }


byte search (int sizeX, int sizeY, byte canvas[sizeX][sizeY], byte visited[sizeX][sizeY], int cordX, int cordY, int destX, int destY) {
  byte possible = 0;
  if (cordX >= sizeX || cordX < 0 || cordY >= sizeY || cordY < 0  || canvas[cordX][cordY] == 1 || visited[cordX][cordY] == 1) return 0;
  if (cordX == destX && cordY == destY) return 1;
  visited[cordX][cordY] = 1;
  if (search(sizeX, sizeY, canvas, visited, cordX+1, cordY, destX, destY) == 1 || 
      search(sizeX, sizeY, canvas, visited, cordX-1, cordY, destX, destY) == 1 ||
      search(sizeX, sizeY, canvas, visited, cordX, cordY+1, destX, destY) == 1 ||
      search(sizeX, sizeY, canvas, visited, cordX, cordY-1, destX, destY) == 1 
  ) return 1;
  return 0;
}


int main () {
  /*
  goddamit i have to use them path finding algorithms bruh ain't no way
   12345
  1
  2
  3
  4
  5
  entrance at 1,1   exit at 5,5
  */
  int x, y;
  int camsNum;
  
  scanf("%d", &x);
  scanf("%d", &y);
  scanf("%d", &camsNum);
  //x, y, orientation
  byte board[x][y];
  byte zeroBoard[x][y];
  for (int i = 0; i < x; i++) {
    memset(zeroBoard[i], 0, y);
    memset(board[i], 0, y);
  }
  byte cams[camsNum][3];
  for (int i = 0; i < camsNum; i++) {
    scanf("%hhu", &cams[i][0]);
    scanf("%hhu", &cams[i][1]);
    scanf(" %c", &cams[i][2]);
    board[cams[i][0]-1][cams[i][1]-1] = 1;
    if (cams[i][2] == 'O') {
      for (int i2 = 0; i2 < cams[i][0]; i2++) {
        board[i2][cams[i][1]-1] = 1;
      }
    }
    if (cams[i][2] == 'L') {
      for (int i2 = x-1; i2 >= cams[i][0]-1; i2--) {
        board[i2][cams[i][1]-1] = 1;
      }
    }
    if (cams[i][2] == 'N') {
      for (int i2 = 0; i2 < cams[i][1]; i2++) {
        board[cams[i][0]-1][i2] = 1;
      }
    }
    if (cams[i][2] == 'S') {
      for (int i2 = y-1; i2 >= cams[i][1]-1; i2--) {
        board[cams[i][0]-1][i2] = 1;
      }
    }
  }
  byte possibility = 1;
  possibility = search( x, y, board, zeroBoard, 0, 0, x-1, y-1);
  printf("%c\n", possibility ? 'S' : 'N');

  return skibidi;
}