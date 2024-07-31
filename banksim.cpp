#include <iostream>
#include <iomanip>  // Para setprecision
#include <sstream>  // Para stringstream
#include <map>
#include <vector>
using namespace std;

#ifdef _WIN32
#include <windows.h>
void clear_screen() {
    system("cls");
}
#else
void clear_screen() {
}
#endif

class ContaBancaria {
private:
    float saldo;
    float limite_credito;
    float fatura;
    float caixinha;
    vector<string> historico;

    string formatar_valor(float valor) {
        stringstream ss;
        ss << fixed << setprecision(2) << valor;
        return ss.str();
    }

public:
    ContaBancaria(float saldo, float limite_credito)
        : saldo(saldo), limite_credito(limite_credito), fatura(0), caixinha(0) {}

    void registrar_acao(const string& acao) {
        if (historico.size() == 5) {
            historico.erase(historico.begin());
        }
        historico.push_back(acao);
    }

    void depositar(float valor) {
        saldo += valor;
        string acao = "Deposito de R$" + formatar_valor(valor) + " realizado. Saldo atual: R$" + formatar_valor(saldo);
        registrar_acao(acao);
        cout << acao << endl;
    }

    void sacar(float valor, bool debito = true) {
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

    void pagar_fatura(char answer) {
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

    void status_conta() {
        cout << "Saldo: R$" << formatar_valor(saldo) << endl;
        cout << "Fatura: R$" << formatar_valor(fatura) << endl;
        cout << "Limite de credito: R$" << formatar_valor(limite_credito) << endl;
    }

    pair<int, int> passar_dia(int dia_atual, int mes_atual) {
        map<int, int> dias_por_mes = {
            {1, 31}, {2, 28}, {3, 31}, {4, 30}, {5, 31}, {6, 30},
            {7, 31}, {8, 31}, {9, 30}, {10, 31}, {11, 30}, {12, 31}
        };

        int proximo_dia = dia_atual + 1;
        int proximo_mes = mes_atual;

        if (proximo_dia > dias_por_mes[mes_atual]) {
            proximo_dia = 1;
            proximo_mes += 1;
            if (proximo_mes > 12) {
                proximo_mes = 1;
            }
        }

        return {proximo_dia, proximo_mes};
    }

    void adicionar_caixinha(float valor) {
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

    void verificar_caixinha() {
        cout << "Valor na caixinha: R$" << formatar_valor(caixinha) << endl;
    }

    void retornar_caixinha(char answer) {
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

    void mostrar_extrato() {
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

int main() {
    int dia, mes;
    float saldo_inicial, limite_inicial;

    cout << "Digite o dia inicial: ";
    cin >> dia;
    cout << "Digite o mes inicial: ";
    cin >> mes;
    cout << "Informe o saldo inicial: R$";
    cin >> saldo_inicial;
    cout << "Informe o limite de credito inicial: R$";
    cin >> limite_inicial;

    ContaBancaria minha_conta(saldo_inicial, limite_inicial);

    while (true) {
        // Menu
        cout << "\n------- MENU -------\n";
        cout << "Dia: " << dia << "/" << mes << endl;
        cout << "1 - Consultar saldo e status da conta" << endl;
        cout << "2 - Depositar" << endl;
        cout << "3 - Sacar (Debito)" << endl;
        cout << "4 - Sacar (Credito)" << endl;
        cout << "5 - Pagar fatura" << endl;
        cout << "6 - Adicionar a caixinha" << endl;
        cout << "7 - Verificar caixinha" << endl;
        cout << "8 - Retirar da caixinha" << endl;
        cout << "9 - Avancar o dia" << endl;
        cout << "10 - Mais opcoes" << endl;
        cout << "0 - Sair" << endl;

        int opcao;
        cout << "Digite a opcao desejada: ";
        cin >> opcao;
        clear_screen();

        switch (opcao) {
            case 1:
                minha_conta.status_conta();
                break;
            case 2:
                float valor_deposito;
                cout << "Digite o valor a depositar: R$";
                cin >> valor_deposito;
                minha_conta.depositar(valor_deposito);
                break;
            case 3:
                float valor_saque_debito;
                cout << "Digite o valor a sacar no debito: R$";
                cin >> valor_saque_debito;
                minha_conta.sacar(valor_saque_debito, true);
                break;
            case 4:
                float valor_saque_credito;
                cout << "Digite o valor a sacar no credito: R$";
                cin >> valor_saque_credito;
                minha_conta.sacar(valor_saque_credito, false);
                break;
            case 5:
                char pagar_total;
                cout << "Deseja pagar a fatura total? (Y/N): ";
                cin >> pagar_total;
                pagar_total = toupper(pagar_total);
                minha_conta.pagar_fatura(pagar_total);
                break;
            case 6:
                float valor_caixinha;
                cout << "Digite o valor a adicionar na caixinha: R$";
                cin >> valor_caixinha;
                minha_conta.adicionar_caixinha(valor_caixinha);
                break;
            case 7:
                minha_conta.verificar_caixinha();
                break;
            case 8:
                char retornar_total;
                cout << "Deseja retornar todo valor da caixinha? (Y/N): ";
                cin >> retornar_total;
                retornar_total = toupper(retornar_total);
                minha_conta.retornar_caixinha(retornar_total);
                break;
            case 9:
                tie(dia, mes) = minha_conta.passar_dia(dia, mes);
                break;
            case 10:
                mais_opcoes(minha_conta);
                break;
            case 0:
                return 0;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
        }
    }
}