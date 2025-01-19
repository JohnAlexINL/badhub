void run(const char *command){
    printf("\e[0;32m ... %s", command);
    printf(" \e[0;31m\n");
    int result = system(command);
    if (result != 0) { printf("Error code %d\n", result%255); exit(1); }   
    printf("\e[0m"); return;
}

void run_ignore(const char *command) {
    printf("\e[0;32m ... %s", command);
    printf(" \e[0;31m\n");
    system(command);
    printf("\e[0m"); return;
}