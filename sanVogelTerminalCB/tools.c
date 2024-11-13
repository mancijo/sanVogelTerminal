#include "tools.h"

void usuarioPadrao() {
    FILE *usuarios = fopen("usuarios.txt", "r");

    if (usuarios != NULL){
        fclose(usuarios);
        return;
    }
        usuarios = fopen("usuarios.txt", "w");
        if (usuarios != NULL) {
            fprintf(usuarios, "master 123 Master Ativo\n");

            fclose(usuarios);
        } else {
            perror("Erro ao abrir o arquivo de usuarios.\n");
            exit(1);
    }
}

void readInt(int *varInt) {
    while (1) {
        if (scanf("%d", varInt) != 1) {
            // Limpa o buffer de entrada se nao for um numero valido
            while (getchar() != '\n');  // Limpa o buffer
            printf("Entrada invalida! Por favor, digite um numero valido.\n");
        } else {
            return;
        }
    }
}

