#ifndef POLIBIUS_H
#define POLIBIUS_H

#include <vector>
#include <string>

#ifdef POLIBIUS_EXPORTS // Это будет определено только при сборке libpolibius.so
#define POLIBIUS_API __attribute__((visibility("default")))
#else
#define POLIBIUS_API
#endif

using namespace std;
class Polibiusquare {
private:
    vector<vector<char>> square;
    void gen_square();
    void find_char(char c, int& row, int& col) const;


public:
    POLIBIUS_API Polibiusquare();
    POLIBIUS_API void encrypts_file(const string& inpath, const string& outpath);
    POLIBIUS_API void decrypts_file(const string& inpath, const string& outpath);
    POLIBIUS_API string encrypts_text(const string& text);
    POLIBIUS_API string decrypts_text(const string& text);
};


#endif
