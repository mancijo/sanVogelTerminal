#ifndef MATH_OPS_H
#define MATH_OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

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


int readFile();
void saveFile();
Product* searchItem(int insertedType, char *insertedSearch);
int insertItem ();

void showAllProducts ();

void editProduct(Product *productPtr, char *element, char *feed);


#endif