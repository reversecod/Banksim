#include <iostream>
#include <iomanip>  // Para setprecision
#include <sstream>  // Para stringstream
#include <map>
#include <vector>
#include "banksim.hpp"
using namespace std;

ContaBancaria::ContaBancaria(float saldo, float limite_credito);

    void ContaBancaria::registrar_acao(const string& acao); 

    void ContaBancaria::depositar(float valor) {
        saldo += valor;
        string acao = "Deposito de R$" + formatar_valor(valor) + " realizado. Saldo atual: R$" + formatar_valor(saldo);
        registrar_acao(acao);
        cout << acao << endl;
    }

    void ContaBancaria::sacar(float valor, bool debito = true) {
        if (debito) {
            if (saldo >= valor) {
                saldo -= valor;
                string acao = "Saque de R$" + formatar_valor(valor) + " realizado no debito. Saldo atual: R$" + formatar_valor(saldo);
                registrar_acao(acao);
                cout << acao << endl;
            } else {
                cout << "Saldo insuficiente." << endl;
            }
        } else {
            if (valor > limite_credito) {
                cout << "Valor de saque excede o limite do credito." << endl;
            } else if (limite_credito >= valor) {
                limite_credito -= valor;
                fatura += valor;
                string acao = "Gasto de R$" + formatar_valor(valor) + " realizado no credito. Fatura atual: R$" + formatar_valor(fatura);
                registrar_acao(acao);
                cout << acao << endl;
            } else {
                cout << "Limite de credito ultrapassado." << endl;
            }
        }
    }

    void ContaBancaria::pagar_fatura(char answer) {
        if (answer == 'Y') {
            if (saldo >= fatura) {
                saldo -= fatura;
                float valorpago = fatura;
                limite_credito += fatura;
                fatura = 0;
                string acao = "Pagamento total da fatura de R$" + formatar_valor(valorpago) + " realizado. Saldo atual: R$" + formatar_valor(saldo) + ". Limite de crédito atual: R$" + formatar_valor(limite_credito);
                registrar_acao(acao);
                cout << acao << endl;
            } else {
                cout << "Voce nao possui saldo o suficiente para pagar toda a fatura!" << endl;
            }
        } else if (answer == 'N') {
            float valor;
            cout << "Digite o valor a pagar da fatura: R$";
            cin >> valor;
            if (fatura >= valor) {
                saldo -= valor;
                limite_credito += valor;
                fatura -= valor;
                string acao = "Pagamento parcial de fatura de R$" + formatar_valor(valor) + " realizado. Fatura restante: R$" + formatar_valor(fatura) + ". Saldo atual: R$" + formatar_valor(saldo) + ". Limite de crédito atual: R$" + formatar_valor(limite_credito);
                registrar_acao(acao);
                cout << acao << endl;
            } else {
                cout << "Valor da fatura excede o valor a pagar." << endl;
            }
        } else {
            cout << "Alternativa invalida!" << endl;
        }
    }

    void ContaBancaria::status_conta() {
        cout << "Saldo: R$" << formatar_valor(saldo) << endl;
        cout << "Fatura: R$" << formatar_valor(fatura) << endl;
        cout << "Limite de credito: R$" << formatar_valor(limite_credito) << endl;
    }

    void ContaBancaria::adicionar_caixinha(float valor) {
        if (valor <= saldo) {
            saldo -= valor;
            caixinha += valor;
            string acao = "Adicionado R$" + formatar_valor(valor) + " a caixinha. Saldo atual: R$" + formatar_valor(saldo) + ". Valor na caixinha: R$" + formatar_valor(caixinha);
            registrar_acao(acao);
            cout << acao << endl;
        } else {
            cout << "Valor excede o saldo disponível para adicionar a caixinha." << endl;
        }
    }

    void ContaBancaria::verificar_caixinha() {
        cout << "Valor na caixinha: R$" << formatar_valor(caixinha) << endl;
    }

    void ContaBancaria::retornar_caixinha(char answer) {
        if (answer == 'Y') {
            saldo += caixinha;
            float caixa_anterior = caixinha;
            caixinha = 0;
            string acao = "Foi retornado o valor total da caixinha de R$" + formatar_valor(caixa_anterior) + ". Saldo atual: R$" + formatar_valor(saldo) + ". Valor na caixinha: R$" + formatar_valor(caixinha);
            registrar_acao(acao);
            cout << acao << endl;
        } else if (answer == 'N') {
            float valor;
            cout << "Digite o valor a retornar da caixinha: R$";
            cin >> valor;
            if (valor <= caixinha) {
                saldo += valor;
                caixinha -= valor;
                string acao = "Valor de R$" + formatar_valor(valor) + " retornado ao saldo. Saldo atual: R$" + formatar_valor(saldo) + ". Valor na caixinha: R$" + formatar_valor(caixinha);
                registrar_acao(acao);
                cout << acao << endl;
            } else {
                cout << "Valor excede o montante na caixinha." << endl;
            }
        } else {
            cout << "Alternativa invalida!" << endl;
        }
    }

    void ContaBancaria::mostrar_extrato() {
        cout << "Ultimas 5 acoes realizadas:" << endl;
        for (const auto& acao : historico) {
            cout << acao << endl;
        }
    }
};

void mais_opcoes(ContaBancaria& conta) {
    while (true) {
        cout << "\n--- MAIS OPCOES ---\n";
        cout << "1 - Ver extrato" << endl;
        cout << "2 - Voltar ao menu" << endl;
        cout << "0 - Sair" << endl;

        int opcao;
        cout << "Digite a opcao desejada: ";
        cin >> opcao;
        clear_screen();

        switch (opcao) {
            case 1:
                conta.mostrar_extrato();
                break;
            case 2:
                return;  
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
        }
    }
}