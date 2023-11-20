#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <unistd.h>
bool venceu; // para indicar se venceu ou não

//-------------- FILA ---------------
typedef struct Fila { // struct da fila
  int numero;
  struct Fila *prox;
} Fila;
void inserirFila(Fila **head, Fila **tail, int n); // inserir numero da árvore na fila
void destruirFila(Fila *head); // liberar memória da fila
void imprimirFila(Fila *head); // printar a fila
void ordenarFila(Fila **head); // insertion sort para ordernar

//-------------- ÁRVORE ---------------
typedef struct Arvore {
  int num;
  struct Arvore *esq;
  struct Arvore *dir;
} Arvore;
void inserirArvore(Arvore **raiz, int n); // inserir nó na árvore
void liberarArvore(Arvore *raiz); // liberar a árvore
void percorrerArvore(Arvore **raiz, Arvore *raizOriginal, Fila **head, Fila **tail, int escolha, int *vidas); // percorrer e verificar as escolhas dentro da árvore

//-------------- MAIN --------------
int main() {
  Arvore *raiz = NULL; // criação da arvore - struct node foi criado la em cima
  Fila *head = NULL; // criação da fila - struct node foi criado la em cima
  Fila *tail = NULL;
  int escolha; // variável das escolhas
  int vidas = 2; // quantidade de vidas

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

  printf("     __          __             _           _                 _   __  __               \n");
  printf("     \\ \\        / /            | |         | |               | | |  \\/  |              \n");
  printf("      \\ \\  /\\  / /__  _ __   __| | ___ _ __| | __ _ _ __   __| | | \\  / | __ _ _______ \n");
  printf("       \\ \\/  \\/ / _ \\| '_ \\ / ` |/ _ \\ '__| |/ _` | ' \\ / ` | | |\\/| |/ _` |  / _ \\\n");
  printf("        \\  /\\  / (_) | | | | (_| |  __/ |  | | (_| | | | | (_| | | |  | | (_| |/ /  __/\n");
  printf("         \\/  \\/ \\___/|_| |_|\\__,_|\\___|_|  |_|\\__,_|_| |_|\\__,_| |_|  |_|\\__,_/___\\___|\n");
  printf("\n");

  printf("                                      !!!Bem-vindo!!!\n");
  printf("A Alice esta perdida e precisa de sua ajuda para voltar pra casa em seguranca.\n");
  printf("Voce tera 5 chances para ajuda-la. Caso o contrario, a Rainha de Copas te matara!\n");
  printf("Boa sorte, jogador!\n");

  printf("                                         - 101 -\n");
  printf("                                        /       \\\n");
  printf("                                       /         \\\n");
  printf("                                  -  55           125  -\n");
  printf("                                   /   \\         /   \\\n");
  printf("                                  10   73      117    140\n");
  printf("                                 / \\   / \\     / \\    / \\\n");
  printf("                                7  20 60  87 110 120 139 155\n");

  inserirFila(&head, &tail, 101); // inserindo a raiz como primeiro elementa da fila

  while (1){
    printf("\nEscolha:\n");
    printf("1 - Direita\n");
    printf("2 - Esquerda\n");
    printf("3 - Sair\n");
    scanf("%d", &escolha);

    if (escolha != 1 && escolha != 2) { // caso de saida do jogo
      printf("Encerrando o jogo...");
      liberarArvore(raiz);
      destruirFila(head);
      break;
    }

    percorrerArvore(&raiz, raizOriginal, &head, &tail, escolha, &vidas); // percorrer

    if (venceu) {
      printf("Parabens, voce chegou ao fim do labirinto!\n");
      printf("Alice chegou em seguranca em casa.\n");
      printf("VOCE VENCEU O JOGO!!!\n");
      
      printf("\nAqui esta o caminho certo do labirinto de forma ordenada.\n");
      printf("Agora voce pode jogar na Mega da Virada :)\n");
      ordenarFila(&head); // chama a função para ordenar a fila
      imprimirFila(head); // imprime a fila ordenada
      
      liberarArvore(raiz);
      destruirFila(head);
      break;
    }

    if (vidas <= 0) {
      printf("Voce perdeu todas as vidas. A Rainha de Copas te pegou!\n");
      printf("Encerrando o jogo...");
      liberarArvore(raiz);
      destruirFila(head);
      break;
    }
  }
  liberarArvore(raiz);
  destruirFila(head);
  sleep(15000);
  return 0;
}

//-------------- FUNÇÕES DA FILA --------------
void inserirFila(Fila **head, Fila **tail, int n){ // inserir numero da árvore na fila
  Fila *novo = (Fila *)malloc(sizeof(Fila));

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

void destruirFila(Fila *head){ // liberar memória da fila
  Fila *atual = head;
  Fila *proximo;

  while (atual != NULL) {
    proximo = atual->prox;
    free(atual);
    atual = proximo;
  }
}

void imprimirFila(Fila *head){ // printar a fila
  while (head != NULL){
    printf("%d", head->numero);
    if (head->prox != NULL) { // verifica se o próximo é NULL antes de imprimir a seta e avançar
      printf(" -> ");
      head = head->prox;
    }else{
      break; // se o próximo é NULL, pare o loop
    }
  }
  printf("\n");
}

void ordenarFila(Fila **head){
  if (*head == NULL || (*head)->prox == NULL) { //a fila está vazia ou tem apenas um elemento, já está ordenada
    return;
  }

  Fila *atual = *head;
  Fila *proximo = atual->prox;
  *head = NULL; //nova cabeça da fila

  while (atual != NULL) {
    Fila *temp = proximo;
    Fila **posicao = head;

    while (*posicao != NULL && (*posicao)->numero < atual->numero) {
      posicao = &(*posicao)->prox;
    }

    atual->prox = *posicao;
    *posicao = atual;
    atual = temp;
    
    if (temp != NULL) {
      proximo = temp->prox;
    }
  }
}

//-------------- FUNÇÕES DA ÁRVORE --------------
void inserirArvore(Arvore **raiz, int n) { // inserir nó na árvore
  if (*raiz == NULL) {
    *raiz = (Arvore *)malloc(sizeof(Arvore));
    (*raiz)->esq = NULL;
    (*raiz)->dir = NULL;
    (*raiz)->num = n;
  } else {
    if (n < (*raiz)->num) {
      inserirArvore(&(*raiz)->esq, n);
    }
    if (n > (*raiz)->num) {
      inserirArvore(&(*raiz)->dir, n);
    }
  }
}

void liberarArvore(Arvore *raiz) { // liberar a árvore
  if (raiz != NULL) {
    liberarArvore(raiz->esq); // liberar subárvore à esquerda
    liberarArvore(raiz->dir); // liberar subárvore à direita
    free(raiz); //liberar o próprio nó
  }
}

void percorrerArvore(Arvore **raiz, Arvore *raizOriginal, Fila **head, Fila **tail, int escolha, int *vidas) { // percorrer e verificar as escolhas dentro da árvore
  if (escolha == 1) { // 1 - direita
    *raiz = (*raiz)->dir;
  } else if (escolha == 2) { // 2 - esquerda
    *raiz = (*raiz)->esq;
  }

  if ((*raiz)->dir == NULL && (*raiz)->esq == NULL && (*raiz)->num % 2 != 0) { // se o lado direito ou esquerdo forem nulos, chegou ao fim do labirinto, e o número é impar
    venceu = true; // mensagens na main
  }

  inserirFila(head, tail, (*raiz)->num);

  if ((*raiz)->num % 2 == 0) { // se o num for par
    printf("Voce errou o caminho, voltando para o inicio do labirinto.\n");
    imprimirFila(*head);

    destruirFila(*head);
    *head = NULL;
    *tail = NULL;
    *raiz = raizOriginal; // reseta para a raíz original

    inserirFila(head, tail, raizOriginal->num); // reinsere a raiz original na fila para a próxima tentativa

    (*vidas)--;
    printf("Voce tem %d vidas restantes.\n", *vidas);

  } else {
    imprimirFila(*head); // imprime a fila se o usuário não errou
    printf("Voce esta indo bem! continue assim.\n");
  }
}