#include "operador.h"

void opcoeOp() {
    printf("\033[1;37;44m");//cor branca com fundo azul
    printf("\n---------MENU----------\n");
    printf("\033[0m");// Retorno cor padro
    printf("Escolha uma das opcoes abaixo: \n");
    printf("==============================\n");
    printf("1. Consultar Estoque.\n");
    printf("2. Vender produto.\n");
    printf("\033[1;37;41m\n"); // Cor branca com fundo vermelho
    printf("0. Sair.                      \n");
    printf("\033[0m"); // Retorno cor padrao
    printf("==============================\n");
}
void storageOpPanel() {
    printf("N�o implementado!\n");
}

void LogVenda(char *nomeProdutoLog, int quantidadeP, float precoUnitario);

void venderProduto() {
    int produtoID;
    int quantidadeDesejada;
    Product *produtoSelecionado;


    // Buscar o produto pelo ID
    printf("Digite o ID do produto que deseja vender: ");
    readInt(&produtoID);

    // Busca o produto no estoque
    char idStr[10];
    sprintf(idStr, "%d", produtoID);
    produtoSelecionado = searchItem(1, idStr);

    if (produtoSelecionado == NULL) {
        printf("Produto n�o encontrado.\n");
        return;
    }

    if (!produtoSelecionado->active) {
        printf("O produto est� inativo e n�o pode ser vendido.\n");
        return;
    }

    printf("Produto: %s\n", produtoSelecionado->name);
    printf("Quantidade disponivel: %d\n", produtoSelecionado->units);
    printf("Preco unitario: R$%.2f\n", produtoSelecionado->price);

    // Solicitar a quantidade desejada para venda
    printf("Digite a quantidade desejada: ");
    readInt(&quantidadeDesejada);

    if (quantidadeDesejada > produtoSelecionado->units) {
        printf("Quantidade indispon�vel em estoque.\n");
        return;
    }

    // Calcular o valor total e atualizar o estoque
    float valorTotal = quantidadeDesejada * produtoSelecionado->price;
    produtoSelecionado->units -= quantidadeDesejada;
    printf("Venda realizada com sucesso! \nValor total: R$%.2f\n", valorTotal);

    // Atualizar o arquivo de estoque
    saveFile();






    // Registrar o log de venda
    LogVenda(produtoSelecionado->name, quantidadeDesejada, produtoSelecionado->price);
}

