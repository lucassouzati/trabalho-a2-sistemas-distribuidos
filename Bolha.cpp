#include <stdio.h>
#include <stdlib.h> 
// #include <conio.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

#define root_process 0
#define send_data_tag 2001
#define return_data_tag 2002
#define max_value 100
// #define num_componentes 1000
 
int main(int argc, char **argv)
{
    int num_componentes = atoi(argv[1]);

    float v[num_componentes], v2[num_componentes], v3[num_componentes], numero_criado; //definindo o ponteiro v
    int i, j, aux;//, num_componentes;    
    

    MPI_Status status;
    int my_id, ierr, num_procs, num_rows, sobra,
    an_id, num_rows_to_receive, avg_rows_per_process, 
    sender, num_rows_received, start_row, end_row, num_rows_to_send; //Variáveis para a Bib.MPI

    clock_t inicio, fim;
    int cont =0;
    

    ierr = MPI_Init(&argc, &argv); //Inicio do MPI
    
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    printf("Inicializando processo %d \n", my_id);
    if(my_id == 0)
    {
      
      //Gerando vetor ordenado ao contrário

      numero_criado = num_componentes;
      
      for (i = 0; i < num_componentes; i++)
      {
        v[i] = numero_criado;
        numero_criado--;
        printf("%f\n", v[i]);
      }
      
      inicio= clock();

      //Dividindo o numero de componentes pela quantidade de processos
      avg_rows_per_process = (num_componentes / num_procs);
      // printf("\n Quantidade de componentes por processo: %d", avg_rows_per_process);


      //Mostrando quais valores vão ser ordenados pelo primeiro processo
      //printf("\nProcesso %d - comeca da linha %d \n", my_id + 1, 0);
      //printf("\nProcesso %d - termina da linha %d \n", my_id + 1, avg_rows_per_process);
      // printf("\nProcesso %d -  Valores ordenados [ ", my_id + 1);
      
      // for(int k = 0; k < avg_rows_per_process; k++){
      //     printf("%.2f, ", v[k]);
      // }
      // printf("] \n");

      /* Distribuindo uma parte do vetor para cada processo */
   
      for(an_id = 1; an_id < num_procs; an_id++) {
        
        start_row = an_id*avg_rows_per_process;
        end_row   = (an_id + 1)*avg_rows_per_process;

        
        if((num_componentes - end_row) < avg_rows_per_process)
           end_row = num_componentes;

        
        num_rows_to_send = end_row - start_row;

                                   
        ierr = MPI_Send( &num_rows_to_send, 1 , MPI_INT,
              an_id, send_data_tag, MPI_COMM_WORLD);

        ierr = MPI_Send( &v[start_row], num_rows_to_send, MPI_FLOAT,
              an_id, send_data_tag, MPI_COMM_WORLD);
      }

      //Vetor 3 é a primeira 

      for( i = 0; i < avg_rows_per_process; i++ )
      {
        v3[i] = v[i];
      }

      for( i = 0; i < avg_rows_per_process + 1; i++ )
      {
        for( j = i + 1; j < avg_rows_per_process; j++ ) // sempre 1 elemento à frente
        {
          // se o (i > (i+1)) então o i passa pra frente (ordem crescente)
          if ( v3[i] > v3[j] )
          {
             aux = v3[i];
             v3[i] = v3[j];
             v3[j] = aux;
          }
        }
      } 

      for(an_id = 1; an_id < num_procs; an_id++) {
        start_row = an_id*avg_rows_per_process;
        end_row   = (an_id + 1)*avg_rows_per_process;

        if((num_componentes - end_row) < avg_rows_per_process)
           end_row = num_componentes;

        num_rows_to_send = end_row - start_row;

        ierr = MPI_Recv( &v3[start_row], num_rows_to_send, MPI_FLOAT, MPI_ANY_SOURCE,
              return_data_tag, MPI_COMM_WORLD, &status);

        sender = status.MPI_SOURCE;

        
      }

      for( i = 0; i < num_componentes; i++ )
      {
        for( j = i + 1; j < num_componentes; j++ ) // sempre 1 elemento à frente
        {
          // se o (i > (i+1)) então o i passa pra frente (ordem crescente)
          if ( v3[i] > v3[j] )
          {
             aux = v3[i];
             v3[i] = v3[j];
             v3[j] = aux;
          }
        }
      }

      // ------ Percorrendo o vetor e imprimindo os valores ----------
      printf("\n*********** Valores do vetor dinamico ************\n\n");
       
      for (i = 0;i < num_componentes; i++)
      {
         printf("%.2f\n",v3[i]);
      }

      fim= clock();

      printf("%f\n", (float)inicio);
      printf("%f\n", (float)fim);

      printf("Diferenca em ms: %f\n",(float)((fim-inicio)/ 1000000.0F ) * 1000);   
      //printf("Diferenca em ms: %f\n",(float) (fim-inicio));   
    }
    
    else{

       /* Este código é para os processos filhos, portanto devem receber o segmento do vetor gravando em um vetor local */
          
         ierr = MPI_Recv( &num_rows_to_receive, 1, MPI_INT, 
               root_process, send_data_tag, MPI_COMM_WORLD, &status);
          
         ierr = MPI_Recv( &v2, num_rows_to_receive, MPI_FLOAT, 
               root_process, send_data_tag, MPI_COMM_WORLD, &status);

         num_rows_received = num_rows_to_receive;

        //printf("\n ID %d de %d processos \n", my_id + 1, num_procs);
        //printf("\nProcesso %d - comeca da linha %d \n", my_id + 1, my_id * num_rows_received);
        //printf("\nProcesso %d - termina da linha %d \n", my_id + 1, (my_id * num_rows_received) + num_rows_received);
        // printf("\nProcesso %d - Valores ordenados [ ", my_id + 1);
        
        // for(j = 0; j < num_rows_received; j++){
        //   printf("%.2f, ", v2[j]);
        // }
        // printf("] \n");


         /*Calculando o somatorio da parte do vetor */

      for( i = 0; i < num_rows_received; i++ )
      {
        for( j = i + 1; j < num_rows_received; j++ ) // sempre 1 elemento à frente
        {
          // se o (i > (i+1)) então o i passa pra frente (ordem crescente)
          if ( v2[i] > v2[j] )
          {
             aux = v2[i];
             v2[i] = v2[j];
             v2[j] = aux;
          }
        }
      }  

    /* Finalmente encaminhando a soma parcial para o processo raiz */

     ierr = MPI_Send( &v2, num_rows_received, MPI_FLOAT, root_process, 
           return_data_tag, MPI_COMM_WORLD);
    } 
    
     
  
    
  ierr = MPI_Finalize();
  return 0;
}    
