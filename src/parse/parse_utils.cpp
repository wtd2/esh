#include "esh.h"
#include "shell.h"
#include "exec.h"
#include "parse.h"

const char* separators[] = {
    ";", "&&", "|", "<", "<<", ">", ">>", NULL
};

char* match_separator(const char* str) {
    int sep_len = strspn(str, ";&|");
    for (int i=0; separators[i]; ++i) {
        if (strncmp(str, separators[i], sep_len)==0 && sep_len==strlen(separators[i])){
            return (char*)separators[i];
        }
    }
    return NULL;
}

bool is_space(char c) {
    return c==' ' || c=='\t' || c=='\n';
}

bool is_quote(char c) {
    return c=='\"' || c=='\'';
}

bool is_sep(char c) {
    return c==';' || c=='&' || c=='|' || c=='<' || c=='>';
}

