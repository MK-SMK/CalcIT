/*
*   main.c -- Hauptroutine
*/
#include "main.h"


double memory[26];

OptEntry options[] = {
    {'h', "Zeigt diese Übersicht an."},
    {'?', "Zeigt diese Übersicht an."},
    {'i', "Zeigt Informationen über das Kompilat an."},
    {'a', "Gibt bei jeder Rechnung eine 32-bit int Binäransicht aus."},
    {'b', "Gibt bei binären Berechnungen eine 32-bit int Binäransicht aus."},
    {'x', "Gibt die hexadezimale Darstellung einer Zahl aus."}
};

void exit_handler(void) {
    write_history(HIST_FILE);
    free(input);
}

void show_help(char **argv) {
    int i;
    size_t lst_len = sizeof(options) / sizeof(options[0]);

    printf("\nBenutzung: %s <optionen>\n", *argv);
    printf("Beenden: STRG+D\n");
    printf("\nOptionen:\n");
    for(i = 0; i < lst_len; i++) {
        assert(strnlen(options[i].desc, MAX_DESC + 1) <= MAX_DESC);
        printf(" -%c\t%s\n", options[i].flag, options[i].desc);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int i, j;
    b = 0;
    
    atexit(exit_handler);
    printf("CalcIT\n");

    if(argc > 1) {
        for(i = 1; i < argc; i++) {
            j = 0;
            if(argv[i][0] != '-') {
                err(E_WARNING, "Ungültige Eingabe '%s'.\n", argv[i]);
            } else {
                while(argv[i][++j] != '\0') {
                    switch(argv[i][j]) {
                        case '?':
                        case 'h':
                            show_help(argv);
                            break;
                        case 'i':
                            printf("Version %s - Marco Konrad, Prof. Hellwig Geisse\n", VERSION);
                            printf("Der Parser basiert auf https://homepages.thm.de/~hg53/icbw-ws1617/demo-c.tar.gz von Prof. Hellwig Geisse.\n");
                            printf("Dieses Kompilat wurde am %s um %s erzeugt.\n\n", __DATE__, __TIME__);
                        case 'a':
                            b = 1;
                            break; 
                        case 'b':
                            b = 2; //info siehe general.h
                            break;
                        case 'x':
                            x = 1;
                            break;
                    }
                }
            }
        }
    }
    
    //TODO: binäre Eingaben (1010)
    for(i = 0; i < 26; i++)
        memory[i] = 0.0;
    read_history(HIST_FILE);
    while((input = readline("Term > "))) {
        if(strnlen(input, MAX_INPUT + 1) <= MAX_INPUT) {
            if(strncmp(input, "", 3) != 0)
                add_history(input);

            input[strnlen(input, MAX_INPUT)] = '\n';
            inp_pos = 0;
            
            parseList();
        } else {
            err(E_WARNING, "Es wurden mehr als die zulässigen %d Zeichen eingegeben. Bitte beschränken Sie sich auf %d Zeichen.", 
            MAX_INPUT, MAX_INPUT);
        }
    }

    printf("\n");
    return EXIT_SUCCESS;
}