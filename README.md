# Trabalho A2 da disciplina de Sistemas Distribuídos

Exemplo de algorimto paralelizado de ordenação Bublle Sort. Nele são gerados uma quantidade de números desordenados (ao contrário) passada por parâmetro e o sistema distribui para quantidade de procesoss que o usuário indicar.

## Modo de usar:

Para executar o programa sem paralelizar, basta apenas indicar a quantidade de números que você quer ordenar:

```sh
./bolha [quantidade de numeros]
```

Ex.: `./bolha 100` (irá executar uma ordenação em um vetor de 100 números)

Para executar o programa paralelizado, você utilizará o seguinte comando:

```sh
mpiexec -np [número de processos]  bolha [quantidade de números]
```

Ex.:

```sh
mpiexec -np 5 bolha 100 //distribuir um vetor de 100 número desordenados para 5 processos (20 pra cada)
```

Ao término da execução, o sistema mostrará o tempo gasto em milissegundos.


## Detalhes da versão:
* Algumas vezes que está executando números não redondos (Ex.: 3 processos trabalhando num vetor de 10 numeros), apresenta alguns erros.