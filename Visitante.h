#ifndef VISITANTE_H
#define VISITANTE_H

#include "Visita.h"
#include <iostream>
#include <string>

class Visitante
{
private:
    string cpf;
    string nome;
    NoVisita *historicoVisitas;

public:
    Visitante(string c, string n);

    string getCpf() const;
    string getNome() const;
    int getNumeroVisitas();

    void registrarVisita(string data, string hora, string motivo);
    bool registrarSaida(string horaSaida);
    bool temVisitaEmAndamento();
    void imprimirHistorico();
    bool atualizarVisitaEmAndamento(string novaData, string novaHoraEntrada, string novoMotivo);
    bool getVisitaEmAndamento(Visita &out);
    bool teveVisitaEmData(string data);
};

#endif