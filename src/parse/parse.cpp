#include "esh.h"
#include "shell.h"
#include "exec.h"
#include "parse.h"

using namespace std;

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
            // do something
        }
    }

    if (is_quote(str[0])) {
        char *other = strchr(str+1, str[0]);
        if (other) {
            (*token) = strndup(str+1, other-str-1);
            (*p_str) += other-str+1;
        }else { // invliad quote
            // do something
        }
    } else {
        int p = strcspn(str, " \t\n;&|");
        (*token) = strndup(str, p);
        (*p_str) += p;
    }

    return 0;
}

Command create_command(vector<char*> tokens) {
    char *path = tokens[0];
    char **argv = (char**)malloc(sizeof(char*) * (tokens.size()+1));
    
    for (int i=1; i<tokens.size(); ++i) {
        argv[i-1] = tokens[i];
    }
    argv[tokens.size()] = NULL;
    
    return Command(path, argv);
}

vector<Command> parse(char *line) {   
    vector<Command> cmds;
    vector<char*> tokens; // passed to commands, do not free here
    char* token; // this is produced by strdup which uses malloc, need to be freed
    char* str = line;
    
    int n=0;
    do{
        int p=strspn(str, " ");
        if (p==strlen(str)) break;
        str += p;
        if (parse_token(&str, &token)) {
            if (tokens.size()){
                cmds.push_back(create_command(tokens));
                tokens.clear();
            }
        } else {
            // printf("push token \"%s\"\n", token);
            tokens.push_back(strdup(token));
        }
        esh_free_str(&token);
    } while (strlen(str)>0 && ++n<8);

    if (tokens.size()) {
        cmds.push_back(create_command(tokens));
    }

    return cmds;
}