#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
bool venceu; //para indicar se venceu ou não

//-------------- FILA ---------------
typedef struct Fila{ //struct da fila
  int numero;
  struct Fila *prox;
} Fila;
void inserirFila (Fila **head, Fila **tail, int n); //inserir numero da árvore na fila 
void destruirFila (Fila *head); //liberar memória da fila
void imprimirFila (Fila *head); //printar a fila

//-------------- ÁRVORE ---------------
typedef struct Arvore{
  int num;
  struct Arvore *esq;
  struct Arvore *dir;
} Arvore;
void inserirArvore (Arvore **raiz, int n); //inserir nó na árvore
void liberarArvore (Arvore *raiz); //liberar a árvore
void percorrerArvore(Arvore **raiz, Arvore *raizOriginal, Fila **head, Fila **tail, int escolha, int *vidas); //percorrer e verificar as escolhas dentro da árvore

//-------------- MAIN --------------
int main(){
  Arvore *raiz = NULL; // criação da arvore - struct node foi criado la em cima
  Fila *head = NULL; // criação da fila - struct node foi criado la em cima
  Fila *tail = NULL;
  int escolha; //variável das escolhas
  int vidas = 2; //quantidade de vidas

  inserirArvore(&raiz, 101); // montar a arvore - inserção de todos os nos com a função de inserção de arvore
  inserirArvore(&raiz, 125);
  inserirArvore(&raiz, 117);
  inserirArvore(&raiz, 110);
  inserirArvore(&raiz, 120);
  inserirArvore(&raiz, 140);
  inserirArvore(&raiz, 139);
  inserirArvore(&raiz, 155);
  inserirArvore(&raiz, 55);
  inserirArvore(&raiz, 10);
  inserirArvore(&raiz, 73);
  inserirArvore(&raiz, 7);
  inserirArvore(&raiz, 20);
  inserirArvore(&raiz, 60);
  inserirArvore(&raiz, 87);
  Arvore *raizOriginal = raiz;

  printf("Bem-vindo ao labirinto do País das Maravilhas!!!\n");
  printf("A Alice está perdida e precisa de sua ajuda para voltar pra casa em segurança.\n");
  printf("Você terá 5 chances para ajudá-la. Caso o contrário, a Rainha de Copas te matará!\n");
  printf("Boa sorte, jogador!\n");

  inserirFila(&head, &tail, 101); //inserindo a raiz como primeiro elementa da fila

  while(1){
    printf("\nEscolha:\n");
    printf("1 - Direita\n");
    printf("2 - Esquerda\n");
    printf("3 - Sair\n");
    scanf("%d", &escolha);

    if (escolha != 1 && escolha != 2 ){ // caso de saida do jogo
      break;
    }

    percorrerArvore(&raiz, raizOriginal, &head, &tail, escolha, &vidas); //percorrer

    if(venceu){
      printf("Parabéns, você chegou ao fim do labirinto!\n");
      printf("Alice chegou em segurança em casa.\n");
      printf("VOCÊ VENCEU O JOGO!!!\n");
      liberarArvore(raiz);
      destruirFila(head);
      break;
    }

    if (vidas <= 0) {
        printf("Você perdeu todas as vidas. A Rainha de Copas te pegou!\n");
        liberarArvore(raiz);
        destruirFila(head);
        break;
    }

  }
  liberarArvore(raiz);
  destruirFila(head);
  return 0;
}

//-------------- FUNÇÕES DA FILA --------------
void inserirFila (Fila **head, Fila **tail, int n){ //inserir numero da árvore na fila
  Fila *novo = (Fila *)malloc(sizeof(Fila));

  if(novo != NULL){
    novo->numero = n;
    novo->prox = NULL;

    if(*head == NULL){
      *head = novo;
      *tail = novo;
    }else{
      (*tail)->prox = novo;
      *tail = novo;
    }
  }
}

void destruirFila (Fila *head){ //liberar memória da fila
  Fila *atual = head;
  Fila *proximo;

  while(atual != NULL){
    proximo = atual->prox;
    free(atual);
    atual = proximo;
  }
}

void imprimirFila(Fila *head){ //printar a fila
  while (head != NULL){
    printf("%d", head->numero);
    if (head->prox != NULL) { //Verifica se o próximo é NULL antes de imprimir a seta e avançar
      printf(" -> ");
      head = head->prox;
    }else{
      break; // Se o próximo é NULL, pare o loop
    }
  }
  printf("\n");
}

//-------------- FUNÇÕES DA ÁRVORE --------------
void inserirArvore (Arvore **raiz, int n){ //inserir nó na árvore
  if(*raiz == NULL){
    *raiz = (Arvore *)malloc(sizeof(Arvore));
    (*raiz)->esq = NULL;
    (*raiz)->dir = NULL;
    (*raiz)->num = n;
  }else{
    if(n < (*raiz)->num){
      inserirArvore(&(*raiz)->esq, n);
    }
    if (n > (*raiz)->num){
      inserirArvore(&(*raiz)->dir, n);
    }
  }
}

void liberarArvore (Arvore *raiz){ //liberar a árvore
  if (raiz != NULL){
    liberarArvore(raiz->esq); //Liberar subárvore à esquerda
    liberarArvore(raiz->dir); //Liberar subárvore à direita
    free(raiz); //Liberar o próprio nó
  }
}

void percorrerArvore(Arvore **raiz, Arvore *raizOriginal, Fila **head, Fila **tail, int escolha, int *vidas){ //percorrer e verificar as escolhas dentro da árvore
  if (escolha == 1){ //1 - direita
    *raiz = (*raiz)->dir;
  }else if (escolha == 2){ //2 - esquerda
    *raiz = (*raiz)->esq;
  }

  if ((*raiz)->dir == NULL && (*raiz)->esq == NULL && (*raiz)->num % 2 != 0){ //se o lado direito ou esquerdo forem nulos, chegou ao fim do labirinto, e o número é impar
    //inserirFila(head, tail, (*raiz)->num);
    //imprimirFila(*head);
    venceu = true; //mensagens na main
  }

  inserirFila(head, tail, (*raiz)->num);

  if((*raiz)->num % 2 == 0){ //se o num for par
    printf("Você errou o caminho, voltando para o início do labirinto.\n");
    imprimirFila(*head);

    destruirFila(*head);
    *head = NULL;
    *tail = NULL;
    *raiz = raizOriginal; //reseta para a raíz original

    inserirFila(head, tail, raizOriginal->num); //reinsere a raiz original na fila para a próxima tentativa

    (*vidas)--;
    printf("Você tem %d vidas restantes.\n", *vidas);
  }else{
    imprimirFila(*head);  //imprime a fila se o usuário não errou
    printf("Você está indo bem! continue assim.\n");
  }
}