#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
// #include <conio.h>
 
int main(void)
{
     //definindo o ponteiro v
    int i, j, aux, num_componentes;    
     
    printf("Informe o numero de componentes do vetor\n");
    scanf("%d", &num_componentes);
    
    float v[num_componentes], numero_criado;  
    // v = (float *) malloc(num_componentes * sizeof(float));  
    
    //Armazenando os dados em um vetor
    numero_criado = num_componentes;
      
      for (i = 0; i < num_componentes; i++)
      {
        v[i] = numero_criado;
        numero_criado--;
        printf("%f\n", v[i]);
      }

    clock_t inicio, fim;
    int cont =0;
    inicio= clock();
    
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
   fim= clock();

  printf("%f\n", (float)inicio);
  printf("%f\n", (float)fim);

  printf("Diferenca em ms: %f\n",(float)((fim-inicio)/ 1000000.0F ) * 1000);   
          
    
   //liberando o espaço de memória alocado 
   
    
   // getch();
   return 0;
} 