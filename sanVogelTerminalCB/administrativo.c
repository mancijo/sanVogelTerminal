#include "administrativo.h"

void opcoesAdm() {
    printf("\n---------MENU----------\n");
    printf("Escolha uma das opcoes abaixo: \n");
    printf("==============================\n");
    printf("1. Acessar Estoque.\n");
    printf("2. Iniciar vendas.\n");
    printf("0. Sair.\n");
    printf("==============================\n");
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
            //editProductPanel();
            break;
        case 3:

            break;
        case 4:

            system("pause");
            break;
        case 0:
            system("cls");
            opcoesAdm();
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
        printf("Produto n�o encontrado.\n");
    }

    fclose(estoque);
}

int editProductPanelAdm() {
int ge;
    printf("\033[1;37;44m"); // cor branca com fundo azul
    printf("\n----------EDITANDO PRODUTOS----------\n");
    printf("\033[0m"); // Retorno cor padr�o
    printf("==============================\n");
    printf("1. .\n");
    printf("2. .\n");
    printf("3. .\n");
    printf("4. Ativar produto.\n");
    printf("\033[1;37;41m\n"); // Cor branca com fundo vermelho
    printf("0. Voltar.                    \n");
    printf("\033[0m"); // Retorno cor padr�o
    printf("==============================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &ge);
}
