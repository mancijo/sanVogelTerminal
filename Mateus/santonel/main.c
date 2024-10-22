//inclusao das bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//abertura
void abertura() {
    printf("==============================\n");
    printf("     BEM-VINDO AO SISTEMA     \n");
    printf("==============================\n");
}

//ponteiro da funcao login
int login();

//funcao de opcoes do usuario
void opcaoUsr() {
    int opUsr;

    printf("----Menu----\n\n");
    printf("1. Tela de Login.\n");
    printf("2. Sair.\n\n");
    scanf("%d", &opUsr);

    switch (opUsr)
    {
    case 1:
        system("CLS");
        login();
        break;
    case 2:
        system("CLS");
        printf("Saindo...");
        break;
    default:
        printf("Opcao invalida !.\n");
        break;
    }

}

//funcao de opçoes do usuario Admin
void opcoesAdm () {
    printf("\nEscolha uma das opcoes abaixo:\n");
    printf("==============================\n");
    printf("1. Gerenciar Estoque.\n");
    printf("2. Consultar Estoque.\n");
    printf("3. Sair.\n");
    printf("==============================\n");

}

//funcao de opçoes do usuario Operador
void opcoeOp () {
    printf("\nEscolha uma das opcoes abaixo: \n");
    printf("==============================\n");
    printf("1. Consultar Estoque.\n");
    printf("2. Sair.\n");
    printf("==============================\n");
}

//funcao de opçoes do usuario Master
void opcoesMa (){
    printf("\nEscolha uma das opcoes abaixo: \n");
    printf("==============================\n");
    printf("1. Gerenciar estoque.\n");
    printf("2. Gerenciar usuario.\n");
    printf("3. Consultar Estoque.\n");
    printf("4. Buscar produto.\n");
    printf("5. sair.\n");
    printf("==============================\n");
}


//funcao para cadastrar usuario
void CadUsr () {
    FILE *usuarios;
        usuarios = fopen("usuarios.txt", "a");

        if (usuarios == NULL){
            printf("Arquivo nao pode ser aberto\n");
            exit(1);
        }

        char lUsr[30];
        char sUsr[30];
        char roleUsr[10];

        printf("Digite o nome do usuario: \n");
        scanf("%s", lUsr);

        printf("Digite a senha do usuario: \n");
        scanf("%s", sUsr);

        printf("Escolha um nivel de hierarquia (Operador, Admin, Master): \n");
        scanf("%s", roleUsr);

        fprintf(usuarios, "\n%s\n %s\n %s\n\n",lUsr, sUsr, roleUsr);

        fclose(usuarios);

        printf("Usuario cadastrado com sucesso !\n\n");

}

//funcao para gerenciar usuario
int gerUser (){

    int gerUsuario;

    printf("==============================\n");
    printf("1. Cadastrar usuario.\n");
    printf("2. Alterar usuario.\n");
    printf("3. Desabilitar usuario.\n");
    printf("==============================\n");
    scanf("%d", &gerUsuario);

    switch(gerUsuario)
    {
    case 1:
        CadUsr();
        break;
    case 2:

        break;
    case 3:

        break;
    default:
        printf("Opção inválida!\n");
    break;
    }

    return 0;
}

//funcao para consultar estoque
void CstEstoque () {
    FILE *estoque;
    estoque = fopen("estoque.txt", "r");

    if (estoque == NULL){
            printf("Arquivo nao pode ser aberto\n");
            exit(1);
    }

    char consutar[1000];

    while(fgets(consutar, sizeof(consutar), estoque) != NULL) {
        printf("%s", consutar);
    }

    fclose(estoque);
}

void cstEstoqueEsp () {
    char buffer[1000];
    char search[1000];
    int found = 0;

    FILE *estoque;
    estoque = fopen("estoque.txt", "r");

    if (estoque == NULL){
        printf("Arquivo nao pode ser aberto.\n");
        exit(1);
        }

    printf("Digite o nome do produto: ");
    scanf("%s", search);

    while (fgets(buffer, sizeof(buffer), estoque) != NULL) {

        if (strstr(buffer, search) != NULL) {
            printf("Produto encontrado: %s", buffer);
            found = 1;
            break;
        }

    }

if (!found) {
        printf("String não encontrada no arquivo.\n");
    }

    // Fechar o arquivo
    fclose(estoque);


}

//funcao para cadastrar produto no estoque
void CadEstoque () {
    FILE *estoque;
        estoque = fopen("estoque.txt", "w");
        fclose(estoque);
        estoque = fopen("estoque.txt", "a");

        if (estoque == NULL){
            printf("Arquivo nao pode ser aberto\n");
            exit(1);
        }

        char nP[100];
        int IdP, qtdP;
        float precoP;

        printf("Digite o ID do produto: \n");
        scanf("%d", &IdP);

        printf("Digite o nome do produto: \n");
        scanf("%s", nP);

        printf("Digite a quantidade do produto: \n");
        scanf("%d", &qtdP);

        printf("Digite o preco do produto: \n");
        scanf("%f", &precoP);

        fprintf(estoque, "\n-----------------\n");
        fprintf(estoque, " ID: %d        \n", IdP);
        fprintf(estoque, " Nome: %s      \n", nP);
        fprintf(estoque, " Quantidade: %d\n", qtdP);
        fprintf(estoque, " Preco: R$%.2f \n", precoP);
        fprintf(estoque, "-----------------\n");


        fclose(estoque);

        printf("Dados inseridos e salvos com sucesso !\n\n");

        printf(" ID: %d\n Nome: %s\n Quantidade: %d\n Preco: %.2lf\n", IdP, nP, qtdP, precoP);
}

//funcao para gerenciar estoque
int gerEstq (){

    int ge;

    printf("==============================\n");
    printf("1. Cadastrar produto. \n");
    printf("2. Excluir produto. \n");
    printf("3. Editar produto \n");
    printf("==============================\n");

    scanf("%d", &ge);

    switch (ge)
    {
    case 1:
        CadEstoque();
        break;
    default:
        printf("Opção inválida!\n");
    break;
    }

    return 0;
}

//funcao da tela de login
int login () {
    FILE *usuariosLog;
    char login_dig[30], senha_dig[30];
    char loginArquivo[30], senhaArquivo[30], roleArquivo[10];
    int loginEncontrado = 0;

    //estrutura de repeticao caso o usuario erre a senha
    do {
        usuariosLog = fopen("usuarios.txt", "r");


        if (usuariosLog == NULL) {
            printf("Erro ao abrir o arquivo de usuarios.\n");
            exit(1);
        }



        printf("\nDigite seu Login: ");
        scanf("%s", login_dig);

        printf("Digite sua senha: ");
        scanf("%s", senha_dig);


        while (fscanf(usuariosLog, "%s %s %s", loginArquivo, senhaArquivo, roleArquivo) != EOF)
        {
            if (strcmp(loginArquivo, login_dig) == 0 && strcmp(senha_dig, senhaArquivo) == 0) {
                loginEncontrado = 1;
                printf("\nlogin bem-sucedido! Bem-vindo %s.\n", loginArquivo);

                if (strcmp(roleArquivo, "Admin") == 0) {

                    int opcaoAdm;

                    do {

                    opcoesAdm();

                    scanf("%d", &opcaoAdm);

                    switch (opcaoAdm)
                    {
                    case 1:
                        gerEstq();

                        system("pause");
                        system("CLS");
                        break;
                    case 2:
                        CstEstoque();

                        system("pause");
                        system("CLS");
                        break;
                    case 3:
                        printf("Saindo...\n");
                        break;
                    default:
                        printf("opcao invalida !\n");
                        break;
                    }
                    } while (opcaoAdm != 3);

                } else if (strcmp(roleArquivo, "Operador") == 0){

                int opcaoOp;

                do{

                    opcoeOp();

                    scanf("%d", &opcaoOp);

                    switch (opcaoOp)
                    {
                        case 1:
                            CstEstoque();

                            system("pause");
                            system("CLS");
                            break;
                        case 2:
                            printf("Saindo...\n");
                            break;
                        default:
                            printf("Opcao invalida !\n");
                            break;
                    }
                }while (opcaoOp != 2);


            } else if (strcmp(roleArquivo, "Master") == 0) {

                int opcaoMa;

                do
                {
                    opcoesMa();

                    scanf("%d", &opcaoMa);

                    switch (opcaoMa) {
                        case 1:
                            gerEstq();

                            system("pause");
                            system("CLS");
                            break;
                        case 2:
                            gerUser();

                            system("pause");
                            system("CLS");
                            break;
                        case 3:
                            CstEstoque();

                            system("pause");
                            system("CLS");
                            break;
                        case 4:
                            cstEstoqueEsp();

                            system("pause");
                            system("CLS");
                            break;
                        case 5:
                            printf("Saindo...\n");
                            break;
                        default:
                            printf("Opcao invalida !\n");
                            break;
                    }
                }  while (opcaoMa != 4);

            }break;
        }
    }

    fclose(usuariosLog);

    if (!loginEncontrado){
        printf("Login e/ou senha incorretos.\n");
        system("pause");
        system("CLS");
    }
} while (!loginEncontrado);

return 0;

}

//inicio da Main principal
int main() {

//chamada da funcao da abertura
    abertura();

//chamada da funcao com as opcoes do usuario
    opcaoUsr();


    return 0;
}
