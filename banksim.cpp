#include "banksim.hpp"

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
        cout << "\n-------------------\n";

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