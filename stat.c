#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <math.h>

//There is a function called stat.
//It is used to get information about a file.
//With your table partner, write a program that
//uses stat to display the following information
//about a file:
//file size
//mode (permissions)
//time of last access (displayed in the following
//format: Fri Oct 28 09:03:01 2016
//Added 10/31. In the same file:
//Modify the size so it is printed out in
//human readable form (that is using B, KB, MB, GB).
//Attempt to print out the permissions in
//ls -l form, ignoring the early bits that
//include the file type information (the
//permissions section of the mode is stored
//in the last 9 bits of the data type).

int main() {
    umask(0000);
    int f;
    f = open("./randomfile", O_CREAT | O_RDWR, 0644);
    umask(0022);
    struct stat *buffer = (struct stat *) malloc(sizeof(struct stat));
    write(f, "random text", 22);
    stat("./randomfile", buffer);
    close(f);
    //file size, B, KB, MB, GB.
    float size;
    size = buffer->st_size;
    printf("NON MODIFIED SIZE: %f\n", size);
    char *sizetype;
    if (size < 1000) {
        sizetype = "B";
    }
    else if (size < 1000000) {
        sizetype = "KB";
        size = size / 1000.0;
    }
    else if (size < 1000000000) {
        sizetype = "MB";
        size = size / 1000000.0;
    }
    else if (size < 1000000000000) {
        sizetype = "GB";
        size = size / 1000000000.0;
    }
    printf("--- size: %.4f %s\n", size, sizetype);
    //permissions
    int perms;
    perms = buffer->st_mode;
    perms %= 512;
    printf("--- perms in NON ls-l form: %o\n", perms);
    //time of last access
    time_t lastime;
    lastime = buffer->st_atime;
    char *formattedtime = ctime(&lastime);
    printf("--- time last accessed: %s", formattedtime);
    printf("didn't succeed in ls -l other form..\n");
    printf("but am studying the code of others who did / am researching.\n");
    //perms in ls -l form.
    char permisions[10] = "-";
    int x = 2;
    //for(; x < 4, x++) {
        //int permoctal = perms/pow(8, 3 - x);
        //printf("permoctal octal: %o, int %d", permoctal, permoctal);
    //}
        //if (permoctla > 3)
    return 0;
}
