#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX 60

typedef struct disciplinas{ //Estrutura com o nome da disciplina, nota da disciplina e endereço para proximo elemento da lista
	char disciplina[50];
	float nota;
	struct disciplinas *prox;
}materia;

typedef struct aluno{ //Estrutura com as informações do aluno
	char rgm[8];
	char nome[50];
	materia *disciplinas;
	int num_Disci;
	materia * ultimo;
}alu;

typedef struct list{ //Lista sequencial de alunos
	alu vetor[MAX];
	int n;
}lis;

lis criar(){ //Cria a lista
	lis lista;
	lista.n = -1;
	return lista;
}

int cheioRG(lis * p){ //Verifica se a lista esta cheia
	return (p -> n == MAX - 1);
}

int addRGM(char rg[8],char nome[50], lis * p){ //Adiciona um RGM à lista
	(p -> n)++;
	int x = p -> n;
	
	strcpy((*p).vetor[x].rgm, rg);
	strcpy((*p).vetor[x].nome, nome);
	(*p).vetor[x].num_Disci = 0;
	
	return 1;
}
void adicionar_disciplina(alu *aluno, char *disciplina, float nota) { //Adiciona uma disciplina e uma nota à lista encadeada
    materia *nova_disciplina = (materia*) malloc(sizeof(materia));
	strcpy(nova_disciplina->disciplina, disciplina);
    nova_disciplina->nota = nota;
	nova_disciplina->prox = NULL;
    if(aluno->num_Disci == 0){ //Adição da primeria disciplina
		aluno->disciplinas = nova_disciplina;
    	aluno->ultimo = nova_disciplina;
	   	aluno->num_Disci = 1;
	}else{
    	materia * alun = aluno->ultimo;
    	alun->prox = nova_disciplina;
	aluno->ultimo = nova_disciplina;
    }
}


int remover_aluno(lis *lista, char *rgm) { //Remove um RGM da lista
    int i;
    for (i = 0; i <= lista->n; i++) {
        if (strcmp(lista->vetor[i].rgm, rgm) == 0) break;
    }
    if (i > lista->n) return 0;

    materia *disciplina = lista->vetor[i].disciplinas;
    while (disciplina != NULL) {
        materia *prox = disciplina->prox;
        free(disciplina);
        disciplina = prox;
    }

    for (; i < lista->n; i++) {
        lista->vetor[i] = lista->vetor[i+1];
    }
    lista->n--;
    return 1;
}

int remover_disciplina(lis *lista, char *rgm, char *disciplina) { //Remove uma disciplina com sua nota de um RGM específico
    int i;
    for (i = 0; i <= lista->n; i++) {
        if (strcmp(lista->vetor[i].rgm, rgm) == 0) break;
    }
    if (i > lista->n) return 0;

    materia *atual = lista->vetor[i].disciplinas;
    materia *anterior = NULL;
    while (atual != NULL && strcmp(atual->disciplina, disciplina) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) return 0;

    if (anterior == NULL) {
        lista->vetor[i].disciplinas = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual);
    
    return 1;

}

int main() {
	setlocale(0,"Portuguese");
	
	int men, ad;
	char RG[8];
	char disciplina [50];
	char nome[50];
    float nota;
	
	lis List = criar();
	
	while(men != 7){ //Menu de opções para alterar a lista de alunos
		printf("\t\t\t\t\t\tLista de Alunos\n");
		printf("\tDigite\n\t1 para vizualiar a lista\n\t2 para adicionar um RGM a lista\n\t3 para procurar por um RGM\n\t4 para adicionar disciplina(s) a algum RGM\n\t5 Apagar aluno pelo RGM \n\t6 Apagar alguma disciplina por RGM\n\t7 Encerrar Programa\n\n\t");
		scanf("%d", &men);
		system("cls");
		switch(men){
			case 1:{
				// 1 para vizualiar a lista
				printf("\t\t\t\t\t\tLista de Alunos\n");
				int i = 0;
                for ( i = 0; i <= List.n; i++) {
                    printf("RGM: %s\n", List.vetor[i].rgm);
                    printf("Nome: %s\n", List.vetor[i].nome);
                    printf("Disciplinas:\n");
                    materia *disciplin = List.vetor[i].disciplinas;
                    while (disciplin != NULL) {
                        printf("- %s: %.1f\n", disciplin->disciplina, disciplin->nota);
                		disciplin = disciplin->prox;
                    }
                    printf("\n");
                }
                if(List.n == -1){
                	printf("\tLista vazia\n");
				}
             	system("pause");
                system("cls");
                break;
			}
			case 2:{
				// 2 para adicionar um RGM a lista
				 printf("\t\t\t\t\t\tLista de Alunos\n");
                if(cheioRG(&List) == 0){
                    printf("\tDigite o RGM: ");
                    scanf("%s", RG);
                    printf("\tDigite o nome: ");
                    scanf("%s", nome);
                    
                    addRGM(RG, nome, &List);
                    
                    printf("\n\tRGM adicionado\n\n");
                    system("pause");
                    system("cls");
                }else{
                    printf("Lista cheia\n\n");
                    system("pause");
                    system("cls");
                }
     		break;
			}
			case 3:{
				// 3 para procurar por um RGM
				printf("\t\t\t\t\t\tLista de Alunos\n");
                printf("\tDigite o RGM: ");
                scanf("%s", RG);
                
                int i;
                for (i = 0; i <= List.n; i++) {
                    if (strcmp(List.vetor[i].rgm, RG) == 0) break;
                }
                if (i > List.n) {
                    printf("Aluno n?o encontrado.\n");
                } else {
                    printf("RGM: %s\n", List.vetor[i].rgm);
                    printf("Nome: %s\n", List.vetor[i].nome);
                    printf("Disciplinas:\n");
                    materia *disciplina = List.vetor[i].disciplinas;
                    while (disciplina != NULL) {
                        printf("- %s\n", disciplina->disciplina, disciplina->nota);
                        disciplina = disciplina->prox;
                    }
                }
             	system("pause");
                system("cls");
                break;
			}
			case 4:{
				// 4 para adicionar disciplina(s) a algum RGM
				printf("\t\t\t\t\t\tLista de Alunos\n");
                printf("\tDigite o RGM: ");
                scanf("%s", RG);
                int i =0;
                for (i = 0; i <= List.n; i++) {
                    if (strcmp(List.vetor[i].rgm, RG) == 0) break;
                }
                if (i > List.n) {
                    printf("\tAluno não encontrado.\n");
                } else {
                    char continuar;
                    do {
                        printf("\tDigite o nome da disciplina: ");
                        scanf("%s", disciplina);
                        printf("\tDigite a nota da disciplina: ");
                        scanf("%f", &nota);
                        adicionar_disciplina(&List.vetor[i], disciplina, nota);

                        printf("\tMais disciplina? (S/N): ");
                        scanf(" %c", &continuar);
                    } while (continuar == 'S' || continuar == 's');
                }
             	system("pause");
            	system("cls");
               break;
			}
			case 5:{
				// 5 Apagar aluno pelo RGM
				printf("\tDigite o RGM do aluno que deseja remover: ");
                scanf("%s", RG);
                
                if (remover_aluno(&List, RG)) {
                    printf("Aluno removido com sucesso.\n");
                } else {
                    printf("Aluno não encontrado no sistema.\n");
                }
             	system("pause");
                system("cls");
                break;
			}
			case 6:{
				// 6 Apagar alguma disciplina por RGM
				printf("\tDigite o RGM do aluno: ");
                scanf("%s", RG);
                printf("\tDigite o nome da disciplina: ");
                scanf("%s", disciplina);

                if (remover_disciplina(&List, RG, disciplina)) {
                    printf("Disciplina removida com sucesso.\n");
                } else {
                    printf("Aluno ou disciplina não encontrados.\n");
                }
                
             	system("pause");
                system("cls");
                break;
			}
			
			case 7:{
				// 7 Encerrar Programa
				men = 7;
				break;
			}
		}
	}
	
 return 0;
}
