#include "esh.h"
#include "shell.h"
#include "exec.h"
#include "parse.h"

using namespace std;

Command* create_command(vector<char*> tokens) {
    char *path = tokens[0];
    char **argv = (char**)malloc(sizeof(char*) * (tokens.size()));
    
    for (int i=1; i<tokens.size(); ++i) {
        argv[i-1] = tokens[i];
    }
    argv[tokens.size()-1] = NULL;
    
    return new Command(path, argv);
}

vector<Command*> parse(char *line) {   
    vector<Command*> cmds;
    vector<char*> tokens; // passed to commands, do not free here except that a parsing error occurs
    char* token; // this is produced by strdup which uses malloc, need to be freed
    char* str = line;
    
    do{
        int p=strspn(str, " ");
        if (p==strlen(str)) break;
        str += p;
        int ret = parse_token(&str, &token);
        if (ret==1) {// separator
            if (tokens.size()){
                cmds.push_back(create_command(tokens));
                tokens.clear();
            }
        }else if (ret==0) {
            tokens.push_back(strdup(token));
        }else{// error
            esh_free_str(&token);
            for (int i=0; i<tokens.size(); ++i) esh_free_str(&tokens[i]);//cleanup
            tokens.clear();
            esh_println_str("abort", 1);
            break;
        }
        esh_free_str(&token);
    } while (strlen(str)>0);

    if (tokens.size()) {
        cmds.push_back(create_command(tokens));
    }

    return cmds;
}