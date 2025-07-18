#include <stdio.h>
#include <string.h>
#include <math.h>
#define byte unsigned char
#define flush int c; while ((c = getchar()) != '\n' && c != EOF);

/* I was gonna try some complex algorithm or sum but it's not realistic for the time limits in obi so imma jst brute force all combinations I guess

for (int i = 0; i < size; i++) {
    if (bufferPos == 0) {
      buffer[bufferPos] = string[i];
      bufferPos++;
    }
    else {
      if (buffer[bufferPos-1] == string[i] && fullCheck(string, i-bufferPos-1, i+bufferPos+1) == 1) {
        if (((i+bufferPos+1) - (i-bufferPos-1)) > maxSize) maxSize = (i+bufferPos+1) - (i-bufferPos-1);
        memset(buffer, 0, size);
      }
      if (buffer[bufferPos-1] != string[i]) {
        
      }
    }
  }
*/

int fullCheck(char *string, int from, int to) {
  byte yes = 1;
  if (to < from) {
    from = to + from;
    to = from - to;
    from = from - to;
  }
  for (int i = from, i2 = to; i < i2; i++, i2--) {
    if (string[i] != string[i2]) yes = 0;
  }
  return yes;
}

int main () {
  int size;
  scanf("%d", &size);
  char string[size+1];
  flush
  fgets(string, size+1, stdin);
  char buffer[size+1];
  int bufferPos = 0;
  int maxSize = 0;
  
  for (int i = 0; i < size; i++) {
    for (int i2 = i; i2 < size; i2++) {
      if (fullCheck(string, i, i2) == 1 && abs(i2-i)+1 > maxSize) {
        maxSize = abs(i2-i)+1;
      }
    }
  }

  printf("%d\n", maxSize);
}