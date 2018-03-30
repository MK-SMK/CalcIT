/*
* function.c -- Funktionserweiterungen
*/

//TODO: IP converter
#include "function.h"

char **argv;

void *malloc_argv(void) {
    int i;

    argv = malloc(MAX_ARGS * sizeof(char *));

    for(i = 0; i < MAX_ARGS; i++) {
        argv[i] = malloc((MAX_INPUT + 1) * sizeof(char));
    }

    return argv;
}

void free_argv(void) {
    int i;

    for(i = 0; i < MAX_ARGS; i++)
        free(argv[i]);

    free(argv);
}

SemanticValue test(void) {
    SemanticValue value;
    value.value = 1.0;
    int i;

    printf("Testfunktion erfolgreich ausgeführt.\n");
    printf("Erkannte Parameter:\n");
    for(i = 0; i < MAX_ARGS; i++) {
            if(argv[i][0] == '\0')
                break;
            printf("%02d: %s\n", i + 1, argv[i]);
        }

    return value;
}

SemanticValue app_exit(void) {
    SemanticValue value;
    value.value = 1.0;

    exit(0);
}

SemanticValue app_show_help(void) {
    SemanticValue value;
    value.value = 1.0;
    char **myarg;
    myarg = malloc(sizeof(char *));
    myarg[0] = malloc(sizeof("./calcit"));
    myarg[0] = "./calcit";

    show_help(myarg);
    return value;
}

SemanticValue app_show_info(void) {
    SemanticValue value;
    value.value = 1.0;
    
    printf("Version %s - Marco Konrad, Prof. Hellwig Geisse\n", VERSION);
    printf("Der Parser basiert auf https://homepages.thm.de/~hg53/icbw-ws1617/demo-c.tar.gz von Prof. Hellwig Geisse.\n");
    printf("Dieses Kompilat wurde am %s um %s erzeugt.\n\n", __DATE__, __TIME__);

    return value;
}

SemanticValue execFunc(const char *funcName) {
    SemanticValue value;
    value.isErr = 1;

    if(strncmp(funcName, "test", MAX_INPUT + 1) == 0) {
        return test();
    }
    if(strncmp(funcName, "exit", MAX_INPUT + 1) == 0) {
        return app_exit();
    }
    if(strncmp(funcName, "help", MAX_INPUT + 1) == 0) {
        return app_show_help();
    }
    if(strncmp(funcName, "info", MAX_INPUT + 1) == 0) {
        return app_show_info();
    }

    err(E_PARSE, "Unbekannte Funktion '%s'.", funcName);

    return value;
}