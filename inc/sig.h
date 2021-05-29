#ifndef SIG_H 
#define SIG_H

#include "signal.h"
#include "setjmp.h"

// static sigjmp_buf interupt_buf;

void signal_running(int sig);

void signal_shell(int sig);

#endif