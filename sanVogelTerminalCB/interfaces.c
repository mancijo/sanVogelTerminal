#include "interfaces.h"

void abertura() {
    printf("==============================\n");
    printf("     BEM-VINDO AO SISTEMA     \n");
    printf("==============================\n");

    printf("Pressione Enter para continuar...");
    getchar();  // Pausa até o usuário pressionar Enter

    system("cls");

}

void defUserPanel (char *roleArquivo) {
if (strcasecmp(roleArquivo, "Admin") == 0) {
        int opcaoAdm;
        do {
            opcoesAdm();
            printf("Escolha uma opcao: ");
            readInt(&opcaoAdm);
            switch (opcaoAdm) {
            case 1:
                system("cls");
                storageAdmPanel();
                break;
            case 2:
                system("cls");
                venderProduto();
                system("pause");
                system("cls");
                break;
            case 0:
                printf("Saindo...\n");
                system("pause");
                system("cls");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
            }
        } while (opcaoAdm != 0);
    } else if (strcasecmp(roleArquivo, "Operador") == 0) {
        int opcaoOp;

        do {
            opcoeOp();
            printf("Escolha uma opcao: ");
            readInt(&opcaoOp);
            switch (opcaoOp) {
            case 1:
                showAllProducts();
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                venderProduto();
                system("pause");
                system("cls");
                break;
            case 0:
                printf("Saindo...\n");
                system("pause");
                system("cls");
                exit(0);
                break;
            default:
                printf("Opcao invalida!\n");
                break;
            }
        } while (opcaoOp != 0);
    } else if (strcasecmp(roleArquivo, "Master") == 0) {
        int opcaoMa;
        do {
            opcoesMa();
            printf("Escolha uma opcao: ");
            readInt(&opcaoMa);
            switch (opcaoMa) {
            case 1:
                system("cls");
                gerUser();
            break;
            case 2:
                system("cls");
                storageTiPanel();
                system("pause");
                system("cls");
            break;
            case 3:
                system("cls");
                venderProduto();
                system("pause");
                system("cls");
                break;
            case 0:
                printf("Saindo...\n");
                system("pause");
                system("cls");
                exit(0);
                break;
            default:
                printf("Opcao invalida!\n");
                opcoesMa();
                break;
            }
        } while (opcaoMa != 0);
    }
}

int login() {
    FILE *usuariosLog;
    char login_dig[30], senha_dig[30];
    char loginArquivo[30], senhaArquivo[30], roleArquivo[10], statusArquivo[10];
    int loginEncontrado = 0, statusInativo = 0;

    do {
        usuariosLog = fopen("usuarios.txt", "r+");

        if (usuariosLog == NULL) {
            printf("Erro ao abrir o arquivo de usuarios.\n");
            exit(1);
        }

        printf("\nDigite seu Login: ");
        scanf("%s", login_dig);

        printf("Digite sua senha: ");
        int i = 0;
        char ch;
        while (1) {
            ch = getch();

            if (ch == '\r') {
                senha_dig[i] = '\0';
                printf("\n");
                break;
            } else if (ch == 8) {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            } else if (i < 29) {
                senha_dig[i++] = ch;
                printf("*");
            }
        }

        while (fscanf(usuariosLog, "%s %s %s %s", loginArquivo, senhaArquivo, roleArquivo, statusArquivo) != EOF) {
            if (strcasecmp(loginArquivo, login_dig) == 0) {
                if (strcasecmp(statusArquivo, "Inativo") == 0) {
                    printf("Usuario Inativo. Por favor entrar com contato com TI.\n");
                    system("pause");
                    statusInativo = 1;
                    system("cls");
                    break;
                }

                if (strcmp(senha_dig, senhaArquivo) == 0) {
                    loginEncontrado = 1;
                    printf("\nLogin bem-sucedido! Bem-vindo %s.\n", loginArquivo);
                    fclose(usuariosLog);
                    system("pause");
                    system("cls");

                    defUserPanel(roleArquivo);
                    return 0;
                }
            }
        }


        fclose(usuariosLog);

        if (!loginEncontrado && !statusInativo) {
            printf("Login e/ou senha incorretos.\n");
            printf("Deseja tentar novamente? (1 - Sim / 0 - Nao): ");
            int tentar;
            readInt(&tentar);
            if (!tentar) {
                printf("Saindo...\n");
                system("pause");
                system("cls");
                exit(0);
            }
            system("cls");
        }
    } while (!loginEncontrado);

    return 0;
}


