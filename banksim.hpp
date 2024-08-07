#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class ContaBancaria {
private:
    float saldo;
    float limite_credito;
    float fatura;
    float caixinha;
    vector<string> historico;

    string formatar_valor(float valor);

public:
    ContaBancaria(float saldo, float limite_credito);

    void registrar_acao(const string& acao);
    void depositar(float valor);
    void sacar(float valor, bool debito = true);
    void pagar_fatura(char answer);
    void status_conta();
    pair<int, int> passar_dia(int dia_atual, int mes_atual);
    void adicionar_caixinha(float valor);
    void verificar_caixinha();
    void retornar_caixinha(char answer);
    void mostrar_extrato();
};

void mais_opcoes(ContaBancaria& conta);

void clear_screen();
