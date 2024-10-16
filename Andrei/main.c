#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    struct product {
        int id;
        char name[30];
        float price;
    };                              // Estrutura dos dados
    typedef struct product Product; // Define Product


    FILE *arqIn, *arqOut; // Ponteiros do arquivo


    Product productIn;  // Cria a variavel productIn com a estrutura Product
    size_t fSize; // variavel com tipo próprio para tamanhos de arquivos

    arqOut = fopen("productList.dat", "ab");
    if(!arqOut){
        printf("file error");
        return(0);
    }    // Abre o arquivo em forma de append e valida se abriu
    do {
        fflush(stdin);   // limpa o buffer do teclado
        system("cls");   // limpa a tela

        printf("Digite 0 para sair\nid: ");  // O programa encerra quando digitar 0 no inicio
        scanf("%d", &productIn.id);     // Coleta o ID
        if(productIn.id == 0) break;    // Se 0 for inserido, encerra
        fflush(stdin);

        printf("nome: ");
        gets(productIn.name); // Coleta o nome
        fflush(stdin);

        printf("preco: ");
        scanf("%f", &productIn.price);  // Coleta o preço
        fflush(stdin);

        fwrite(&productIn, sizeof(productIn), 1, arqOut);   // Escreve no arquivo
    } while(1);     // Loop se encerra apenas com o break

    fclose(arqOut);  // Fecha o Arquivo


    arqIn = fopen("productList.dat", "rb");  // Abre o
    if(!arqIn){
        printf("file error");
        return(0);
    }   // Abre o arquivo como leitura e verifica se abriu

    system("cls");      // Limpa a tela

    fseek(arqIn, 0l, SEEK_END); //  Define o ponteiro ao final do arquivo
    fSize = ftell(arqIn); // Função retorna a posição do ponteiro, descobrindo o tamanho do arquivo
    printf("Tamanho do arquivo: %d (Bytes)\n", fSize);
    printf("Numero de registros: %d\n\n", (fSize/sizeof(Product))); // Divide o tamanho do arquivo pelo tamanho dos elementos, trazendo a quantidade de registros
    fseek(arqIn, 0l, SEEK_SET);


    while(fread(&productIn, sizeof(productIn), 1, arqIn))
    {
        printf("%i\t%8s\t%5.1f\n", productIn.id, productIn.name, productIn.price);
    }


}
