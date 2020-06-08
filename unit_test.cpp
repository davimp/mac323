/*
 * MAC0323 Algoritmos e Estruturas de Dados II
 * 
 * Contador de frequencia de palavras em um texto
 *
 *     http://www.ime.usp.br/~pf/mac0122-2003/aulas/symb-table.html
 * 
 * AVISO: Este programa quebra se o conjunto de caracters nao 
 *        for de 7-bits ASCII, ou seja, textos iso-latin 8859-1
 *        com acentos, cedilha, ... fazem o programa quebrar.
 *        UTF-8 nem pensar.
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <time.h>
using namespace std;

#include "util.hpp"    /* emalloc(), ecalloc(), strCmp(), getLine(), stringCopy(), 
//                         ERRO(), AVISO(), getLine() */

/* tabela de símbolos */
#include "tabeladesimbolos.hpp"  /* devolve(), insere(), remove(), ... */

#define PROMPT      cout << ">>> ";
#define MIN_ST      "minST"
#define DELMIN_ST   "delminST"
#define GET_ST      "getST"
#define RANK_ST     "rankST"
#define DELETE_ST   "deleteST"
#define SELECT_ST   "selectST"

/*---------------------------------------------------------------*/
/*
 *  P R O T Ó T I P O S
 */
static void 
mostreUso (char *nomePrograma);

template <class ST>
void 
testeOperacoes(ST st);

/*---------------------------------------------------------------*/
/* 
 *  M A I N 
 */
int 
main(int argc, char *argv[])
{
    fstream arqTexto;

    if (argc < 3) mostreUso(argv[0]);

    /* abra arquivo com texto */
    arqTexto.open(argv[1]);

    if (arqTexto.fail()) {
        cout << "ERRO: arquivo" << argv[1] << "nao pode ser aberto.\n";
        exit(EXIT_FAILURE);
    }

    arqTexto.close();

    string nome_arquivo = argv[1];
    string tipo = argv[2];

    /* crie a ST*/
    cout << "criando ST...\n";

    /* usadas para medir tempo de processamento */
    clock_t start, end; 
    double elapsed = 0;

    if (tipo == "VD"){
        start = clock(); 
        vetorDes<String,Integer> *st = new vetorDes<String, Integer>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
    }
    else if (tipo == "VO"){
        start = clock(); 
        vetorOrd<String,Integer> *st = new vetorOrd<String,Integer>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
    }
    else if (tipo == "LD"){
        start = clock(); 
        listaDes<String,Integer> *st = new listaDes<String,Integer>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
    }
    else if (tipo == "LO"){
        start = clock(); 
        listaOrd<String,Integer> *st = new listaOrd<String,Integer>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
    }
    else if (tipo == "AB"){
        start = clock(); 
        arvoreBin<String,Integer> *st = new arvoreBin<String,Integer>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
    }
    else if (tipo == "TR"){
        start = clock(); 
        treap<String,Integer> *st = new treap<String,Integer>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
    }
    else if (tipo == "A23"){
        start = clock(); 
        arvore23<String,Integer> *st = new arvore23<String,Integer>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
    }
    else if (tipo == "RN"){
        start = clock(); 
        arvoreRN<String,Integer> *st = new arvoreRN<String,Integer>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
    }
    else if (tipo == "HS"){
        start = clock(); 
        hashTable<String,Integer> *st = new hashTable<String,Integer>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
    }
    else {
        cout << "A estrutura" << tipo << "não é válida";
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

/*-------------------------------------------------------*/
/* 
 *  TESTEOPEARCOES(ST) 
 *
 *  RECEBE uma tabela de símbolos ST e testa várias operações
 *  interativamente.
 *
 *  A função supõe que as chaves são do tipo String e os
 *  valores são do tipo Integer (ver util.h).
 */
template <class ST>
void 
testeOperacoes(ST st)
{
    String linha    = NULL;
    
    /* mostre uso */
    cout << "Possiveis operacoes do teste interativo:\n";
    cout << "minST, delminST, getST <chave>; rankST <chave>, deleteST <chave>, selectST <int>\n";
    cout << "CRTL-D para encerrar.\n";
    PROMPT;
    while ((linha = getLine(stdin))) {
        /* pegue operacao a ser testada */
        String operacao = getNextToken(linha);
        if (operacao == NULL) {
             ERROR(operacao esperada);
        }
        /*---------------------------------*/
        else if (!strcmp(operacao, MIN_ST)) {
            String key = st->seleciona(0);
            if (key == NULL) {
                cout << "ST vazia\n";
            } else {
                cout << key;
            }
        }
        /*---------------------------------*/
        else if (!strcmp(operacao,DELMIN_ST)) {
            String key = st->seleciona(0);
            if (key == NULL) {
                cout << "ST já está vazia\n";
            } else {
                st->remove(key);
                cout << "\"" << key << "\" foi removida\n";
            }
        }
        /*---------------------------------*/
        else {
            /* operaÃ§Ã£o necessita de argumento key */
            String key = getNextToken(NULL);
            if (key == NULL) {
                ERROR(operacao necessita uma palavra);
            } else {
                /*---------------------------------*/
                if (!strcmp(operacao,GET_ST)) {
                    Integer frequencia = NULL;
                    frequencia = st->devolve(key); /* consulte a ST */
                    /* mostre o resultado da consulta */
                    if (frequencia == NULL) {
                        cout << key << ": 0\n";
                    } else {
                        cout << key << ": " << *frequencia << "\n";
                    }
                }
                /*---------------------------------*/
                else if (!strcmp(operacao,RANK_ST)) {
                    int r = st->rank(key);
                    cout << r << "\n";
                }
                /*---------------------------------*/
                else if (!strcmp(operacao,DELETE_ST)) {
                    st->remove(key);
                    cout << "\"" << key << "\" foi removida\n";
                }
                else if (!strcmp(operacao,SELECT_ST)) {
                    int pos = atoi(key);
                    String chave = st->seleciona(pos);
                    cout << "Posição " << key << " = " << chave << "\n";
                }
                else {
                    ERROR(operacao nao reconhecida);
                }
            }
        }
        if (operacao != NULL) free(operacao);
        free(linha);
        PROMPT;
    }
    cout << "\n";
}


/*-----------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S
 *                 A U X I L I A R E S 
 */
static void 
mostreUso (char *nomePrograma)
{
    cout << "Uso \n"
	     << "prompt> " << nomePrograma << " nome-arquivo tipo-tabela\n"
	     << "    nome-arquivo = nome do arquivo com o texto\n"
         << "    tipo-tabela  = sigla de estrutura que deve ser usada\n";
    exit(EXIT_FAILURE);
}   