#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Transforma um inteiro no formato string em um inteiro
 * @param string string inicial
 * @param tamanho quantidade de digitos do número
 * @return inteiro convertido
 */
int stringToInt(char string[11], int tamanho){
	int valorLido = 0;
	for (int i = 0; i < tamanho; i++) {
        valorLido = valorLido * 10 + (string[i] - '0');
    }
	return valorLido;
}

/**
 * Determina se é o final do arquivo sem alterar a posição do ponteiro
 * caso não seja
 * @param arquivo arquivo a ser lido
 * @return retorna 1 caso seja o final e 0 caso não seja
 */
int finalDoArquivo(FILE* arquivo){
    int isFinal = 0;
    char finalByte;
    isFinal = (fread(&finalByte,sizeof(char),1,arquivo)==0)? 1:0;
    if(!isFinal) fseek(arquivo,-1,SEEK_CUR);
    return isFinal;
}

/**
 * Determina se uma string é nula, ou seja, se já começa com \0
 * @param string string a ser analisada
 * @return retorna a própria string ou uma string padrão caso seja nula
 */
char* ajustaString(char* string) {
    return (string[0] == '\0') ? "campo com valor nulo" : string;
}

/**
 * Imprime um inteiro ou campo com valor nulo caso ele seja -1
 * @param inteiro inteiro a ser analisada
 */
void imprimeInteiro(int inteiro){
    if(inteiro == -1){
        printf("campo com valor nulo\n");
    } else {
        printf("%d\n",inteiro);
    }
}

/**
 * Imprime um campo de um registro
 * @param descricao descrição do campo
 * @param valor ponteiro para o valor que será impresso
 * @param isInt determina se o valor a ser impresso é inteiro ou string, sendo > 0 para
 * @return retorna a própria string ou uma string padrão caso seja nula
 */
void imprimirCampo(char* descricao, void* valor, int isInt){
    if(isInt >0){
        int* valorInteiro =  (int*)valor;
        printf("%s: ",descricao);
        imprimeInteiro(*valorInteiro);
    } else {
        char* valorString =  (char*)valor;
        printf("%s: %s\n",descricao,ajustaString(valorString));
    }
}

// FUNCOES FORNECIDAS PELOS MONITORES
void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}


