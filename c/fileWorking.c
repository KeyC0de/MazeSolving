#include <stdio.h>
#include "fileWorking.h"

// count Lines of a file
size_t countLinesOfFile(char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    char ch;
    size_t lines = 0;
    do {
        ch = fgetc(fp);
        if(ch == '\n')
            lines++;
    } while (ch != EOF);
    //while (!feof(fp))

    
    fclose(fp);
    return lines;
}

// assuming that the file has equal number of columns for all its lines
// (or just 1 line)
size_t countColumnsOfFile(char *fileName)
{
    FILE *fp = fopen(fileName, "r");
    char ch = fgetc(fp);
    size_t columns = 0;
    while (ch != '\n' && ch != '\r') { // we only want to count one line so which ever comes first{
        ch = fgetc(fp);
        columns++;
    } 
    columns--;
    //feof(fp) = found end of file, returns non zero(true) if found

    fclose(fp);
    return columns;
}
