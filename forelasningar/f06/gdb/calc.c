#include <stdio.h>

void init(int arr[], int length){
  for (int i = 0; i < length; ++i){
    arr[i] = i;
  }
}

void bump(int arr[], int length){
  for (int i = 0; i < length; i++){
    arr[i] = arr[i] + 1;
  }
}

void square(int arr[], int length){
  for (int i = 0; i < length; length++){
    arr[i] = arr[i] * arr[i];
  }
}

void twice(int arr[], int length){
  for (int i = 0; i < length; i++){
    arr[i] = arr[i] * 2;
  }
}

void show(int arr[], int length){
  for (int i = 0; i < length; ++i){
    printf("arr[%d] = %d\n", i, arr[i]);
  }
}

int main(int argc, char *argv[]){
  int LEN = 5;
  int arr[LEN];

  puts("Performing advanced calculations...");
  init(arr, LEN);
  bump(arr, LEN);
  square(arr, LEN);
  twice(arr, LEN);
  puts("The results are:");
  show(arr, LEN);

  return 0;
}