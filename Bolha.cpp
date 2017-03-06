#include <stdio.h>
#include <stdlib.h> 
#include <conio.h>
 
int main(void)
{
    float *v; //definindo o ponteiro v
    int i, j, aux, num_componentes;    
     
    printf("Informe o numero de componentes do vetor\n");
    scanf("%d", &num_componentes);
    
      
    v = (float *) malloc(num_componentes * sizeof(float));  
    
    //Armazenando os dados em um vetor
    for (i = 0; i < num_componentes; i++)
    {
      printf("\nDigite o valor para a posicao %d do vetor: ", i+1);
      scanf("%f",&v[i]);
    }
    
    for( i = 0; i < num_componentes; i++ )
    {
    for( j = i + 1; j < num_componentes; j++ ) // sempre 1 elemento à frente
    {
      // se o (i > (i+1)) então o i passa pra frente (ordem crescente)
      if ( v[i] > v[j] )
      {
         aux = v[i];
         v[i] = v[j];
         v[j] = aux;
      }
    }
  }  
     
   // ------ Percorrendo o vetor e imprimindo os valores ----------
   printf("\n*********** Valores do vetor dinamico ************\n\n");
    
   for (i = 0;i < num_componentes; i++)
   {
       printf("%.2f\n",v[i]);
   }
   
          
    
   //liberando o espaço de memória alocado 
   free(v);
    
   getch();
   return 0;
}    
