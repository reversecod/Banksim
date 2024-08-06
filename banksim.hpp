#include <iostream>
#include <iomanip>  // Para setprecision
#include <sstream>  // Para stringstream
#include <map>
#include <vector>
#include <string>

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
    ContaBancaria(float saldo, float limite_credito);

    void registrar_acao(const string& acao); 

    void depositar(float valor);

    void sacar(float valor, bool debito = true);

    void pagar_fatura(char answer);

    void status_conta();

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

    void adicionar_caixinha(float valor);

    void verificar_caixinha();

    void retornar_caixinha(char answer);

    void mostrar_extrato();
};

void mais_opcoes(ContaBancaria& conta)