#include <iostream>
#include "ArvoreRubroNegra.h"
#include "Visitante.h"

using namespace std;

int main() {
    ArvoreRubroNegra sistema;
    int opcao;

    do {
        cout << "\n=== SISTEMA DE CONTROLE DE VISITANTES (IFRN) ===\n";
        cout << "1. Registrar Entrada (Inserir/Atualizar)\n";
        cout << "2. Registrar Saida\n";
        cout << "3. Listar Visitantes (Ordenado)\n";
        cout << "4. Buscar e Ver Historico\n";
        cout << "5. Debug: Percurso em Largura (Ver Cores)\n";
        cout << "0. Sair\n";
        cout << "Opcao: ";
        cin >> opcao;

        if (opcao == 1) {
            string cpf, nome, motivo, data, horaEntrada;
            cout << "CPF: "; cin >> cpf;

            Visitante* v = sistema.buscar(cpf);
            if (v == nullptr) {
                cout << "Visitante novo! Digite Nome: ";
                cin.ignore(); getline(cin, nome);

                v = new Visitante(cpf, nome);
                sistema.inserir(v);
                cout << ">> Visitante cadastrado na arvore.\n";
            } else {
                cout << ">> Visitante encontrado: " << v->getNome() << endl;
                cin.ignore();
            }

            cout << "Data (dd/mm/aaaa): "; getline(cin, data);
            cout << "Hora de entrada (hh:mm): "; getline(cin, horaEntrada);
            cout << "Motivo da visita: "; getline(cin, motivo);

            v->registrarVisita(data, horaEntrada, motivo);
            cout << ">> Entrada registrada com sucesso!\n";

                } else if (opcao == 3) {
                    sistema.listarVisitantes();
                } else if (opcao == 4) {
                    string cpf;
                    cout << "CPF: "; cin >> cpf;
                    Visitante* v = sistema.buscar(cpf);
                    if(v) v->imprimirHistorico();
                    else cout << ">> Nao encontrado.\n";
                } else if (opcao == 5) {
                    sistema.percursoLargura();
                }

            } while (opcao != 0);

            return 0;
        }