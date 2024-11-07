#include "operador.h"

void opcoeOp() {
    printf("\033[1;37;44m");//cor branca com fundo azul
    printf("\n---------MENU----------\n");
    printf("\033[0m");// Retorno cor padro
    printf("Escolha uma das opcoes abaixo: \n");
    printf("==============================\n");
    printf("1. Consultar Estoque.\n");
    printf("2. Vender produto.\n");
    printf("0. Sair.\n");
    printf("==============================\n");
}
void storageOpPanel() {
    printf("Não implementado!\n");
}

void venderProduto() {
    int idProduto, quantidadeVenda;
    printf("Digite o ID do produto que deseja vender: ");
    scanf("%d", &idProduto);

    Product* produto = searchItem(1, (char*)&idProduto);

    if (produto == NULL || !produto->active) {
        printf("Produto não encontrado ou está inativo.\n");
        return;
    }

    printf("Digite a quantidade que deseja vender: ");
    scanf("%d", &quantidadeVenda);

    if (produto->units < quantidadeVenda) {
        printf("Estoque insuficiente! Quantidade disponível: %d\n", produto->units);
        return;
    }

    produto->units -= quantidadeVenda;
    printf("Venda realizada com sucesso! Estoque atualizado: %d unidades restantes.\n", produto->units);

    saveFile(); // Atualiza o arquivo com o novo estoque
}
