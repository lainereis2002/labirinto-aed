#include <stdio.h>
#include <stdlib.h>

//-------- FUNÇÕES DA FILA
//struct
typedef struct Node{
  int numero;
  struct Node *prox;
}Node;

// enfileira nó
void inserirFila(Node **head, Node **tail, int n) {
  Node *novo = (Node *)malloc(sizeof(Node));

  if (novo != NULL) {
    novo->numero = n;
    novo->prox = NULL;
    
    if (*head == NULL) {
      *head = novo;
      *tail = novo;
    } else {
      (*tail)->prox = novo;
      *tail = novo;
    }
  } 
}

//libera espaço da fila
void destruirFila(Node *head) {
  Node *atual = head;
  Node *proximo;

  while (atual != NULL) {
     proximo = atual->prox;
    free(atual);
    atual = proximo;
  }
}

// imprime a fila
void printFila(Node *head) {
  while (head != NULL) {
    printf("%d-> ", head->numero);
    head = head->prox;
  }
  printf("NULL \n");
}

//--------- FUNÇÕES DA ARVORE
//struct
typedef struct arvore {
  int num;
  struct arvore *esq;
  struct arvore *dir;
} Arvore;

//inserir em arvore
void inserir(Arvore **t, int n) {
  if (*t == NULL) {
    *t = (Arvore *)malloc(sizeof(Arvore));
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

//liberar arvore
void liberarArvore(Arvore *raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);  // Liberar subárvore à esquerda
        liberarArvore(raiz->dir);  // Liberar subárvore à direita
        free(raiz);               // Liberar o próprio nó
    }
}

//função de percorrer a arvore com as condições de 
//(if a escolha recebida for de percorrer para direita:
// 1. o ponteiro agr vai verificar se esta apontando p null (if estivar imprima que o usuario ganhou e chegou ao final, se nao faça o ponteiro apontar para direita),
// 2. vai chamar a função de inserir em fila e armazenas esse nó, 
// 3. mostrar a fila para o usuario com a função de printar fila)
//(if a escolha recebida for de percorrer para esquerda, 
// 1. o ponteiro agr vai verificar se esta apontando p null (if estivar imprima que o usuario ganhou e chegou ao final, se nao faça o ponteiro apontar para esquerda
// 2. chamar a função de inserir em fila e armazenar esse no,
// 3. imprimir a fila para o usuario)
void percorrerArvore(Arvore *raiz, Node **head, int escolha) {//troquei Fila *head por Node *head
  Arvore *auxiliar = raiz; //ponteiro auxiliar p percorrer a arvore e n trar a raiz
  imprimirFila(*head); //tive que trocar por head, pq n tava achando fila (não tem criado com o nome fila)

  switch(escolha){
    case 1:
      if (auxiliar->dir == NULL){
        printf("Parabéns! Você chegou ao final do labirinto!\n");
        break;
      } 

      if (auxiliar->dir->num % 2 == 0){
        printf("Você errou! Voltando para o início.\n");
        inserirFila(head, head, auxiliar->num);
        *auxiliar = *raiz; //???? a value of type "Arvore **" cannot be assigned to an entity of type "Arvore"
        break;
      }else{ //ainda não chegou no final
        auxiliar = auxiliar->dir; //anda o auxiliar para a direita
        inserirFila(head, head, auxiliar->num); //coloca o numero na fila para depois ser printado
      }
    case 2:
      if (auxiliar->esq == NULL){
        inserirFila(head, head, auxiliar->num);
        printf("Parabéns! Você chegou ao final do labirinto!\n");
        break;
      } 

      if (auxiliar->esq->num % 2 == 0){
        printf("Você errou! Voltando para o início.\n");
        inserirFila(head, head, auxiliar->num);
        *auxiliar = *raiz; //???? a value of type "Arvore **" cannot be assigned to an entity of type "Arvore"
        break;
      }else{
        inserirFila(head, head, auxiliar->num);
        auxiliar = auxiliar->esq;
      }
  }
}

int main(){
  //criação da arvore - struct node foi criado la em cima
  Arvore *raiz = NULL;
  //montar a arvore - inserção de todos os nos com a função de inserção de arvore 
  inserir(&raiz, 101);
  inserir(&raiz, 125);
  inserir(&raiz, 117);
  inserir(&raiz, 110);
  inserir(&raiz, 120);
  inserir(&raiz, 140);
  inserir(&raiz, 139);
  inserir(&raiz, 155);
  inserir(&raiz, 55);
  inserir(&raiz, 10);
  inserir(&raiz, 73);
  inserir(&raiz, 7);
  inserir(&raiz, 20);
  inserir(&raiz, 60);
  inserir(&raiz, 87);

  //criação da fila - struct node foi criado la em cima
  Node *head = NULL;
  Node *tail = NULL;
  //int valorFila;
  //ja empilha o valor da raiz da arvore que é o primeiro no p mostrar
  inserirFila(&head, &tail, 300); //exemplo

  //varivael das escolhas
  int escolha;

  printf("Bem-vindo ao labirinto do País das Maravilhas!!!\n");
  printf("A Alice está perdida e precisa de sua ajuda para voltar pra casa em segurança.\n");
  printf("Você terá 5 chances para ajudá-la. Caso o contrário, a Rainha de Copas te matará!\n");
  printf("Boa sorte, jogador!\n");

  inserirFila(head, tail, 101);

  while (1){
    printf("\nEscolha:\n");
    printf("1 - Direita\n");
    printf("2 - Esquerda\n");
    printf("3 - Sair\n");
    scanf("%d", &escolha);

    //caso de saida do jogo
    if(escolha != 1 || escolha != 2){
      break;
    }

    //percorrer
    percorrerArvore(&raiz, &head, &escolha); 

    //liberar a arvore 
    liberarArvore(raiz); //como liberar uma arvore completa? no por no ou so a estrutura toda
  }

  destruirFila(head);
  return 0;
}