#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>
#include <string.h>

using namespace std;

vector<Command> parse(char *line);

// utils
char* match_separator(const char* str); // return NULL if no match

bool is_space(char c);
bool is_quote(char c);
bool is_sep(char c);

void add_quoted_word_token(vector<string> *tokens, string *p_str);

void add_sep_token(vector<string> *tokens, string *p_str);

void add_plain_word_token(vector<string> *tokens, string *p_str);

#endif