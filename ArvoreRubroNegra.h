#ifndef ARVORERUBRONEGRA_H
#define ARVORERUBRONEGRA_H

#include "NoRB.h"

class ArvoreRubroNegra
{
private:
    NoRB *raiz;
    NoRB *TNULL;

    void inicializarSentinel();
    void rotacaoEsquerda(NoRB *x);
    void rotacaoDireita(NoRB *x);
    void inserirFixup(NoRB *k);

    void auxiliarListar(NoRB *no);
    NoRB *buscarNo(string cpf);
    int contarVisitantesEmDataAux(NoRB *node, string data);

    void transplant(NoRB *u, NoRB *v);
    NoRB *minimo(NoRB *node);
    void removerFixup(NoRB *x);

    void apagarSubarvore(NoRB *node);

public:
    ArvoreRubroNegra();
    ~ArvoreRubroNegra();

    void inserir(Visitante *visitante);
    Visitante *buscar(string cpf);
    void listarVisitantes();
    int contarVisitantesEmData(string data);
    void percursoLargura();
    bool remover(const std::string &cpf);
};

#endif