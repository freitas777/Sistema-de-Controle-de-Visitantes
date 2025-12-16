#ifndef FILANORB_H
#define FILANORB_H

#include "NoRB.h"

struct NoFila {
    NoRB* valor;
    NoFila* prox;

    NoFila(NoRB* v) : valor(v), prox(nullptr) {}
};

class FilaNoRB {
private:
    NoFila* ini;
    NoFila* fim;

public:
    FilaNoRB() : ini(nullptr), fim(nullptr) {}

    bool vazia() const {
        return ini == nullptr;
    }

    void enfileirar(NoRB* v) {
        NoFila* novo = new NoFila(v);
        if (fim == nullptr) {
            ini = fim = novo;
        } else {
            fim->prox = novo;
            fim = novo;
        }
    }

    NoRB* desenfileirar() {
        if (ini == nullptr) return nullptr;

        NoFila* temp = ini;
        NoRB* v = temp->valor;

        ini = ini->prox;
        if (ini == nullptr) fim = nullptr;

        delete temp;
        return v;
    }

    ~FilaNoRB() {
        while (!vazia()) desenfileirar();
    }
};

#endif
