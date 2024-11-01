#include "ti.h"

void opcoesTi() {
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
            alterarUsr();
            system("pause");
        break;
    case 3:
        printf("Funcionalidade de desabilitar usuario ainda nao implementada.\n");
        break;
    case 4:
        system("cls");
        opcoesTi();
        break;
    default:
        printf("Opcao invalida!\n");
        gerUser(); // Chama a fun��o novamente em caso de op��o inv�lida
        break;
    }

    return 0;
}

void alterarUsr() {
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
