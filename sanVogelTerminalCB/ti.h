#ifndef TI_H_INCLUDED
#define TI_H_INCLUDED

#include "commonLibs.h"

#define MAX_USUARIOS 100

typedef struct {
    char login[30];
    char senha[30];
    char role[10];
    char status[10];
} Usuario;

void opcoesMa();
void cadUsr();
void alterarUsr();
int gerUser();
int storageTiPanel();
void inativarUsuario();

#endif // TI_H_INCLUDED
