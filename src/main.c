#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mpi.h"
// Definir o primeiro ID das tarefas como ponto de referencia
#define  MASTER		0

int main(int argc, char **argv)
{
    // Recebendo e convertendo para int argumento que vem da linha de comando.
    int token = atoi(argv[1]);
    // Inicializar o ambiente MPI
    MPI_Init(&argc, &argv);
    // Adquirir o numero total de tarefas
    int num_tasks;
    MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
    // Adquirir o ID das tarefas
    int task_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &task_id);
    // Inicializando o atributo "tag" como 0 pois neste caso nao sera utilizado
    int tag =0;
    // Primeira tarefa recebe o token
    if (task_id == MASTER)
    {
        printf("node %d comecou com token = %d \n",task_id,token);
        // Incremento do token para ser enviado
        int send = token + 1;
        MPI_Send(&send,1,MPI_INT,1,tag,MPI_COMM_WORLD);
        printf("node %d enviou token = %d \n\n",task_id,send);
    }
    // Tarefas seguintes ate a penultima
    if (task_id<num_tasks-1)
    {
        int recv;
        // definir e receber mensagem da tarefa anterior
        int previous_task = task_id -1;
        MPI_Recv(&recv,1,MPI_INT,previous_task,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("node %d recebeu token = %d \n",task_id,recv);
        // incrementar e enviar mensagem para a proxima tarefa
        recv += 1;
        int next_task = task_id + 1;
        MPI_Send(&recv,1,MPI_INT,next_task,tag,MPI_COMM_WORLD);
        printf("node %d enviou token = %d \n\n",task_id,recv);
    }
    // Ultima tarefa
    else
    {
        int recv;
        // definir e receber mensagem da tarefa anterior
        int previous_task = task_id -1;
        MPI_Recv(&recv,1,MPI_INT,previous_task,tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("node %d recebeu token = %d \n",task_id,recv);
        // incrementar a mensagem
        recv += 1;
        // Enviar a mensagem para a tarefa 0 (MASTER)
        int next_task = 0;
        MPI_Send(&recv,1,MPI_INT,next_task,tag,MPI_COMM_WORLD);
        printf("node %d enviou token = %d \n\n",task_id,recv);
    }
    // Encerrar o ambiente MPI
    MPI_Finalize();
    return 0;
}
