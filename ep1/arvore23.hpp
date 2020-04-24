#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#ifndef A23_H
#define A23_H

/***************** Arvore 2-3 **************************/
struct node23
{
    std::string chave1;
    std::string chave2;
    int valor1;
    int valor2;
    bool dois;
    struct node23 * pai;
    struct node23 * esq;
    struct node23 * dir;
    struct node23 * meio;
};
typedef struct node23 Node23;

template<class Chave, class Item>
class arvore23
{
    private:
    Node23 * ini;

    public:
    arvore23(std::string texto); /* construtor */
    ~arvore23(); /* destrutor */

    int quantasChaves(Node23 * arvore); /* funcao auxiliar pra contar quantos nos a arvore tem */
    void apaga(Node23 * q);
    void debug(Node23 * q);
    void removeChave(Node23 * q, Chave chave);

    void insere(Chave chave, Item valor);
    Item devolve(Chave chave); /* devolve o valor*/
    void remove(Chave chave);
    int rank(Chave chave); /* é o "índice" da chave seguindo a ordenação */
    Chave seleciona(int k); /* Para Você selecionar uma chave com rank k */
};

template <class Chave, class Item>
arvore23<Chave, Item>::arvore23(std::string texto)
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
arvore23<Chave, Item>::~arvore23()
{
   apaga(ini);
}

template<class Chave, class Item>
void arvore23<Chave, Item>::apaga(Node23 *q){
    if(q == nullptr) return;
    if(q->dois == false){
      apaga(q->dir);
    }
    apaga(q->meio);
    apaga(q->esq);
    delete q;
}

template<class Chave, class Item>
void arvore23<Chave, Item>::debug(Node23 *q){
  if(q == nullptr){
    std::cout << "parou\n"; return;
  }

  if(q->dois){
    std::cout << "doisno(" << q->chave1 <<")\n";
    debug(q->meio);
    debug(q->esq);
  }
  else{
    std::cout << "tresno(" << q->chave1 << "; " << q->chave2 << ")\n";
    debug(q->dir);
    debug(q->meio);
    debug(q->esq);
  }
}

template <class Chave, class Item> 
void arvore23<Chave, Item>::insere(Chave chave, Item valor)
{
    Node23 *i, *q, *aux;
    Node23 *a, *b, *c, *d;
    Node23 *x, *y;
    i = ini;
    if(ini == nullptr){
      q = new Node23;
      q->chave1 = chave;
      q->chave2 = "";
      q->valor1 = valor;
      q->valor2 = 0;
      q->dois = true;
      q->pai = nullptr;
      q->esq = nullptr;
      q->meio = nullptr;
      q->dir = nullptr;
      ini = q;
      return;
    }

    while(i != nullptr){
      aux = i;
      if(i->dois){
        if(chave < i->chave1){
          i = i->esq;
        }
        else if(i->chave1 < chave){
          i = i->meio;
        }
        else{
          i->valor1 = valor;
          return;
        }
      }
      else{
        if(chave <= i->chave1){
          if(chave == i->chave1){
            i->valor1 = valor;
            return;
          }
          i = i->esq;
        }
        else if(chave <= i->chave2){
          if(chave == i->chave2){
            i->valor2 = valor;
            return;
          }
          i = i->meio;
        }
        else{
          i = i->dir;
        }
      }
    }
    /* achou o lugar certo para inserir */
    /* cria o nó */
    q = new Node23;
    q->chave1 = chave;
    q->chave2 = "";
    q->valor1 = valor;
    q->valor2 = 0;
    q->dois = true;
    q->pai = aux;
    q->esq = nullptr;
    q->meio = nullptr;
    q->dir = nullptr;

    /* upward phase */
    while(aux != nullptr && aux->dois == false){
      /*junta com tres nó*/
      i = aux;
      aux = i->pai;
      if(q->chave1 < i->chave1){
        /* primeiro caso */
        a = q->esq;
        b = q->meio;
        c = i->meio;
        d = i->dir;
        x = new Node23;
        y = new Node23;
        
        /* x */
        x->chave1 = q->chave1;
        x->valor1 = q->valor1;
        x->esq = a;
        x->meio = b;
        x->dois = true;
        if(a != nullptr) a->pai = x;
        if(b != nullptr) b->pai = x;

        /* y */
        y->chave1 = i->chave2;
        y->valor1 = i->valor2;
        y->esq = c;
        y->meio = d;
        y->dois = true;
        if(c != nullptr) c->pai = y;
        if(d != nullptr) d->pai = y;

        /* novo q (i)*/
        i->chave1 = i->chave1;
        i->valor1 = i->valor1;
        i->esq = x;
        i->meio = y;
        i->dois = true;

        /* ajusta pais */
        x->pai = i;
        y->pai = i;
      }
      else if(q->chave1 < i->chave2){
        /* segundo caso */
        a = i->esq;
        b = q->esq;
        c = q->meio;
        d = i->dir;
        x = new Node23;
        y = new Node23;

        /* x */
        x->chave1 = i->chave1;
        x->valor1 = i->valor1;
        x->esq = a;
        x->meio = b;
        x->dois = true;
        if(a != nullptr) a->pai = x;
        if(b != nullptr) b->pai = x;

        /* y */
        y->chave1 = i->chave2;
        y->valor1 = i->valor2;
        y->esq = c;
        y->meio = d;
        y->dois = true;
        if(c != nullptr) c->pai = y;
        if(d != nullptr) d->pai = y;

        /* novo q (a partir do i)*/
        i->chave1 = q->chave1;
        i->valor1 = q->valor1;
        i->esq = x;
        i->meio = y;
        i->dois = true;
        
        /* ajusta os pais*/
        y->pai = i;
        x->pai = i;
      }
      else{
        /* terceiro caso */
        a = i->esq;
        b = i->meio;
        c = q->esq;
        d = q->meio;
        x = new Node23;
        y = new Node23;
        
        /* x */
        x->chave1 = i->chave1;
        x->valor1 = i->valor1;
        x->esq = a;
        x->meio = b;
        x->dois = true;
        if(a != nullptr) a->pai = x;
        if(b != nullptr) b->pai = x;

        /* y */
        y->chave1 = q->chave1;
        y->valor1 = q->valor1;
        y->esq = c;
        y->meio = d;
        y->dois = true;
        if(c != nullptr) c->pai = y;
        if(d != nullptr) d->pai = y;

        /* novo q (i)*/
        i->chave1 = i->chave2;
        i->valor1 = i->valor2;
        i->esq = x;
        i->meio = y;
        i->dois = true;

        /* ajusta pais */
        x->pai = i;
        y->pai = i;
       }
       /* atualiza o q */
       delete q;
       q = nullptr;
       q = i;
    }

    /*ve se chegou na raiz*/
    if(aux == nullptr){
      /* aumenta a altura da arvore*/
      ini = q;
    }
    else{
      /* junta com dois nó (transforma em três nó) */
      aux->dois = false;
      if(q->chave1 < aux->chave1){
        aux->chave2 = aux->chave1;
        aux->valor2 = aux->valor1;
        aux->dir = aux->meio;
        /*junta*/
        aux->chave1 = q->chave1;
        aux->valor1 = q->valor1;
        aux->esq = q->esq;
        aux->meio = q->meio;
      }
      else{
        aux->chave2 = q->chave1;
        aux->valor2 = q->valor1;
        aux->meio = q->esq;
        aux->dir = q->meio;
      }
      if(aux->esq != nullptr) aux->esq->pai = aux;
      if(aux->meio != nullptr) aux->meio->pai = aux;
      if(aux->dir != nullptr) aux->dir->pai = aux;

      delete q;
    }
}

template<class Chave, class Item>
Item arvore23<Chave, Item>::devolve(Chave chave)
{
    Node23 * i;
    i = ini;
    while(i != nullptr){
        /* se for dois no */
        if(i->dois){
          if(chave <= i->chave1){
            if(chave == i->chave1) return i->valor1;
            i = i->esq;
          }
          else{
            i = i->meio;
          }
        }
        else{ 
          /* se for tres no */
          if(chave <= i->chave1){
            if(chave == i->chave1) return i->valor1;
            i = i->esq;
          }
          else if(chave <= i->chave2){
            if(chave == i->chave2) return i->valor2;
            i = i->meio;
          }
          else{
            i = i->dir;
          }
        }
    }
    return 0;
}

template<class Chave, class Item>
void arvore23<Chave, Item>::removeChave(Node23 *q, Chave chave)
{
  Node23 *parent, *sibling;
  Node23 *a, *b, *c, *d, *e;
  std::string x, y;
  int xi, yi;
  parent = q->pai;
  
  if(q->dois == false){
    /* caso 1: se for 3-no */
    if(chave == q->chave1){
      q->chave1 = q->chave2;
      q->valor1 = q->valor2;
      q->dois = true;
    }
    else{
      q->dois = true;
    }
    return;
  }
  else{
    /* se for 2-no */
    /* caso 2: se for raiz */
    if(parent == nullptr){
      /*raiz*/
      ini = q->esq;
      delete q;
      return;
    }
    else if(parent->dois){
      /* se o pai for 2-no*/
      /* acha o irmao*/
      if(parent->esq == q){
        sibling = parent->meio;
      }
      else{
        sibling = parent->esq;
      }
      /* caso 3: pai eh 2-no e irmao eh 2-no */
      if(sibling->dois){
        if(parent->esq == q){
          q->chave1 = parent->chave1;
          q->valor1 = parent->valor1;
          q->chave2 = sibling->chave1;
          q->valor2 = sibling->valor1;
          q->esq = q->esq;
          q->meio = sibling->esq;
          q->dir = sibling->meio;
          if(q->esq != nullptr) q->esq->pai = q;
          if(q->meio != nullptr) q->meio->pai = q;
          if(q->dir != nullptr) q->dir->pai = q;
          q->dois = false;
          q->pai = parent;

          parent->esq = q;
          delete sibling;
        }
        else{
          sibling->chave2 = q->chave1;
          sibling->valor2 = q->valor1;
          sibling->dir = q->esq;
          sibling->dois = false;
          sibling->pai = parent;
          if(sibling->esq != nullptr) sibling->esq->pai = sibling;
          if(sibling->meio != nullptr) sibling->meio->pai = sibling;
          if(sibling->dir != nullptr) sibling->dir->pai = sibling;

          parent->esq = sibling;
          delete q;
        }
        removeChave(parent, parent->chave1);
      }
      else{
        /* caso 4: pai eh 2 no e irmao eh 3-no */
        if(parent->esq == q){
          q->chave1 = sibling->chave1;
          q->valor1 = sibling->valor1;
          q->meio = sibling->esq;
          if(q->esq != nullptr) q->esq->pai = q;
          if(q->meio != nullptr) q->meio->pai = q;
          q->dois = true;

          sibling->chave1 = sibling->chave2;
          sibling->valor1 = sibling->valor2;
          sibling->esq = sibling->meio;
          sibling->meio = sibling->dir;
          if(sibling->esq != nullptr) sibling->esq->pai = sibling;
          if(sibling->meio != nullptr) sibling->meio->pai = sibling;
          sibling->dois = true;
        }
        else{
          sibling->dois = true;

          q->chave1 = sibling->chave2;
          q->valor1 = sibling->valor2;
          q->meio = q->esq;
          q->esq = sibling->dir;
          if(q->esq != nullptr) q->esq->pai = q;
          if(q->meio != nullptr) q->meio->pai = q;
          q->dois = true;
        }
      }
    }
    else{
      /* se o pai for 3-no */
      /* acha quem é o irmão*/
      if(parent->esq == q || parent->dir == q){
        sibling = parent->meio;
      }
      else{
        sibling = parent->esq;
      }

      if(sibling->dois){
        /* caso 5*/
        if(parent->esq == q){
          a = q->esq;
          b = sibling->esq;
          c = sibling->meio;
          d = parent->dir;

          q->chave1 = parent->chave1;
          q->valor1 = parent->valor1;
          q->chave2 = sibling->chave1;
          q->valor2 = sibling->valor1;
          q->esq = a;
          q->meio = b;
          q->dir = c;
          if(a != nullptr) a->pai = q;
          if(b != nullptr) b->pai = q;
          if(c != nullptr) c->pai = q;
          q->dois = false;
          q->pai = parent;

          parent->chave1 = parent->chave2;
          parent->valor1 = parent->valor2;
          parent->dois = true;
          parent->esq = q;
          parent->meio = d;
          if(q != nullptr) q->pai = parent;
          if(d != nullptr) d->pai = parent;

          delete sibling;
        }
        else if(parent->meio == q){
          a = sibling->esq;
          b = sibling->meio;
          c = q->esq;
          d = parent->dir;

          /*sibling->chave1 = sibling->chave1;
          sibling->valor1 = sibling->valor1;*/
          sibling->chave2 = parent->chave1;
          sibling->valor2 = parent->valor1;
          sibling->esq = a;
          sibling->meio = b;
          sibling->dir = c;
          if(a != nullptr) a->pai = sibling;
          if(b != nullptr) b->pai = sibling;
          if(c != nullptr) c->pai = sibling;
          sibling->dois = false;
          sibling->pai = parent;

          parent->chave1 = parent->chave2;
          parent->valor1 = parent->valor2;
          parent->dois = true;
          parent->esq = sibling;
          parent->meio = d;
          if(sibling != nullptr) sibling->pai = parent;
          if(d != nullptr) d->pai = parent;

          delete q;
        }
        else{
          a = parent->esq;
          b = sibling->esq;
          c = sibling->meio;
          d = q->esq;

          /*sibling->chave1 = sibling->chave1;
          sibling->valor1 = sibling->valor1;*/
          sibling->chave2 = parent->chave2;
          sibling->valor2 = parent->valor2;
          sibling->esq = a;
          sibling->meio = b;
          sibling->dir = c;
          if(a != nullptr) a->pai = sibling;
          if(b != nullptr) b->pai = sibling;
          if(c != nullptr) c->pai = sibling;
          sibling->dois = false;
          sibling->pai = parent;

          /*parent->chave1 = parent->chave1;
          parent->valor1 = parent->valor1;*/
          parent->dois = true;
          parent->esq = a;
          parent->meio = sibling;
          if(a != nullptr) a->pai = parent;
          if(sibling != nullptr) sibling->pai = parent;
        }
        return;
      }
      else{
        /* caso 6 */
        if(parent->esq == q){
          a = q->esq;
          b = sibling->esq;
          c = sibling->meio;
          d = sibling->dir;
          e = parent->dir;
          x = sibling->chave1;
          xi = sibling->valor1;
          y = parent->chave2;
          yi = parent->valor2;

          q->chave1 = parent->chave1;
          q->valor1 = parent->valor1;
          q->esq = a;
          q->meio = b;
          if(a != nullptr) a->pai = q;
          if(b != nullptr) b->pai = q;
          q->dois = true;

          sibling->chave1 = sibling->chave2;
          sibling->valor1 = sibling->valor2;
          sibling->esq = c;
          sibling->meio = d;
          if(c != nullptr) c->pai = sibling;
          if(d != nullptr) d->pai = sibling;


          /* parent */
          parent->chave1 = x;
          parent->valor1 = xi;
          parent->chave2 = y;
          parent->valor2 = yi;
          parent->esq = q;
          parent->meio = sibling;
          parent->dir = e;
          if(q != nullptr) q->pai = parent;
          if(sibling != nullptr) sibling->pai = parent;
          if(e != nullptr) e->pai = parent;
          parent->dois = false;
        }
        else if(parent->meio == q){
          a = sibling->esq;
          b = sibling->meio;
          c = sibling->dir;
          d = q->esq;
          e = parent->dir;
          x = sibling->chave2;
          xi = sibling->valor2;
          y = parent->chave2;
          yi = parent->valor2;

          q->chave1 = parent->chave1;
          q->valor1 = parent->valor1;
          q->esq = c;
          q->meio = d;
          if(c != nullptr) c->pai = q;
          if(d != nullptr) d->pai = q;
          q->dois = true;

          sibling->dois = true;

          /* parent */
          parent->chave1 = x;
          parent->valor1 = xi;
          parent->chave2 = y;
          parent->valor2 = yi;
          parent->esq = sibling;
          parent->meio = q;
          parent->dir = e;
          if(q != nullptr) q->pai = parent;
          if(sibling != nullptr) sibling->pai = parent;
          if(e != nullptr) e->pai = parent;
          parent->dois = false;
        }
        else{
          a = parent->esq;
          b = sibling->esq;
          c = sibling->meio;
          d = sibling->dir;
          e = q->esq;
          x = parent->chave1;
          xi = parent->valor1;
          y = sibling->chave2;
          yi = sibling->valor2;

          q->chave1 = parent->chave2;
          q->valor1 = parent->valor2;
          q->esq = d;
          q->meio = e;
          if(d != nullptr) d->pai = q;
          if(e != nullptr) e->pai = q;
          q->dois = true;

          sibling->dois = true;

          /* parent */
          parent->chave1 = x;
          parent->valor1 = xi;
          parent->chave2 = y;
          parent->valor2 = yi;
          parent->esq = a;
          parent->meio = sibling;
          parent->dir = q;
          if(q != nullptr) q->pai = parent;
          if(sibling != nullptr) sibling->pai = parent;
          if(a != nullptr) a->pai = parent;
          parent->dois = false;
        }
      }
    }

  }


}

template<class Chave, class Item>
void arvore23<Chave, Item>::remove(Chave chave)
{ 
  int numero_da_chave;
  Node23 *i, *f;
  i = ini;
  f = nullptr;
  /* procura qual no que deve remover */
   while(i != nullptr){
        /* se for dois no */
        if(i->dois){
          if(chave <= i->chave1){
            if(chave == i->chave1){
              numero_da_chave = 1;
              f = i->meio;
              break;
            }
            i = i->esq;
          }
          else{
            i = i->meio;
          }
        }
        else{ 
          /* se for tres no */
          if(chave <= i->chave1){
            if(chave == i->chave1){
              numero_da_chave = 1;
              f = i->meio;
              break;
            }
            i = i->esq;
          }
          else if(chave <= i->chave2){
            if(chave == i->chave2){
              numero_da_chave = 2;
              f = i->dir;
              break;
            }
            i = i->meio;
          }
          else{
            i = i->dir;
          }
        }
    }

    if(i == nullptr) return;
    /*std::cout << "chave escolhida "<< i->chave1 << "\n";*/

    if(f != nullptr){
      /* acha o proximo "in-order", que esta numa folha */
      while(f->esq != nullptr){
        f = f->esq;
      }
      if(numero_da_chave == 1){
        i->chave1 = f->chave1;
        i->valor1 = f->valor1;
      }
      else{
        i->chave2 = f->chave1;
        i->valor2 = f->valor1;
      }
      removeChave(f, f->chave1);
    }
    else{
      /* i é uma folha */
      /*std::cout << "entrei aqui\n";*/
      if(i->dois || i->chave1 == chave)
        removeChave(i, i->chave1);
      else
        removeChave(i, i->chave2);
      
    }
}

template<class Chave, class Item>
int arvore23<Chave, Item>::rank(Chave chave)
{
    int r;
    Node23 *i;
    r = 0;
    i = ini;
    while(i != nullptr){
        if(i->dois){
          if(chave <= i->chave1){
            if(chave == i->chave1){
              r += quantasChaves(i->esq);
              return r;
            }
            i = i->esq;
          }
          else{
            r += quantasChaves(i->esq) + 1;
            i = i->meio;
          }
        }
        else{ /* se for tres no */
          if(chave <= i->chave1){
            if(chave == i->chave1){
              r += quantasChaves(i->esq);
              return r;
            }
            i = i->esq;
          }
          else if(chave <= i->chave2){
            r += quantasChaves(i->esq) + 1;
            if(chave == i->chave2){
              r += quantasChaves(i->meio);
              return r;
            }
            i = i->meio;
          }
          else{
            r += quantasChaves(i->esq) + quantasChaves(i->meio) + 2;
            i = i->dir;
          }
        }
    }

    return r;
}

template<class Chave, class Item>
Chave arvore23<Chave, Item>::seleciona(int k)
{
    Node23 *i;
    int aux1, aux2;
    int numero_da_chave;
    i = ini;
    numero_da_chave = 1;
    while(i != nullptr){
      aux1 = rank(i->chave1);
      if(i->dois){
          if(aux1 > k){
              i = i->esq;
          }
          else if(aux1 <  k){
              i = i->meio;
          }   
          else{
              numero_da_chave = 1;
              break;
          }
      }
      else{
        aux2 = rank(i->chave2);
        if(aux1 >= k){
          if(aux1 == k){
            numero_da_chave = 1;
            break;
          }
          i = i->esq;
        }
        else if(aux2 >= k){
          if(aux2 == k){
            numero_da_chave = 2;
            break;
          }
          i = i->meio;
        }
        else{
          i = i->dir;
        }
      }
    }
    if(i == nullptr) return "";
    if(numero_da_chave == 1) return i->chave1;
    else return i->chave2;
}

template<class Chave, class Item>
int arvore23<Chave, Item>::quantasChaves(Node23 * arvore)
{
  if(arvore == nullptr) return 0;
  if(arvore->dois) return 1 + quantasChaves(arvore->esq) + quantasChaves(arvore->meio); 
  return 2 + quantasChaves(arvore->dir) + quantasChaves(arvore->esq) + quantasChaves(arvore->meio);
}
/*************************************************************************/
#endif