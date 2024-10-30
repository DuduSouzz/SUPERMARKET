#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nozin {
    char nome[50];
    struct Nozin* prox;
} Nozin;

typedef struct {
    Nozin* inicio;
} Lista;

void criaLista(Lista* lista) {
    lista->inicio = NULL;
}

void inserirLista(Lista* lista, const char* nomeProduto) {
    Nozin* novo = (Nozin*)malloc(sizeof(Nozin));
    if (novo) {
        strcpy(novo->nome, nomeProduto); 
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }
}

void exibirLista(Lista* lista) {
    Nozin* atual = lista->inicio;
    while (atual) {
        printf("Produto: %s\n", atual->nome);
        atual = atual->prox;
    }
}

int verificarVazia(Lista* lista) {
    return lista->inicio == NULL;
}

Nozin* buscarLista(Lista* lista, const char* nomeProduto) {
    Nozin* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->nome, nomeProduto) == 0) {
            return atual; 
        }
        atual = atual->prox;
    }
    return NULL; 
}

void excluirLista(Lista* lista, const char* nomeProduto) {
    Nozin* atual = lista->inicio;
    Nozin* anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nomeProduto) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("O produto %s não foi encontrado \n", nomeProduto);
        return;
    }

    if (anterior == NULL) {
        lista->inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual);
}

void liberarLista(Lista* lista) {
    Nozin* atual = lista->inicio;
    while (atual != NULL) {
        Nozin* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    lista->inicio = NULL;
}

void inserirOrdem(Lista* lista, const char* nomeProduto) {
    Nozin* novo = (Nozin*)malloc(sizeof(Nozin));
    if (!novo) {
        printf("Não foi possível alocar a memória \n");
        return;
    }
    strcpy(novo->nome, nomeProduto);
    novo->prox = NULL;

    if (lista->inicio == NULL || strcmp(lista->inicio->nome, nomeProduto) > 0) {
        novo->prox = lista->inicio;
        lista->inicio = novo;
    } else {
        Nozin* atual = lista->inicio;
        while (atual->prox != NULL && strcmp(atual->prox->nome, nomeProduto) < 0) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
}

int main() {
    Lista lista;
    criaLista(&lista);
    int opcao;
    char nomeProduto[50];

    do {
        printf("Qual sua escolha de hoje? \n");
        printf("1. Adicionar produto \n");
        printf("2. Exibir os produtos \n");
        printf("3. Excluir os produtos adicionados \n");
        printf("4. Verificar se a lista está vazia \n");
        printf("5. Procurar algum produto: \n");
        printf("6. Liberar produtos \n");
        printf("7. Inserir produtos em ordem crescente \n");
        printf("8. Sair do mercado\n");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("Diga o nome do produto: ");
                fgets(nomeProduto, sizeof(nomeProduto), stdin);
                nomeProduto[strcspn(nomeProduto, "\n")] = 0; 
                inserirLista(&lista, nomeProduto);
                break;
            case 2:
                exibirLista(&lista);
                break;
            case 3:
                printf("Diga o nome do produto para excluir: ");
                fgets(nomeProduto, sizeof(nomeProduto), stdin);
                nomeProduto[strcspn(nomeProduto, "\n")] = 0;
                excluirLista(&lista, nomeProduto);
                break;
            case 4:
                printf("A lista %s vazia \n", verificarVazia(&lista) ? "está" : "não está");
                break;
            case 5:
                printf("Diga o nome do produto para buscarmos: ");
                fgets(nomeProduto, sizeof(nomeProduto), stdin);
                nomeProduto[strcspn(nomeProduto, "\n")] = 0;
                Nozin* encontrado = buscarLista(&lista, nomeProduto);
                printf("O produto %s encontrado \n", encontrado ? "foi" : "não foi");
                break;
            case 6:
                liberarLista(&lista);
                printf("Produtos liberados.\n");
                break;
            case 7:
                printf("Diga o nome do produto para deixar em ordem: ");
                fgets(nomeProduto, sizeof(nomeProduto), stdin);
                nomeProduto[strcspn(nomeProduto, "\n")] = 0;
                inserirOrdem(&lista, nomeProduto);
                break;
            case 8:
                printf("Saindo do mercado...Good Bye!\n");
                liberarLista(&lista);
                break;
            default:
                printf("Opção desconhecida por mim. Tente novamente! \n");
        }
    } while (opcao != 8);

    return 0;
}
