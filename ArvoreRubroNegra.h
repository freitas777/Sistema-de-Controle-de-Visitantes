#ifndef ARVORERUBRONEGRA_H
#define ARVORERUBRONEGRA_H

#include "NoRB.h"

class ArvoreRubroNegra {
private:
    NoRB* raiz;
    NoRB* TNULL; 

    void inicializarSentinel();
    void rotacaoEsquerda(NoRB* x);
    void rotacaoDireita(NoRB* x);
    void inserirFixup(NoRB* k);

    void auxiliarListar(NoRB* no);
    NoRB* buscarNo(string cpf);

public:
    ArvoreRubroNegra(); 

    void inserir(Visitante* visitante);
    Visitante* buscar(string cpf);
    void listarVisitantes(); 
    void percursoLargura(); 
};

#endif