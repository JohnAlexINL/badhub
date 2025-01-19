#define ERROR -1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "file.c"
#include "merge.c"
#include "run.c"

const char *gh_rm =       "rm -rf ./.ignore/gh";
const char *gh_empty =    "rm -rf ./*";
const char *gh_mkdir =    "mkdir -p ./.ignore && mkdir -p ./.ignore/gh";
const char *gh_pull =     "git clone %s ./.ignore/gh";
const char *gh_commit =   "git add . && git commit -m %s";
const char *gh_cp =       "rm -rf ./.ignore/gh/* && find . -type f ! -path './.ignore/*' -exec cp {} .ignore/gh/ \\;";
const char *gh_cd =       "cd ./.ignore/gh";
const char *gh_push =     "git push -u origin main";
const char *gh_ret =      "cd ../..";

int main (int argc, char **argv) {
    if ( argc == 2 ) { if (argv[1][0] =='-' ) { printf("badhub version 0.0.0, Modula.dev\nquick usage: badhub {commit message}\n"); exit(0); }}
    if ( argc < 2 ) { printf("badhub expects a commit message\n"); exit(ERROR); }
    
    if ( argc == 3 ) {
        if (strcmp(argv[1], "gh")==0) {
            char *url = argv[2];
            char pull_command[512]; sprintf(pull_command, gh_pull, url);
            file_write("./.ignore/.url", url, strlen(url));
            run_ignore(gh_rm);
            run(gh_mkdir);
            run(pull_command);
            exit(0);
        }
    }

    char *message = merge(argc, argv);
    char url[512]; file_read("./.ignore/.url", url, sizeof(url));
    char commit_command[512]; sprintf(commit_command, gh_commit, message);
    run(gh_cp);
    run(gh_cd);
    run(gh_empty);
    run(commit_command);
    run(gh_push);
    exit(0);
}