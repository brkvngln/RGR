#ifndef RSA_H
#define RSA_H
#include <cstdint>
#include <string>

#ifdef RSA_EXPORTS
#define RSA_API __attribute__((visibility("default")))
#else
#define RSA_API
#endif

using namespace std;
RSA_API bool prime(uint64_t n);
RSA_API uint64_t gen_prime();
RSA_API uint64_t gcd(uint64_t a, uint64_t b);
RSA_API uint64_t pow(uint64_t base, uint64_t exp, uint64_t mod);
RSA_API void gen_keys(uint64_t& e, uint64_t& d, uint64_t& n);
RSA_API void encrypt_file(const string& input_file, const string& output_file, const string& key_file);
RSA_API void decrypt_file(const string& input_file, const string& output_file, uint64_t d, uint64_t n);
RSA_API string encrypt_text(const string& text, uint64_t e, uint64_t n);
RSA_API string decrypt_text(const string& text, uint64_t d, uint64_t n);
#endif
