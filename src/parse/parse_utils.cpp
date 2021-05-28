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

int parse_token(char **p_str, char **token) {
    char *str = *p_str;
    // printf("parse *%s*\n", str);
    if (is_sep(str[0])) {
        char *sep = match_separator(str);
        if (sep) {
            (*token) = strdup(sep);
            (*p_str) += strlen(sep);
            return 1;
        }else { // invalid sep
            esh_println_str("error: invalid seperator", 2);
            return -1;
        }
    }

    if (is_quote(str[0])) {
        char *other = strchr(str+1, str[0]);
        if (other) {
            (*token) = strndup(str+1, other-str-1);
            (*p_str) += other-str+1;
        }else { // invliad quote
            esh_println_str("error: unpaired quote", 2);
            return -1;
        }
    } else {
        int p = strcspn(str, " \t\n;&|");
        (*token) = strndup(str, p);
        (*p_str) += p;
    }

    return 0;
}