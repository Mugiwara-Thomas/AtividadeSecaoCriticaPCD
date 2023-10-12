/*
Algoritmo de Manna-Pnueli que implementa entrada em SC por algoritmo Cliente-Servidor
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 1000000000 // 1 bilhão

int soma = 0;

void cliente(int id) {
  int local;
  int id_processo = omp_get_thread_num();

  if (id != id_processo) {
    // aqui ta o ponto de diferença, no controle, nós setamos essa parte como região critica, então apenas um thread por vez pode fazer isso.
    #pragma omp critical
    {
      while (soma != id_processo) {
        continue;
      }
    }
  }
  
  #pragma omp critical
  {
    local = soma;
    sleep(rand() % 2);
    soma = local + 1;
  }

  printf("Cliente %d: soma = %d\n", id, soma);
}

int main() {
  int i;

  // Essa parte é igual em ambos pois é apenas a chamada para entrar na região critica onde cada thread vai pedir para entrar N/4 vezes, isso é feito quando se chama a função cliente
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
