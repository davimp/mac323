#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#ifndef ARN_H
#define ARN_H

/***************** Arvore rubro negra **************************/
struct nodeRN
{
    std::string chave;
    int valor;
    int cor;
    struct nodeRN * esq;
    struct nodeRN * dir;
    struct nodeRN * pai;
};
typedef struct nodeRN NodeRN;

template<class Chave, class Item>
class arvoreRN
{
    private:
    NodeRN * ini;
    NodeRN * fim;

    public:
    arvoreRN(std::string texto); /* construtor */
    ~arvoreRN(); /* destrutor */

    int quantosNos(NodeRN * arvore); /* funcao auxiliar pra contar quantos nos a arvore tem */
    void rotacionaDir(NodeRN *q); /* right-rotate */
    void rotacionaEsq(NodeRN *q); /* left-rotate */
    NodeRN * findLeaf(NodeRN *q); 
    void duploPreto(NodeRN *q); /* conserta o duplo preto */
    void debug(NodeRN *i);
    void consertaInsere(NodeRN* q);
    void apaga(NodeRN *q);

    void insere(Chave chave, Item valor);
    Item devolve(Chave chave); /* devolve o valor*/
    void remove(Chave chave);
    int rank(Chave chave); /* é o "índice" da chave seguindo a ordenação */
    Chave seleciona(int k); /* Para Você selecionar uma chave com rank k */
};

template <class Chave, class Item>
arvoreRN<Chave, Item>::arvoreRN(std::string texto)
{
    std::fstream arquivo;
    std::string str;
    int aux = 0;
    ini = nullptr;
    arquivo.open(texto);

    if (arquivo.fail()) {
        std::cout << "ERRO: arquivo" << texto << "nao pode ser aberto.\n";
        exit(EXIT_FAILURE);
    }
    while(arquivo >> str){
        aux = devolve(str);
        insere(str, aux+1);
    }
    arquivo.close();
}

template<class Chave, class Item>
arvoreRN<Chave, Item>::~arvoreRN()
{
   apaga(ini);
}

template<class Chave, class Item>
void arvoreRN<Chave, Item>::apaga(NodeRN *q){
    if(q == nullptr) return;
    apaga(q->dir);
    apaga(q->esq);
    delete q;
}

template<class Chave, class Item>
void arvoreRN<Chave, Item>::rotacionaDir(NodeRN *q)
{
    NodeRN *p = q->pai;
    NodeRN *avo;
    avo = p->pai;

    p->esq = q->dir;
    if(q->dir != nullptr) q->dir->pai = p;
    q->dir = p;
    p->pai = q;
    q->pai = avo;

    if(q->pai == nullptr) ini = q;
    else{
        q->pai = avo;
        if(avo->esq == p){
            avo->esq = q;
        }
        else{
            avo->dir = q;
        }
    }
}

template<class Chave, class Item>
void arvoreRN<Chave, Item>::rotacionaEsq(NodeRN *q)
{
    NodeRN *p = q->pai;
    NodeRN *avo;
    avo = p->pai;

    p->dir = q->esq;
    if(q->esq != nullptr) q->esq->pai = p;
    q->esq = p;
    p->pai = q;
    q->pai = avo;

    if(q->pai == nullptr) ini = q;
    else{
        q->pai = avo;
        if(avo->esq == p){
            avo->esq = q;
        }
        else{
            avo->dir = q;
        }
    }
}

template <class Chave, class Item> 
void arvoreRN<Chave, Item>::consertaInsere(NodeRN *q)
{
    NodeRN *avo, *tio, *pai;
    avo = nullptr;
    tio = nullptr;
    pai = q->pai;
    /* se for raiz*/
    if(q == ini){
        q->cor = 1;
        return;
    }

    /*define avo e tio*/
    avo = pai->pai;
    if(avo == nullptr){
        tio = nullptr;
    }
    else if(avo->esq == pai){
        tio = avo->dir;
    }
    else{
        tio = avo->esq;
    }

    /*caso 2, se o pai for vermelho*/
    if(pai->cor == 0){
        /* se o tio for vermelho*/
        if(tio != nullptr && tio->cor == 0){
            pai->cor = 1;
            tio->cor = 1;
            avo->cor = 0;
            consertaInsere(avo);
            return;
        }
        else{
            // left left
            if(avo->esq == pai && pai->esq == q){
                avo->cor = 0;
                pai->cor = 1;
                rotacionaDir(pai);
            }
            // left right
            if(avo->esq == pai && pai->dir == q){
                rotacionaEsq(q);
                q->cor = 1;
                avo->cor = 0;
                rotacionaDir(q);
            }
            // right right
            if(avo->dir == pai && pai->dir == q){
                avo->cor = 0;
                pai->cor = 1;
                rotacionaEsq(pai);
            }
            // right left
            if(avo->dir == pai && pai->esq == q){
                rotacionaDir(q);
                q->cor = 1;
                avo->cor = 0;
                rotacionaEsq(q);
            }
            return;
        }
    }
    else{ /* se o pai for preto, esta tudo certo*/
        return;
    }
}

template <class Chave, class Item> 
void arvoreRN<Chave, Item>::insere(Chave chave, Item valor)
{
   NodeRN *i, *q, *aux;
   if(ini == nullptr){ /* se a arvore esta vazia */
       q = new NodeRN;
       q->chave = chave;
       q->valor = valor;
       q->cor = 1;
       q->dir = nullptr;
       q->esq = nullptr;
       q->pai = nullptr;
       ini = q;
       return;
   }

   i = ini;
   aux = ini;
   while(i != nullptr){
       aux = i;
       if(i->chave < chave){
           i = i->dir;
       }
       else if(i->chave > chave){
           i = i->esq;

       }
       else{
           i->valor = valor;
           return;
       }
   }

   q = new NodeRN;
   q->chave = chave;
   q->valor = valor;
   q->cor = 0;
   q->dir = nullptr;
   q->esq = nullptr;
   q->pai = nullptr;
   if(chave > aux->chave){
        aux->dir = q;
    }
    else{
        aux->esq = q;
    }
   q->pai = aux;
   if(aux->cor == 1) return;

   consertaInsere(q);
}

template<class Chave, class Item>
void arvoreRN<Chave, Item>::debug(NodeRN* i)
{
    if(i != nullptr){
        std::cout << i->chave << "(" << i->cor << ")  ";
        debug(i->dir);
        debug(i->esq);
    }
    else std::cout << "parou\n";
    return;
}

template<class Chave, class Item>
Item arvoreRN<Chave, Item>::devolve(Chave chave)
{
    NodeRN * i;
    i = ini;
    while(i != nullptr){
        if(i->chave == chave){
            return i->valor;
        }
        else if(i->chave < chave){
            i = i->dir;
        }
        else{
            i = i->esq;
        }
    }
    return 0;
}

template<class Chave, class Item>
NodeRN* arvoreRN<Chave, Item>::findLeaf(NodeRN *q)
{
    // tem os dois filhos
    if (q->esq != nullptr && q->dir != nullptr){
      q = q->dir;
      while(q->esq != nullptr)
        q = q->esq;
      return q;
    }
  
    // quando for folha devolver null
    if (q->esq == nullptr && q->dir == nullptr) 
      return nullptr; 
  
    // so possui um filho 
    if (q->esq != nullptr) 
      return q->esq; 
    else
      return q->dir; 
}

template<class Chave, class Item>
void arvoreRN<Chave, Item>::duploPreto(NodeRN *q)
{
    NodeRN *irmao;
    NodeRN *parent = q->pai;

    if(q == ini) return;/* se for raiz */ 
  
    if(parent->esq == q){
        irmao = parent->dir;
    }
    else{
        irmao = parent->esq;
    }

    if(irmao == nullptr){ 
      // joga o duplo preto pro pai
      duploPreto(parent); 
    }
    else{ 
      if(irmao->cor == 0) { 
        // irmao vermelho 
        parent->cor = 0; 
        irmao->cor = 1; 
        if (parent->esq == irmao) { 
          // left case
          rotacionaDir(irmao); 
        } else { 
          // right case 
          rotacionaEsq(irmao);
        } 
        duploPreto(q); 
      } 
      else{ 
        // irmao preto
        if((irmao->esq != nullptr && irmao->esq->cor == 0)||(irmao->dir != nullptr && irmao->dir->cor == 0)) { 
          // pelo menos um dos filhos eh vermelho
          if(irmao->esq != nullptr && irmao->esq->cor == 0){ 
            if(parent->esq == irmao){ 
              // left left 
              irmao->esq->cor = irmao->cor; 
              irmao->cor = parent->cor; 
              rotacionaDir(irmao); 
            } 
            else{ 
              // right left 
              irmao->esq->cor = parent->cor; 
              rotacionaDir(irmao->esq); 
              rotacionaEsq(irmao); 
            } 
          } 
          else{ 
            if(parent->esq == irmao){ 
              // left right 
              irmao->dir->cor = parent->cor; 
              rotacionaEsq(irmao->dir); 
              rotacionaDir(irmao); 
            }
            else{ 
              // right right 
              irmao->dir->cor = irmao->cor; 
              irmao->cor = parent->cor; 
              rotacionaEsq(irmao);
            } 
          } 
          parent->cor = 1; 
        } 
        else{ 
          // o irmao tem dois filhos pretos
          irmao->cor = 0; 
          if(parent->cor == 1) 
            duploPreto(parent); 
          else
            parent->cor = 1; 
        } 
      } 
    }
}

template<class Chave, class Item>
void arvoreRN<Chave, Item>::remove(Chave chave)
{
    std::string c;
    int v;
    NodeRN *i, *f, *parent, *aux;
    i = ini;
    /* procura o nó que contem a chave */
    while(i != nullptr){
        if(i->chave < chave){
            i = i->dir;
        }
        else if(i-> chave > chave){
            i = i->esq;
        }
        else{
            break;
        }
    }

    /* se for null, não precisa remover */
    if(i == nullptr) return;
    /* se for a raiz, deleta*/
    if(i->pai == nullptr){
        ini = nullptr;
        delete i;
        return;
    }


    /* procura a folha para fazer a substituição e depois a remoção */
    f = findLeaf(i);
    parent = i->pai;

    if(f == nullptr){ 
      // caso em que o i já é uma folha
      if (i->pai == nullptr){ 
        // se  i for a raiz
        ini = nullptr;
        delete i; 
      }
      else{ 
        if(i->cor == 1){ 
          // i é preto 
          // i eh uma folha, duplo preto i 
          duploPreto(i);
        } 
        else{ 
          // f ou i eh vermelho
          if(i->pai->esq == i){
              aux = i->pai->dir;
          }
          else{
              aux = i->pai->esq;
          }
          /* aux é o irmao de i*/
          if (aux != nullptr) 
            // pinta o irmao de vermelho 
            aux->cor = 0; 
        } 
  
        // tira i da arvore
        if(i->pai->esq == i){ 
          i->pai->esq = nullptr; 
        } 
        else{ 
          i->pai->dir = nullptr; 
        } 
      } 
      delete i; 
      return; 
    }

    /* se não for uma folha */
    
    if(i->esq == nullptr || i->dir == nullptr){ 
      // i tem um filho 
      if(i == ini){ 
        // i é raiz
        i->chave = f->chave;
        i->valor = f->valor;
        i->esq = i->dir = nullptr; 
        delete f; 
      } 
      else{ 
        // deleta i
        if(parent->esq == i) { 
          parent->esq = f; 
        } 
        else{ 
          parent->dir = f; 
        } 
        delete i;
        f->pai = parent; 
        if(f->cor == 1){ 
          // se a folha era preta, conseta o duplo preto 
          duploPreto(f); 
        } 
        else{ 
          // se ela era vermelha pinta a folha de preto
          f->cor = 1; 
        } 
      } 
      return; 
    }

    // i tem dois filhos
    v = f->valor;
    f->valor = i->valor;
    i->valor = v;

    c = f->chave;
    f->chave = i->chave;
    i->chave = c;
    remove(f->chave);
}

template<class Chave, class Item>
int arvoreRN<Chave, Item>::rank(Chave chave)
{
    int r;
    NodeRN *i;
    r = 0;
    i = ini;
    while(i != nullptr && i->chave != chave){
        if(i->chave < chave){
            r += quantosNos(i->esq) + 1;
            i = i->dir;
        }
        else {
            i = i->esq;
        }
    }
    if(i == nullptr) return r;
    return r += quantosNos(i->esq);
}

template<class Chave, class Item>
Chave arvoreRN<Chave, Item>::seleciona(int k)
{
    NodeRN *i;
    int aux;
    i = ini;
    while(i != nullptr){
        aux = rank(i->chave);
        if(aux > k){
            i = i->esq;
        }
        else if(aux <  k){
            i = i->dir;
        }   
        else{
            break;
        }
    }
    if(i == nullptr) return "";
    return i->chave;
}

template<class Chave, class Item>
int arvoreRN<Chave, Item>::quantosNos(NodeRN * arvore)
{
    if(arvore == nullptr) return 0;
    return 1 + quantosNos(arvore->dir) + quantosNos(arvore->esq);
}


/*************************************************************************/


#endif