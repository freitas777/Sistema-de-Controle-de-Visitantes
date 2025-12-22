#include "Visitante.h"

Visitante::Visitante(string c, string n) {
    cpf = c;
    nome = n;
    historicoVisitas = nullptr;
}

string Visitante::getCpf() const { return cpf; }
string Visitante::getNome() const { return nome; }

void Visitante::registrarVisita(string data, string hora, string motivo) {
    Visita v(data, hora, motivo);
    NoVisita* novo = new NoVisita(v);
    novo->proximo = historicoVisitas;
    historicoVisitas = novo;
}

bool Visitante::registrarSaida(string horaSaida) {
    NoVisita* atual = historicoVisitas;
    while (atual != nullptr) {
        if (atual->dados.horaSaida == "EM ANDAMENTO") {
            atual->dados.horaSaida = horaSaida;
            return true;
        }
        atual = atual->proximo;
    }
    return false; 
}

bool Visitante::temVisitaEmAndamento() {
    NoVisita* atual = historicoVisitas;
    while (atual != nullptr) {
        if (atual->dados.horaSaida == "EM ANDAMENTO") return true;
        atual = atual->proximo;
    }
    return false;
}

bool Visitante::teveVisitaEmData(string data) {
    NoVisita* atual = historicoVisitas;
    while (atual != nullptr) {
        if (atual->dados.data == data) return true;
        atual = atual->proximo;
    }
    return false;
}

int Visitante::getNumeroVisitas() {
    int count = 0;
    NoVisita* atual = historicoVisitas;
    while(atual != nullptr) { 
        count++; 
        atual = atual->proximo; 
    }
    return count;
}

void Visitante::imprimirHistorico() {
    cout << "--- Historico de: " << nome << " (CPF: " << cpf << ") ---\n";
    NoVisita* atual = historicoVisitas;
    int i = 1;
    while (atual != nullptr) {
        cout << i++ << ". Data: " << atual->dados.data 
             << " | Ent: " << atual->dados.horaEntrada 
             << " | Sai: " << atual->dados.horaSaida 
             << " | Motivo: " << atual->dados.motivo << endl;
        atual = atual->proximo;
    }
    cout << "------------------------------------------\n";
}

bool Visitante::atualizarVisitaEmAndamento(string novaData, string novaHoraEntrada, string novoMotivo) {
    NoVisita* atual = historicoVisitas;

    while (atual != nullptr) {
        if (atual->dados.horaSaida == "EM ANDAMENTO") {
            atual->dados.data = novaData;
            atual->dados.horaEntrada = novaHoraEntrada;
            atual->dados.motivo = novoMotivo;
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}

bool Visitante::getVisitaEmAndamento(Visita& out) {
    NoVisita* atual = historicoVisitas;

    while (atual != nullptr) {
        if (atual->dados.horaSaida == "EM ANDAMENTO") {
            out = atual->dados;
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}