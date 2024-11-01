#ifndef MATH_OPS_H
#define MATH_OPS_H

#include "commonLibs.h"

typedef struct {
    int id;
    char name[30];
    float price;
    int units;
    bool active;
} Product;

FILE *arqIn; // Ponteiro do arquivo
Product *vProducts; // Ponteiro para a array de produtos
int productQuantity; // Quantidade de produtos


int readFile();         // Lê o arquivo e cria o vetor
void saveFile();        // Salva o vetor no arquivo
Product* searchItem(int insertedType, char *insertedSearch);    // Procura um item específico, busca por ID(1) ou nome(2)
int insertItem();      // Um loop para inserção de produtos
void showAllProducts ();        // Mostra uma lista de produtos
void editProduct(Product *productPtr, char *element, char *feed);       // Edita um produto específico


#endif
