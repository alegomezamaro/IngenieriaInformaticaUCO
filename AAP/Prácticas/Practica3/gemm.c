#include <stdio.h>

#define M 4
#define N 4
#define K 4

int main() {

  int A[M * K] = {0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15}; //Column-major order
  int B[K * N] = {0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15}; //Column-major order 
  int C[M * N] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};       //Row-major order

  int i, j, z, a;

  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++) 
      for (z = 0; z < K; z++) 
        C[i * N + j] += A[z * M + i] * B[j * K + z];


  for (i = 0; i < M; i++) {
    for (j = 0; j < N; j++)
      printf("%d ", C[i * N + j] );
    printf("\n");
  }

}
