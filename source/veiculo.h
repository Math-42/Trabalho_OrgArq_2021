#ifndef _VEICULO_H_
#define _VEICULO_H_

typedef struct{
	char removido;
	int tamanhoRegistro;
	char prefixo[5];
	char data[10];
	int quantidadeLugares;
	int codLinha;
	int tamanhoModelo;
	char modelo[100];
	int tamanhoCategoria;
	char caregoria[100];
}veiculo;

#endif