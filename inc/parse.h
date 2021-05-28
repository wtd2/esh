#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>
#include <string.h>

using namespace std;

vector<Command*> parse(char *line);

// parsing utils
char* match_separator(const char* str); // return NULL if no match

bool is_space(char c);
bool is_quote(char c);
bool is_sep(char c);

int parse_token(char **p_str, char **token); // return 1 if the token is a separator

#endif