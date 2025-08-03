#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_ALUNOS 100
#define MAX_AVALIACOES 10



typedef struct {
    float nota;
    float peso;
} Avaliacao;

typedef struct {
    char nome[50];
    int qtdAvaliacoes;
    Avaliacao avaliacoes[MAX_AVALIACOES];
    float mediaFinal;
} Aluno;

void trocar(Aluno *a, Aluno *b) {
    Aluno temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Aluno alunos[], int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && alunos[esq].mediaFinal > alunos[maior].mediaFinal)
        maior = esq;

    if (dir < n && alunos[dir].mediaFinal > alunos[maior].mediaFinal)
        maior = dir;

    if (maior != i) {
        trocar(&alunos[i], &alunos[maior]);
        heapify(alunos, n, maior);
    }
}

void heapSort(Aluno alunos[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(alunos, n, i);

    for (int i = n - 1; i >= 0; i--) {
        trocar(&alunos[0], &alunos[i]);
        heapify(alunos, i, 0);
    }
}

float calcularMediaPonderada(Aluno aluno) {
    float somaPesos = 0, somaNotas = 0;
    for (int i = 0; i < aluno.qtdAvaliacoes; i++) {
        somaNotas += aluno.avaliacoes[i].nota * aluno.avaliacoes[i].peso;
        somaPesos += aluno.avaliacoes[i].peso;
    }
    return somaPesos == 0 ? 0 : somaNotas / somaPesos;
}

void mostrarAlunos(Aluno alunos[], int n) {
    printf("\nAlunos ordenados por media final:\n");
    for (int i = 0; i < n; i++) {
        printf("Nome: %s | Media Final: %.2f\n", alunos[i].nome, alunos[i].mediaFinal);
    }
}

int main() {
    Aluno alunos[MAX_ALUNOS];
    int quantidadeAlunos;

    printf("Quantos alunos deseja cadastrar? ");
    scanf("%d", &quantidadeAlunos);

    if (quantidadeAlunos <= 0 || quantidadeAlunos > MAX_ALUNOS) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    for (int i = 0; i < quantidadeAlunos; i++) {
        printf("\n--- Aluno %d ---\n", i + 1);
        getchar(); // Limpar buffer
        printf("Nome: ");
        fgets(alunos[i].nome, sizeof(alunos[i].nome), stdin);
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0';

        printf("Quantas avaliacoes? (Max %d): ", MAX_AVALIACOES);
        scanf("%d", &alunos[i].qtdAvaliacoes);

        if (alunos[i].qtdAvaliacoes <= 0 || alunos[i].qtdAvaliacoes > MAX_AVALIACOES) {
            printf("Quantidade de avaliacoes invalida.\n");
            return 1;
        }

        for (int j = 0; j < alunos[i].qtdAvaliacoes; j++) {
            printf("Nota da avaliacao %d: ", j + 1);
            scanf("%f", &alunos[i].avaliacoes[j].nota);
            printf("Peso da avaliacao %d: ", j + 1);
            scanf("%f", &alunos[i].avaliacoes[j].peso);
        }

        alunos[i].mediaFinal = calcularMediaPonderada(alunos[i]);
    }

    heapSort(alunos, quantidadeAlunos);
    mostrarAlunos(alunos, quantidadeAlunos);

    return 0;
}
