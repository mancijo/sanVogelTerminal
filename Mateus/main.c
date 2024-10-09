//inclusao das bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*//criacao da estrutura
typedef struct {
    char login[30];
    char senha[30];
} pessoa;*/

//abertura
void abertura() {
    printf("===============================\n");
    printf("BEM-VINDO AO SISTEMA\n");
    printf("===============================\n");
}

//funcao de opções do usuario Admin
void opcoesAdm () {
    printf("Escolha uma das opcoes abaixo.\n");
    printf("======================================\n");
    printf("1. Consultar Estoque.\n");
    printf("2. Inserir Produtos.\n");
    printf("3. Alterar preco, quantidade e nome.\n");
    printf("======================================\n");

}

//funcao de opções do usuario Operador
void opcoeOp () {
    printf("Escolha uma das opcoes abaixo. \n");
    printf("======================================\n");
    printf("1. ler dados do produto.\n");
    printf("2. ler a quantidade do produto.\n");
    printf("======================================\n");
}

//funcao de opções do usuario Master
void opcoesMa (){
    printf("Escolha uma das opcoes abaixo. \n");
    printf("=================================================\n");
    printf("1. Inserir produtos.\n");
    printf("2. Alterar nome, preco e quantidade dos produtos.\n");
    printf("3. Alterar senha e nome dos usuarios\n");
    printf("4. Consultar Estoque.\n");
    printf("=================================================\n");

}

//definicao de login e senha do Admin
void logAdmin (char login[30], char senha[30]) {
    strcpy(login,"admin");
    strcpy(senha,"123");
}

//definição de login e senha do Operador
void logOp (char login1[30], char senha1[30]) {
    strcpy(login1,"operador");
    strcpy(senha1,"1234");
}

//definição de login e senha do Master
void logMaster (char login2[30], char senha2[30]) {
    strcpy(login2,"master");
    strcpy(senha2,"12345");
}

//inicio da Main principal
int main() {

    int opcaoAdm, opcaoOp, opcaoMa;

//chamada da funcao da abertura
    abertura();

//definicao de login e senha
    char login[30], senha[30];
    char login1[30], senha1[30];
    char login2[30], senha2[30];

//chamada da funcao de cada usuario
    logAdmin(login, senha);
    logOp(login1, senha1);
    logMaster(login2, senha2);

//variavel para isercao de login e senha
    char login_dig[30];
    char senha_dig[30];

//coleta de login e senha
    printf("\nDigite seu Login: ");
    scanf("%s", login_dig);

    printf("\nDigite sua senha: ");
    scanf("%s", senha_dig);


//comparacao de login e senha
    if (strcmp(login, login_dig) == 0 && strcmp(senha, senha_dig) == 0){
        printf("*******\n");
        printf("* Usuario logado. *\n");
        printf("*******\n\n");
        opcoesAdm();

        scanf("%d", &opcaoAdm);

        switch (opcaoAdm)
        {
        case 1:
            printf("Consultar estoque\n");
            break;
        case 2:
            printf("Inserir produtos\n");
            break;
        case 3:
            printf("Alterar preco, quantidade e nome\n");
            break;
        default:
            break;
        }


    }
    else if (strcmp(login1, login_dig) == 0 && strcmp(senha1, senha_dig) == 0){
            printf("*******\n");
            printf("* Usuario logado. *\n");
            printf("*******\n\n");
            opcoeOp();

            scanf("%d", &opcaoOp);

            switch (opcaoOp)
            {
            case 1:
                printf("1. ler dados do produto.\n");
                break;
            case 2:
                printf("ler a quantidade do produto.\n");
            default:
                break;
            }
    }
    else if (strcmp(login2, login_dig) == 0 && strcmp(senha2, senha_dig) == 0){
            printf("*******\n");
            printf("* Usuario logado. *\n");
            printf("*******\n\n");
            opcoesMa();

            scanf("%d", &opcaoMa);

            switch (opcaoMa)
            {
            case 1:
                printf("1. Inserir produtos.\n");
                break;
            case 2:
                printf("2. Alterar nome, preco e quantidade dos produtos.\n");
                break;
            case 3:
                printf("3. Alterar senha e nome dos usuarios\n");
                break;
            case 4:
                printf("4. Consultar Estoque.\n");
                break;
            default:
                break;
            }
    }

    else{
      printf("==============================\n");
      printf("Login e/ou senha incorretos !.\n");
      printf("==============================\n");
      exit(1);
    }

    return 0;

   }
