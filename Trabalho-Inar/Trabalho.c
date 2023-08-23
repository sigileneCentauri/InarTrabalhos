#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do n� da �rvore
struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
};

// Fun��o para criar um novo n�
struct No* criarNo(int valor) {
    // Aloca mem�ria para um novo n�
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    // Define o valor do n� como o valor fornecido
    novoNo->valor = valor;
    // Inicializa os ponteiros esquerdo e direito como NULL
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    // Retorna o novo n� criado
    return novoNo;
}

// Fun��o para inserir um n� na �rvore
struct No* inserirNo(struct No* raiz, int valor) {
    // Se a raiz for NULL, cria um novo n� com o valor fornecido
    if (raiz == NULL) {
        return criarNo(valor);
    }

    // Caso contr�rio, insere o n� na sub�rvore esquerda ou direita
    if (valor < raiz->valor) {
        raiz->esquerda = inserirNo(raiz->esquerda, valor);
    } else {
        raiz->direita = inserirNo(raiz->direita, valor);
    }

    // Retorna a raiz atualizada da �rvore
    return raiz;
}

// Fun��o para buscar em profundidade (pr�-ordem)
void buscarProfundidade(struct No* raiz) {
    // Se a raiz n�o for NULL
    if (raiz != NULL) {
        // Imprime o valor do n� atual
        printf("%d ", raiz->valor);
        // Chama a busca em profundidade para a sub�rvore esquerda
        buscarProfundidade(raiz->esquerda);
        // Chama a busca em profundidade para a sub�rvore direita
        buscarProfundidade(raiz->direita);
    }
}

// Fun��o para buscar em largura (ordem de n�vel)
void buscarLargura(struct No* raiz) {
    // Se a raiz for NULL, n�o h� nada para buscar
    if (raiz == NULL) {
        return;
    }

    // Cria uma fila para armazenar os n�s a serem explorados
    struct No* fila[100];
    int frente = 0;
    int tras = 0;

    // Enfileira a raiz para come�ar a busca
    fila[tras++] = raiz;

    // Enquanto h� elementos na fila
    while (frente < tras) {
        // Remove o primeiro elemento da fila (o n� atual)
        struct No* atual = fila[frente++];
        // Imprime o valor do n� atual
        printf("%d ", atual->valor);

        // Enfileira os filhos (se existirem)
        if (atual->esquerda != NULL) {
            fila[tras++] = atual->esquerda;
        }
        if (atual->direita != NULL) {
            fila[tras++] = atual->direita;
        }
    }
}

struct Pilha {
    struct No* elementos[100];
    int topo;
};

void inicializarPilha(struct Pilha* pilha) {
    // Inicializa o topo da pilha como -1
    pilha->topo = -1;
}

void empilhar(struct Pilha* pilha, struct No* elemento) {
    // Incrementa o topo e armazena o elemento na pilha
    pilha->topo++;
    pilha->elementos[pilha->topo] = elemento;
}

struct No* desempilhar(struct Pilha* pilha) {
    // Obt�m o elemento do topo, decrementa o topo e retorna o elemento
    struct No* elemento = pilha->elementos[pilha->topo];
    pilha->topo--;
    return elemento;
}

int buscarEArmazenarCaminho(struct No* raiz, int alvo, struct Pilha* pilha) {
    // Se a raiz for NULL, n�o encontrou o alvo
    if (raiz == NULL) {
        return 0;
    }

    // Se o valor da raiz for o alvo, empilha o n� e retorna 1
    if (raiz->valor == alvo) {
        empilhar(pilha, raiz);
        return 1;
    }

    // Tenta buscar o alvo na sub�rvore esquerda ou direita
    // Se encontrado, empilha o n� e retorna 1
    if (buscarEArmazenarCaminho(raiz->esquerda, alvo, pilha) ||
        buscarEArmazenarCaminho(raiz->direita, alvo, pilha)) {
        empilhar(pilha, raiz);
        return 1;
    }

    // Alvo n�o encontrado nesta sub�rvore
    return 0;
}

// Fun��o para buscar por profundidade um n� com valor x e empilhar elementos
// dos caminhos nos respectivos n�s
int buscarProfundidadeX(struct No* raiz, int alvo, struct Pilha* pilha) {
    if (raiz == NULL) {
        return 0;
    }

    empilhar(pilha, raiz);

    if (raiz->valor == alvo) {
        printf("Caminho para encontrar %d: ", alvo);
        int i;
        for (i = 0; i <= pilha->topo; i++) {
            printf("%d ", pilha->elementos[i]->valor);
        }
        printf("\n");
        return 1; // Retorna 1 quando o n� alvo � encontrado
    }

    int encontrado = buscarProfundidadeX(raiz->esquerda, alvo, pilha) ||
                     buscarProfundidadeX(raiz->direita, alvo, pilha);

    desempilhar(pilha);

    return encontrado;
}

// Fun��o para mostrar de forma ordenada os caminhos para encontrar
// os diversos n�s x na �rvore
void mostrarCaminhosOrdenados(struct No* raiz, int* alvos, int numAlvos) {
    struct Pilha caminhoPilha;
    inicializarPilha(&caminhoPilha);
    int i;
    for (i = 0; i < numAlvos; i++) {
        int encontrados = 0;
        printf("Caminhos ordenados para encontrar %d:\n", alvos[i]);

        // Busca e mostra pelo menos dois caminhos para cada n� alvo
        while (encontrados < 2) {
            if (buscarProfundidadeX(raiz, alvos[i], &caminhoPilha)) {
                encontrados++;
            } else {
                break; // Se n�o encontrar mais caminhos, para
            }
        }
    }
}


int main() {
    struct No* raiz = NULL;
    
    // Inserindo 20 n�s na �rvore
    int valores[] = {10, 5, 15, 3, 8, 12, 18, 2, 4, 7, 9, 11, 14, 17, 20, 1, 6, 13, 16, 19};
    int i=0;
    for (i; i < 20; i++) {
        raiz = inserirNo(raiz, valores[i]);
    }

    // Busca em profundidade
    printf("Busca por profundidade: ");
    buscarProfundidade(raiz);
    printf("\n");

    // Busca em largura
    printf("Busca em largura: ");
    buscarLargura(raiz);
    printf("\n");

    // Inicializa a pilha para armazenar o caminho
    struct Pilha caminhoPilha;
    inicializarPilha(&caminhoPilha);

    
    // N�s a serem buscados
    int alvos[] = {11};
    int numAlvos = sizeof(alvos) / sizeof(alvos[0]);

    // Mostra os caminhos ordenados para os n�s alvos
    mostrarCaminhosOrdenados(raiz, alvos, numAlvos);

    return 0;
}

