#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>

typedef struct {
    int id;
    char name[30];
    float price;
    int units;
    bool active;
} Product;

FILE *arqIn; // Ponteiro do arquivo
Product *vProducts; // Ponteiro para a array de produtos
int productQuantity; // Quantidade de produtos




int readFile() {            //L� o arquivo e gera a array
    // Abre o arquivo e verifica se abriu
    size_t fSize;
    arqIn = fopen("productList.dat", "rb");
    if (!arqIn) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }
    // Descobre o tamanho do arquivo e a quantidade de itens nele
    fseek(arqIn, 0l, SEEK_END);
    fSize = ftell(arqIn);
    productQuantity = fSize / sizeof(Product);
    fseek(arqIn, 0l, SEEK_SET);
    // Aloca mem�ria para o vetor
    vProducts = malloc(fSize);
    if (!vProducts) {
        fclose(arqIn);
        perror("Falha ao alocar vetor!");
        return 0;
    }
    // Insere os itens do arquivo no vetor alocado
    size_t readCount = fread(vProducts, sizeof(Product), productQuantity, arqIn);
    if (readCount != (size_t)productQuantity) {
        perror("Erro ao ler produtos do arquivo");
    }

    fclose(arqIn);
    return 1;
}

//Salvando o arquivo
void saveFile() {           // Salva o vetor no arquivo binario
    arqIn = fopen("productList.dat", "wb");
    for(int i = 0; i <= productQuantity - 1; i++) {
        fwrite(&vProducts[i], sizeof(vProducts[0]), 1, arqIn);
    }
    fclose(arqIn);
}

//Fun��o para busca de itens no estoque
Product* searchItem(int insertedType, char *insertedSearch) { // A funcao recebe dois parametros e retorna um item com a struct Product
    readFile();
    switch(insertedType) {
        case 1:  //Busca por ID
            for(int i = 0; i < productQuantity; i++) {
                if(vProducts[i].id == atoi(insertedSearch)) {
                    return &vProducts[i];
                }
            }
        break;
        case 2:   //Busca pelo nome
            for(int i = 0; i < productQuantity; i++) {
                if(strcasecmp(insertedSearch, vProducts[i].name) == 0) {
                    return &vProducts[i];
                }
            }
        break;
        default:
            return NULL;
    }
    return NULL;
}

// Fun��o para inser��o de produtos
int insertItem () {                  // Loop de inser��o de itens
    readFile();                                 // Atualiza quantidade de produtos (necess�rio para definir ID)
    arqIn = fopen("productList.dat", "ab");
    if(!arqIn){                                 // Abre o arquivo em forma de append e valida se abriu
        printf("file error");
        return(0);
    }

    char choice;
    do {
        printf("Inserir novo produto? [S/N]: ");
        choice = getchar();
        while (getchar() != '\n'); // Limpa o buffer

        if (choice != 's' && choice != 'S') {
            break;
        }

        Product newProduct = { productQuantity++, "", 0.0f, 0, true }; // Define os valores padr�o

        printf("Nome: ");
        fgets(newProduct.name, sizeof(newProduct.name), stdin);
        newProduct.name[strcspn(newProduct.name, "\n")] = 0; // Remove o '\n'

        printf("Pre�o: ");
        scanf("%f", &newProduct.price);
        printf("Unidades: ");
        scanf("%i", &newProduct.units);
        getchar(); // Limpa o buffer

        fwrite(&newProduct, sizeof(newProduct), 1, arqIn);
    } while (1);        // Loop se encerra apenas com o break

    fclose(arqIn);  // Fecha o Arquivo

    return(0);
}

// Fun��o para listar todos os produtos
void showAllProducts () {           //Mostrar todos os produtos
    readFile();
    for(int i = 0; i < productQuantity; i++){
        if(vProducts[i].active){
            printf("%i\t\t%s\t\t\t%i\t\t%3.2f\n", vProducts[i].id, vProducts[i].name, vProducts[i].units, vProducts[i].price);
        }
    }
}

// Editar produtos
void editProduct(Product *productPtr, char *element, char *feed) { //funcao para alterar os dados de produto na array
    if(strcasecmp(element, "nome") == 0){
        strcpy(productPtr->name, feed);
    } else
    if(strcasecmp(element, "preco") == 0){
        productPtr->price = atof(feed);
    } else
    if(strcasecmp(element, "quantidade") == 0){
        productPtr->units = atoi(feed);
    } else {
        printf("Erro ao editar"); system("pause");
    }
}

// Abertura do sistema
void abertura() {
    printf("==============================\n");
    printf("\033[1;32m"); // Inicia a cor verde claro
    printf("     BEM-VINDO AO SISTEMA     \n");
    printf("\033[0m");// Retorno cor padr�o
    printf("==============================\n");
    system("pause");
    system("cls");
}

// Prototipa��o das fun��es
int login();
void opcoesAdm();
void opcoeOp();
void opcoesMa();
void CadUsr();
int gerUser();
int gerEstq();
void AtivarProduto(); // Prototipagem correta
void AlterarUsr();    // Adicionando o prot�tipo da fun��o AlterarUsr

void subVirgpPonto(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
}


// Fun��o de op��es para usu�rio Operador
void opcoeOp() {
    printf("\033[1;37;44m");//cor branca com fundo azul
    printf("\n---------MENU----------\n");
    printf("\033[0m");// Retorno cor padr�o
    printf("Escolha uma das opcoes abaixo: \n");
    printf("==============================\n");
    printf("1. Consultar Estoque.\n");
    printf("2. Vender produto.\n");
    printf("0. Sair.\n");
    printf("==============================\n");
}

// Fun��o de op��es para usu�rio Admin
void opcoesAdm() {
    printf("\n---------MENU----------\n");
    printf("Escolha uma das opcoes abaixo: \n");
    printf("==============================\n");
    printf("1. Acessar Estoque.\n");
    printf("2. Iniciar vendas.\n");
    printf("0. Sair.\n");
    printf("==============================\n");
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

// Fun��o para cadastrar usu�rio
void CadUsr() {
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

// Fun��o para gerenciar usu�rios
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
        CadUsr();
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
                                gerEstq();
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

// Fun��o principal
int main() {
    // Chamada da fun��o de abertura
    abertura();
    login();
    return 0;
}
