#include <stdio.h>
#include <stdlib.h>
#define X 10

typedef struct node Node;

struct node {
    int num;
    Node* prox;
};

int imprimeVetoresIntercalados(int * par, int * impar, int indice) {
	if (indice == X) return 0;

	int retirado = -1;

	printf("%d ", impar[indice]);
	impar[indice] = retirado;
	printf("(retirado)\n");

	printf("%d ", par[indice]);
	par[indice] = retirado;
	printf("(retirado)\n");

	return imprimeVetoresIntercalados(par, impar, indice + 1);
}

int imprimeVetoresVazios(int * par, int * impar, int indice) {
    if (indice == X) return 0;

	printf("par %d: %d\n", (indice + 1), par[indice]);
    printf("impar %d: %d\n", (indice + 1), impar[indice]);

	return imprimeVetoresVazios(par, impar, indice + 1);
}


void imprimeListaEncadeada(Node* n) {
    if (n == NULL) {
        printf("NULL\n");
        return;
    }
    printf("%d -> ", n->num);
    imprimeListaEncadeada(n->prox);
}

int imprimeVetores(int *par, int *impar, int indice) {
    if (indice == X) return 0;

    int retirado = -1;
    
    printf("%d ", impar[indice]);
    impar[indice] = retirado;
    printf("(retirado)\n");

    printf("%d ", par[indice]);
    par[indice] = retirado;
    printf("(retirado)\n");

    return imprimeVetores(par, impar, indice + 1);
}

Node* CriaStruct(int n, Node* ant) {
    Node* n1 = (Node*)malloc(sizeof(Node));
    if (n1 == NULL) {
        printf("Erro na alocacao de memoria.\n");
        return NULL;
    }
    n1->num = n;
    n1->prox = ant;
    return n1;
}

Node* CriaLista(int v[], int n) {
    Node* lista = NULL;
    for (int i = n - 1; i >= 0; i--) {
        lista = CriaStruct(v[i], lista);
    }
    return lista;
}

Node* intercalaListas(Node* par, Node* impar) {
    Node temp;
    Node* atual = &temp;
    temp.prox = NULL;  
    Node* aux;

    while (par && impar) {
        printf("Retirando %d da lista de ímpares\n", impar->num);
        atual->prox = impar;
        impar = impar->prox;
        atual = atual->prox;
        imprimeListaEncadeada(impar);
        
        printf("Retirando %d da lista de pares\n", par->num);
        atual->prox = par;
        par = par->prox;
        atual = atual->prox;
        imprimeListaEncadeada(par);
    }

    if (impar) {
        atual->prox = impar;
    }

    if (par) {
        atual->prox = par;
    }

    return temp.prox; 
}


int par[X] = { 10, 20, 30, 34, 36, 38, 50, 60, 62, 70 };
int impar[X] = { 9, 11, 13, 33, 35, 41, 43, 55, 61, 71 };

int main(void) {
    Node* listaPar = CriaLista(par, X);
    Node* listaImpar = CriaLista(impar, X);
    
    printf("Intercalando listas encadeadas: \n");
    Node* listaIntercalada = intercalaListas(listaPar, listaImpar);
    
    printf("Lista intercalada (encadeada): \n");
    imprimeListaEncadeada(listaIntercalada);

    printf("\n");
    
    printf("Impressao a partir de vetores:\n");
	imprimeVetoresIntercalados(par, impar, 0);

	printf("Impressao de verificacao de numeros retirados dos vetores:\n");
	imprimeVetoresVazios(par, impar, 0);

    return 0;
}
