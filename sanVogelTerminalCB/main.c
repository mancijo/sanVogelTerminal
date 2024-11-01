#include "commonLibs.h"


void AtivarProduto();
void AlterarUsr();    // Adicionando o prot�tipo da fun��o AlterarUsr

// Abertura do sistema
void subVirgpPonto(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
}


void AlterarUsr() {
    FILE *usuarios;
    char nomeAntigo[30], novoNome[30], novaSenha[30], novoRole[10];
    char tempName[30], tempPass[30], tempRole[10];
    int found = 0;

    usuarios = fopen("usuarios.txt", "r+"); // Abre o arquivo para leitura e escrita
    if (usuarios == NULL) {
        printf("Arquivo n�o pode ser aberto\n");
        exit(1);
    }

    printf("Digite o nome do usu�rio que deseja alterar: ");
    scanf("%s", nomeAntigo);

    // Ler todo o conte�do para uma lista tempor�ria
    // Aqui, estamos usando um array para armazenar os dados.
    // Considere usar uma estrutura de dados din�mica (como linked list) se necess�rio.
    char linhas[100][100]; // Ajuste o tamanho conforme necess�rio
    int i = 0;

    while (fscanf(usuarios, "%s %s %s", tempName, tempPass, tempRole) != EOF) {
        snprintf(linhas[i], sizeof(linhas[i]), "%s %s %s", tempName, tempPass, tempRole);
        i++;
    }

    // Agora que temos todos os dados, podemos procurar o usu�rio
    for (int j = 0; j < i; j++) {
        if (strstr(linhas[j], nomeAntigo) != NULL) { // Verifica se o usu�rio est� na linha
            found = 1;
            printf("Usu�rio encontrado! Deseja alterar o nome? (1 - Sim / 0 - N�o): ");
            int alterarNome;
            scanf("%d", &alterarNome);
            if (alterarNome) {
                printf("Digite o novo nome: ");
                scanf("%s", novoNome);
                sscanf(linhas[j], "%s %s %s", tempName, tempPass, tempRole);
                snprintf(linhas[j], sizeof(linhas[j]), "%s %s %s", novoNome, tempPass, tempRole);
            }

            printf("Deseja alterar a senha? (1 - Sim / 0 - N�o): ");
            int alterarSenha;
            scanf("%d", &alterarSenha);
            if (alterarSenha) {
                printf("Digite a nova senha: ");
                int k = 0;
                char ch;
                while ((ch = getch()) != '\r' && k < 29) {
                    novaSenha[k++] = ch;
                    printf("*");
                }
                novaSenha[k] = '\0'; // Termina a string
                sscanf(linhas[j], "%s %s %s", tempName, tempPass, tempRole);
                snprintf(linhas[j], sizeof(linhas[j]), "%s %s %s", tempName, novaSenha, tempRole);
            }

            printf("Deseja alterar o n�vel de hierarquia? (1 - Sim / 0 - N�o): ");
            int alterarRole;
            scanf("%d", &alterarRole);
            if (alterarRole) {
                printf("Digite o novo n�vel de hierarquia (Operador, Admin, Master): ");
                scanf("%s", novoRole);
                sscanf(linhas[j], "%s %s %s", tempName, tempPass, tempRole);
                snprintf(linhas[j], sizeof(linhas[j]), "%s %s %s", tempName, tempPass, novoRole);
            }
        }
    }

    if (found) {
        // Agora reescrevemos o arquivo
        freopen("usuarios.txt", "w", usuarios); // Reabre o arquivo para escrita
        for (int j = 0; j < i; j++) {
            fprintf(usuarios, "%s\n", linhas[j]);
        }
        printf("Usu�rio alterado com sucesso!\n");
    } else {
        printf("Usu�rio n�o encontrado.\n");
    }

    fclose(usuarios);
}

void AtivarProduto() {
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

// Fun��o de login com verifica��o case-insensitive


// Fun��o principal
int main() {
    // Chamada da fun��o de abertura
    abertura();
    login();
    return 0;
}
