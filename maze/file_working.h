#pragma once

int doesFileExist(FILE* fp);
size_t countLinesOfFile(char *fileName);
size_t countColumnsOfFile(char *fileName);
void wc(char* filename);
void countLetterOccurences(char* filename);
int fileCopy(char* inFileName, char* outFileName);
int cat(int argc, char* argv[]);
void cpy (FILE* ifp, FILE* ofp);
int redirectIo();

