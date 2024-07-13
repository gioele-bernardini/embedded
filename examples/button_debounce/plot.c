#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define N_COLUMNS 130
#define N_ROWS 5

void set_default(int* array) {
  for (int i = 0; i < N_COLUMNS; i++)
    array[i] = 0;
}

void set_custom(int* array) {
  for (int i = 0; i < N_COLUMNS; i++) {
    array[i] = rand() % 2;
  }
}

void print_column(int* array, int index) {
  for (int i = 0; i < N_ROWS; i++) {
    if (array[index] == 1) {
      printf("*");
    } else {
      printf(" ");
    }
    printf("\n");
  }
}

void print_matrix(int* array) {
  for (int i = 0; i < N_COLUMNS; i++) {
    print_column(array, i);
  }
  printf("\n");
}

void update_forward(int* array) {
  for (int i = 0; i < N_COLUMNS - 1; i++) {
    array[i] = array[i + 1];
  }
  array[N_COLUMNS - 1] = rand() % 2; // Randomize the last element to create a moving effect
}

int main() {
  int array[N_COLUMNS];
  srand(time(NULL));

  set_custom(array);

  while (1) {
    print_matrix(array);
    usleep(200000); // Sleep for 200 milliseconds
    system("clear");
    update_forward(array);
  }

  return 0; // should NOT happen
}
