#include <stdio.h>
#include <stdlib.h>

//estrutura do nó
typedef struct No {
    int dado;
    struct No* esquerda;
    struct No* direita;
} No;

//Função para criar um novo nó
No* criarNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

//função de inserir no em arvore
void inserir(Arv **t, int n) {
    if (*t == NULL) {
        *t = (Arv *)malloc(sizeof(Arv));
        (*t)->esq = NULL;
        (*t)->dir = NULL;
        (*t)->num = n;
    } else {
        if (n < (*t)->num) {
            inserir(&(*t)->esq, n);
        }
        if (n > (*t)->num) {
            inserir(&(*t)->dir, n);
        }
    }
}

// Função para criar uma nova fila
typedef struct NoFila {
    Arv *no;
    struct NoFila *prox;
} NoFila;

typedef struct Fila {
    NoFila *inicio, *fim;
} Fila;

//função de inserção em fila (que guardara as os nos percorridos)
void inserirFila(Fila *fila, Arv *no) {
    NoFila *novoNo = (NoFila *)malloc(sizeof(NoFila));
    novoNo->no = no;
    novoNo->prox = NULL;

    if (fila->inicio == NULL) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    } else {
        fila->fim->prox = novoNo;
        fila->fim = novoNo;
    }
}

////função de printar fila
void imprimirFila(Fila *fila) {
    NoFila *atual = fila->inicio;

    while (atual != NULL) {
        printf("%d ", atual->no->num);
        atual = atual->prox;
    }

    printf("\n");
}

//função de percorrer a arvore com as condições de 
//(if a escolha recebida for de percorrer para direita:
// 1. o ponteiro agr vai verificar se esta apontando p null (if estivar imprima que o usuario ganhou e chegou ao final, se nao faça o ponteiro apontar para direita),
// 2. vai chamar a função de inserir em fila e armazenas esse nó, 
// 3. mostrar a fila para o usuario com a função de printar fila)
//(if a escolha recebida for de percorrer para esquerda, 
// 1. o ponteiro agr vai verificar se esta apontando p null (if estivar imprima que o usuario ganhou e chegou ao final, se nao faça o ponteiro apontar para esquerda
// 2. chamar a função de inserir em fila e armazenar esse no,
// 3. imprimir a fila para o usuario)
void percorrerArvore(Arv *raiz, int escolha) {
    Fila fila;
    fila.inicio = fila.fim = NULL;

    Arv *atual = raiz;

    while (1) {
        //int escolha;

        // Aqui você solicita a escolha do usuário (1 para direita, 2 para esquerda)
        if (escolha == 1) {
            // Percorrer para a direita
            if (atual->dir == NULL) {
                printf("Parabéns! Você chegou ao final do labirinto!\n");
                break;
            } else if (atual->dir->num % 2 == 0) {
                printf("Você errou! Voltando para o início.\n");
                percorrerArvore(raiz);
                break;
            } else {
                atual = atual->dir;
            }
        } else if (escolha == 2) {
            // Percorrer para a esquerda
            if (atual->esq == NULL) {
                printf("Parabéns! Você chegou ao final do labirinto!\n");
                break;
            } else if (atual->esq->num % 2 == 0) {
                printf("Você errou! Voltando para o início.\n");
                percorrerArvore(raiz);
                break;
            } else {
                atual = atual->esq;
            }
        }

        inserirFila(&fila, atual);
        imprimirFila(&fila);
    }
}

//função que percorrer voltando para a raiz 


// Função principal
int main() {
    //criação da arvore e inserção com a função de inserção de arvore 
    int escolha;

    printf("Bem-vindo ao labirinto do País das Maravilhas!!!\n");
    printf("A Alice está perdida e precisa de sua ajuda para voltar pra casa em segurança.\n");
    printf("Você terá 5 chances para ajudá-la. Caso o contrário, a Rainha de Copas te matará!\n");
    printf("Boa sorte, jogador!\n");

    while (1) {
        printf("\nEscolha:\n");
        printf("1 - Direita\n");
        printf("2 - Esquerda\n");
        printf("3 - Sair\n");
        scanf("%d", &escolha);

        if(escolha != 1 || escolha != 2){
          break;
        }

        switch(escolha){
          case 1: 
            //verificar se ta apontando p null - função de verificação de nulo (if tiver nulo retorna que ganhou, se nao continua)
            //função de percorrer a direita - essa função mostra a fila de valores ja escolhidos, joga ele na fila (usando função de inserir em fila), e faz o ponteiro apontar p proximo valor a direita

          case 2:
            //verificar se ta apontando p null - função de verificação de nulo (if tiver nulo retorna que ganhou, se nao continua)
            //função de percorrer a esq - essa função mostra a fila de valores ja escolhidos, joga ele na fila (usando função de inserir em fila), e faz o ponteiro apontar p proximo valor a esq
        }
    }
    return 0;
}