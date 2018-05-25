// Vitor Saldanha da Silveira 158508
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <stdint.h>
#define max_entrada 10000000
//Declaracao de variaveis globais
unsigned long int entrada[max_entrada];
int indice = 0;
int tam = 0;

typedef struct{
  unsigned long int* vetor;
  int inicio;
  int final;
}dados;
// Declaracao de funcoes
void* bubleSort(void*arg);
void insertionSort(unsigned long int vetor[], int tamanhoVetor );
void trocarPosicaoValores( unsigned long int *posicaoA, unsigned long int *posicaoB);



// ---------------- funçao main() -------------------
int main(){
   pthread_t threads[2]; 
   int i = 0;

// Lendo a entrada da String e vendo o tamanho dela 
   while( scanf("%lu", &entrada[i]) == 1 ){
      i++;
      if((entrada[i]!=' ')||(entrada[i]!= '\n')){
            tam++;
        }
    }

//Ordena por threads
        indice = tam/2;
        dados parte1,parte2;
        //Estrtura de dados da primeira parte do vetor entrada
        parte1.vetor = entrada;
        parte1.inicio = 0;
        parte1.final = indice-1;
        //Estrtura de dados da segunda parte do vetor entrada
        parte2.vetor = entrada;
        parte2.inicio = indice;
        parte2.final = tam-1;
        
        pthread_create(&(threads[0]), NULL,bubleSort,&parte1);
        pthread_create(&(threads[1]), NULL,bubleSort,&parte2);
//Esperando threads morrerem
   for (i = 0; i < 2; i++) {
       pthread_join(threads[i], NULL);
    }

   insertionSort(entrada,tam);//Imprimindo o Vetos
   
   for (i = 0; i < tam-1; i++) {
      printf("%lu ", entrada[i]);
   }
   printf("%lu\n",entrada[tam-1]);

   return 0;

}

// ---------------- BubleSort de ordenacao de pedacos de um vetor-------------------
void* bubleSort(void* arg){
   int i, j;
   dados* informacoes;
   informacoes = (dados*)arg;
   for( i = informacoes->inicio; i < ( informacoes->final -1 );  i++ )
   {
      for( j=informacoes->inicio; j <(informacoes->final -( i +1 ) ); j++ )  
      {
         if( informacoes->vetor[j] > informacoes->vetor[j+1] )  
         {          
            trocarPosicaoValores( &informacoes->vetor[j], &informacoes->vetor[j+1]); 
         }
      } 
   }
}
// ---------------- Troca Valores -------------------
void trocarPosicaoValores( unsigned long int *posicaoA, unsigned long int *posicaoB ){
   unsigned long int temporario;
   temporario = *posicaoA;
   *posicaoA = *posicaoB;
   *posicaoB = temporario;     
}

void insertionSort(unsigned long int vetor[], int tamanhoVetor ){
   int i, j;
   unsigned long int valorAtual;
 
   for( j=1; j < tamanhoVetor; j++ ) 
   {
      valorAtual = vetor[j];
      i = j-1;
      
      while(i >= 0 && vetor[i] > valorAtual)
      {
        vetor[i+1] = vetor[i];
        i--;
      } 
              
      vetor[i+1] = valorAtual;
   }
}

