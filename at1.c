#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma música
typedef struct Musica {
    char artista[100];
    char nome[100];
    struct Musica *prox;
    struct Musica *ant;
} Musica;

// Função para criar um novo nó
Musica* criarNo(char artista[], char nome[]) {
    Musica *novoNo = (Musica*)malloc(sizeof(Musica));
    strcpy(novoNo->artista, artista);
    strcpy(novoNo->nome, nome);
    novoNo->prox = NULL;
    novoNo->ant = NULL;
    return novoNo;
}

// Função para inserir um novo nó no fim da lista
void inserirNo(Musica **inicio, char artista[], char nome[]) {
    Musica *novoNo = criarNo(artista, nome);
    if (*inicio == NULL) {
        *inicio = novoNo;
        novoNo->prox = novoNo;
        novoNo->ant = novoNo;
    } else {
        Musica *ultimo = (*inicio)->ant;
        ultimo->prox = novoNo;
        novoNo->ant = ultimo;
        novoNo->prox = *inicio;
        (*inicio)->ant = novoNo;
    }
}

// Função para exibir a playlist pela ordem de cadastro
void exibirPlaylistCadastro(Musica *inicio) {
    if (inicio == NULL) {
        printf("Playlist vazia.\n");
        return;
    }
    Musica *atual = inicio;
    do {
        printf("%s - %s\n", atual->artista, atual->nome);
        atual = atual->prox;
    } while (atual != inicio);
}

// Função para liberar a memória alocada para a lista
void liberarLista(Musica **inicio) {
    if (*inicio == NULL) return;
    Musica *atual = *inicio;
    do {
        Musica *temp = atual;
        atual = atual->prox;
        free(temp);
    } while (atual != *inicio);
    *inicio = NULL;
}

// Função para ler o arquivo e criar a lista de músicas
void lerArquivo(Musica **inicio, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    char artista[100], nomeMusica[100];
    while (fscanf(arquivo, "%[^;];%[^\n]\n", artista, nomeMusica) == 2) {
        inserirNo(inicio, artista, nomeMusica);
    }
    fclose(arquivo);
}

int main() {
    Musica *playlist = NULL;
    lerArquivo(&playlist, "musicas.txt");

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Exibir playlist pela ordem de cadastro\n");
        printf("2. Exibir playlist ordenada pelo nome das músicas\n");
        printf("3. Inserir nova música\n");
        printf("4. Remover uma música\n");
        printf("5. Buscar por uma música\n");
        printf("6. Avançar para próxima música\n");
        printf("7. Retornar a música anterior\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                exibirPlaylistCadastro(playlist);
                break;
            // Adicione os outros casos aqui
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    liberarLista(&playlist);

    return 0;
}

