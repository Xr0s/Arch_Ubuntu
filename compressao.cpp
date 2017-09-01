#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;


#define MAX 100

typedef struct node{
	int valor;
	int freq;
	string code="";
	node* esq=NULL;
	node* dir=NULL;
}node;

struct fila_prioridade{
    int qtd;
    struct node dados[MAX];
};

typedef struct{
	int freq;
	int valor;
}Histograma;

typedef struct fila_prioridade FilaPrio;

node* extrair_min(FilaPrio* fp);
int inserir_no(FilaPrio* fp, int somafreq, int valor,node* x,node* y);
FilaPrio* cria_FilaPrio();
void libera_FilaPrio(FilaPrio* fp);
int insere_FilaPrio(FilaPrio* fp, int freq, int valor);
int remove_FilaPrio(FilaPrio* fp);
int tamanho_FilaPrio(FilaPrio* fp);
int estaCheia_FilaPrio(FilaPrio* fp);
int estaVazia_FilaPrio(FilaPrio* fp);
void imprime_FilaPrio(FilaPrio* fp);
//node* construir_arvore(FilaPrio* fp,Histograma* H, unsigned int N);
FilaPrio* construir_arvore(FilaPrio* fp,Histograma* H, unsigned int N);

unsigned int i=0;

FilaPrio* cria_FilaPrio(){
    FilaPrio *fp;
    fp = new FilaPrio[sizeof(struct fila_prioridade)];
    if(fp != NULL)
        fp->qtd = 0;
    return fp;
}

void libera_FilaPrio(FilaPrio* fp){
    free(fp);
}

//node* 
FilaPrio* construir_arvore(FilaPrio* fp,Histograma* H, unsigned int N) {

	unsigned int i;
	for(i = 0; i < N; i++)
			insere_FilaPrio(fp, H[i].freq,H[i].valor);
		while(tamanho_FilaPrio(fp) > 1){
			node* x = extrair_min(fp);
			node* y = extrair_min(fp);
			inserir_no(fp, x->freq + y->freq, 0xFFF, x, y);
	}
//return extrair_min(fp);
	remove_FilaPrio(fp);
	return fp;
}

void promoverElemento(FilaPrio* fp, int filho){
    int pai;
    node temp;
    pai = (filho - 1) / 2;
    while((filho > 0) && (fp->dados[pai].freq > fp->dados[filho].freq)){
        temp = fp->dados[filho];
        fp->dados[filho] = fp->dados[pai];
        fp->dados[pai] = temp;

        filho = pai;
        pai = (pai - 1) / 2;
    }
}

int insere_FilaPrio(FilaPrio* fp, int freq, int valor){
    if(fp == NULL)
        return 0;
    if(fp->qtd == MAX)//fila cheia
        return 0;
    /* insere na primeira posição livre */
    fp->dados[fp->qtd].valor = valor;
    fp->dados[fp->qtd].freq = freq;
    /* desloca elemento para posição correta */
    promoverElemento(fp,fp->qtd);
    /* incrementa número de elementos no heap */
    fp->qtd++;
    return 1;
}

int inserir_no(FilaPrio* fp, int somafreq, int valor, node* x, node* y){

    return 1;
}

void rebaixarElemento(FilaPrio* fp, int pai){
    node temp;
    int filho = 2 * pai + 1;
    while(filho < fp->qtd){

        if(filho < fp->qtd-1) /* verifica se tem 2 filhos */
            if(fp->dados[filho].freq > fp->dados[filho+1].freq)
                filho++; /*filho aponta para filho menor */

        if(fp->dados[pai].freq <= fp->dados[filho].freq)
            break; /* encontrou lugar */

        temp = fp->dados[pai];
        fp->dados[pai] = fp->dados[filho];
        fp->dados[filho] = temp;

        pai = filho;
        filho = 2 * pai + 1;
    }
}

int remove_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return 0;
    if(fp->qtd == 0)
        return 0;

    fp->qtd--;
    fp->dados[0] = fp->dados[fp->qtd];
    rebaixarElemento(fp,0);
    return 1;
}

node* extrair_min(FilaPrio* fp){
    node* x=&fp->dados[0];
    remove_FilaPrio(fp);
    return x;
}

int tamanho_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return -1;
    else
        return fp->qtd;
}

int estaCheia_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return -1;
    return (fp->qtd == MAX);
}

int estaVazia_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return -1;
    return (fp->qtd == 0);
}

void imprime_FilaPrio(FilaPrio* fp){
    if(fp == NULL)
        return;
    int i;
    for(i=0; i < fp->qtd ; i++){
        printf("%i) Prio: %d \tNome: %X\n",i,fp->dados[i].freq,fp->dados[i].valor);
    }
}

int main(int argc, char **argv){

	FilaPrio* fp = cria_FilaPrio();
	node* arvoreHuf=new node[MAX*2];
	Histograma* histograma = new Histograma[7];
	histograma[0].valor=0x10;
	histograma[0].freq=1;
	histograma[1].valor=0x20;
	histograma[1].freq=1;
	histograma[2].valor=0x30;
	histograma[2].freq=1;
	histograma[3].valor=0x40;
	histograma[3].freq=1;
	histograma[4].valor=0x50;
	histograma[4].freq=1;
	histograma[5].valor=0x60;
	histograma[5].freq=1;
	histograma[6].valor=0x70;
	histograma[6].freq=1;
	fp=construir_arvore(fp, histograma, 7);
	imprime_FilaPrio(fp);
	
	return 0;
}	
