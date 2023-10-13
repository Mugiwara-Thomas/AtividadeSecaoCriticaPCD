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

    // int id_processo = omp_get_thread_num();

    // if (id != id_processo) {
    //     while (counter != id_processo) {
    //         continue;
    //     }
    // }

    local = counter;
    sleep(rand() % 2);
    counter = local + 1; // Região crítica

    printf("Cliente %d: counter = %d\n", id, counter); 
}

void Server() {
  sleep(rand() % 2);
  printf("Servidor: counter = %d\n", counter);
}

int main (){
    int i, id;

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
