#include "esh.h"
#include "shell.h"
#include "exec.h"
#include "parse.h"

#include <fcntl.h>

using namespace std;

Command* create_command(
    vector<char*> tokens, 
    char* sep,
    char* in_file,
    char* out_file,
    char* error_file,
    bool append) 
{
    char *path = strdup(tokens[0]);
    char **argv = (char**)malloc(sizeof(char*) * (tokens.size()+1));
    
    for (int i=0; i<tokens.size(); ++i) {
        argv[i] = tokens[i];
    }
    argv[tokens.size()] = NULL;
    
    if (in_file) in_file = strdup(in_file);
    if (out_file) out_file = strdup(out_file);
    if (error_file) error_file = strdup(error_file);

    return new Command(
        path, argv, sep, 
        in_file, out_file, error_file, append);
}

vector<Command*> parse(char *line) {   
    vector<Command*> cmds;

    vector<char*> args; // passed to commands, do not free here except that a parsing error occurs

    char *in_file = NULL;
    char *out_file = NULL; bool append=false;
    char *error_file = NULL;

    char* token; // this is produced by strdup which uses malloc, need to be freed
    char* str = line;
    
    do{
        int p=strspn(str, " ");
        if (p==strlen(str)) break;
        str += p;
        int ret = parse_token(&str, &token);
        esh_println_str(token, 1);
        if (ret==1) {// separator
            cmds.push_back(
                create_command(args, strdup(token), 
                in_file, out_file, error_file, 
                append));
            args.clear();
            esh_free_str(&in_file);
            esh_free_str(&out_file);
            esh_free_str(&error_file);
        }else if (ret>=2){// redirect
            p=strspn(str, " ");
            if (p==strlen(str)) break;
            str += p;
            parse_token(&str, &token);
            if (ret==2) in_file = strdup(token);
            else {
                out_file = strdup(token);
                if (ret==3) append=false;
                if (ret==4) append=true;
            }
        }
        else if (ret==0) {// argument
            args.push_back(strdup(token));
        }
        else{// error
            esh_free_str(&token);
            for (int i=0; i<args.size(); ++i) esh_free_str(&args[i]);//cleanup
            args.clear();
            esh_println_str("abort", 1);
            break;
        }
        esh_free_str(&token);
    } while (strlen(str)>0);

    if (args.size()) {
        cmds.push_back(create_command(args, NULL, in_file, out_file, error_file, append));
    }

    return cmds;
}