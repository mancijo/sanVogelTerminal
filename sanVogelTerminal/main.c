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




int readFile() {            //Lê o arquivo e gera a array
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
    // Aloca memória para o vetor
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

//Função para busca de itens no estoque
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

// Função para inserção de produtos
int insertItem () {                  // Loop de inserção de itens
    readFile();                                 // Atualiza quantidade de produtos (necessário para definir ID) 
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

        Product newProduct = { productQuantity++, "", 0.0f, 0, true }; // Define os valores padrão

        printf("Nome: ");
        fgets(newProduct.name, sizeof(newProduct.name), stdin);
        newProduct.name[strcspn(newProduct.name, "\n")] = 0; // Remove o '\n'

        printf("Preço: ");
        scanf("%f", &newProduct.price);
        printf("Unidades: ");
        readInt(&newProduct.units);
        getchar(); // Limpa o buffer

        fwrite(&newProduct, sizeof(newProduct), 1, arqIn);
    } while (1);        // Loop se encerra apenas com o break

    fclose(arqIn);  // Fecha o Arquivo

    return(0);
}

// Função para listar todos os produtos
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
    printf("\033[0m");// Retorno cor padrão
    printf("==============================\n");
    system("pause");
    system("cls");
}

// Prototipação das funções
int login();
void opcoesAdm();
void opcoeOp();
void opcoesMa();
void CadUsr();
int gerUser();
int gerEstq();
void AtivarProduto(); // Prototipagem correta
void AlterarUsr();    // Adicionando o protótipo da função AlterarUsr

void subVirgpPonto(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
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

    // Verifica se o arquivo de usuários pode ser aberto
    usuarios = fopen("usuarios.txt", "a+");
    if (usuarios == NULL){
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    printf("Digite o nome do usuario: ");
    scanf("%s", lUsr);

    //Verificar se o usuário já existe no arquivo
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
    while (1) {
        ch = getch(); // Lê um caractere

        if (ch == '\r') { // Se Enter
            sUsr[i] = '\0'; // Termina a string
            printf("\n"); // Nova linha após a senha
            break;
        } else if (ch == 8) { // Se Backspace
            if (i > 0) {
                i--; // Decrementa o índice
                printf("\b \b"); // Apaga o último caractere na tela
    }
        } else if (i < 29) { // Limita o tamanho da senha
            sUsr[i++] = ch; // Armazena o caractere
            printf("*"); // Exibe um asterisco
        }
    }

    printf("\nEscolha um nivel de hierarquia (Operador, Admin, Master): ");
    scanf("%s", roleUsr);

    // Adiciona o novo usuário ao arquivo
    fprintf(usuarios, "%s %s %s\n", lUsr, sUsr, roleUsr);
    fclose(usuarios);

    printf("\nUsuario cadastrado com sucesso!\n\n");
}

// Função para gerenciar usuários
int gerUser() {
    int gerUsuario;
    printf("\033[1;37;44m"); // cor branca com fundo azul
    printf("\n-------------MENU-------------\n");
    printf("\033[0m"); // Retorno cor padrão
    printf("==============================\n");
    printf("1. Cadastrar usuario.\n");
    printf("2. Alterar usuario.\n");
    printf("3. Desabilitar usuario.\n");
    printf("\033[1;37;41m\n"); // Cor branca com fundo vermelho
    printf("4. Voltar.                    \n");
    printf("\033[0m"); // Retorno cor padrão
    printf("==============================\n");
    printf("Escolha uma opcao: ");
    readInt(&gerUsuario);

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
        gerUser(); // Chama a função novamente em caso de opção inválida
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
        printf("Arquivo não pode ser aberto\n");
        exit(1);
    }

    printf("Digite o nome do usuário que deseja alterar: ");
    scanf("%s", nomeAntigo);

    // Ler todo o conteúdo para uma lista temporária
    // Aqui, estamos usando um array para armazenar os dados.
    // Considere usar uma estrutura de dados dinâmica (como linked list) se necessário.
    char linhas[100][100]; // Ajuste o tamanho conforme necessário
    int i = 0;

    while (fscanf(usuarios, "%s %s %s", tempName, tempPass, tempRole) != EOF) {
        snprintf(linhas[i], sizeof(linhas[i]), "%s %s %s", tempName, tempPass, tempRole);
        i++;
    }

    // Agora que temos todos os dados, podemos procurar o usuário
    for (int j = 0; j < i; j++) {
        if (strstr(linhas[j], nomeAntigo) != NULL) { // Verifica se o usuário está na linha
            found = 1;
            printf("Usuário encontrado! Deseja alterar o nome? (1 - Sim / 0 - Não): ");
            int alterarNome;
            readInt(&alterarNome);
            if (alterarNome) {
                printf("Digite o novo nome: ");
                scanf("%s", novoNome);
                sscanf(linhas[j], "%s %s %s", tempName, tempPass, tempRole);
                snprintf(linhas[j], sizeof(linhas[j]), "%s %s %s", novoNome, tempPass, tempRole);
            }

            printf("Deseja alterar a senha? (1 - Sim / 0 - Não): ");
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
                sscanf(linhas[j], "%s %s %s", tempName, tempPass, tempRole);
                snprintf(linhas[j], sizeof(linhas[j]), "%s %s %s", tempName, novaSenha, tempRole);
            }

            printf("Deseja alterar o nível de hierarquia? (1 - Sim / 0 - Não): ");
            int alterarRole;
            readInt(&alterarRole);
            if (alterarRole) {
                printf("Digite o novo nível de hierarquia (Operador, Admin, Master): ");
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
        printf("Usuário alterado com sucesso!\n");
    } else {
        printf("Usuário não encontrado.\n");
    }

    fclose(usuarios);
}

void AtivarProduto() {
    FILE *estoque;
    estoque = fopen("estoque.txt", "r+");

    if (estoque == NULL) {
        printf("Arquivo não pode ser aberto\n");
        exit(1);
    }

    int id;
    printf("Digite o ID do produto a ser ativado: ");
    readInt(&id);

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
        printf("Produto não encontrado.\n");
    }

    fclose(estoque);
}

// Função para gerenciar estoque
int gerEstq() {  
    int ge;
    printf("\033[1;37;44m"); // cor branca com fundo azul
    printf("\n-------------MENU-------------\n");
    printf("\033[0m"); // Retorno cor padrão
    printf("==============================\n");
    printf("1. Cadastrar produto.\n");
    printf("2. Editar produto.\n");
    printf("3. Inativar produto.\n");
    printf("4. Ativar produto.\n");
    printf("\033[1;37;41m\n"); // Cor branca com fundo vermelho
    printf("5. Voltar.                    \n");
    printf("\033[0m"); // Retorno cor padrão
    printf("==============================\n");
    printf("Escolha uma opcao: ");
    readInt(&ge);

    switch (ge) {
        case 1:
            //CadEstoque();
            system("pause");
            system("cls");
            break;
        case 2:
            printf("Funcionalidade de editar produto ainda nao implementada.\n");
            break;
        case 3:
    //InativarProduto();
    system("pause");
    break;
case 4:
    AtivarProduto();
    system("pause");
    break;
        case 5:
            system("cls");
            opcoesMa();
            system("cls");
            break;
        default:
            printf("Opcao invalida!\n");
            gerEstq(); // Chama a função novamente em caso de opção inválida
            break;
    }

    return 0;
}

// void InativarProduto() {
//     FILE *estoque;
//     estoque = fopen("estoque.txt", "r+");

//     if (estoque == NULL) {
//         printf("Arquivo não pode ser aberto\n");
//         exit(1);
//     }

//     int id;
//     printf("Digite o ID do produto a ser inativado: ");
//     readInt(&id);

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
//             fgets(buffer, sizeof(buffer), estoque); // Preço
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
//         printf("Produto não encontrado.\n");
//     }

//     fclose(estoque);
// }

// Função de login com verificação case-insensitive
int login() {
    FILE *usuariosLog;
    char login_dig[30], senha_dig[30];
    char loginArquivo[30], senhaArquivo[30], roleArquivo[10];
    int loginEncontrado = 0;

    // Estrutura de repetição caso o usuario erre a senha
    do {
        usuariosLog = fopen("usuarios.txt", "a+");

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
            ch = getch(); // Lê um caractere

            if (ch == '\r') { // Se Enter
                senha_dig[i] = '\0'; // Termina a string
                printf("\n"); // Nova linha após a senha
                break;
            } else if (ch == 8) { // Se Backspace
                if (i > 0) {
                    i--; // Decrementa o índice
                    printf("\b \b"); // Apaga o último caractere na tela
        }
            } else if (i < 29) { // Limita o tamanho da senha
                senha_dig[i++] = ch; // Armazena o caractere
                printf("*"); // Exibe um asterisco
            }
        }

        while (fscanf(usuariosLog, "%s %s %s", loginArquivo, senhaArquivo, roleArquivo) != EOF) {
            // Comparação case-insensitive para login e senha
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
                        readInt(&opcaoAdm);
                        switch (opcaoAdm) {
                        case 1:
                            system("pause");
                            system("cls");
                                gerEstq();
                            break;
                        case 2:
                            //CstEstoque();
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
                } else if (strcasecmp(roleArquivo, "Operador") == 0) {
                    int opcaoOp;
                    do {
                        opcoeOp();
                        printf("Escolha uma opcao: ");
                        readInt(&opcaoOp);
                        switch (opcaoOp) {
                        case 1:
                            //CstEstoque();
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
                } else if (strcasecmp(roleArquivo, "Master") == 0) {
                    int opcaoMa;
                    do {
                        opcoesMa();
                        printf("Escolha uma opcao: ");
                        readInt(&opcaoMa);
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

// Função principal
int main() {
    // Chamada da função de abertura
    abertura();
    login();
    return 0;
}
