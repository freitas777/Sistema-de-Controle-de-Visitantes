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

void ArvoreRubroNegra::apagarSubarvore(NoRB* node) {
    if (node == TNULL) return;

    apagarSubarvore(node->esquerda);
    apagarSubarvore(node->direita);

    if (node->visitante)
        delete node->visitante;

    delete node;
}

ArvoreRubroNegra::~ArvoreRubroNegra() {
    apagarSubarvore(raiz);
    delete TNULL;
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
    if (x->pai == TNULL) {
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

int ArvoreRubroNegra::contarVisitantesEmDataAux(NoRB* node, string data) {
    if (node == TNULL) return 0;

    int count = 0;

    if (node->visitante != nullptr) {
        if (node->visitante->teveVisitaEmData(data)) {
            count = 1;
        }
    }

    count += contarVisitantesEmDataAux(node->esquerda, data);
    count += contarVisitantesEmDataAux(node->direita, data);

    return count;
}

int ArvoreRubroNegra::contarVisitantesEmData(string data) {
    if (raiz == TNULL) return 0;
    return contarVisitantesEmDataAux(raiz, data);
}

void ArvoreRubroNegra::percursoLargura() {
    std::cout << "\n--- Percurso em Largura ---\n";
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

void ArvoreRubroNegra::transplant(NoRB* u, NoRB* v) {
    if (u->pai == TNULL) {
        raiz = v;
    } else if (u == u->pai->esquerda) {
        u->pai->esquerda = v;
    } else {
        u->pai->direita = v;
    }
    v->pai = u->pai;
}

NoRB* ArvoreRubroNegra::minimo(NoRB* node) {
    while (node->esquerda != TNULL) {
        node = node->esquerda;
    }
    return node;
}

void ArvoreRubroNegra::removerFixup(NoRB* x) {
    while (x != raiz && x->cor == PRETO) {
        if (x == x->pai->esquerda) {
            NoRB* w = x->pai->direita;
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoEsquerda(x->pai);
                w = x->pai->direita;
            }
            if (w->esquerda->cor == PRETO && w->direita->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (w->direita->cor == PRETO) {
                    w->esquerda->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoDireita(w);
                    w = x->pai->direita;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->direita->cor = PRETO;
                rotacaoEsquerda(x->pai);
                x = raiz;
            }
        } else {
            NoRB* w = x->pai->esquerda;
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoDireita(x->pai);
                w = x->pai->esquerda;
            }
            if (w->direita->cor == PRETO && w->esquerda->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (w->esquerda->cor == PRETO) {
                    w->direita->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoEsquerda(w);
                    w = x->pai->esquerda;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->esquerda->cor = PRETO;
                rotacaoDireita(x->pai);
                x = raiz;
            }
        }
    }
    x->cor = PRETO;
}

bool ArvoreRubroNegra::remover(const std::string& cpf) {
    NoRB* z = buscarNo(cpf);
    if (z == TNULL) return false; // não encontrado

    if (z->visitante && z->visitante->temVisitaEmAndamento()) {
        return false;
    }

    NoRB* y = z;
    Cor yOriginalCor = y->cor;
    NoRB* x = nullptr;

    Visitante* visitanteParaDeletar = nullptr;

    if (z->esquerda == TNULL) {
        x = z->direita;
        visitanteParaDeletar = z->visitante;
        transplant(z, z->direita);
    } else if (z->direita == TNULL) {
        x = z->esquerda;
        visitanteParaDeletar = z->visitante;
        transplant(z, z->esquerda);
    } else {
        y = minimo(z->direita);
        yOriginalCor = y->cor;
        x = y->direita;

        if (y->pai == z) {
            x->pai = y;
        } else {
            transplant(y, y->direita);
            y->direita = z->direita;
            y->direita->pai = y;
        }

        visitanteParaDeletar = z->visitante;

        transplant(z, y);
        y->esquerda = z->esquerda;
        y->esquerda->pai = y;
        y->cor = z->cor;

    }

    if (yOriginalCor == PRETO) {
        removerFixup(x);
    }

    delete z;

    if (visitanteParaDeletar) {
        delete visitanteParaDeletar;
    }

    return true;
}