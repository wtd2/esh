#ifndef EXEC_H
#define EXEC_H

#include <vector>

using namespace std;

class Command {
    public:
        char *path;
        char **argv;

        Command(char *path, char *argv[]);
        ~Command();
};  

#endif