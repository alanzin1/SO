#include <stdio.h>
#include <stdlib.h>

#define MAX_TAREFAS 100

typedef struct {
    int periodo;
    int tempo_de_computacao;
    int deadline;
} Tarefa;

void escalonamento_edf(Tarefa tarefas[], int num_tarefas) {
    int tempo_atual = 1;
    int i, j;

    printf("Escalonamento EDF:\n");

    while (tempo_atual < 100) {  // Tempo de execução máximo

        // Encontrar a tarefa com o menor deadline
        int menor_deadline = 10000; 
        int tarefa_selecionada = -1;

        for (i = 0; i < num_tarefas; i++) {
            if (tarefas[i].periodo > 0 && tarefas[i].deadline < menor_deadline) {
                menor_deadline = tarefas[i].deadline;
                tarefa_selecionada = i;
            }
        }

        if (tarefa_selecionada != -1) {
            // Executar a tarefa selecionada
            printf("Tempo %d: Tarefa %d\n", tempo_atual, tarefa_selecionada + 1);
            tarefas[tarefa_selecionada].tempo_de_computacao--;

            if (tarefas[tarefa_selecionada].tempo_de_computacao == 0) {
                // Tarefa concluída, reiniciar o tempo de computação e definir novo deadline
                tarefas[tarefa_selecionada].tempo_de_computacao = tarefas[tarefa_selecionada].periodo;
                tarefas[tarefa_selecionada].deadline += tarefas[tarefa_selecionada].periodo;
            }
        }

        // Atualizar os períodos restantes das tarefas
        for (j = 0; j < num_tarefas; j++) {
            if (tarefas[j].periodo > 0) {
                tarefas[j].periodo--;
            }
        }

        tempo_atual++;
    }
}

void exibir_tarefas(Tarefa tarefas[], int num_tarefas) {
    printf("\nTarefas:\n");
    printf("ID | DEADLINE\n");
    for (int i = 0; i < num_tarefas; i++) {
        printf("%2d |", i + 1);
        printf(" Deadline no tempo %d", tarefas[i].deadline); // Adiciona a indicação do tempo do deadline
        printf("\n");
    }
}
int main() {
    FILE *arquivo;
    Tarefa tarefas[MAX_TAREFAS];
    int num_tarefas = 0;

    arquivo = fopen("tarefas.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Ler as tarefas do arquivo
    while (fscanf(arquivo, "%d %d %d", &tarefas[num_tarefas].periodo, &tarefas[num_tarefas].tempo_de_computacao, &tarefas[num_tarefas].deadline) == 3) {
        num_tarefas++;
    }

    fclose(arquivo);

    // Exibir as tarefas
    exibir_tarefas(tarefas, num_tarefas);

    // Executar o algoritmo EDF
    escalonamento_edf(tarefas, num_tarefas);

    return 0;
}
