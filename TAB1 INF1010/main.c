#include <stdio.h>
#include <stdlib.h>


#define MAX_LINHA 20
#define MAX_LINHAS 20

// criar struct para paciente
typedef struct paciente Paciente;
struct paciente {
	int senha;
    char* cor;
	Paciente* prox;
};

// função para imprimir a lista
void imprime_pacientes (Paciente* pacientes) {
	Paciente* p;
	for (p = pacientes; p != NULL; p = p->prox)
		printf("senha = % d\n", p->senha);
	printf("fim");
}

// função para verificar a prioridade do paciente
int verifica_prioridade(const char* cor) {
    if (strcmp(cor, "vermelha") == 0) return 1;
    if (strcmp(cor, "amarela") == 0) return 2;
    if (strcmp(cor, "verde") == 0) return 3;
    return 4; // cor inválida
}

// - função para criar lista de pacientes
Paciente* cria_lista(void) {
	return NULL;
}

// função para inserir o paciente na lista de acordo com sua prioridade
void insere_paciente(Paciente** lista, int senha, const char* cor) {
    Paciente* novo = malloc(sizeof(Paciente));
    novo->senha = senha;
    strcpy(novo->cor, cor);
    novo->prox = NULL;

    // Inserção ordenada
    if (*lista == NULL ||
        prioridade_cor(cor) < prioridade_cor((*lista)->cor) ||
        (prioridade_cor(cor) == prioridade_cor((*lista)->cor) && senha < (*lista)->senha)) {
        novo->prox = *lista;
        *lista = novo;
        return;
    }

    Paciente* atual = *lista;
    while (atual->prox != NULL &&
        (prioridade_cor(cor) > prioridade_cor(atual->prox->cor) ||
            (prioridade_cor(cor) == prioridade_cor(atual->prox->cor) && senha > atual->prox->senha))) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

// função para remover um paciente quando ele for atendido
void remove_paciente(Paciente** lista, int senha) {
    Paciente* atual = *lista;
    Paciente* anterior = NULL;

    while (atual != NULL && atual->senha != senha) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (anterior == NULL) {
            *lista = atual->prox;
        }
        else {
            anterior->prox = atual->prox;
        }
        free(atual);
    }
}


// função lê_arquivo (lê e insere o paciente na lista)
char** le_arquivo(void) {
    FILE* arquivo = fopen("dados_trabalho1", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    Paciente* pacientes;
    char* linha;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';

        char tipo;
        int senha;
        char cor[20];
        sscanf(linha, "%c-%d-%s", &tipo, &senha, cor);

        if (tipo == 'c') {
            inserir_paciente(&pacientes, senha, cor);
        }
        else if (tipo == 'a') {
            remover_paciente(&pacientes, senha);
        }
    }

    fclose(arquivo);

    return pacientes;
}


//- ordena_paciente(verifica onde deve ser inserido

int main(void) {

    Paciente* fila = le_arquivo();
    imprime_pacientes(fila);

	// lembrar de dar free na lista
	return 0;
}


