#include "ArvoreRubroNegra.h"
#include "FilaNoRB.h"
#include <iostream>

using namespace std;

void ArvoreRubroNegra::inicializarSentinel() {
    TNULL = new NoRB(nullptr);
    TNULL->cor = PRETO;

    TNULL->esquerda = TNULL;
    TNULL->direita  = TNULL;
    TNULL->pai      = TNULL;

    raiz = TNULL;
}

ArvoreRubroNegra::ArvoreRubroNegra() {
    inicializarSentinel();
}

void ArvoreRubroNegra::rotacaoEsquerda(NoRB* x) {
    NoRB* y = x->direita;
    x->direita = y->esquerda;
    if (y->esquerda != TNULL) {
        y->esquerda->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == TNULL) {
        raiz = y;
    } else if (x == x->pai->esquerda) {
        x->pai->esquerda = y;
    } else {
        x->pai->direita = y;
    }
    y->esquerda = x;
    x->pai = y;
}

void ArvoreRubroNegra::rotacaoDireita(NoRB* x) {
    NoRB* y = x->esquerda;
    x->esquerda = y->direita;
    if (y->direita != TNULL) {
        y->direita->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == nullptr) {
        raiz = y;
    } else if (x == x->pai->direita) {
        x->pai->direita = y;
    } else {
        x->pai->esquerda = y;
    }
    y->direita = x;
    x->pai = y;
}

void ArvoreRubroNegra::inserirFixup(NoRB* k) {
    NoRB* u;
    while (k->pai->cor == VERMELHO) {
        if (k->pai == k->pai->pai->direita) {
            u = k->pai->pai->esquerda;
            if (u->cor == VERMELHO) {
                u->cor = PRETO;
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                k = k->pai->pai;
            } else {
                if (k == k->pai->esquerda) {
                    k = k->pai;
                    rotacaoDireita(k);
                }
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(k->pai->pai);
            }
        } else {
            u = k->pai->pai->direita;
            if (u->cor == VERMELHO) {
                u->cor = PRETO;
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                k = k->pai->pai;
            } else {
                if (k == k->pai->direita) {
                    k = k->pai;
                    rotacaoEsquerda(k);
                }
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                rotacaoDireita(k->pai->pai);
            }
        }
        if (k == raiz) break;
    }
    raiz->cor = PRETO;
}

void ArvoreRubroNegra::inserir(Visitante* visitante) {
    NoRB* novoNo = new NoRB(visitante);
    novoNo->pai = TNULL;
    novoNo->esquerda = TNULL;
    novoNo->direita = TNULL;
    novoNo->cor = VERMELHO;

    NoRB* y = TNULL;
    NoRB* x = raiz;

    while (x != TNULL) {
        y = x;
        if (novoNo->chave < x->chave) x = x->esquerda;
        else x = x->direita;
    }

    novoNo->pai = y;
    if (y == TNULL) raiz = novoNo;
    else if (novoNo->chave < y->chave) y->esquerda = novoNo;
    else y->direita = novoNo;

    inserirFixup(novoNo);
}

NoRB* ArvoreRubroNegra::buscarNo(string cpf) {
    NoRB* atual = raiz;
    while (atual != TNULL) {
        if (cpf == atual->chave) return atual;
        if (cpf < atual->chave) atual = atual->esquerda;
        else atual = atual->direita;
    }
    return TNULL;
}

Visitante* ArvoreRubroNegra::buscar(string cpf) {
    NoRB* res = buscarNo(cpf);
    if (res == TNULL) return nullptr;
    return res->visitante;
}

void ArvoreRubroNegra::auxiliarListar(NoRB* no) {
    if (no != TNULL) {
        auxiliarListar(no->esquerda);
        cout << "CPF: " << no->chave 
             << " | Nome: " << no->visitante->getNome() 
             << " | Visitas: " << no->visitante->getNumeroVisitas() << endl;
        auxiliarListar(no->direita);
    }
}

void ArvoreRubroNegra::listarVisitantes() {
    cout << "\n--- Lista de Visitantes (Ordenada por CPF) ---\n";
    auxiliarListar(raiz);
}

void ArvoreRubroNegra::percursoLargura() {
    std::cout << "\n--- Percurso em Largura (Debug RBT) ---\n";
    if (raiz == TNULL) return;

    FilaNoRB fila;
    fila.enfileirar(raiz);

    while (!fila.vazia()) {
        NoRB* atual = fila.desenfileirar();

        std::string corStr = (atual->cor == VERMELHO) ? "VERMELHO" : "PRETO";
        std::cout << "[CPF: " << atual->chave << " | Cor: " << corStr << "]\n";

        if (atual->esquerda != TNULL) fila.enfileirar(atual->esquerda);
        if (atual->direita != TNULL) fila.enfileirar(atual->direita);
    }
}