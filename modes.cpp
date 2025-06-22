#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <limits>
#include "modes.h"
#include "rsa.h"
#include "code_word.h"
#include "polibius.h"

using namespace std;

void save_to_file(const string& filename, const string& content) {
    setlocale(LC_ALL,"ru_RU.UTF-8");
	ofstream file(filename);
    if (file) {
        file << content;
        cout << "Текст сохранен в файл: " << filename << endl;
    }
    else {
        cerr << "Ошибка при сохранении в файл." << endl;
    }
}
void validateInput(int input) {
	setlocale(LC_ALL,"ru_RU.UTF-8");
    if (input != 1 && input != 2) {
        throw invalid_argument("Некорректный ввод.");
    }
}
InputMode get_input_mode() {
	setlocale(LC_ALL,"ru_RU.UTF-8");
    cout << "1. Работа с файлом\n2. Работа с текстом\nВыберите режим: ";
    int mode;
    cin >> mode;
    cin.ignore();
    return mode == 1 ? InputMode::FILE : (mode == 2 ? InputMode::TEXT : InputMode::UNKNOWN);
}

void handle_polibius() {
	setlocale(LC_ALL,"ru_RU.UTF-8");
    Polibiusquare cipher;
    int command;
    InputMode mode = get_input_mode();

    if (mode == InputMode::FILE) {
        string inpath, outpath;
        cout << "1. Шифрование\n2. Дешифрование\nВыберите режим: ";
        cin >> command;
        cin.ignore();

        cout << "Введите путь к исходному файлу: ";
        getline(cin, inpath);
        cout << "Введите путь к файлу для результата: ";
        getline(cin, outpath);

        try {
            if (command == 1) {
                cipher.encrypts_file(inpath, outpath);
                cout << "Шифрование завершено.";
            }
            else if (command == 2) {
                cipher.decrypts_file(inpath, outpath);
                cout << "Шифрование завершено.";
            }
            else {
                cout << "Неизвестная команда";
            }
        }
        catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }
    else if (mode == InputMode::TEXT) {
        string text;
        cout << "Введите текст для шифрования: ";
        getline(cin, text);

        try {
                string encrypted = cipher.encrypts_text(text);
                cout << "Шифрование завершено: " << encrypted << endl;
                cout << "Сохранить в файл? (y/n)";
                char choice;
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    string filename;
                    cout << "Введите путь к файлу для результата: ";
                    cin >> filename;
                    save_to_file(filename, encrypted);
		    cout << "Сохранено.";
                }
            }
        catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }
    else {
        cout << "Некорректный ввод.";
    }
}

void handle_code_word() {
	 setlocale(LC_ALL,"ru_RU.UTF-8");
    int command;
    InputMode mode = get_input_mode();

    if (mode == InputMode::FILE) {
        string input, output, key;
        cout << "1. Шифровать файл\n2. Дешифровать файл\nВыберите действие: ";
        cin >> command;
        cin.ignore();

        cout << "Введите путь к файлу: ";
        getline(cin, input);
        cout << "Введите путь для сохранения: ";
        getline(cin, output);
        cout << "Введите кодовое слово: ";
        getline(cin, key);

        try {
            if (process_file(input, output, key)) {
                cout << (command == 1 ? "Файл зашифрован!" : "Файл расшифрован!") << endl;
            }
            else {
                throw runtime_error("Не удалось обработать файл. Проверьте ввод.");
            }
        }
        catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }
    else if (mode == InputMode::TEXT) {
        string text, key;
        cout << "Введите текст: ";
        getline(cin, text);
        cout << "Введите кодовое слово: ";
        getline(cin, key);

        try {
            string result = process_text(text, key);
            cout << "Зашифрованный текст: " << result << endl;
                cout << "\nВАЖНО! Для дешифрования вам понадобится тот же ключ: " << key << endl;        
            cout << "Сохранить результат в файл? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' ||  choice == 'Y') {
                string filename;
                cout << "Введите имя файла: ";
                cin >> filename;
                save_to_file(filename, result);
                    cout << "Сохранить ключ в файл? (y/n): ";
                    cin >> choice;
                    if (choice == 'y' ||  choice == 'Y') {
                        string key_filename = filename + ".key";
                        save_to_file(key_filename, key);
                        cout << "Ключ сохранен в файл: " << key_filename << endl;
                    }
                }
            }
        catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }
    else {
        cout << "Некорректный выбор режима!\n";
    }
}
	
void handle_RSA() {
	setlocale(LC_ALL,"ru_RU.UTF-8");
    	int command;
    InputMode mode = get_input_mode();

    if (mode == InputMode::FILE) {
        try {
            cout << "1. Шифрование\n2. Дешифрование\nВыберите режим: ";
            if (!(cin >> command)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Некорректный ввод.");
            }

            validateInput(command);
            cin.ignore();

            if (command == 1) {
                string in, out, keys;
                cout << "Введите путь к исходному файлу: ";
                getline(cin, in);
                cout << "Введите путь к файлу для результата: ";
                getline(cin, out);
                cout << "Введите путь к файлу для хранения ключей: ";
                getline(cin, keys);
                encrypt_file(in, out, keys);
            }
            else if (command == 2) {
                string in, out, key_file;
                cout << "Введите путь к исходному файлу: ";
                getline(cin, in);
                cout << "Введите путь к файлу для результата: ";
                getline(cin, out);
                cout << "Введите путь к файлу с ключами: ";
                getline(cin, key_file);

                ifstream keys(key_file);
                if (!keys) {
                    throw runtime_error("Не удалось открыть файл с ключами.");
                }

                string line;
        	getline(keys, line);    
	    	uint64_t d, n;
		keys >> d >> n;
                decrypt_file(in, out, d, n);
            }
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }
    else if (mode == InputMode::TEXT) {
try {
            cout << "1. Шифровать текст\n2. Дешифровать текст\nВыберите действие: ";
            if (!(cin >> command)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Ошибка: введено нечисловое значение!");
            }

            validateInput(command);
            cin.ignore();

            string text;
            cout << "Введите текст: ";
            getline(cin, text);

            if (command == 1) {
                uint64_t e, d, n;
                gen_keys(e, d, n);
                string encrypted = encrypt_text(text, e, n);
                cout << "Открытый ключ (e, n): " << e << ", " << n << endl;
                cout << "Закрытый ключ (d, n): " << d << ", " << n << endl;
                cout << "Зашифрованный текст: " << encrypted << endl;
            } else if (command == 2) {
                 uint64_t d, n;
                cout << "Введите закрытый ключ d: ";
                cin >> d;
                cout << "Введите модуль n: ";
                cin >> n;
                cin.ignore();
                string decrypted = decrypt_text(text, d, n);
                cout << "Расшифрованный текст: " << decrypted << endl;
            }
        } catch (const exception& e) {
            cerr << "ОШИБКА: " << e.what() << endl;
        }
    }
}
