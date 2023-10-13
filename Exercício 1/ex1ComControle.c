/*
INTEGRANTES:
    - Thomas Lincoln Victor da Silva - 156603
    - Luiz Fernando de Cristo Moloni - 159325

Algoritmo de Manna-Pnueli que implementa entrada em SC por algoritmo Cliente-Servidor

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 1000000000 // Total de Iterações - 1 bilhão
#define N_THREADS 4 // Número de threads Clientes

int counter = 0; // Variável compartilhada

void Client(int id) {
  int local;
  int id_processo = omp_get_thread_num();

  // if (id != id_processo) {
  //   // aqui ta o ponto de diferença, no controle, nós setamos essa parte como região critica, então apenas um thread por vez pode fazer isso.
  //   #pragma omp critical
  //   {
  //     while (counter != id_processo) {
  //       continue;
  //     }
  //   }
  // }
  
  #pragma omp critical 
  {
    local = counter;
    sleep(rand() % 2);
    counter = local + 1;
  }

  printf("Cliente %d: soma = %d\n", id, counter);
}

void Server() {
  sleep(rand() % 2);

  #pragma omp critical
  {
    printf("Servidor: soma = %d\n", counter);
  }
}

int main() {
  int i, id;

  // Essa parte é igual em ambos pois é apenas a chamada para entrar na região critica onde cada thread vai pedir para entrar N/4 vezes, isso é feito quando se chama a função cliente
  #pragma omp parallel for num_threads(N_THREADS + 1) // +1 para o processo servidor
  for (i = 0; i < N; i++) {      
    id = omp_get_thread_num();

    if(id < N_THREADS) {
        Client(id); 
    }else {  
      if(id == N_THREADS) {
          Server();
      }
    }                
  }

  printf("Counter final = %d\n", counter);

  return 0;
}
