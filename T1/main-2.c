#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct compactadora {
    char simbolo;
    unsigned int codigo;
    int tamanho;
};
//* Luana Pinho Bueno Penha 2312082 3WA */ 

//funcao auxiliar para transformar um número em binário
char *numToBin(unsigned int numero, int tam) {
    char *stringBinaria = malloc(sizeof(char) * (tam + 1));
    if (stringBinaria == NULL) {
        printf("Erro na alocação da stringBinaria\n");
        exit(1);
    }
  // Transforma o numero em decimal para um binario
    for (int i = tam - 1; i >= 0; i--) {
        stringBinaria[i] = (numero & 1) ? '1' : '0';
        numero >>= 1;

    }
  // Adicionando \0 no final da string
    stringBinaria[tam] = '\0';
  // retorna um binario em string
    return stringBinaria;
}

//transformei em binario e concatenei em uma string, agora vou escrever essa string no arquivo bin
void compacta(FILE *arqTexto, FILE *arqBin, struct compactadora *v) {
    char caracter;
    char stringChar[360];
    stringChar[0] = '\0'; 
    int index = 0;
    while ((caracter = fgetc(arqTexto)) != EOF) {
        for (int i = 0; i < 32; i++) {
            if (caracter == v[i].simbolo) {
                strcat(stringChar, numToBin(v[i].codigo, v[i].tamanho));
                break;
            }
        }
  }
    // Adicionando o EOF: questao falou que ia ser na posicao 31
      strcat(stringChar, numToBin(v[31].codigo, v[31].tamanho));

  //adicionando no arq bin (quebro em bytes e adiciono)
    unsigned char byte = 0;
    int count = 7;
    for (int i = 0; stringChar[i] != '\0'; i++) {
        byte |= (stringChar[i] == '1') << count;
        count--;
        if (count < 0) {
            fwrite(&byte, sizeof(unsigned char), 1, arqBin);
            count = 7;
            byte = 0;
        }
    }
    if (count != 7)
        fwrite(&byte, sizeof(unsigned char), 1, arqBin);
}

void descompacta(FILE *arqBin, FILE *arqTexto, struct compactadora *v) {
    char string[360];
    unsigned char byte;
    int pos = 0;


    //Lendo a entrada

    while (fread(&byte, sizeof(unsigned char), 1, arqBin) > 0) {
        for (int i = 7; i >= 0; i--) {
            char bit = (byte >> i) & 1; //Extraindo o bit da posição i
            string[pos++] = (bit == 0) ? '0' : '1'; //Convertendo o bit para '0' ou '1' e adiciona ao array

        }
    }
    string[pos] = '\0';

    //escrevendo na saida:
    int index = 0;
    // Faz um loop para percorrer a string
    while (1) {
        int found = 0;

        // Busca o simbolo no vetor da struct compactadora
        for (int i = 0; i < 32; i++) {

            // Verifica se o simbolo foi encontrado
            if (strncmp(&string[index], numToBin(v[i].codigo, v[i].tamanho), v[i].tamanho) == 0) {
                // Se o simbolo for 0, significa que o arquivo terminou
                if (v[i].simbolo == 0) {
                    return;
                }

                // caso contrário, ele escreve o simbolo no arquivo de texto
                fputc(v[i].simbolo, arqTexto);
                index += v[i].tamanho;
                found = 1;
                break;
            }
        }

        // Se o simbolo não foi encontrado, significa que o arquivo está corrompido
        if (!found) {
            printf("Valor inválido %d\n", index);
            return;
        }
    }
}


int main(void) {
    struct compactadora c[] = {
        {'K', 1, 12},
        {'W', 2, 12},
        {'Y', 3, 12},
        {'Z', 2, 11},
        {'J', 3, 11},
        {'X', 1, 9},
        {'\n', 1, 8},
        {'H', 1, 7},
        {'F', 36, 7},
        {'G', 37, 7},
        {'B', 1, 6},
        {'Q', 16, 6},
        {',', 17, 6},
        {'V', 19, 6},
        {'.', 49, 6},
        {'P', 48, 6},
        {'D', 1, 5},
        {'C', 17, 5},
        {'O', 16, 5},
        {'M', 25, 5},
        {'R', 1, 4},
        {'L', 7, 4},
        {'N', 6, 4},
        {'A', 5, 4},
        {'T', 9, 4},
        {'S', 14, 4},
        {'U', 15, 4},
        {'I', 13, 4},
        {'E', 1, 3},
        {' ', 5, 3},
        {0, 0, 0},
        {4, 0, 12}
    };

    FILE * arq; 
    FILE* arquivoBinario;
    arq = fopen("text.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de texto\n");
        return 1;
    }

    arquivoBinario = fopen("bin.bin", "wb");
    if (arquivoBinario == NULL) {
        printf("Erro ao criar o arquivo binário\n");
        fclose(arq);
        return 1;
    }
    compacta(arq, arquivoBinario, c);
    fclose(arq);
    fclose(arquivoBinario);
    arq = fopen("saida.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de texto\n");
        return 1;
    }
    arquivoBinario = fopen("bin.bin", "rb");
    if (arquivoBinario == NULL) {
        printf("Erro ao criar o arquivo binário\n");
        fclose(arq);
        return 1;
    }
    descompacta(arquivoBinario, arq, c);
    fclose(arq);
    fclose(arquivoBinario);
    printf("oi"); 
    return 0;
}
