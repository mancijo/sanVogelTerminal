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
int productQuantity; // Quantidade de produtos


//Lendo o arquivo e gerando a array
int readFile() {
    arqIn = fopen("productList.dat", "rb");  // Abre o
    if(!arqIn){
        printf("file error");
        return(0);
    }   // Abre o arquivo como leitura e verifica se abriu

    fseek(arqIn, 0l, SEEK_END); //  Define o ponteiro ao final do arquivo
    fSize = ftell(arqIn); // Fun��o retorna a posição do ponteiro, descobrindo o tamanho do arquivo
    //printf("Tamanho do arquivo: %d (Bytes)\n", fSize);
    //printf("Numero de registros: %d\n\n", (fSize/sizeof(Product))); // Divide o tamanho do arquivo pelo tamanho dos elementos, trazendo a quantidade de registros
    productQuantity = fSize/sizeof(Product);
    fseek(arqIn, 0l, SEEK_SET);

    vProducts = (Product *) malloc(fSize);
    if(!vProducts) {
        printf("Falha ao alocar vetor!");
        return(0);
    }  // verificacao se vetor foi criado

    for(int i = 0; fread(&productIn, sizeof(productIn), 1, arqIn); i++) {
        vProducts[i] = productIn;
    } // Salva os elementos no arquivo em uma array
    fclose(arqIn);
    return(1);
}

//Função para busca de itens no estoque
Product searchItem (int insertedType, char insertedSearch[30]) { // A funcao recebe dois parametros e retorna um item com a struct Product
    readFile();
    switch(insertedType) {
        case 1:  
            for(int i = 0; i < productQuantity; i++) {
                if(vProducts[i].id == atoi(insertedSearch)) {
                    return vProducts[i];
                }
            }
        break;
        case 2: 
            for(int i = 0; i < productQuantity; i++) {
                if(strcmp(insertedSearch, vProducts[i].name) == 0) {
                    return vProducts[i];
                }
            }
        break;
        default: 
            return(Product){0};
    }
    return(Product){0};
}

// Loop de inserção de itens
int insertItem () {
    arqIn = fopen("productList.dat", "ab");
    if(!arqIn){
        printf("file error");
        return(0);
    }    // Abre o arquivo em forma de append e valida se abriu
    do {
        fflush(stdin);   // limpa o buffer do teclado
        system("cls");   // limpa a tela

        char choice;
        printf("Inserir novo produto? [S/N]: "); 
        choice = getchar(); // Leitura do caractere inserido    
        while (getchar() != '\n'); // elimina o enter do buffer

        // verifica o caractere inserido 
        if (choice != 's' && choice != 'S') {
            break;
        }

        // printf("Digite 0 para sair\nid: ");  // O programa encerra quando digitar 0 no inicio
        // scanf("%d", &productIn.id);     // Coleta o ID
        // if(productIn.id == 0) break;    // Se 0 for inserido, encerra
        // fflush(stdin);

        //Gerar ID
        fflush(stdin);
        productIn = (Product){productQuantity++, "", 0.0f}; // Reseta a variavel e define o id



        printf("nome: ");
        fgets(productIn.name, sizeof(productIn.name), stdin); // Coleta o nome
        productIn.name[strcspn(productIn.name, "\n")] = 0; // Remove o \n ao final da string coletada
        fflush(stdin);

        printf("preco: ");
        scanf("%f", &productIn.price);  // Coleta o pre�o
        fflush(stdin);

        fwrite(&productIn, sizeof(productIn), 1, arqIn);   // Escreve no arquivo

        system("cls");

        
    } while(1);     // Loop se encerra apenas com o break

    fclose(arqIn);  // Fecha o Arquivo

    return(0);
}

//Mostrar todos os produtos
void showAllProducts () {
    readFile();
    for(int i = 0; i < productQuantity; i++){
        printf("%i\t\t%s\t\t%3.2f\n", vProducts[i].id, vProducts[i].name, vProducts[i].price);
    }

}

int main()
{
    readFile();
    Product produtoAchado;

    insertItem();

    produtoAchado = searchItem(2, "Banana");
    produtoAchado = searchItem(2, "banana");

    printf("%i\t\t%s\t\t%3.2f\n", produtoAchado.id, produtoAchado.name, produtoAchado.price);

    
}
