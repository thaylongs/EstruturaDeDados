#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 4
typedef struct{
    struct no * ramo;
    int info;
}chaves;

typedef struct no{
    struct no * pai;
    struct no * ramoMenor;
    int tam;
    chaves key[MAX+1];
}ab;

void imprimirTudo(ab **no);
void inicializar(ab ** raiz);
ab * novoNo();
void ordenarBolha(ab ** no);
void inserir(ab ** raiz, int info, ab ** pai);
void quebrar(ab ** no) ;
void inseriKey(chaves KEY, ab ** arvo) ;
ab *buscarNo(ab ** no, int x);
void removeKey(ab**raiz,int key);
int posicao(ab ** raiz,int valor);
ab *menorNO(ab ** raiz);
int qtdMinimo();
int posicaoNoPai(ab ** no,ab ** Pai);
ab *maiorNO(ab ** raiz);
ab * trocarChavesMaiorImediato(ab ** raiz,int info);
void descerPaiESobeIrmaoMaior(ab ** eu,ab **  irmao, int minhaPosisaoNoPai);
void Excluir(ab ** raiz,int valor);
void tratar_remocao(ab ** no);
void juntaIrmaoMaior(ab ** eu, int posiIrmao);
void descerPaiESobeIrmaoMenor(ab ** eu,ab **  irmao, int posiIrmao);
void subir(ab ** eu);
#endif // FUNCOES_H
