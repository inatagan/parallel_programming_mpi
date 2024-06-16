# parallel_programming_mpi
Algorithms for parallel programming using OpenMpi.

### Objetivo
Demonstrar um programa que crie um círculo paralelo para vários processos, sendo que processo 0 envia um token para o processo 1 e assim por diante, até que o processo 0 receba o token do processo n-1. A cada passagem o token deve ser incrementado.

### Requerimentos
Para compilar e executar este projeto e necessario ter os seguintes pacotes:

* gcc
* openmpi-bin 
* libopenmpi-dev

Em sistemas baseados no Debian, podem ser instalados com o seguinte comando:

`sudo apt update && sudo apt install openmpi-bin libopenmpi-dev -y`


### Compilar
Este algoritmos ja possui uma versao compilada que se encontra no diretorio `/builds`.

Mas caso deseje compilar o codigo fonte utilize este comando a partir da raiz do projeto:

`mpicc src/main.c -o builds/main`

### Executando
Este algoritmo espera receber um token como argumento, ou seja quando for executar voce deve tambem adicionar um token numerico de tipo `INT` ao comando, a partir da raiz do projeto esta e a sintaxe:

`mpirun -np $PROCESSOS build/main $TOKEN`

Ou seja para executar este algoritmo com 4 processos/nucleos e um token de numero 1000 o comando ficaria:

`mpirun -np 4 builds/main 1000`

Onde o `output` devera ser:

    $_ mpirun -np 4 builds/main 1000
    node 0 comecou com token = 1000
    node 0 enviou token = 1001

    node 1 recebeu token = 1001
    node 1 enviou token = 1002

    node 2 recebeu token = 1002
    node 2 enviou token = 1003

    node 3 recebeu token = 1003
    node 3 enviou token = 1004

    node 0 recebeu token = 1004
    node 0 enviou token = 1005

*Observacao: a ordem pode variar.