// Code for priting a plot on the cli

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N_COLUMNS 130

void set_default(int* array) {
  for (int i = 0; i < N_COLUMNS; i++)
    array[i] = 0;
}

void set_custom(int* array) {
  for (int i = 0; i < N_COLUMNS; i++) {
    array[i] = rand() % 2;
  }
}

void print_array(int* array) {
  for (int i = 0; i < N_COLUMNS; i++)
    printf("%d", array[i]);

  printf("\n");
}

void update_forward(int* array) {
  for (int i = 0; i < N_COLUMNS -1; i++) {
    array[i] = array[i +1];
  }
}

int main() {
  int array[N_COLUMNS];
  srand(time(NULL));

  set_custom(array);

  while(1) {
    print_array(array);

    system("clear");
    sleep(0.2);
    update_forward(array);
  }

  return 0; // should NOT happen
}

