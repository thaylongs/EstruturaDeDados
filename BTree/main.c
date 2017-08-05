#include <stdio.h>
#include "funcoes.h"

int main(void)
{

    ab* raiz;
    inicializar(&raiz);  
    inserir(&raiz,10,NULL);
    inserir(&raiz,20,NULL);
    inserir(&raiz,30,NULL);
    inserir(&raiz,40,NULL);
    inserir(&raiz,50,NULL);  
    imprimirTudo(&raiz);
    return 0;
}

