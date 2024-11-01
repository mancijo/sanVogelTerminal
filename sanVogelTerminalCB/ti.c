#include "ti.h"

void cadUsr() {
    FILE *usuarios;
    char lUsr[30];
    char sUsr[30];
    char roleUsr[10];

    // Verifica se o arquivo de usu�rios pode ser aberto
    usuarios = fopen("usuarios.txt", "a+");
    if (usuarios == NULL){
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    printf("Digite o nome do usuario: ");
    scanf("%s", lUsr);

    //Verificar se o usu�rio j� existe no arquivo
    char tempName[30], tempPass[30], tempRole[10];
    while (fscanf(usuarios, "%s %s %s", tempName, tempPass, tempRole) != EOF) {
        if (strcmp(tempName, lUsr) == 0) {
            printf("Usu�rio '%s' j� cadastrado.\n", lUsr);
            fclose(usuarios); // Certifica-se de fechar o arquivo antes de retornar
            return;
        }
    }

    fclose(usuarios);

    // Abre o arquivo novamente em modo de adi��o
    usuarios = fopen("usuarios.txt", "a+");
    if (usuarios == NULL) {
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    printf("Digite a senha do usuario: ");

    // Mascarando a senha
    int i = 0;
    char ch;
    while (1) {
        ch = getch(); // L� um caractere

        if (ch == '\r') { // Se Enter
            sUsr[i] = '\0'; // Termina a string
            printf("\n"); // Nova linha ap�s a senha
            break;
        } else if (ch == 8) { // Se Backspace
            if (i > 0) {
                i--; // Decrementa o �ndice
                printf("\b \b"); // Apaga o �ltimo caractere na tela
    }
        } else if (i < 29) { // Limita o tamanho da senha
            sUsr[i++] = ch; // Armazena o caractere
            printf("*"); // Exibe um asterisco
        }
    }

    printf("\nEscolha um nivel de hierarquia (Operador, Admin, Master): ");
    scanf("%s", roleUsr);

    // Adiciona o novo usu�rio ao arquivo
    fprintf(usuarios, "%s %s %s\n", lUsr, sUsr, roleUsr);
    fclose(usuarios);

    printf("\nUsuario cadastrado com sucesso!\n\n");
}

int gerUser() {
    int gerUsuario;
    printf("\033[1;37;44m"); // cor branca com fundo azul
    printf("\n-------------MENU-------------\n");
    printf("\033[0m"); // Retorno cor padr�o
    printf("==============================\n");
    printf("1. Cadastrar usuario.\n");
    printf("2. Alterar usuario.\n");
    printf("3. Desabilitar usuario.\n");
    printf("\033[1;37;41m\n"); // Cor branca com fundo vermelho
    printf("4. Voltar.                    \n");
    printf("\033[0m"); // Retorno cor padr�o
    printf("==============================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &gerUsuario);

    switch (gerUsuario) {
    case 1:
        cadUsr();
        break;
    case 2:
            AlterarUsr();
            system("pause");
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
        gerUser(); // Chama a fun��o novamente em caso de op��o inv�lida
        break;
    }

    return 0;
}
