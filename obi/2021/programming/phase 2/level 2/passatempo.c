#include <stdio.h>
#include <stdlib.h>
#define flush int c; while ((c = getchar()) != '\n' && c != EOF);

//bro this one is actually hard so imma do this later

int main () {
  int x, y;
  scanf("%d", &x);
  scanf("%d", &y);
  flush
  char (*board)[y][3] = malloc(sizeof(char[x][y][3]));
  int *valuesOnDaSide = malloc((x + y) * sizeof(int));
  for (int i = 0; i <= y; i++) {
    for (int i2 = 0; i2 <= x; i++) {
      if (i == y) {
        if (i2 != x) {
          scanf("%d", &valuesOnDaSide[i2+i]);
          flush
        }
      }
      else if (i2 == x) {
        scanf("%d", &valuesOnDaSide[i]);
        flush
      }
      else {
        scanf("%2s", board[i2][i]);
      }
    }
  }
  free(board);
  free(valuesOnDaSide);

}