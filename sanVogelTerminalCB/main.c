#include "commonLibs.h"


void subVirgpPonto(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
}


int main() {
    editProductPanel();
    return 0;
}
