#include <iostream>
#include "ArvoreRubroNegra.h"
#include "Visitante.h"

using namespace std;

int main()
{
    ArvoreRubroNegra sistema;
    int opcao;

    do
    {
        cout << "\n=== SISTEMA DE CONTROLE DE VISITANTES (IFRN) ===\n";
        cout << "1. Registrar Entrada (Inserir/Atualizar)\n";
        cout << "2. Registrar Saida\n";
        cout << "3. Listar Visitantes (Ordenado)\n";
        cout << "4. Buscar e Ver Historico\n";
        cout << "5. Percurso em Largura (Ver Cores)\n";
        cout << "6. Numero de visitantes em um dia\n";
        cout << "7. Remover Visitante\n";
        cout << "0. Sair\n";
        cout << "Opcao: ";
        cin >> opcao;

        if (opcao == 1)
        {
            string cpf, nome, motivo, data, horaEntrada;

            cout << "CPF: ";
            cin >> cpf;

            Visitante *v = sistema.buscar(cpf);

            if (v == nullptr)
            {
                cout << "Visitante novo! Digite Nome: ";
                cin.ignore();
                getline(cin, nome);

                v = new Visitante(cpf, nome);
                sistema.inserir(v);

                cout << ">> Visitante cadastrado na arvore.\n";

                cout << "Data (dd/mm/aaaa): ";
                getline(cin, data);

                cout << "Hora de entrada (hh:mm): ";
                getline(cin, horaEntrada);

                cout << "Motivo da visita: ";
                getline(cin, motivo);

                v->registrarVisita(data, horaEntrada, motivo);
                cout << ">> Entrada registrada com sucesso!\n";
            }
            else
            {
                cout << ">> Visitante encontrado: " << v->getNome() << endl;

                if (v->temVisitaEmAndamento())
                {
                    Visita atual;
                    if (v->getVisitaEmAndamento(atual))
                    {
                        cout << "\n--- Visita em andamento ---\n";
                        cout << "Data: " << atual.data << endl;
                        cout << "Hora de entrada: " << atual.horaEntrada << endl;
                        cout << "Motivo: " << atual.motivo << endl;
                        cout << "---------------------------\n";
                    }

                    cout << "Deseja atualizar esta visita? (s/n): ";
                    char resp;
                    cin >> resp;
                    cin.ignore();

                    if (resp == 's' || resp == 'S')
                    {
                        cout << "Nova Data (dd/mm/aaaa): ";
                        getline(cin, data);

                        cout << "Nova Hora de entrada (hh:mm): ";
                        getline(cin, horaEntrada);

                        cout << "Novo Motivo da visita: ";
                        getline(cin, motivo);

                        bool ok = v->atualizarVisitaEmAndamento(data, horaEntrada, motivo);
                        if (ok)
                            cout << ">> Visita atualizada com sucesso!\n";
                        else
                            cout << ">> Falha ao atualizar. Tente novamente.\n";
                    }
                    else
                    {
                        cout << ">> Nada alterado. Saindo para o menu.\n";
                    }
                }
                else
                {
                    cout << "Data (dd/mm/aaaa): ";
                    cin.ignore();
                    getline(cin, data);

                    cout << "Hora de entrada (hh:mm): ";
                    getline(cin, horaEntrada);

                    cout << "Motivo da visita: ";
                    getline(cin, motivo);

                    v->registrarVisita(data, horaEntrada, motivo);
                    cout << ">> Entrada registrada com sucesso!\n";
                }
            }
        }
        else if (opcao == 2)
        {
            string cpf, horaSaida;
            cout << "CPF: ";
            cin >> cpf;

            Visitante *v = sistema.buscar(cpf);
            if (v == nullptr)
            {
                cout << ">> Visitante nao encontrado.\n";
            }
            else
            {
                cout << "Hora de saida (hh:mm): ";
                cin.ignore();
                getline(cin, horaSaida);

                if (v->registrarSaida(horaSaida))
                {
                    cout << ">> Saida registrada com sucesso!\n";
                }
                else
                {
                    cout << ">> Nao ha visita em andamento para este visitante.\n";
                }
            }
        }
        else if (opcao == 3)
        {
            sistema.listarVisitantes();
        }
        else if (opcao == 4)
        {
            string cpf;
            cout << "CPF: ";
            cin >> cpf;
            Visitante *v = sistema.buscar(cpf);
            if (v)
                v->imprimirHistorico();
            else
                cout << ">> Nao encontrado.\n";
        }
        else if (opcao == 5)
        {
            sistema.percursoLargura();
        }
        else if (opcao == 6)
        {
            string dataConsulta;
            cout << "Data (dd/mm/aaaa): ";
            cin.ignore();
            getline(cin, dataConsulta);

            int total = sistema.contarVisitantesEmData(dataConsulta);
            cout << ">> Numero de visitantes em " << dataConsulta << ": " << total << "\n";
        }
        else if (opcao == 7)
        {
            string cpf;
            cout << "CPF para remover: ";
            cin >> cpf;
            if (sistema.remover(cpf))
            {
                cout << ">> Visitante removido com sucesso.\n";
            }
            else
            {
                cout << ">> Nao foi possivel remover o visitante (nao encontrado ou visita em andamento).\n";
            }
        }

    } while (opcao != 0);

    return 0;
}