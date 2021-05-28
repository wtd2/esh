#ifndef EXEC_H
#define EXEC_H

#include <vector>

using namespace std;

class Command {
    public:
        char *path;
        char **argv;

        char *sep;
        char *in_file;
        char *out_file;

        Command(char *path, char *argv[], char *sep, char *in_file, char *out_file);
        ~Command();
};  

#endif