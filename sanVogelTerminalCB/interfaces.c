#include "interfaces.h"

void usuarioPadrao() {
    FILE *usuarios = fopen("usuarios.txt", "r");

    if (usuarios != NULL){
        fclose(usuarios);
        return;
    }
        usuarios = fopen("usuarios.txt", "w");
        if (usuarios != NULL) {
            fprintf(usuarios, "master 123 Master Ativo\n");

            fclose(usuarios);
        } else {
            perror("Erro ao abrir o arquivo de usuarios.\n");
            exit(1);
    }
}


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
            scanf("%d", &opcaoAdm);
            switch (opcaoAdm) {
            case 1:
                system("cls");
                storageAdmPanel();
                break;
            case 2:
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
            scanf("%d", &opcaoOp);
            switch (opcaoOp) {
            case 1:
                //CstEstoque();
                system("pause");
                system("cls");
                break;
            case 2:
                printf("vender produto\n");
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
        } while (opcaoOp != 2);
    } else if (strcasecmp(roleArquivo, "Master") == 0) {
        int opcaoMa;
        do {
            opcoesMa();
            printf("Escolha uma opcao: ");
            scanf("%d", &opcaoMa);
            switch (opcaoMa) {
            case 1:
                system("cls");
                gerUser();
            break;
            case 2:
                //storageOpPanel();
                system("cls");
            break;
            case 3:
                system("cls");
                    //CstEstoque();
                    system("pause");
                break;
            case 4:
                //cstEstoqueEsp();
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
        } while (opcaoMa != 5);
    }
}

int login() {
    FILE *usuariosLog;
    char login_dig[30], senha_dig[30];
    char loginArquivo[30], senhaArquivo[30], roleArquivo[10], statusArquivo[10];
    int loginEncontrado = 0;

    // Estrutura de repeti��o caso o usuario erre a senha
    do {
        usuariosLog = fopen("usuarios.txt", "r+");

        if (usuariosLog == NULL) {
            printf("Erro ao abrir o arquivo de usuarios.\n");
            exit(1);
        }

        printf("\nDigite seu Login: ");
        scanf("%s", login_dig);

        printf("Digite sua senha: ");
        //mascarando senha
        int i = 0;
        char ch;
        while (1) {
            ch = getch(); // L� um caractere

            if (ch == '\r') { // Se Enter
                senha_dig[i] = '\0'; // Termina a string
                printf("\n"); // Nova linha ap�s a senha
                break;
            } else if (ch == 8) { // Se Backspace
                if (i > 0) {
                    i--; // Decrementa o �ndice
                    printf("\b \b"); // Apaga o �ltimo caractere na tela
        }
            } else if (i < 29) { // Limita o tamanho da senha
                senha_dig[i++] = ch; // Armazena o caractere
                printf("*"); // Exibe um asterisco
            }
        }

        while (fscanf(usuariosLog, "%s %s %s %s", loginArquivo, senhaArquivo, roleArquivo, statusArquivo) != EOF) {
            // Compara��o case-insensitive para login e senha
            if (strcasecmp(statusArquivo, "Inativo") == 0) {
                printf("Usuario Inativo.\n");
                system("pause");
                system("cls");
                login();
                }

            if (strcasecmp(loginArquivo, login_dig) == 0 && strcmp(senha_dig, senhaArquivo) == 0) {
                loginEncontrado = 1;
                printf("\nLogin bem-sucedido! Bem-vindo %s.\n", loginArquivo);
                system("pause");
                system("cls");

                defUserPanel(roleArquivo);

                break; // Encerra o loop ap�s encontrar o usu�rio
            }
        }

        fclose(usuariosLog);

        if (!loginEncontrado) {
            printf("Login e/ou senha incorretos.\n");
            printf("Deseja tentar novamente? (1 - Sim / 0 - Nao): ");
            int tentar;
            scanf("%d", &tentar);
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

