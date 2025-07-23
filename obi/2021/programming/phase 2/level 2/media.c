#include <stdio.h>

// bro wtf is this why is this so easy bruh i finished it in 3 minutes wtf why is this in level 2 phase 2 bruh they giving free points out :sob:

void swap(int *a, int *b) {
    int sigma = *a;
    *a = *b;
    *b = sigma;
}

int main () {
  int a,b;
  scanf("%d", &a);
  scanf("%d", &b);
  if (a > b) swap(&a, &b);
  printf("%d\n", a - (b-a));
}