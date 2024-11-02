#include "commonLibs.h"


void subVirgpPonto(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
}

// Fun��o para gerenciar estoque

// void InativarProduto() {
//     FILE *estoque;
//     estoque = fopen("estoque.txt", "r+");

//     if (estoque == NULL) {
//         printf("Arquivo n�o pode ser aberto\n");
//         exit(1);
//     }

//     int id;
//     printf("Digite o ID do produto a ser inativado: ");
//     scanf("%d", &id);

//     char buffer[1000];
//     int found = 0;

//     char linhas[100][100];
//     int i = 0;

//     while (fgets(buffer, sizeof(buffer), estoque) != NULL) {
//         if (strstr(buffer, "ID:") != NULL && atoi(&buffer[4]) == id) {
//             found = 1;
//             snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
//             fgets(buffer, sizeof(buffer), estoque); // Nome
//             snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
//             fgets(buffer, sizeof(buffer), estoque); // Quantidade
//             snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
//             fgets(buffer, sizeof(buffer), estoque); // Pre�o
//             snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
//             snprintf(linhas[i++], sizeof(linhas[i]), "Ativo: false\n"); // Inativa o produto
//         } else {
//             snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
//         }
//     }

//     if (found) {
//         freopen("estoque.txt", "w", estoque);
//         for (int j = 0; j < i; j++) {
//             fprintf(estoque, "%s", linhas[j]);
//         }
//         printf("Produto inativado com sucesso!\n");
//     } else {
//         printf("Produto n�o encontrado.\n");
//     }

//     fclose(estoque);
// }

int main() {
    setlocale(LC_ALL,"Portuguese");
    showAllProducts();
    insertItem();
    editProductPanel();
    return 0;
}
