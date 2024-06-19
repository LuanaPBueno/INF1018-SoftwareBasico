// //* Luana Pinho Bueno Penha 2312082 3WA */ 

// //funcao auxiliar para transformar um número em binário
// char *numToBin(unsigned int numero, int tam) {
//     char *stringBinaria = malloc(sizeof(char) * (tam + 1));
//     if (stringBinaria == NULL) {
//         printf("Erro na alocação da stringBinaria\n");
//         exit(1);
//     }
//   // Transforma o numero em decimal para um binarioa
//     for (int i = tam - 1; i >= 0; i--) {
//         stringBinaria[i] = (numero & 1) ? '1' : '0';
//         numero >>= 1;

//     }
//   // Adicionando \0 no final da string
//     stringBinaria[tam] = '\0';
//   // retorna um binario em string
//     return stringBinaria;
// }

// //transformei em binario e concatenei em uma string, agora vou escrever essa string no arquivo bin
// void compacta(FILE *arqTexto, FILE *arqBin, struct compactadora *v) {
//     char caracter;
//     char stringChar[360];
//     stringChar[0] = '\0'; 
//     int index = 0;
//     while ((caracter = fgetc(arqTexto)) != EOF) {
//         for (int i = 0; i < 32; i++) {
//             if (caracter == v[i].simbolo) {
//                 strcat(stringChar, numToBin(v[i].codigo, v[i].tamanho));
//                 break;
//             }
//         }
//   }
//     // Adicionando o EOF: questao falou que ia ser na posicao 31
//       strcat(stringChar, numToBin(v[31].codigo, v[31].tamanho));

//   //adicionando no arq bin (quebro em bytes e adiciono)
//     unsigned char byte = 0;
//     int count = 7;
//     for (int i = 0; stringChar[i] != '\0'; i++) {
//         byte |= (stringChar[i] == '1') << count;
//         count--;
//         if (count < 0) {
//             fwrite(&byte, sizeof(unsigned char), 1, arqBin);
//             count = 7;
//             byte = 0;
//         }
//     }
//     if (count != 7)
//         fwrite(&byte, sizeof(unsigned char), 1, arqBin);
// }

// void descompacta(FILE *arqBin, FILE *arqTexto, struct compactadora *v) {
//     char string[360];
//     unsigned char byte;
//     int pos = 0;


//     //Lendo a entrada

//     while (fread(&byte, sizeof(unsigned char), 1, arqBin) > 0) {
//         for (int i = 7; i >= 0; i--) {
//             char bit = (byte >> i) & 1; //Extraindo o bit da posição i
//             string[pos++] = (bit == 0) ? '0' : '1'; //Convertendo o bit para '0' ou '1' e adiciona ao array

//         }
//     }
//     string[pos] = '\0';

//     //escrevendo na saida:
//     int index = 0;
//     // Faz um loop para percorrer a string
//     while (1) {
//         int found = 0;

//         // Busca o simbolo no vetor da struct compactadora
//         for (int i = 0; i < 32; i++) {

//             // Verifica se o simbolo foi encontrado
//             if (strncmp(&string[index], numToBin(v[i].codigo, v[i].tamanho), v[i].tamanho) == 0) {
//                 // Se o simbolo for 0, significa que o arquivo terminou
//                 if (v[i].simbolo == 0) {
//                     return;
//                 }

//                 // caso contrário, ele escreve o simbolo no arquivo de texto
//                 fputc(v[i].simbolo, arqTexto);
//                 index += v[i].tamanho;
//                 found = 1;
//                 break;
//             }
//         }

//         // Se o simbolo não foi encontrado, significa que o arquivo está corrompido
//         if (!found) {
//             printf("Valor inválido %d\n", index);
//             return;
//         }
//     }
// }
