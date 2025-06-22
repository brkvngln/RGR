#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

void xorr(vector<unsigned char>& data, const string& key) {
    if (key.empty()) {
        throw invalid_argument("Кодовое слово не может быть пустым!");
    }

    size_t keyLength = key.length();
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] ^= key[i % keyLength];
    }
}

string process_text(const string& text, const string& key) {
    if (key.empty()) {
        throw invalid_argument("Кодовое слово не может быть пустым!");
    }

    vector<unsigned char> data(text.begin(), text.end());
    xorr(data, key);
    return string(data.begin(), data.end());
}

bool process_file(const string& input, const string& output, const string& key) {
    try {
        if (input.empty() || output.empty()) {
            throw invalid_argument("Пути к файлам не могут быть пустыми!");
        }

        ifstream input_file(input, ios::binary);
        if (!input_file) {
            throw runtime_error("Не удалось открыть входной файл: " + input);
        }

        vector<unsigned char> data(
            (istreambuf_iterator<char>(input_file)),
            istreambuf_iterator<char>()
        );
        input_file.close();

        xorr(data, key);

        ofstream output_file(output, ios::binary);
        if (!output_file) {
            throw runtime_error("Не удалось создать выходной файл: " + output);
        }
        output_file.write(reinterpret_cast<char*>(data.data()), data.size());
        output_file.close();

        return true;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return false;
    }
}
