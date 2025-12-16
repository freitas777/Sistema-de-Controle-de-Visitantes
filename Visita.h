#ifndef VISITA_H
#define VISITA_H

#include <string>
using namespace std;

struct Visita {
    string data;
    string horaEntrada;
    string horaSaida;
    string motivo;

    Visita(string d, string he, string m) 
        : data(d), horaEntrada(he), horaSaida("EM ANDAMENTO"), motivo(m) {}
    
    Visita() {}
};

struct NoVisita {
    Visita dados;
    NoVisita* proximo;

    NoVisita(Visita v) : dados(v), proximo(nullptr) {}
};

#endif