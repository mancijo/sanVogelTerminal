#include "interfaces.h"

void abertura() {
    printf("==============================\n");
    printf("\033[1;32m"); // Inicia a cor verde claro
    printf("     BEM-VINDO AO SISTEMA     \n");
    printf("\033[0m");// Retorno cor padrão
    printf("==============================\n");
    system("pause");
    system("cls");
}

int login() {
    FILE *usuariosLog;
    char login_dig[30], senha_dig[30];
    char loginArquivo[30], senhaArquivo[30], roleArquivo[10];
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

        while (fscanf(usuariosLog, "%s %s %s", loginArquivo, senhaArquivo, roleArquivo) != EOF) {
            // Compara��o case-insensitive para login e senha
            if (strcasecmp(loginArquivo, login_dig) == 0 && strcmp(senha_dig, senhaArquivo) == 0) {
                loginEncontrado = 1;
                printf("\nLogin bem-sucedido! Bem-vindo %s.\n", loginArquivo);
                system("pause");
                system("cls");

                if (strcasecmp(roleArquivo, "Admin") == 0) {
                    int opcaoAdm;
                    do {
                        opcoesAdm();
                        printf("Escolha uma opcao: ");
                        scanf("%d", &opcaoAdm);
                        switch (opcaoAdm) {
                        case 1:
                            system("cls");
                            strgPanel();
                            break;
                        case 2:
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
                    } while (opcaoAdm != 3);
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
                            //    gerEstq();
                        break;
                        case 2:
                            system("cls");
                            gerUser();
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
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            opcoesMa();
                            break;
                        }
                    } while (opcaoMa != 5);
                }
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



// Fun��o de op��es para usu�rio Master
void opcoesMa() {
    printf("\033[1;37;44m");//cor branca com fundo azul
    printf("\n-------------MENU-------------\n");
    printf("\033[0m");// Retorno cor padr�o
    printf("==============================\n");
    printf("Escolha uma das opcoes abaixo: \n");
    printf("\n");
    printf("1. Acessar estoque\n");
    printf("2. Gerenciar usuario.\n");
    printf("\033[1;37;41m\n"); // Cor branca com fundo vermelho
    printf("0. Sair.                      \n");
    printf("\033[0m"); // Retorno cor padr�o
    printf("==============================\n");
}


int strgPanel() {
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
    printf("5. Voltar.                    \n");
    printf("\033[0m"); // Retorno cor padr�o
    printf("==============================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &ge);

    switch (ge) {
        case 1:
            insertItem();
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            system("pause");
            break;
        case 5:
            system("cls");
            opcoesAdm();
            break;
    }
    return 0;
}

