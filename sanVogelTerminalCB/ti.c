#include "ti.h"

void opcoesMa() {
    printf("\033[1;37;44m");//cor branca com fundo azul
    printf("\n-------------MENU-------------\n");
    printf("\033[0m");// Retorno cor padr�o
    printf("==============================\n");
    printf("Escolha uma das opcoes abaixo: \n");
    printf("\n");
    printf("1. Gerenciar usuario\n");
    printf("2. Acessar estoque\n");
    printf("3. Vender\n");
    printf("\033[1;37;41m\n"); // Cor branca com fundo vermelho
    printf("0. Sair.                      \n");
    printf("\033[0m"); // Retorno cor padrao
    printf("==============================\n");
}

void cadUsr() {
    FILE *usuarios;
    char lUsr[30];
    char sUsr[30];
    char roleUsr[10];
    char statusUsr[10] = "Ativo";

    // Verifica se o arquivo de usu�rios pode ser aberto
    usuarios = fopen("usuarios.txt", "a+");
    if (usuarios == NULL){
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    printf("Digite o nome do usuario: ");
    scanf("%s", lUsr);

    //Verificar se o usu�rio j� existe no arquivo
    char tempName[30], tempPass[30], tempRole[10], tempStatus[10];
    while (fscanf(usuarios, "%s %s %s %s", tempName, tempPass, tempRole, tempStatus) != EOF) {
        if (strcmp(tempName, lUsr) == 0) {
            printf("Usuario '%s' ja cadastrado.\n", lUsr);
            system("pause");
            system("cls");
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
    fprintf(usuarios, "%s %s %s %s\n", lUsr, sUsr, roleUsr, statusUsr);
    fclose(usuarios);

    printf("\nUsuario cadastrado com sucesso!\n\n");
    system("pause");
    system("cls");
}

void alterarUsr() {
    FILE *usuarios;
    char nomeAntigo[30], novoNome[30], novaSenha[30], novoRole[10], novoStatus[10];
    char tempName[30], tempPass[30], tempRole[10], tempStatus[10];
    int found = 0;

    usuarios = fopen("usuarios.txt", "r+");
    if (usuarios == NULL) {
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    printf("Digite o nome do usuario que deseja alterar: ");
    scanf("%s", nomeAntigo);

    char linhas[100][100]; // Ajuste o tamanho conforme necessário
    int i = 0;

    // Lê todos os usuários no arquivo e os armazena em 'linhas'
    while (fscanf(usuarios, "%s %s %s %s", tempName, tempPass, tempRole, tempStatus) != EOF) {
        snprintf(linhas[i], sizeof(linhas[i]), "%s %s %s %s", tempName, tempPass, tempRole, tempStatus);
        i++;
    }

    // Procura pelo usuário a ser alterado
    for (int j = 0; j < i; j++) {
        if (strstr(linhas[j], nomeAntigo) != NULL) { // Verifica se o usuário está na linha
            found = 1;

            // Alteração do nome
            printf("Usuario encontrado! \nDeseja alterar o nome? (1 - Sim / 0 - Nao): ");
            int alterarNome;
            readInt(&alterarNome);
            if (alterarNome) {
                printf("Digite o novo nome: ");
                scanf("%s", novoNome);
                sscanf(linhas[j], "%s %s %s %s", tempName, tempPass, tempRole, tempStatus);
                snprintf(linhas[j], sizeof(linhas[j]), "%s %s %s %s", novoNome, tempPass, tempRole, tempStatus);
            }

            // Alteração da senha
            printf("Deseja alterar a senha? (1 - Sim / 0 - Nao): ");
            int alterarSenha;
            readInt(&alterarSenha);
            if (alterarSenha) {
                printf("Digite a nova senha: ");
                int k = 0;
                char ch;
                while ((ch = getch()) != '\r' && k < 29) {
                    novaSenha[k++] = ch;
                    printf("*");
                }
                novaSenha[k] = '\0'; // Termina a string
                sscanf(linhas[j], "%s %s %s %s", tempName, tempPass, tempRole, tempStatus);
                snprintf(linhas[j], sizeof(linhas[j]), "%s %s %s %s", tempName, novaSenha, tempRole, tempStatus);
            }

            // Alteração do nível de hierarquia
            printf("Deseja alterar o nivel de hierarquia? (1 - Sim / 0 - Nao): ");
            int alterarRole;
            readInt(&alterarRole);
            if (alterarRole) {
                printf("Digite o novo nivel de hierarquia (Operador, Admin, Master): ");
                scanf("%s", novoRole);
                sscanf(linhas[j], "%s %s %s %s", tempName, tempPass, tempRole, tempStatus);
                snprintf(linhas[j], sizeof(linhas[j]), "%s %s %s %s", tempName, tempPass, novoRole, tempStatus);
            }

            // Alteração do status
            printf("Deseja alterar o status do usuario? (1 - Sim / 0 - Nao): ");
            int alterarStatus;
            readInt(&alterarStatus);
            if (alterarStatus) {
                printf("Digite o novo status do usuario (Ativo ou Inativo): ");
                scanf("%s", novoStatus);
                sscanf(linhas[j], "%s %s %s %s", tempName, tempPass, tempRole, tempStatus);
                snprintf(linhas[j], sizeof(linhas[j]), "%s %s %s %s", tempName, tempPass, tempRole, novoStatus);
            }
        }
    }

    if (found) {
        // Reabre o arquivo para sobrescrever os dados atualizados
        freopen("usuarios.txt", "w", usuarios);
        for (int j = 0; j < i; j++) {
            fprintf(usuarios, "%s\n", linhas[j]);
        }
        printf("Usuario alterado com sucesso!\n");
    } else {
        printf("Usuario nao encontrado.\n");
    }

    fclose(usuarios);
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
    printf("0. Voltar.                    \n");
    printf("\033[0m"); // Retorno cor padr�o
    printf("==============================\n");
    printf("Escolha uma opcao: ");
    readInt(&gerUsuario);

    switch (gerUsuario) {
    case 1:
        cadUsr();
        break;
    case 2:
        alterarUsr();
        system("pause");
        system("cls");
        break;
    case 3:
        inativarUsuario();
        system("pause");
        system("cls");
        break;
    case 0:
        system("cls");
        opcoesMa();
        system("cls");
        break;
    default:
        printf("Opcao invalida!\n");
        gerUser(); // Chama a fun��o novamente em caso de op��o inv�lida
        break;
    }

    return 0;
}

int editProductPanelTi() {
    // Declaração das variáveis
    int type;
    char search[30], searchNI[30];
    Product* produtoAlvo;

    puts("Insira 1 para selecionar o produto usando ID. \nInsira 2 para selecionar o produto usando o nome. \n");
    scanf(" %i", &type);
    if(type != 1 && type != 2 && type != 3){
        puts("Valor invalido.");
        system("pause");
        system("cls");
        return editProductPanel();
    } // Verificação do caractere
 /*   if(type == 3) {
        system("cls");
        showAllProducts();
    } */// Mostrar todos os produtos



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

    puts("O que deseja alterar?");
    puts("1. Nome");
    puts("2. Preco");
    puts("3. Quantidade");
    puts("0. Cancelar");

    fflush(stdin);
    readInt(&type);
    switch (type) {
        case 1: {
            char newName[30];

            puts("\nInsira o novo nome do produto:");
            while (getchar() != '\n' && getchar() != EOF);
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = 0;

            editProduct(produtoAlvo, "nome", newName);

            puts("Produto editado!");
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
            break;
        }
        case 0: {
            opcoesMa();
            break;
        }
        default:
            printf("Erro!\n");
            break;
    }

    return 1;
}

int storageTiPanel() {
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
    printf("6. Consultar estoque.\n");
    printf("\033[1;37;41m\n"); // Cor branca com fundo vermelho
    printf("0. Voltar.                    \n");
    printf("\033[0m"); // Retorno cor padrao
    printf("==============================\n");
    printf("Escolha uma opcao: ");
    readInt(&ge);

    switch (ge) {
        case 1:
            system("cls");
            insertItem();
            break;
        case 2:
            editProductPanelTi();
            system("cls");
            break;
        case 3:
            inativarProduto();
            system("pause");
            system("cls");
            break;
        case 4:
            ativarProduto();
            system("pause");
            system("cls");
            break;
        case 5:
            exibirHistoricoVendas();
            system("pause");
            system("cls");
            break;
        case 6:
            showAllProducts();
            system("pause");
            system("cls");
        case 0:
            system("cls");
            opcoesMa();
            break;
    }
    return 0;
}

void inativarUsuario() {
    Usuario usuarios[MAX_USUARIOS];
    int totalUsuarios = 0;
    char loginParaInativar[30];
    int usuarioEncontrado = 0;

    // Abrir o arquivo de usuários para leitura
    FILE *file = fopen("usuarios.txt", "r+");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Carregar todos os usuários do arquivo para a memória
    while (fscanf(file, "%s %s %s %s", usuarios[totalUsuarios].login, usuarios[totalUsuarios].senha,
                  usuarios[totalUsuarios].role, usuarios[totalUsuarios].status) == 4) {
        totalUsuarios++;
        if (totalUsuarios >= MAX_USUARIOS) {
            printf("Número máximo de usuários atingido.\n");
            break; // Evita overflow
        }
    }

    // Solicitar o login do usuário a ser inativado
    printf("Digite o login do usuario que deseja inativar: ");
    scanf("%s", loginParaInativar);

    // Buscar e inativar o usuário na memória
    for (int i = 0; i < totalUsuarios; i++) {
        // Comparar o status de forma case-insensitive
        if (strcasecmp(usuarios[i].login, loginParaInativar) == 0 &&
            strcasecmp(usuarios[i].status, "Ativo") == 0) {
            strcpy(usuarios[i].status, "inativo");  // Marca o usuário como inativo
            printf("Usuario '%s' foi inativado com sucesso.\n", usuarios[i].login);
            usuarioEncontrado = 1;
            break;
        }
    }

    if (!usuarioEncontrado) {
        printf("Usuario '%s' nao encontrado ou ja esta inativo.\n", loginParaInativar);
    }

    // Voltar ao início do arquivo para sobrescrever os dados
    rewind(file);

    // Escrever todos os usuários atualizados de volta ao arquivo
    for (int i = 0; i < totalUsuarios; i++) {
        fprintf(file, "%s %s %s %s\n", usuarios[i].login, usuarios[i].senha, usuarios[i].role, usuarios[i].status);
    }

    fclose(file);
}

