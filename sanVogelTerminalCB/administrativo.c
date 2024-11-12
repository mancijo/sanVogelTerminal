#include "commonLibs.h"


void opcoesAdm() {
    printf("\n---------MENU----------\n");
    printf("Escolha uma das opcoes abaixo: \n");
    printf("==============================\n");
    printf("1. Acessar Estoque.\n");
    printf("2. Iniciar vendas.\n");
    printf("0. Sair.\n");
    printf("==============================\n");
}

int editProductPanel() {
    // Declaração das variáveis
    int type;
    char search[30];
    Product* produtoAlvo;

    puts("Insira 0 para ver todos os produtos.");
    puts("Deseja usar ID ou o nome do produto?\n1: ID\n2: Nome");
    scanf(" %i", &type);
    if(type != 1 && type != 2 && type != 0){
        puts("Valor invalido.");
        system("pause");
        system("cls");
        return editProductPanel();
    } // Verificação do caractere
    if(type == 0) {
        system("cls");
        showAllProducts();
        return editProductPanel();
    } // Mostrar todos os produtos

    puts((type == 1) ? "Insira o ID do produto." : "Insira o nome do produto.");
    while (getchar() != '\n' && getchar() != EOF);
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = 0; // Remove o '\n'

    produtoAlvo = searchItem(type, search);
    if (produtoAlvo == NULL) {
        puts("Produto nao encontrado.");
        system("pause");
        system("cls");
        return editProductPanel();
    }
    system("cls");

    puts("Produto encontrado:");
    printf("%i\t\t%s\t\t\t%i\t\t%3.2f\n", produtoAlvo->id, produtoAlvo->name, produtoAlvo->units, produtoAlvo->price);

    int result;
    puts("O que deseja alterar?");
    puts("1. Nome");
    puts("2. Preco");
    puts("3. Quantidade");
    puts("0. Cancelar");

    fflush(stdin);
    scanf("%i", &type);
    switch (type) {
        case 1: {
            char newName[30];

            puts("\nInsira o novo nome do produto:");
            while (getchar() != '\n' && getchar() != EOF);
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = 0;

            editProduct(produtoAlvo, "nome", newName);

            puts("Produto editado!");
            system("pause");
            break;
        }
        case 2: {
            char newPrice[30];
            puts("Insira o novo preco do produto:");
            while (getchar() != '\n' && getchar() != EOF);
            fgets(newPrice, sizeof(newPrice), stdin);
            newPrice[strcspn(newPrice, "\n")] = 0;

            editProduct(produtoAlvo, "preco", newPrice);

            puts("Produto editado!");
            system("pause");
            break;
        }
        case 3: {
            char newQuantity[30];
            puts("Insira a nova quantidade do produto:");
            while (getchar() != '\n' && getchar() != EOF);
            fgets(newQuantity, sizeof(newQuantity), stdin);
            newQuantity[strcspn(newQuantity, "\n")] = 0;

            editProduct(produtoAlvo, "quantidade", newQuantity);

            puts("Produto editado!");
            system("pause");
            break;
        }
        default:
            printf("Erro!\n");
            break;
    }

    return 1;
}

int storageAdmPanel() {
    int ge;
    printf("\033[1;37;44m"); // cor branca com fundo azul
    printf("\n-------------MENU-------------\n");
    printf("\033[0m"); // Retorno cor padr�o
    printf("==============================\n");
    printf("1. Cadastrar produtos.\n");
    printf("2. Editar produto.\n");
    printf("3. Inativar produto.\n");
    printf("4. Ativar produto.\n");
    printf("5. Historico de Vendas.\n");
    printf("6. Consultar estoque.\n");
    printf("\033[1;37;41m\n"); // Cor branca com fundo vermelho
    printf("0. Voltar.                    \n");
    printf("\033[0m"); // Retorno cor padrao
    printf("==============================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &ge);

    switch (ge) {
        case 1:
            system("cls");
            insertItem();
            break;
        case 2:
            editProductPanel();
            system("cls");
            break;
        case 3:
            inativarProduto();
            system("pause");
            system("cls");
            break;
        case 4:
            ativarProduto();
            system("pause");
            system("cls");
            break;
        case 5:
            exibirHistoricoVendas();
            system("pause");
            system("cls");
            break;
        case 6:
            showAllProducts();
            system("pause");
            system("cls");
        case 0:
            system("cls");
            opcoesAdm();
            system("cls");
            break;
    }
    return 0;
}

void ativarProduto() {
    FILE *estoque;
    estoque = fopen("productList.dat", "r+b");  // Abrir arquivo binário para leitura e escrita

    if (estoque == NULL) {
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    int id;
    printf("Digite o ID do produto a ser ativado: ");
    scanf("%d", &id);

    Product product;
    int found = 0;

    while (fread(&product, sizeof(Product), 1, estoque)) {
        if (product.id == id && product.active == 0) {
            product.active = 1;  // Ativar o produto
            fseek(estoque, -sizeof(Product), SEEK_CUR);  // Voltar para o início do registro
            fwrite(&product, sizeof(Product), 1, estoque);  // Reescrever o produto ativado
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Produto ativado com sucesso!\n");
    } else {
        printf("Produto nao encontrado ou ja esta ativo.\n");
    }

    fclose(estoque);
}

void inativarProduto() {
    FILE *estoque;
    estoque = fopen("productList.dat", "r+b");  // Abrir arquivo binário para leitura e escrita

    if (estoque == NULL) {
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    int id;
    printf("Digite o ID do produto a ser inativado: ");
    scanf("%d", &id);

    Product product;
    int found = 0;

    // Itera por todos os produtos do arquivo
    while (fread(&product, sizeof(Product), 1, estoque)) {
        // Verifica se o produto encontrado tem o ID correto e está ativo
        if (product.id == id && product.active == 1) {
            printf("Produto encontrado: ID = %d, Nome = %s, Ativo = %d\n", product.id, product.name, product.active);
            product.active = 0;  // Inativa o produto
            fseek(estoque, -sizeof(Product), SEEK_CUR);  // Volta para o início do registro atual no arquivo
            fwrite(&product, sizeof(Product), 1, estoque);  // Reescreve o produto inativado
            found = 1;
            break;  // Sai do loop após inativar o produto
        }
    }

    if (found) {
        printf("Produto inativado com sucesso!\n");
    } else {
        printf("Produto nao encontrado ou ja esta inativo.\n");
    }

    fclose(estoque);
}



