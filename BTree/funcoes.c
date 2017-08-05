#include "funcoes.h"

void inicializar(ab ** raiz){
    *raiz =NULL;
}

int posicao(ab ** raiz,int valor){   
    int i;
    for(i=0;i<(*raiz)->tam;i++){
        if((*raiz)->key[i].info==valor)
            return i;
    }
    return -1;
}

int posicaoNoPai(ab ** no,ab ** Pai){
    int i;
    if((*Pai)->ramoMenor==(*no))
        return -1;
    for(i=0;i<(*Pai)->tam;i++){
        if((*Pai)->key[i].ramo==(*no))
            return i;
    }
    printf("\nVAi dar erroooooo nao to achado o pai\n");
    return -2;
}

ab * novoNo(){
    ab * novo = (ab*)malloc(sizeof(ab));
    novo->tam=0;
    novo->ramoMenor=NULL;
    novo->pai=NULL;
    int i=0;
    for(i=0;i<=MAX;i++){
        novo->key[i].info=0;
        novo->key[i].ramo=NULL;
    }
    return novo;
}

void inserir(ab ** raiz, int info, ab ** pai){
    if(*raiz==NULL){
        ab * novo = novoNo();
        novo->key[0].info=info;
        novo->key[0].ramo=NULL;
        novo->tam=1;
        if(pai==NULL)
            novo->pai=NULL;
        else
            novo->pai=(*pai);
        *raiz = novo;
    }else{
        if(info < (*raiz)->key[0].info && (*raiz)->ramoMenor!=NULL){
            inserir(&(*raiz)->ramoMenor,info,&(*raiz));
            return;
        }else{
            int i=0;
            for(i=((*raiz)->tam-1);i>=0;i--){
                if((*raiz)->key[i].info<info && (*raiz)->key[i].ramo!=NULL){
                    inserir(&(*raiz)->key[i].ramo,info,&(*raiz));
                    return;
                }
            }
        }
        (*raiz)->key[(*raiz)->tam].info=info;
        (*raiz)->key[(*raiz)->tam].ramo=NULL;
        (*raiz)->tam++;
        ordenarBolha(&(*raiz));
        if((*raiz)->tam == MAX+1)
            quebrar(&(*raiz));
    }
}

void ordenarBolha(ab ** no) {    
    chaves temp;
    int x, j;
    for (x = 0; x < (*no)->tam; x++) {
        for (j = x + 1; j < (*no)->tam; j++) {
            if ((*no)->key[x].info > (*no)->key[j].info) {
                temp = (*no)->key[x];
                (*no)->key[x] = (*no)->key[j];
                (*no)->key[j] = temp;
            }
        }
    }
}

void imprimirTudo(ab **no) {   
    if (*no != NULL) {
        imprimirTudo(&(*no)->ramoMenor);
        int i;
        printf("\n--------------------------------------\n");
        for (i = 0; i < (*no)->tam; i++) {
            printf("%d\n", (*no)->key[i].info);
            imprimirTudo(&(*no)->key[i].ramo);
        }
        printf("\n--------------------------------------\n");
    }
}

void quebrar(ab ** no) {    
    int numSubNo = MAX/2;
    int i,j=0;
    if ((*no)->pai == NULL) {
        ab * NoEsquerdo, * NoDireito;
        NoDireito = novoNo();
        NoEsquerdo = novoNo();
        NoEsquerdo->tam = numSubNo;
        NoEsquerdo->ramoMenor = (*no)->ramoMenor; // aqui o NoEsquerdo no campo ramoMenor recebe o ponteiro que estar no aux no campoMenor
        NoEsquerdo->pai = *no;
        NoDireito->pai = *no;
        NoDireito->tam = numSubNo;
        NoDireito->ramoMenor = (*no)->key[numSubNo].ramo; //reapontando os ponteiro, aqui o NoDireito no campoMenor recebe o ponterio que estar no nó do meio no campo ramo
        j = numSubNo+1;
        for(i=0;i<numSubNo;i++){
            NoEsquerdo->key[i] = (*no)->key[i];
            NoDireito->key[i] = (*no)->key[j];
            j++;
        }
        (*no)->tam = 1;
        (*no)->pai = NULL;
        (*no)->ramoMenor = NoEsquerdo; // a raiz no campoMenor  recebe o NoEsquerdo
        (*no)->key[0] = (*no)->key[numSubNo];
        (*no)->key[0].ramo = NoDireito; // a raiz no campo na posição 0 no campo ramo recebe o NoDireito
        int x;
        for (x = 1; x <=MAX; x++) {
            (*no)->key[x].info = 0;
            (*no)->key[x].ramo = NULL;
        }
    } else {
        chaves temp;
        ab *NoDireito;
        NoDireito = novoNo();
        NoDireito->pai = (*no)->pai;
        NoDireito->ramoMenor = (*no)->key[numSubNo].ramo; //reapontando os ponteiro, aqui o NoDireito no campoMenor recebe o ponterio que estar no nó do meio no campo ramo
        NoDireito->tam = numSubNo;
        j = numSubNo+1;
        for(i=0;i<numSubNo;i++){
            NoDireito->key[i] = (*no)->key[j];
            (*no)->key[j].ramo = NULL;
            (*no)->key[j].info = 0;
            j++;
        }
        (*no)->key[numSubNo].ramo = NoDireito; // o nó a subir no campo ramo recebe NoDireito
        (*no)->tam = (*no)->tam-numSubNo; // Diminuo o tamanho de aux
        temp = (*no)->key[numSubNo];
        inseriKey(temp,&(*no)->pai);
    }
}

void inseriKey(chaves KEY, ab ** arvo) {
    (*arvo)->key[(*arvo)->tam] = KEY; // Insiro a chave passada
    (*arvo)->tam++;
    ordenarBolha(&(*arvo)); // Organizo em ordem crecente
    if ((*arvo)->tam == MAX+1)
        quebrar(&(*arvo)); // caso o tamanho depois de inserir seja igual a 5, chama-se a função quebrar
}

ab *buscarNo(ab ** no, int x) {
    if (*no == NULL) {
        return NULL;
    } else {
        int posi = posicao(&(*no),x);
        if (posi>=0) {
            return (*no);
        }
        /*--------------------Recursividade-----------------*/
        int i;
        if (x < (*no)->key[0].info && (*no)->ramoMenor != NULL) {
            return buscarNo(&(*no)->ramoMenor, x);
        } else {
            for(i=((*no)->tam-1);i>=0;i--){
                if((*no)->key[i].info<x && (*no)->key[i].ramo!=NULL)
                    return buscarNo(&(*no)->key[i].ramo, x);
            }
        }
        /*-----------------Recursividade--------------------*/
    }
    return NULL;
}

int isFolha(ab ** raiz){
    if(*raiz==NULL)
        return -1;
    if((*raiz)->ramoMenor!=NULL)
        return 0;
    int i;
    for(i=0;i<(*raiz)->tam;i++){
        if((*raiz)->key[i].ramo!=NULL)
            return 0;
    }
    return 1;
}

int isRaiz(ab ** raiz){
    if(*raiz==NULL)
        return -1;
    if(( *raiz)->pai==NULL)
        return 1;
    return 0;
}

void removeKey(ab**raiz,int key){
    if(*raiz!=NULL){
        int posi,j;
        if((*raiz)->tam-1==0){
            free(&(*raiz));
            *raiz = NULL;
            return;
        }
        posi = posicao(&(*raiz),key);
        for(j=posi;j<((*raiz)->tam-1);j++)
            (*raiz)->key[j]=(*raiz)->key[(j+1)];
        (*raiz)->key[(*raiz)->tam-1].info=0;
        (*raiz)->key[(*raiz)->tam-1].ramo=NULL;
        (*raiz)->tam--;
    }
}

ab* menorNO(ab ** raiz){
    if(*raiz==NULL)
        return NULL;
    if((*raiz)->ramoMenor!=NULL)
        return menorNO(&(*raiz)->ramoMenor);
    return (*raiz);
}

ab*maiorNO(ab ** raiz){
    if(*raiz==NULL)
        return NULL;
    if((*raiz)->key[(*raiz)->tam-1].ramo!=NULL)
        return menorNO(&(*raiz)->key[(*raiz)->tam-1].ramo);
    return (*raiz);
}

int qtdMinimo(){
    return MAX/2;
}
