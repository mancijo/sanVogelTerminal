#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "managEstq.h"

int readFile() {            //Lê o arquivo e gera a array
    // Abre o arquivo e verifica se abriu
    size_t fSize;
    arqIn = fopen("productList.dat", "rb");
    if (!arqIn) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }
    // Descobre o tamanho do arquivo e a quantidade de itens nele
    fseek(arqIn, 0l, SEEK_END);
    fSize = ftell(arqIn);
    productQuantity = fSize / sizeof(Product);
    fseek(arqIn, 0l, SEEK_SET);
    // Aloca memória para o vetor
    vProducts = malloc(fSize);
    if (!vProducts) {
        fclose(arqIn);
        perror("Falha ao alocar vetor!");
        return 0;
    }
    // Insere os itens do arquivo no vetor alocado
    size_t readCount = fread(vProducts, sizeof(Product), productQuantity, arqIn);
    if (readCount != (size_t)productQuantity) {
        perror("Erro ao ler produtos do arquivo");
    }

    fclose(arqIn);
    return 1;
}

//Salvando o arquivo 
void saveFile() {           // Salva o vetor no arquivo binario
    arqIn = fopen("productList.dat", "wb");
    for(int i = 0; i <= productQuantity - 1; i++) {
        fwrite(&vProducts[i], sizeof(vProducts[0]), 1, arqIn);
    }
    fclose(arqIn);
} 

//Função para busca de itens no estoque
Product* searchItem(int insertedType, char *insertedSearch) { // A funcao recebe dois parametros e retorna um item com a struct Product
    readFile();
    switch(insertedType) {
        case 1:  //Busca por ID
            for(int i = 0; i < productQuantity; i++) {
                if(vProducts[i].id == atoi(insertedSearch)) {
                    return &vProducts[i];
                }
            }
        break;
        case 2:   //Busca pelo nome 
            for(int i = 0; i < productQuantity; i++) {
                if(strcasecmp(insertedSearch, vProducts[i].name) == 0) {
                    return &vProducts[i];
                }
            }
        break;
        default: 
            return NULL;
    }
    return NULL;
}

int insertItem () {                  // Loop de inserção de itens
    readFile();                                 // Atualiza quantidade de produtos (necessário para definir ID) 
    arqIn = fopen("productList.dat", "ab");
    if(!arqIn){                                 // Abre o arquivo em forma de append e valida se abriu
        printf("file error");
        return(0);
    }    

    char choice;
    do {
        printf("Inserir novo produto? [S/N]: "); 
        choice = getchar();
        while (getchar() != '\n'); // Limpa o buffer

        if (choice != 's' && choice != 'S') {
            break;
        }

        Product newProduct = { productQuantity++, "", 0.0f, 0, true }; // Define os valores padrão

        printf("Nome: ");
        fgets(newProduct.name, sizeof(newProduct.name), stdin);
        newProduct.name[strcspn(newProduct.name, "\n")] = 0; // Remove o '\n'

        printf("Preço: ");
        scanf("%f", &newProduct.price);
        printf("Unidades: ");
        scanf("%i", &newProduct.units);
        getchar(); // Limpa o buffer

        fwrite(&newProduct, sizeof(newProduct), 1, arqIn);
    } while (1);        // Loop se encerra apenas com o break

    fclose(arqIn);  // Fecha o Arquivo

    return(0);
}

void showAllProducts () {           //Mostrar todos os produtos
    readFile();
    for(int i = 0; i < productQuantity; i++){
        if(vProducts[i].active){
            printf("%i\t\t%s\t\t\t%i\t\t%3.2f\n", vProducts[i].id, vProducts[i].name, vProducts[i].units, vProducts[i].price);
        }
    }
}

// Editar produtos
void editProduct(Product *productPtr, const char *element, char *feed) { //funcao para alterar os dados de produto na array
    if(strcasecmp(element, "nome") == 0){
        strcpy(productPtr->name, feed);
    } else
    if(strcasecmp(element, "preco") == 0){
        productPtr->price = atof(feed);
    } else
    if(strcasecmp(element, "quantidade") == 0){
        productPtr->units = atoi(feed);
    } else {
        printf("Erro ao editar"); system("pause");
    }
}
