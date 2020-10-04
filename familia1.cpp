//
// Created by eric on 04/10/2020.
//

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

int main(){
    int vida_pai = 60;
    int nasc_filho_1 = 14;
    int nasc_filho_2 = 16;
    int nasc_neto_filho_1 = 26;
    int nasc_neto_filho_2 = 30;

    pid_t pid, pid_filho1, pid_filho2;
    system("clear");
    cout << "Programa Familia de Processos" << endl;
    cout << endl << "Eu sou o processo-pai, PID " << getpid() << endl;

    for (int i = 0; i < vida_pai; ++i) {
        cout << endl << "Tempo de vida do pai " << i << "s - " << getpid() << endl;
        if (i == nasc_filho_1){
            pid = fork();
            pid_t pid_avo = getppid();
            switch (pid) {
                case -1:
                    exit(1);
                case 0:
                    cout << "Eu sou o processo-filho 1, filho de " << getppid() <<", nasci aos " << i << "s"
                    << " e meu PID eh " << getpid() << endl;
                    system("ps");
                    for (int j = 0; j < (30 - nasc_filho_1); ++j) {
                        cout << "\tTempo de vida do filho 1 " << j << "s - " << getpid() << endl;
                        if (j == (nasc_neto_filho_1 - nasc_filho_1)){
                            pid_filho1 = fork();
                            switch (pid_filho1) {
                                case -1:
                                    break;
                                case 0:
                                    cout << "Eu sou o processo-neto 1, filho de " << getppid() <<
                                    ", neto de " << pid_avo << ", nasci aos " << nasc_neto_filho_1 << "s"
                                    << " e meu PID eh " << getpid() << endl;
                                    system("ps");
                                    for (int k = 0; k < 12; ++k) {
                                        cout << "\t\tTempo de vida do neto 1 " << k << "s - " << getpid() << endl;
                                        sleep(1);
                                    }
                                    cout << "Time to die, neto 1!! (" << getpid() << ")" << endl << endl;
                                    kill(getpid(), SIGKILL);
                                    break;
                                default:
                                    cout << endl << "\tNasceu meu filho, neto de " << pid_avo << endl;
                                    cout << endl << "\tMeu PID eh " << getpid() << endl;
                                    break;
                            }
                        }
                        sleep(1);
                    }
                    cout << "Time to die, filho 1!(" << getpid() << ")" << endl << endl;
                    kill(getpid(), SIGKILL);
                    break;
                default:
                    cout << endl << "Nasceu meu primeiro filho!" << endl;
                    break;
            }
        }

        if (i == nasc_filho_2){
            pid = fork();
            pid_t pid_avo = getppid();
            switch (pid) {
                case -1:
                    exit(1);
                case 0:
                    cout << "Eu sou o processo-filho 2, filho de " << getppid() <<", nasci aos " << i << "s"
                         << "e meu PID eh " << getpid() << endl;
                    system("ps");
                    for (int j = 0; j < (30 - nasc_filho_2); ++j) {
                        cout << "\tTempo de vida do filho 2 " << j << "s - " << getpid() << endl;
                        if (j == (nasc_neto_filho_2 - nasc_filho_2)){
                            pid_filho2 = fork();
                            switch (pid_filho2) {
                                case -1:
                                    break;
                                case 0:
                                    cout << "Eu sou o processo-neto 2, filho de " << getppid() <<
                                         ", neto de " << pid_avo << ", nasci aos " << nasc_neto_filho_2 << "s"
                                         << " e meu PID eh " << getpid() << endl;
                                    system("ps");
                                    for (int k = 0; k < 18; ++k) {
                                        cout << "\t\tTempo de vida do neto 2 " << k << "s - " << getpid() << endl;
                                        sleep(1);
                                    }
                                    cout << "Time to die, neto 2!! (" << getpid() << ")" << endl;
                                    kill(getpid(), SIGKILL);
                                    break;
                                default:
                                    cout << endl << "\tNasceu meu filho, neto de " << pid_avo << endl;
                                    cout << endl << "\tMeu PID eh " << getpid() << endl;
                                    break;
                            }
                        }
                        sleep(1);
                    }
                    cout << "Time to die, filho 2!!(" << getpid() << ")" << endl;
                    kill(getpid(), SIGKILL);
                    break;
                default:
                    cout << endl << "Nasceu meu segundo filho!" << endl;
                    break;
            }
        }
        sleep(1);
    }
    cout << "Agora eh o pai quem vai dizer:  Time to die!(" << getpid() << ")" << endl;
    return 0;
}