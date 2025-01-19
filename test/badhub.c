#define ERROR -1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "file.c"
#include "merge.c"
#include "run.c"

const char *gh_delete =   "rm -rf ./.ignore/gh";
const char *gh_mkdir =    "mkdir -p ./.ignore && mkdir -p .ignore/gh";
const char *gh_clone =    "git clone %s ./.ignore/gh";
const char *gh_clear =    "rm -rf ./.ignore/gh/*";
const char *gh_copy =     "cp * ./.ignore/gh -r";
const char *gh_move =     "cd ./.ignore/gh";
const char *gh_commit =   "git add -f . && git commit -m \"%s\"";
const char *gh_push =     "git push";

int main (int argc, char **argv) {
    if ( argc == 2 ) { if (argv[1][0] =='-' ) { printf("badhub version 0.0.0, Modula.dev\nquick usage: \n    badhub remote {url}\n    badhub {commit message}\n"); exit(0); }}
    if ( argc < 2 ) { printf("badhub expects a commit message\n"); exit(ERROR); }
    
    if ( argc == 3 ) {
        if (strcmp(argv[1], "remote")==0) {
            char *url = argv[2];
            run_ignore(gh_mkdir);
            int code = file_write(".ignore/.url", url, strlen(url));
            if (code == false) { printf("badhub unable to write to .ignore/.url\n"); exit(1); }
            exit(0);
        }
    }

    char *message = merge(argc, argv);
    if ( file_exists(".ignore/.url") == false ) { printf("badhub expects a remote. run `badhub remote {url}\n"); exit(1); }
    char remote[512]; file_read(".ignore/.url", remote, sizeof(remote));

    char gh_clone_command[512]; sprintf(gh_clone_command, gh_clone, remote);
    char gh_commit_command[512]; sprintf(gh_commit_command, gh_commit, message);

    run_ignore(gh_delete);
    run_ignore(gh_mkdir);
    run(gh_clone_command);
    run_ignore(gh_clear);
    run(gh_copy);
    run(gh_move);
    run(gh_commit_command);
    run(gh_push);

}