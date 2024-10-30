#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // Inclua esta biblioteca para usar getch()
#include <locale.h>
#include <stdbool.h>

// Definição da struct produto
typedef struct {
    int IdP;
    int qtdP;
    char precoP[10];
    char nP[100];
    bool active; // inativar e ativar produto
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
void InativarProduto();
void AtivarProduto(); // Prototipagem correta
void AlterarUsr();    // Adicionando o protótipo da função AlterarUsr

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
            scanf("%d", &alterarNome);
            if (alterarNome) {
                printf("Digite o novo nome: ");
                scanf("%s", novoNome);
                sscanf(linhas[j], "%s %s %s", tempName, tempPass, tempRole);
                snprintf(linhas[j], sizeof(linhas[j]), "%s %s %s", novoNome, tempPass, tempRole);
            }

            printf("Deseja alterar a senha? (1 - Sim / 0 - Não): ");
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

            printf("Deseja alterar o nível de hierarquia? (1 - Sim / 0 - Não): ");
            int alterarRole;
            scanf("%d", &alterarRole);
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


// Função para consultar todo o estoque
void CstEstoque() {
    FILE *estoque;
    estoque = fopen("estoque.txt", "a+");

    if (estoque == NULL) {
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    char consultar[1000];

    while (fgets(consultar, sizeof(consultar), estoque) != NULL) {
        printf("%s", consultar);
    }

    fclose(estoque);
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
        printf("Produto não encontrado.\n");
    }

    fclose(estoque);
}
// Função para consultar um produto específico no estoque
void cstEstoqueEsp() {
    char buffer[1000];
    char search[100];
    int found = 0;

    FILE *estoque;
    estoque = fopen("estoque.txt", "r");

    if (estoque == NULL) {
        printf("Arquivo nao pode ser aberto.\n");
        exit(1);
    }

    printf("Digite o nome ou ID do produto que deseja buscar: ");
    fflush(stdin);
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = 0; // Remove o newline

    while (fgets(buffer, sizeof(buffer), estoque) != NULL) {
        if (strstr(buffer, search) != NULL) {
            printf("Produto encontrado:\n");
            printf("%s", buffer);  // Exibe a linha com o nome ou ID encontrado

            for (int i = 0; i < 3; i++) {
                if (fgets(buffer, sizeof(buffer), estoque) != NULL) {
                    printf("%s", buffer);
                }
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Produto nao encontrado no estoque.\n");
    }

    fclose(estoque);
}

// Função para cadastrar produto no estoque
void CadEstoque() {
    FILE *estoque;
    estoque = fopen("estoque.txt", "a");

    if (estoque == NULL) {
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }

    produto p;

    // Gerador de número randômico para o id
    p.IdP = rand() % 1000 + 1;

    printf("Digite o nome do produto: ");
    scanf("%s", p.nP);

    printf("Digite a quantidade do produto: ");
    scanf("%d", &p.qtdP);

    printf("Digite o preco do produto: ");
    scanf("%s", p.precoP);

    // Define como ativo
    p.active = true;

    subVirgpPonto(p.precoP);
    float precoConver = atof(p.precoP);

    fprintf(estoque, "\n-----------------\n");
    fprintf(estoque, "ID: %d\n", p.IdP);
    fprintf(estoque, "Nome: %s\n", p.nP);
    fprintf(estoque, "Quantidade: %d\n", p.qtdP);
    fprintf(estoque, "Preco: R$%s\n", p.precoP);
    fprintf(estoque, "Ativo: true\n"); // Como o produto é cadastrado como ativo, sempre salva true
    fprintf(estoque, "-----------------\n");

    fclose(estoque);

    printf("Dados inseridos e salvos com sucesso!\n\n");
    printf("ID: %d\nNome: %s\nQuantidade: %d\nPreco: R$%s\n", p.IdP, p.nP, p.qtdP, p.precoP);
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
    scanf("%d", &ge);

    switch (ge) {
        case 1:
            CadEstoque();
            system("pause");
            system("cls");
            break;
        case 2:
            printf("Funcionalidade de editar produto ainda nao implementada.\n");
            break;
        case 3:
    InativarProduto();
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
void InativarProduto() {
    FILE *estoque;
    estoque = fopen("estoque.txt", "r+");

    if (estoque == NULL) {
        printf("Arquivo não pode ser aberto\n");
        exit(1);
    }

    int id;
    printf("Digite o ID do produto a ser inativado: ");
    scanf("%d", &id);

    char buffer[1000];
    int found = 0;

    char linhas[100][100];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), estoque) != NULL) {
        if (strstr(buffer, "ID:") != NULL && atoi(&buffer[4]) == id) {
            found = 1;
            snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
            fgets(buffer, sizeof(buffer), estoque); // Nome
            snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
            fgets(buffer, sizeof(buffer), estoque); // Quantidade
            snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
            fgets(buffer, sizeof(buffer), estoque); // Preço
            snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
            snprintf(linhas[i++], sizeof(linhas[i]), "Ativo: false\n"); // Inativa o produto
        } else {
            snprintf(linhas[i++], sizeof(linhas[i]), "%s", buffer);
        }
    }

    if (found) {
        freopen("estoque.txt", "w", estoque);
        for (int j = 0; j < i; j++) {
            fprintf(estoque, "%s", linhas[j]);
        }
        printf("Produto inativado com sucesso!\n");
    } else {
        printf("Produto não encontrado.\n");
    }

    fclose(estoque);
}

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
                        scanf("%d", &opcaoAdm);
                        switch (opcaoAdm) {
                        case 1:
                            system("pause");
                            system("cls");
                                gerEstq();
                            break;
                        case 2:
                                CstEstoque();
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
                        scanf("%d", &opcaoOp);
                        switch (opcaoOp) {
                        case 1:
                                CstEstoque();
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
                                CstEstoque();
                                system("pause");
                            break;
                        case 4:
                                cstEstoqueEsp();
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
    // Chamada da função de abertura
    insertItem();
    return 0;
}
