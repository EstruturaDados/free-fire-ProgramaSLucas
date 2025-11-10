#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

// -----------------------------------------
// Struct principal
// -----------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// -----------------------------------------
// Funções auxiliares
// -----------------------------------------
void cadastrarComponentes(Componente lista[], int *qtd);
void listarComponentes(Componente lista[], int qtd);
void bubbleSortNome(Componente lista[], int qtd, int *comparacoes, double *tempo);
void insertionSortTipo(Componente lista[], int qtd, int *comparacoes, double *tempo);
void selectionSortPrioridade(Componente lista[], int qtd, int *comparacoes, double *tempo);
int buscaBinariaNome(Componente lista[], int qtd, char chave[], int *comparacoes);

int main() {
    Componente componentes[MAX_COMP];
    int qtd = 0, opcao;
    int comparacoes = 0;
    double tempo = 0;
    char chave[30];

    do {
        printf("\n==== MENU PRINCIPAL ====\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Listar componentes\n");
        printf("3. Ordenar por NOME (Bubble Sort)\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6. Buscar componente-chave (Busca Binaria por nome)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarComponentes(componentes, &qtd);
                break;

            case 2:
                listarComponentes(componentes, qtd);
                break;

            case 3:
                comparacoes = 0;
                tempo = 0;
                bubbleSortNome(componentes, qtd, &comparacoes, &tempo);
                printf("\nOrdenacao concluida (Bubble Sort - Nome)\n");
                printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                listarComponentes(componentes, qtd);
                break;

            case 4:
                comparacoes = 0;
                tempo = 0;
                insertionSortTipo(componentes, qtd, &comparacoes, &tempo);
                printf("\nOrdenacao concluida (Insertion Sort - Tipo)\n");
                printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                listarComponentes(componentes, qtd);
                break;

            case 5:
                comparacoes = 0;
                tempo = 0;
                selectionSortPrioridade(componentes, qtd, &comparacoes, &tempo);
                printf("\nOrdenacao concluida (Selection Sort - Prioridade)\n");
                printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                listarComponentes(componentes, qtd);
                break;

            case 6:
                printf("Digite o nome do componente-chave: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';
                comparacoes = 0;
                int pos = buscaBinariaNome(componentes, qtd, chave, &comparacoes);
                if (pos != -1)
                    printf("Componente '%s' encontrado na posicao %d (%d comparacoes).\n", chave, pos + 1, comparacoes);
                else
                    printf("Componente '%s' NAO encontrado (%d comparacoes).\n", chave, comparacoes);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// -----------------------------------------
// Funções de cadastro e listagem
// -----------------------------------------
void cadastrarComponentes(Componente lista[], int *qtd) {
    if (*qtd >= MAX_COMP) {
        printf("Limite maximo de componentes atingido!\n");
        return;
    }

    int n;
    printf("Quantos componentes deseja cadastrar (max %d)? ", MAX_COMP - *qtd);
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n && *qtd < MAX_COMP; i++) {
        printf("\n--- Componente %d ---\n", *qtd + 1);
        printf("Nome: ");
        fgets(lista[*qtd].nome, 30, stdin);
        lista[*qtd].nome[strcspn(lista[*qtd].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(lista[*qtd].tipo, 20, stdin);
        lista[*qtd].tipo[strcspn(lista[*qtd].tipo, "\n")] = '\0';

        do {
            printf("Prioridade (1 a 10): ");
            scanf("%d", &lista[*qtd].prioridade);
            getchar();
        } while (lista[*qtd].prioridade < 1 || lista[*qtd].prioridade > 10);

        (*qtd)++;
    }
    printf("\nCadastro concluido!\n");
}

void listarComponentes(Componente lista[], int qtd) {
    if (qtd == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    printf("\n=== LISTA DE COMPONENTES ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("%2d. Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
}

// -----------------------------------------
// Ordenações
// -----------------------------------------
void bubbleSortNome(Componente lista[], int qtd, int *comparacoes, double *tempo) {
    clock_t inicio = clock();
    Componente temp;
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    *tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
}

void insertionSortTipo(Componente lista[], int qtd, int *comparacoes, double *tempo) {
    clock_t inicio = clock();
    for (int i = 1; i < qtd; i++) {
        Componente chave = lista[i];
        int j = i - 1;
        while (j >= 0 && (++(*comparacoes)) && strcmp(lista[j].tipo, chave.tipo) > 0) {
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = chave;
    }
    *tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
}

void selectionSortPrioridade(Componente lista[], int qtd, int *comparacoes, double *tempo) {
    clock_t inicio = clock();
    for (int i = 0; i < qtd - 1; i++) {
        int min = i;
        for (int j = i + 1; j < qtd; j++) {
            (*comparacoes)++;
            if (lista[j].prioridade < lista[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = lista[i];
            lista[i] = lista[min];
            lista[min] = temp;
        }
    }
    *tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
}

// -----------------------------------------
// Busca binária (por nome)
// -----------------------------------------
int buscaBinariaNome(Componente lista[], int qtd, char chave[], int *comparacoes) {
    int inicio = 0, fim = qtd - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(chave, lista[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}
