#ifndef MODES_H
#define MODES_H

#include <string>
#include "rsa.h"
#include "polibius.h"
#include "code_word.h"

using namespace std;

#ifdef MODES_EXPORTS
#define MODES_API __attribute__((visibility("default")))
#else
#define MODES_API
#endif

enum class InputMode { FILE, TEXT, UNKNOWN };

MODES_API InputMode get_input_mode();
MODES_API void handle_polibius();
MODES_API void handle_code_word();
MODES_API void handle_RSA();
MODES_API void save_to_file(const string& filename, const string& content);

#endif
