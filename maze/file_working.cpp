#include <cstdio>
#include "file_working.h"


// access function to open a file cross platform method
int doesFileExist( FILE* fp )
{
	if ( ( fp = fopen( "sample.txt", "r" ) ) != nullptr )
	{
		// file exists
		//if (fopen("sample.txt", "r")){// file exists
		fclose(fp);
		return 1;
	}
	else {
		return 0; //File not found
	}
}

// count lines of a file
size_t countLinesOfFile( char* fileName )
{
	FILE *fp = fopen( fileName, "r" );
	char ch;
	size_t lines = 1; // every file starts from line #1

	do
	{
		ch = fgetc( fp );
		if( ch == '\n' )
		{
			++lines;
		}
	} while ( ch != EOF );
	//while ( !feof( fp ) )

	fclose( fp );
	return lines;
}

// assuming that the file has equal ammount of columns
// calculate columns of a file (maximum ammount of columns in any given line)
size_t countColumnsOfFile( char* fileName )
{
	FILE *fp = fopen( fileName, "r" );
	char ch = ' ';
	size_t columns = 0;

	while ( ch != '\n' && ch != EOF )
	{
		ch = fgetc(fp);
		columns++;
	}
	// note that #(chars in the line) = #(columns) - 1

	fclose( fp );
	return columns;
}

// counts digits, white space, others
void countLetterOccurences( char* filename )
{
	int c, i, nwhite, nother;
	int ndigit[10];
	int nchar[26] = {0};
	nwhite = nother = 0;

	FILE* fd = fopen( filename, "r" );

	for ( i = 0; i < 10; ++i )
	{
		ndigit[i] = 0;
	}

	// iterate through file
	while ( ( c = fgetc( fd ) ) != EOF )
	{
		if ( c >= '0' && c <= '9' )
			++ndigit[c-'0'];
		else if ( c >= 'a' && c <= 'z' )
			++nchar[c-'a'];
		else if ( c >= 'A' && c <= 'Z' )
			++nchar[c-'A'];
		else if ( c == ' ' || c == '\n' || c == '\r' || c == '\t' )
			++nwhite;
		else
			++nother;
	}

	// print results
	printf( "digits:\n" );
	for ( i = 0; i < 10; ++i )
		printf( "%5d", i );
	printf( "\n" );
	for ( i = 0; i < 10; ++i )
		printf( "%5d", ndigit[i] );
	printf( "\nCharacter (case insensitive):\n" );
	for ( i = 0; i < 13; ++i )
		printf( "%5c", 'a' + i );
	printf( "\n" );
	for ( i = 0; i < 13; ++i)
		printf( "%5d", nchar[i] );
	printf( "\n" );
	for ( i = 13; i < 26; ++i)
		printf( "%5c", 'a' + i );
	printf( "\n" );
	for ( i = 13; i < 26; ++i)
		printf( "%5d", nchar[i] );
	printf( "\n" );
	printf( "\nwhite space = %d, other = %d\n", nwhite, nother );
}