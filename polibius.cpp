#include "polibius.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

Polibiusquare::Polibiusquare() {
    gen_square();
}

void Polibiusquare::gen_square() {
    square.resize(16, vector<char>(16));

    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            square[i][j] = static_cast<char>(i * 16 + j);
        }
    }
}

void Polibiusquare::find_char(char c, int& row, int& col) const {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (square[i][j] == c) {
                row = i;
                col = j;
                return;
            }
        }
    }
    throw runtime_error("Символ не найден в квадрате Полибия");
}

string Polibiusquare::encrypts_text(const string& text) {
    string result;
    for (char c : text) {
        int row, col;
        find_char(c, row, col);
        result += static_cast<char>(row);
        result += static_cast<char>(col);
    }
    return result;
}

string Polibiusquare::decrypts_text(const string& text) {
    string result;
    for (size_t i = 0; i < text.size(); i += 2) {
        if (i + 1 >= text.size()) break;
        int r = static_cast<unsigned char>(text[i]);
        int c = static_cast<unsigned char>(text[i + 1]);
        result += square[r][c];
    }
    return result;
}

void Polibiusquare::encrypts_file(const string& inpath, const string& outpath) {
    ifstream input(inpath, ios::binary);
    ofstream output(outpath, ios::binary);

    if (!input.is_open()) {
        throw runtime_error("Не получается открыть исходный файл");
    }
    if (!output.is_open()) {
        throw runtime_error("Не получается открыть файл для шифротекста");
    }

    char c;
    while (input.get(c)) {
        int row, col;
        find_char(c, row, col);
        output.put(static_cast<char>(row));
        output.put(static_cast<char>(col));
    }
}

void Polibiusquare::decrypts_file(const string& inpath, const string& outpath) {
    ifstream input(inpath, ios::binary);
    ofstream output(outpath, ios::binary);

    if (!input.is_open()) {
        throw runtime_error("Не получается открыть файл с шифротекстом");
    }
    if (!output.is_open()) {
        throw runtime_error("Не получается открыть файл для расшифрованного текста");
    }

    char row, col;
    while (input.get(row) && input.get(col)) {
        int r = static_cast<unsigned char>(row);
        int c = static_cast<unsigned char>(col);
        output.put(square[r][c]);
    }
}
