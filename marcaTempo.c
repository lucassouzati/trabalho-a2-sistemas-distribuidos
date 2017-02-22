#include <stdio.h>
#include <time.h>

main(int argc, char **argv) 
{
   clock_t inicio, fim;
   int cont =0;
   inicio= clock();
	
   for(cont=0; cont<1000000000; cont++){
	// Código...	
   }
   fim= clock();

   printf("%f\n", (float)inicio);
   printf("%f\n", (float)fim);

   printf("Diferença em ms: %f\n",(float)((fim-inicio)/ 1000000.0F ) * 1000);
   //ierr = MPI_Finalize();
}

