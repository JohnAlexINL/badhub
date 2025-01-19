char *merge(int argc, char **argv) {
    int len = 0; int i; // get len of argv
    for (i=1; i < argc; ++i) { len += strlen(argv[i]) + 1; }
    char *result = malloc(len); result[0] = '\0'; // prep empty
    for (int i = 1; i < argc; ++i) {
        strcat(result, argv[i]);
        if (i < argc - 1) { strcat(result, " "); }
    }   return result;
}