#include <stdio.h>
#define byte unsigned char

// why is this in phase 2 level 2 yall this is prob the easiest one i ever saw

int main () {
  byte points[5];
  for (int i = 0; i < 5; i++) scanf("%hhu", &points[i]);
  byte trofeus = 0;
  byte placas = 0;
  byte which = 0;
  byte *handle = &trofeus;
  byte reference = points[0];
  for (int i = 0; i < 5; i++) {
    if (points[i] == reference) {
      (*handle)++;
    }
    if (points[i] < reference) {
      if (which < 1) {
        reference = points[i];
        handle = &placas;
        (*handle)++;
        which++;
      }
      else break;
    }
  }
  printf("%d %d\n", trofeus, placas);
  
  return 0;
}