#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // Inclua esta biblioteca para usar getch()
#include <locale.h>
#include "managEstq.h"

// Definição da struct produto
typedef struct {
    int IdP;
    int qtdP;
    char precoP[10];
    char nP[100];
} produto;

// Abertura do sistema
void abertura() {
    printf("==============================\n");
    printf("\033[1;32m"); // Inicia a cor verde claro
    printf("     BEM-VINDO AO SISTEMA     \n");
    printf("\033[0m");// Retorno cor padrão
    printf("==============================\n");
    system("pause");
    system("cls");
}

// Prototipação das funções
int login();
void opcaoUsr();
void opcoesAdm();
void opcoeOp();
void opcoesMa();
void CadUsr();
int gerUser();
void CstEstoque();
void cstEstoqueEsp();
void CadEstoque();
int gerEstq();

void subVirgpPonto(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
}

// Função de opções para usuário Admin
void opcoesAdm() {
    printf("\n---------MENU----------\n");
    printf("Escolha uma das opcoes abaixo: \n");
    printf("==============================\n");
    printf("1. Gerenciar Estoque.\n");
    printf("2. Consultar Estoque.\n");
    printf("3. Sair.\n");
    printf("==============================\n");
}

// Função de opções para usuário Operador
void opcoeOp() {
    printf("\033[1;37;44m");//cor branca com fundo azul
    printf("\n---------MENU----------\n");
    printf("\033[0m");// Retorno cor padrão
    printf("Escolha uma das opcoes abaixo: \n");
    printf("==============================\n");
    printf("1. Consultar Estoque.\n");
    printf("2. Vender produto.\n");
    printf("3. Sair.\n");
    printf("==============================\n");
}

// Função de opções para usuário Master
void opcoesMa() {
    printf("\033[1;37;44m");//cor branca com fundo azul
    printf("\n-------------MENU-------------\n");
    printf("\033[0m");// Retorno cor padrão
    printf("==============================\n");
    printf("Escolha uma das opcoes abaixo: \n");
    printf("\n");
    printf("1. Gerenciar estoque.\n");
    printf("2. Gerenciar usuario.\n");
    printf("3. Consultar Estoque.\n");
    printf("4. Buscar produto.\n");
    printf("\033[1;37;41m\n"); // Cor branca com fundo vermelho
    printf("5. Sair.                      \n");
    printf("\033[0m"); // Retorno cor padrão
    printf("==============================\n");
}

// Função para cadastrar usuário
void CadUsr() {
    FILE *usuarios;
    char lUsr[30];
    char sUsr[30];
    char roleUsr[10];

    // Verifica se o arquivo de usu rios pode ser aberto
    usuarios = fopen("usuarios.txt", "a+");
    if (usuarios == NULL){
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    printf("Digite o nome do usuario: ");
    scanf("%s", lUsr);

    //Verificar se o usuário já  existe no arquivo
    char tempName[30], tempPass[30], tempRole[10];
    while (fscanf(usuarios, "%s %s %s", tempName, tempPass, tempRole) != EOF) {
        if (strcmp(tempName, lUsr) == 0) {
            printf("Usuário '%s' já cadastrado.\n", lUsr);
            fclose(usuarios); // Certifica-se de fechar o arquivo antes de retornar
            return;
        }
    }

    fclose(usuarios);

    // Abre o arquivo novamente em modo de adição
    usuarios = fopen("usuarios.txt", "a+");
    if (usuarios == NULL) {
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    printf("Digite a senha do usuario: ");

    // Mascarando a senha
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < 29) { // L  at  o Enter
        sUsr[i++] = ch;
        printf("*"); // Exibe um asterisco para cada caractere
    }
    sUsr[i] = '\0'; // Termina a string

    printf("\nEscolha um nivel de hierarquia (Operador, Admin, Master): ");
    scanf("%s", roleUsr);

    // Adiciona o novo usu rio ao arquivo
    fprintf(usuarios, "%s %s %s\n", lUsr, sUsr, roleUsr);
    fclose(usuarios);

    printf("\nUsuario cadastrado com sucesso!\n\n");
}

// Função para gerenciar usuários
int gerUser() {
    int gerUsuario;
    printf("\033[1;37;44m");//cor branca com fundo azul
    printf("\n-------------MENU-------------\n");
    printf("\033[0m");// Retorno cor padrão
    printf("==============================\n");
    printf("1. Cadastrar usuario.\n");
    printf("2. Alterar usuario.\n");
    printf("3. Desabilitar usuario.\n");
    printf("\033[1;37;41m\n"); // Cor branca com fundo vermelho
    printf("4. Voltar.                    \n");
    printf("\033[0m");// Retorno cor padrão
    printf("==============================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &gerUsuario);

    switch (gerUsuario) {
    case 1:
        CadUsr();
        break;
    case 2:
        printf("Funcionalidade de alterar usuario ainda nao implementada.\n");
        break;
    case 3:
        printf("Funcionalidade de desabilitar usuario ainda nao implementada.\n");
        break;
    case 4:
        system("cls");
        opcoesMa();
        break;
    default:
        printf("Opcao invalida!\n");
        gerUser(); // Chama a função novamente em caso de opção inválida
        break;
    }

    return 0;
}

// Função de login
int login() {
    FILE *usuariosLog;
    char login_dig[30], senha_dig[30];
    char loginArquivo[30], senhaArquivo[30], roleArquivo[10];
    int loginEncontrado = 0;

    // Estrutura de repetição caso o usuario erre a senha
    do {
        usuariosLog = fopen("usuarios", "a+");

        if (usuariosLog == NULL) {
            printf("Erro ao abrir o arquivo de usuarios.\n");
            exit(1);
        }

        printf("\nDigite seu Login: ");
        scanf("%s", login_dig);

        printf("Digite sua senha: ");
        // Mascarando a senha
        int i = 0;
        char ch;
        while ((ch = getch()) != '\r' && i < 29) { // Lê até o Enter
            senha_dig[i++] = ch;
            printf("*"); // Exibe um asterisco para cada caractere
        }
        senha_dig[i] = '\0'; // Termina a string
        printf("\n"); // Nova linha após a senha

        while (fscanf(usuariosLog, "%s %s %s", loginArquivo, senhaArquivo, roleArquivo) != EOF) {
            if (strcmp(loginArquivo, login_dig) == 0 && strcmp(senha_dig, senhaArquivo) == 0) {
                loginEncontrado = 1;
                printf("\nLogin bem-sucedido! Bem-vindo %s.\n", loginArquivo);
                system("pause");
                system("cls");

                if (strcmp(roleArquivo, "Admin") == 0) {
                    int opcaoAdm;
                    do {
                        opcoesAdm();
                        printf("Escolha uma opcao: ");
                        scanf("%d", &opcaoAdm);
                        switch (opcaoAdm) {
                        case 1:
                            system("pause");
                            system("cls");
                            break;
                        case 2:
                            system("pause");
                            system("cls");
                            break;
                        case 3:
                            printf("Saindo...\n");
                            system("pause");
                            system("cls");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                        }
                    } while (opcaoAdm != 3);
                } else if (strcmp(roleArquivo, "Operador") == 0) {
                    int opcaoOp;
                    do {
                        opcoeOp();
                        printf("Escolha uma opcao: ");
                        scanf("%d", &opcaoOp);
                        switch (opcaoOp) {
                        case 1:
                            system("pause");
                            system("cls");
                            break;
                        case 2:
                            printf("vender produto\n");
                            break;
                        case 3:
                            printf("Saindo...\n");
                            system("pause");
                            system("cls");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            break;
                        }
                    } while (opcaoOp != 2);
                } else if (strcmp(roleArquivo, "Master") == 0) {
                    int opcaoMa;
                    do {
                        opcoesMa();
                        printf("Escolha uma opcao: ");
                        scanf("%d", &opcaoMa);
                        switch (opcaoMa) {
                        case 1:
                            system("cls");
                        break;
                        case 2:
                            system("cls");
                            gerUser();
                            system("cls");
                        break;
                        case 3:
                            system("cls");
                            system("cls");
                            break;
                        case 4:
                            system("pause");
                            system("cls");
                            break;
                        case 5:
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
                break; // Encerra o loop após encontrar o usuário
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

// Função principal
int main() {

    setlocale(LC_ALL, "Portuguese");
    // Chamada da função de abertura
     
    login();

    return 0;
}

