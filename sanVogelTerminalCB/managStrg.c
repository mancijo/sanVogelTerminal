#include "managStrg.h"

int readFile() {            //L� o arquivo e gera a array
    // Abre o arquivo e verifica se abriu
    size_t fSize;
    productQuantity = 0;
    arqIn = fopen("productList.dat", "rb");
    if (!arqIn) {
        perror("Erro ao abrir o arquivo");
    }
    // Descobre o tamanho do arquivo e a quantidade de itens nele
    fseek(arqIn, 0l, SEEK_END);
    fSize = ftell(arqIn);
    productQuantity = fSize / sizeof(Product);
    fseek(arqIn, 0l, SEEK_SET);
    // Aloca mem�ria para o vetor
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

//Fun��o para busca de itens no estoque
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

int insertItem () {                  // Loop de inser��o de itens
    readFile();                                 // Atualiza quantidade de produtos (necess�rio para definir ID)
    arqIn = fopen("productList.dat", "ab");
    if(!arqIn){                                 // Abre o arquivo em forma de append e valida se abriu
        printf("file error");
        return(0);
    }

    fflush(stdin);
    char choice;
    do {
        printf("Inserir novo produto? [S/N]: ");
        choice = getchar();
        while (getchar() != '\n'); // Limpa o buffer

        if (choice != 's' && choice != 'S') {
            break;
        }

        Product newProduct = { productQuantity++, "", 0.0f, 0, true }; // Define os valores padr�o

        printf("Nome: ");
        fgets(newProduct.name, sizeof(newProduct.name), stdin);
        newProduct.name[strcspn(newProduct.name, "\n")] = 0; // Remove o '\n'

        printf("Preco: ");
        scanf("%f", &newProduct.price);
        printf("Unidades: ");
        readInt(&newProduct.units);
        fflush(stdin);

        fwrite(&newProduct, sizeof(newProduct), 1, arqIn);

        system("cls");
    } while (1);        // Loop se encerra apenas com o break

    fclose(arqIn);  // Fecha o Arquivo
    system("cls");
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

void editProduct(Product *productPtr, char *element, char *feed) {
    // Check for null pointers to avoid segmentation fault
    if (productPtr == NULL || element == NULL || feed == NULL) {
        printf("Invalid input. Null pointer detected.\n");
        return;
    }

    // Edit name
    if (strcasecmp(element, "nome") == 0) {
        // Ensure the new name doesn't exceed the buffer size
        if (strlen(feed) < sizeof(productPtr->name)) {
            strcpy(productPtr->name, feed);
        } else {
            printf("Erro: Nome muito longo\n");
            return;
        }
    }
    // Edit price
    else if (strcasecmp(element, "preco") == 0) {
        // Ensure the feed is a valid float value
        char *endptr;
        float price = strtof(feed, &endptr);
        if (*endptr == '\0') {
            productPtr->price = price;
        } else {
            printf("Error: Preco invalido.\n");
            return;
        }
    }
    // Edit quantity
    else if (strcasecmp(element, "quantidade") == 0) {
        // Ensure the feed is a valid integer value
        char *endptr;
        int quantity = strtol(feed, &endptr, 10);
        if (*endptr == '\0') {
            productPtr->units = quantity;
        } else {
            printf("Error: Quantidade invalida.\n");
            return;
        }
    }
    // If element doesn't match, print an error
    else {
        printf("Error: Produto nao encontrado.\n");
        return;
    }
    saveFile();
}

void LogVenda(char *nomeProdutoLog, int quantidadeP, float precoUnitario) {
    FILE *logFile = fopen("logVendas.txt", "a");
    if (logFile == NULL) {
        printf("Erro ao abrir o arquivo de log de vendas.\n");
        return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    float totalPrice = quantidadeP * precoUnitario;
    char date[20];
    sprintf(date, "%02d/%02d/%04d %02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);

    fprintf(logFile, "%s | Produto: %s | Quantidade: %d | Preco Unitario: %.2f | Total: %.2f\n",
            date, nomeProdutoLog, quantidadeP, precoUnitario, totalPrice);

    fclose(logFile);
    printf("Venda registrada no log com sucesso!\n");
}

void exibirHistoricoVendas() {
    FILE *historico = fopen("logVendas.txt", "r+");
    if (historico == NULL) {
        printf("Nenhum hist�rico de vendas encontrado.\n");
        return;
    }

    char linha[256];
    printf("\n--- Historico de Vendas ---\n");
    while (fgets(linha, sizeof(linha), historico)) {
        printf("%s", linha);
    }

    fclose(historico);
}
