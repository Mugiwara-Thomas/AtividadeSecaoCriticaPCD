#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 1000000000

int soma = 0;

void cliente(int id) {
  int local;
  int id_processo = omp_get_thread_num();

  if (id != id_processo) {
    while (soma != id_processo) {
      usleep(1);
    }
  }

  local = soma;
  sleep(2);
  soma = local + 1;

  printf("Cliente %d: soma = %d\n", id, soma);
}

int main() {
  int i;

  #pragma omp parallel num_threads(4)
  {
    #pragma omp for
    for (i = 0; i < N; i++) {
      cliente(omp_get_thread_num());
    }
  }

  printf("Soma final = %d\n", soma);

  return 0;
}
