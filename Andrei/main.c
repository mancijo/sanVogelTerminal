#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    struct product {
        int id;
        char name[30];
        float price;
    };
    typedef struct product Product;


    FILE *arqIn, *arqOut;

    Product productIn;

    arqOut = fopen("productList.dat", "ab");
    if(!arqOut){
        printf("file error");
        return(0);
    }
    do {
        fflush(stdin);
        system("cls");

        printf("Digite 0 para sair\nid: ");
        scanf("%d", &productIn.id);
        if(productIn.id == 0) break;
        fflush(stdin);

        printf("nome: ");
        gets(productIn.name);

        printf("preco: ");
        scanf("%f", &productIn.price);

        fwrite(&productIn, sizeof(productIn), 1, arqOut);
    } while(1);

    fclose(arqOut);

    siistem("cls");
    printf()
}
