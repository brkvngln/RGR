#include "rsa.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool prime(uint64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (uint64_t i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

uint64_t gen_prime() {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dist(1000, 10000);
    uint64_t p;
    while (!prime(p = dist(gen)));
    return p;
}

uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

uint64_t pow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

void gen_keys(uint64_t& e, uint64_t& d, uint64_t& n) {
    uint64_t p = gen_prime();
    uint64_t q = gen_prime();
    while (q == p) q = gen_prime();
    n = p * q;
    uint64_t phi = (p - 1) * (q - 1);
    e = 65537;
    while (gcd(e, phi) != 1) e++;
    for (d = 2; d < phi; d++)
        if ((e * d) % phi == 1)
            break;
}

string encrypt_text(const string& text, uint64_t e, uint64_t n) {
    stringstream result;
    for (char ch : text) {
        uint64_t encrypted = pow(static_cast<uint8_t>(ch), e, n);
        result << encrypted << ' ';
    }
    return result.str();
}

string decrypt_text(const string& text, uint64_t d, uint64_t n) {
    stringstream result;
    stringstream ss(text);
    uint64_t num;
    while (ss >> num) {
        uint8_t decrypted = static_cast<uint8_t>(pow(num, d, n));
        result << decrypted;
    }
    return result.str();
}

void encrypt_file(const string& input_file, const string& output_file,
    const string& key_file) {
	setlocale(LC_ALL,"ru_RU.UTF-8");
	uint64_t e, d, n;
    gen_keys(e, d, n);
    ifstream in(input_file, ios::binary);
    ofstream out(output_file, ios::binary);
    ofstream keys(key_file);
    char ch;
    while (in.get(ch)) {
        uint64_t encrypted = pow(static_cast<uint8_t>(ch), e, n);
        out << encrypted << ' ';
    }
    keys << e << ' ' << n << endl
        << d << ' ' << n;
    cout << "Щифрование завершено. Результат сохранен в " << output_file << endl
	    << "Ключи сохранены в " << key_file << endl;
}

void decrypt_file(const string& input_file, const string& output_file,
    uint64_t d, uint64_t n) {
    ifstream in(input_file);
    ofstream out(output_file, ios::binary);
    uint64_t num;
    setlocale(LC_ALL,"ru_RU.UTF-8");
    while (in >> num) {
        uint8_t decrypted = static_cast<uint8_t>(pow(num, d, n));
        out << decrypted;
    }
    cout << "Дешифрование завершено. Результат сохранен в " << output_file << endl;
}
