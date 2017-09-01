#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2


ifstream entrada;

FILE* input;
FILE* output;

#define MAX 10000
#define RANGE 255

typedef struct node{
	int valor;
	int freq;
	string code="";
	node* esq=NULL;
	node* dir=NULL;
}node;

struct fila_prioridade{
    int qtd;
    struct node* dados=new node[MAX];
};

typedef struct{
	int freq=0;
	int valor;
}Histograma;

typedef struct fila_prioridade FilaPrio;

int inserir_Unico(FilaPrio* fp, int somafreq, node* x, node* arvoreHuff);
node* extrair_min(FilaPrio* fp);
int inserir_no(FilaPrio* fp, int somafreq, node* x, node* y, node* arvoreHuff);
FilaPrio* cria_FilaPrio();
void libera_FilaPrio(FilaPrio* fp);
int insere_FilaPrio(FilaPrio* fp, int freq, int valor,node* x, node* y);
int remove_FilaPrio(FilaPrio* fp);
int tamanho_FilaPrio(FilaPrio* fp);
int estaCheia_FilaPrio(FilaPrio* fp);
int estaVazia_FilaPrio(FilaPrio* fp);
void imprime_FilaPrio(FilaPrio* fp);
void construir_arvore(FilaPrio* fp,Histograma* H, unsigned int N, node* arvoreHuff);


unsigned int HOFF=0;
node* HEAD;

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

void construir_arvore(FilaPrio* fp,Histograma* H, unsigned int N, node* arvoreHuff) {

	unsigned int i;
	for(i = 0; i < N; i++)
			insere_FilaPrio(fp, H[i].freq,H[i].valor,NULL,NULL);
		while(tamanho_FilaPrio(fp) > 1){
			node* x = extrair_min(fp);
			node* y = extrair_min(fp);
			inserir_no(fp, x->freq + y->freq, x, y, arvoreHuff);
		}
		
			node* z = extrair_min(fp);
		if(N==1){
			inserir_Unico(fp,z->freq, z,arvoreHuff);
		}
return;
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

int insere_FilaPrio(FilaPrio* fp, int freq, int valor,node* x, node* y){
    if(fp == NULL)
        return 0;
    if(fp->qtd == MAX)//fila cheia
        return 0;
    /* insere na primeira posição livre */
    fp->dados[fp->qtd].valor = valor;
    fp->dados[fp->qtd].freq = freq;
    fp->dados[fp->qtd].esq = x;
    fp->dados[fp->qtd].dir = y;
    /* desloca elemento para posição correta */
    promoverElemento(fp,fp->qtd);
    /* incrementa número de elementos no heap */
    fp->qtd++;
    return 1;
}

int inserir_no(FilaPrio* fp, int somafreq, node* x, node* y, node* arvoreHuff){
	HEAD=&arvoreHuff[HOFF];
	arvoreHuff[HOFF].valor=0xFFF;
	arvoreHuff[HOFF++].freq=somafreq;
	
	arvoreHuff[HOFF].valor=x->valor;
	arvoreHuff[HOFF].freq=x->freq;
	arvoreHuff[HOFF].esq=x->esq;
	arvoreHuff[HOFF++].dir=x->dir;
	
	arvoreHuff[HOFF].valor=y->valor;
	arvoreHuff[HOFF].freq=y->freq;
	arvoreHuff[HOFF].esq=y->esq;
	arvoreHuff[HOFF].dir=y->dir;

	arvoreHuff[HOFF-2].esq=&arvoreHuff[HOFF-1];
	x=&arvoreHuff[HOFF-1];
	arvoreHuff[HOFF-2].dir=&arvoreHuff[HOFF];
	y=&arvoreHuff[HOFF];
	HOFF++;
	
	
	
	insere_FilaPrio(fp, somafreq, 0xFFF, x, y); 
	return 1;
}

int inserir_Unico(FilaPrio* fp, int somafreq, node* x, node* arvoreHuff){
	HEAD=&arvoreHuff[HOFF];
	arvoreHuff[HOFF].valor=0xFFF;
	arvoreHuff[HOFF++].freq=somafreq;
	
	arvoreHuff[HOFF].valor=x->valor;
	arvoreHuff[HOFF].freq=x->freq;
	arvoreHuff[HOFF].esq=x->esq;
	arvoreHuff[HOFF++].dir=x->dir;

	arvoreHuff[HOFF-2].esq=&arvoreHuff[HOFF-1];
	arvoreHuff[HOFF-2].dir=NULL;
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

        swap(fp->dados[pai],fp->dados[filho]);

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
    swap(fp->dados[0],fp->dados[fp->qtd]);
    rebaixarElemento(fp,0);
    return 1;
}

node* extrair_min(FilaPrio* fp){
    if(fp == NULL)
        return 0;
    if(fp->qtd == 0)
        return 0;

    fp->qtd--;
    node* x=&fp->dados[fp->qtd];
    swap(fp->dados[0],fp->dados[fp->qtd]);
    
    rebaixarElemento(fp,0);
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

void printCodes(node* root, string str)
{
    if (!root)
        return;
 
    if (root->valor != 0xFFF){
		root->code=str;
      //  printf("Valor:0x%X Codigo:%s\n", root->valor, root->code.c_str());
    }
 
    printCodes(root->esq, str + "0");
    printCodes(root->dir, str + "1");
}

void imprimirRLE(Histograma* histograma, int aux, float txcompressaoRLE, int impressao){
	fprintf(output, "%d: [RLE ", impressao);
	fprintf(output, "%.2f%c]", txcompressaoRLE, '%');
	for(int j=0;j<aux+1;j++){
			fprintf(output, " 0x%02X 0x%X",histograma[j].freq, histograma[j].valor);
	}
	fprintf(output, "\n");
return;	
}

void criaHeap(int *vet, int i, int f){
    int aux = vet[i];
    int j = i * 2 + 1;
    while (j <= f){
        if(j < f){
            if(vet[j] < vet[j + 1]){
                j = j + 1;
            }
        }
        if(aux < vet[j]){
            vet[i] = vet[j];
            i = j;
            j = 2 * i + 1;
        }else{
            j = f + 1;
        }
    }
    vet[i] = aux;
}

void heapSort(int *vet, int N){
    int i, aux;
    for(i=(N - 1)/2; i >= 0; i--){
        criaHeap(vet, i, N-1);
    }
    for (i = N-1; i >= 1; i--){
        aux = vet[0];
        vet [0] = vet [i];
        vet [i] = aux;
        criaHeap(vet, 0, i - 1);
    }
}

void criaHeapNODE(node *vet, int i, int f){
    node aux = vet[i];
    int j = i * 2 + 1;
    while (j <= f){
        if(j < f){
            if(vet[j].valor < vet[j + 1].valor){
                j = j + 1;
            }
        }
        if(aux.valor < vet[j].valor){
            vet[i] = vet[j];
            i = j;
            j = 2 * i + 1;
        }else{
            j = f + 1;
        }
    }
    vet[i] = aux;
}

void heapSortNODE(node *vet, int N){
    int i; 
    node aux;
    for(i=(N - 1)/2; i >= 0; i--){
        criaHeapNODE(vet, i, N-1);
    }
    for (i = N-1; i >= 1; i--){
        aux = vet[0];
        vet [0] = vet [i];
        vet [i] = aux;
        criaHeapNODE(vet, 0, i - 1);
    }
}

int main(int argc, char **argv){
	unsigned int qtd, qtdDados; 
	unsigned int contadorRLE=0, contadorHUF=0,impressao=0;
	float txcompressaoRLE;
	FilaPrio* fp = cria_FilaPrio();
	node* arvoreHuff=new node[MAX*2];
	clock_t start = clock();
	
//input = fopen("entrada.txt", "r");
	input = fopen("compressao.input.txt", "r");
	output = fopen("saida.txt", "w");

		//fscanf ( input , "%d" , &qtd);
		//for(unsigned int i=0;i<qtd;i++){
			//fscanf ( input , "%d" , &qtdDados);
			int *sequencia = new int[7];
			int *textohuff = new int[7];
			qtdDados=7;
			//for(unsigned int j=0;j<qtdDados;j++){
					sequencia[0]=0x10;
					textohuff[0]=sequencia[0];
					sequencia[1]=0x20;
					textohuff[1]=sequencia[1];
					sequencia[2]=0x30;
					textohuff[2]=sequencia[2];
					sequencia[3]=0x40;
					textohuff[3]=sequencia[3];
					sequencia[4]=0x50;
					textohuff[4]=sequencia[4];
					sequencia[5]=0x60;
					textohuff[5]=sequencia[5];
					sequencia[6]=0x70;
					textohuff[6]=sequencia[6];					
					
					
			Histograma *histograma=new Histograma[qtdDados];
			Histograma *histohuff=new Histograma[qtdDados];
			
			heapSort(textohuff,7);
			
			for(unsigned int j=0;j<qtdDados;j++){
					
					if(j+1==qtdDados || sequencia[j]==sequencia[j+1]){
						histograma[contadorRLE].freq++;
						histograma[contadorRLE].valor=sequencia[j];
					}
					else{
						histograma[contadorRLE].freq++;
						histograma[contadorRLE].valor=sequencia[j];
						contadorRLE++;
					}
					if(j+1==qtdDados || textohuff[j]==textohuff[j+1]){
						histohuff[contadorHUF].freq++;
						histohuff[contadorHUF].valor=textohuff[j];
					}
					else{
						histohuff[contadorHUF].freq++;
						histohuff[contadorHUF].valor=textohuff[j];
						contadorHUF++;
					}
			 }
			
			construir_arvore(fp, histohuff, contadorHUF+1, arvoreHuff);
			
			string teste ="";
			printCodes(HEAD,teste);
			
			heapSortNODE(arvoreHuff,HOFF);
			

			
			cout << endl;
			
			HOFF=0;
			contadorRLE=0;
			contadorHUF=0;
			delete[]histohuff;
			delete[]textohuff;
			delete[]histograma;
			delete[]sequencia;
			impressao++;
	//	}
   clock_t end = clock();	
   printf("Duracao: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
   fclose(input);
   fclose(output);
	return 0;
}	
