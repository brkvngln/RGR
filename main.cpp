#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <limits>
#include "modes.h"

using namespace std;

enum class Ciphers { WORD_CODE, POLIBIUS, RSA, UNKNOWN };

Ciphers fromSt(const string& str) {
    if (str == "wCODE") return Ciphers::WORD_CODE;
    if (str == "POLIBIUS") return Ciphers::POLIBIUS;
    if (str == "RSA") return Ciphers::RSA;
    return Ciphers::UNKNOWN;
}

int main() {
    setlocale(LC_ALL, "Russian");
    string task;
    cout << "Выберите алгоритм шифрования(wCODE, POLIBIUS, RSA): ";
    cin >> task;

    switch (fromSt(task)) {
    case Ciphers::WORD_CODE:
        handle_code_word();
        break;
    case Ciphers::POLIBIUS:
        handle_polibius();
        break;
    case Ciphers::RSA:
        handle_RSA();
        break;
    default:
        cerr << "Неизвестный алгоритм шифрования" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
