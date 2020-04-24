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
        vetorDes<string,int> *st = new vetorDes<string,int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "VO"){
        start = clock(); 
        vetorOrd<string,int> *st = new vetorOrd<string,int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "LD"){
        start = clock(); 
        listaDes<string,int> *st = new listaDes<string,int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "LO"){
        start = clock(); 
        listaOrd<string,int> *st = new listaOrd<string,int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "AB"){
        start = clock(); 
        arvoreBin<string,int> *st = new arvoreBin<string,int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "TR"){
        start = clock(); 
        treap<string,int> *st = new treap<string,int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "A23"){
        start = clock(); 
        arvore23<string,int> *st = new arvore23<string,int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "RN"){
        start = clock(); 
        arvoreRN<string,int> *st = new arvoreRN<string,int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
    }
    else if (tipo == "HS"){
        start = clock(); 
        hashTable<string,int> *st = new hashTable<string,int>(nome_arquivo);
        end = clock();

        /* calcule o tempo */
        elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
        cout << "arquivo lido e ST construida em " << elapsed << " segundos\n";

        testeOperacoes(st);
        delete st;
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
 *  A função supõe que as chaves são do tipo string e os
 *  valores são do tipo int (ver util.h).
 */
template <class ST>
void 
testeOperacoes(ST st)
{
    string linha;
    
    /* mostre uso */
    cout << "Possiveis operacoes do teste interativo:\n";
    cout << "minST, delminST, getST <chave>; rankST <chave>, deleteST <chave>, selectST <int>\n";
    cout << "CRTL-D para encerrar.\n";
    PROMPT;
    while (cin >> linha) {
        /* pegue operacao a ser testada */
        string operacao;
        cin >> operacao;
        if (operacao == "") {
             ERROR(operacao esperada);
        }
        /*---------------------------------*/
        else if (operacao == MIN_ST) {
            string key = st->seleciona(0);
            if (key == "") {
                cout << "ST vazia\n";
            } else {
                cout << key;
            }
        }
        /*---------------------------------*/
        else if (operacao == DELMIN_ST) {
            string key = st->seleciona(0);
            if (key == "") {
                cout << "ST já está vazia\n";
            } else {
                st->remove(key);
                cout << "\"" << key << "\" foi removida\n";
            }
        }
        /*---------------------------------*/
        else {
            /* operaÃ§Ã£o necessita de argumento key */
            /*string key = getNextToken(NULL);*/
            string key;
            cin >> key;
            if (key == "") {
                ERROR(operacao necessita uma palavra);
            } else {
                /*---------------------------------*/
                if (operacao == GET_ST) {
                    int frequencia = 0;
                    frequencia = st->devolve(key); /* consulte a ST */
                    /* mostre o resultado da consulta */
                    if (frequencia == 0) {
                        cout << key << ": 0\n";
                    } else {
                        cout << key << ": " << frequencia << "\n";
                    }
                }
                /*---------------------------------*/
                else if (operacao == RANK_ST) {
                    int r = st->rank(key);
                    cout << r << "\n";
                }
                /*---------------------------------*/
                else if (operacao == DELETE_ST) {
                    st->remove(key);
                    cout << "\"" << key << "\" foi removida\n";
                }
                else if (operacao == SELECT_ST) {
                    int pos = stoi(key);
                    string chave = st->seleciona(pos);
                    cout << "Posição " << key << " = " << chave << "\n";
                }
                else {
                    ERROR(operacao nao reconhecida);
                }
            }
        }
        /*if (operacao != NULL) free(operacao);
        free(linha);*/
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