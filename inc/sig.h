#ifndef SIG_H
#define SIG_H

#include "setjmp.h"
#include "signal.h"

void signal_running(int sig);

void signal_shell(int sig);

#endif