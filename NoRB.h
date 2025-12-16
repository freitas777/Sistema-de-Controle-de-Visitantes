#ifndef NORB_H
#define NORB_H

#include "Visitante.h"

enum Cor { VERMELHO, PRETO };

struct NoRB {
    Visitante* visitante; 
    string chave;  
    Cor cor;
    NoRB *pai, *esquerda, *direita;

    NoRB(Visitante* v) {
        visitante = v;
        if(v) chave = v->getCpf();
        cor = VERMELHO; 
        pai = esquerda = direita = nullptr;
    }
};

#endif