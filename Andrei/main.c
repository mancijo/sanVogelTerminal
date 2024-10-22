#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct product {
        int id;
        char name[30];
        float price;
    };                              // Estrutura dos dados
typedef struct product Product; // Define Product

FILE *arqIn; // Ponteiro do arquivo
Product productIn;  // Cria a variavel productIn com a estrutura Product
size_t fSize; // variavel com tipo proprio para tamanhos de arquivos
Product *vProducts; // Ponteiro para a array de produtos

//Função para busca de itens no estoque
Product* searchItem(int insertedType, char insertedSearch[30]) {
    int sizeFile = (sizeof( vProducts ) / sizeof( vProducts[0]));
    switch(insertedType) {
        case 1:  
            for(int i = 0; i < sizeFile; i++) {
                if(vProducts[i].id == atoi(insertedSearch)) {
                    return &vProducts[i];
                }
            }
        break;
        case 2: 
            for(int i = 0; i < sizeFile; i++) {
                if(strcmp(insertedSearch, vProducts[i].name)) {
                    return &vProducts[i];
                }
            }
        break;
        default: return(NULL);
    }
}


int main()
{
    arqIn = fopen("productList.dat", "ab");
    if(!arqIn){
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
        scanf("%f", &productIn.price);  // Coleta o pre�o
        fflush(stdin);

        fwrite(&productIn, sizeof(productIn), 1, arqIn);   // Escreve no arquivo
    } while(1);     // Loop se encerra apenas com o break

    fclose(arqIn);  // Fecha o Arquivo


    arqIn = fopen("productList.dat", "rb");  // Abre o
    if(!arqIn){
        printf("file error");
        return(0);
    }   // Abre o arquivo como leitura e verifica se abriu

    system("cls");      // Limpa a tela

    fseek(arqIn, 0l, SEEK_END); //  Define o ponteiro ao final do arquivo
    fSize = ftell(arqIn); // Fun��o retorna a posição do ponteiro, descobrindo o tamanho do arquivo
    printf("Tamanho do arquivo: %d (Bytes)\n", fSize);
    printf("Numero de registros: %d\n\n", (fSize/sizeof(Product))); // Divide o tamanho do arquivo pelo tamanho dos elementos, trazendo a quantidade de registros
    fseek(arqIn, 0l, SEEK_SET);

    vProducts = (Product *) malloc(fSize);
    if(!vProducts) {
        printf("Falha ao alocar vetor!");
        return(0);
    }  // verificacao se vetor foi criado

    for(int i = 0; fread(&productIn, sizeof(productIn), 1, arqIn); i++) {
        vProducts[i] = productIn;
    } // Salva os elementos no arquivo em uma array
    system("pause");

    
}
