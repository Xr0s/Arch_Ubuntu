#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include <fstream>
using namespace std;

ifstream entrada;
ofstream escreve;

int main(int argc, char **argv){
	unsigned int qtd, linhas, colunas;
	unsigned int* inicio;
	string line;
	unsigned int matriz[100][100];
	entrada.open("entrada.txt");
	escreve.open("saida.txt");
	//entrada.open(argv[1]);
	//escreve.open(argv[2]);

		entrada>>line;
		qtd=atoi(line.c_str());
	
	for(unsigned int i=0;i<qtd;i++){
			entrada>>line;
			colunas=atoi(line.c_str());
			entrada>>line;
			linhas=atoi(line.c_str());
			for(unsigned int l=0;l<linhas;l++){
					for(unsigned int c=0;c<colunas;c++){
						entrada >> line;
						matriz[l][c]=atoi(line.c_str());
						if(line=="X"){
							matriz[l][c]=8;
							inicio=&matriz[l][c];
						}
					}
			}
			
			for(unsigned int l=0;l<linhas;l++){
					for(unsigned int c=0;c<colunas;c++){
						cout << matriz[l][c] << " ";
					}
					cout << endl;
			}
			cout << endl;		
	}
	
	entrada.close();
	escreve.close();
	
   //clock_t end = clock();	
   //printf("Duracao: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}	
