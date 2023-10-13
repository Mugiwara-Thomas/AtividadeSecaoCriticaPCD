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

omp_lock_t lock; //Lock para controlar a região critica
int counter = 0; // Variável compartilhada

void Client(int id) {
  int local;

  //Para controlar a região critica, usamos o omp_set_lock, que vai setar o lock, então apenas um thread por vez pode fazer isso.
  omp_set_lock(&lock); //Pre protocolo

  //Acessando a Região Critica
  local = counter;
  sleep(rand() % 2);
  counter = local + 1; //Alterando o Valor da Variavel Compartilhada

  printf("Cliente %d: soma = %d\n", id, counter);
  
  omp_unset_lock(&lock); //Pos protocolo
}

void Server() {
//   sleep(rand() % 2);
  omp_set_lock(&lock); //Pre protocolo
  printf("Servidor: soma = %d\n", counter); //Acessando a Região Critica
  omp_unset_lock(&lock); //Pos protocolo
}

int main() {
  int i, id;

  // Essa parte é igual em ambos pois é apenas a chamada para entrar na região critica onde cada thread vai pedir para entrar N/4 vezes, isso é feito quando se chama a função cliente
  #pragma omp parallel for num_threads(N_THREADS + 1) // +1 para o processo servidor
  for (i = 0; i < N; i++) {      
    id = omp_get_thread_num();

    if(id < N_THREADS) { // Processos Clientes
        Client(id); 
    }else {  
      if(id == N_THREADS) { // Processo Servidor
          Server();
      }
    }                
  }

  printf("Counter final = %d\n", counter);

  return 0;
}
