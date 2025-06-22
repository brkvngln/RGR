#ifndef CODE_WORD_H
#define CODE_WORD_H

#include <iostream>
#include <vector>
#include <string>

#ifdef CODE_WORD_EXPORTS
#define CODE_WORD_API __attribute__((visibility("default")))
#else
#define CODE_WORD_API
#endif

using namespace std;

CODE_WORD_API void xorr(vector<unsigned char>& data, const string& key);
CODE_WORD_API bool process_file(const string& input, const string& output, const string& key);
CODE_WORD_API string process_text(const string& text, const string& key);
#endif
