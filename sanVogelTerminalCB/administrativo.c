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
    printf("\033[1;37;41m\n"); // Cor branca com fundo vermelho
    printf("0. Voltar.                    \n");
    printf("\033[0m"); // Retorno cor padr�o
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
            break;
        case 3:

            break;
        case 4:
            ativarProduto();
            system("pause");
            break;
        case 5:
            exibirHistoricoVendas();
            system("pause");
            system("cls");
            break;
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
    estoque = fopen("estoque.txt", "r+");

    if (estoque == NULL) {
        printf("Arquivo n�o pode ser aberto\n");
        exit(1);
    }

    int id;
    printf("Digite o ID do produto a ser ativado: ");
    scanf("%d", &id);

    char buffer[1000];
    int found = 0;

    char linhas[100][100];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), estoque) != NULL) {
        if (strstr(buffer, "ID:") != NULL && atoi(&buffer[4]) == id) {
            found = 1;
            snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
            fgets(buffer, sizeof(buffer), estoque);
            snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
            fgets(buffer, sizeof(buffer), estoque);
            snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
            fgets(buffer, sizeof(buffer), estoque);
            snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
            snprintf(linhas[i++], sizeof(linhas[i]), "Ativo: true\n"); // Ativa o produto
        } else {
            snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
        }
    }

    if (found) {
        freopen("estoque.txt", "w", estoque);
        for (int j = 0; j < i; j++) {
            fprintf(estoque, "%s", linhas[j]);
        }
        printf("Produto ativado com sucesso!\n");
    } else {
        printf("Produto nao encontrado.\n");
    }

    fclose(estoque);
}




