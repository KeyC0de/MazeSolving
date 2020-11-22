#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
#include "queue_llist.h"
#include "file_working.h"

#define true  1
#define false 0

// '.' = open position
// '#' = blocked
// 'S' = starting position
// 'G' = goal
// '=' = trace correct path

//// traverse rows with y = vertical Coordinate   ////
//// &     columns with x = horizontal Coordinate ////
void displayMaze( size_t rows,
	size_t columns,
	std::vector<std::vector<qType>>& maze )
{
    size_t y, x;
	for ( y = 0; y < rows; y++ )
	{
        for ( x = 0; x < columns; x++ )
		{
            if ( maze[y][x].inPath
				&& maze[y][x].ch != 'S' )
			{
				maze[y][x].ch = '=';
			}
			printf( "%c", maze[y][x].ch );
        }
        printf( "\n" );
	}
	printf( "\n\n" );
}


// solves a given maze
bool solveMazeBFS( char *fileName )
{
    // Read amount of rows and columns from the file which depicts the maze
    size_t rows = countLinesOfFile( fileName );
    size_t columns = countColumnsOfFile( fileName );

    //printf("\nrows = %d columns = %d\n", rows, columns); // for debugging

    // declare a pointer to an array of type qType (the type that will rests inside the queue
    // with number of rows and columns evaluated at runtime
	std::vector<std::vector<qType>> maze( rows, std::vector<qType>( columns ) );

    // 1. Create & Initialize Queue
	Queue Q;
	initQueue(&Q);

    // 2. Now read maze from file and store it in "maze"
    FILE *fp = fopen( fileName, "r" );
    if ( fp ) {
        size_t x = 0, y = 0;
        //size_t length = 0;
        char ch;

        // 3. Populate maze char array with file contents
        while( ( ch = (char)fgetc( fp ) ) != EOF )
		{
            // CR and LF characters are captured together (if working on Windows environment)
            // and counted as one char using '\n'
            if ( ch == '\n' )
			{
                y++;
				x = 0;
            }
            else
			{
                maze[y][x].ch = ch;
                maze[y][x].horizCoord = x;
                maze[y][x].vertCoord = y;
                maze[y][x].visited = false;
                maze[y][x].inPath = false;

                // Enqueue starting position
                if ( maze[y][x].ch == 'S' )
				{
                    enqueue( maze[y][x], &Q );
				}
                x++;
            }
            //length++; // length of file (including '\n' & special characters)
        } // O(rows * columns)
        fclose(fp);
    }

    printf( "*** MAZE - Iteration ***\n" );
	displayMaze( rows,
		columns,
		maze );

    qType current;  // current square
    int y, x;       // current coordinates in the maze

    // 4. Iteration
	while( !isEmpty( &Q ) )
	{
        // 4.1 Dequeue Node(s) from the Queue, until we reach a start Node which denotes the end of that path
        current = peek( &Q );

        std::vector<qType> arr( rows * columns ); // hopefully it is big enough
        int count = 0; // array element count
        do
		{
            arr[count] = dequeue( &Q );
        } while (arr[count++].ch != 'S');

        // 4.2 If we reached the goal stop the iteration
        if ( current.ch == 'G' )
		{
            // 4.2.1 Mark correct path, those squares until the first 'S' square
            while( --count )
			{
                qType temp = arr[count];
                maze[temp.vertCoord][temp.horizCoord].inPath = true;
            }

            displayMaze( rows,
				columns,
				maze );  // display the solution
            return true;    // job done
        }


        x = current.horizCoord;
        y = current.vertCoord;
        // 4.4 Examine the Von Neumann neighborhood of the current square in the maze.
        //     Enqueue squares not visited previously
        //     (with Bounds checking - for each neighbour)

        // Western neighbour //
        if ( x - 1 >= 0 )
		{// bounds checking
            if ( ( maze[y][x - 1].ch == '.'
				|| maze[y][x - 1].ch == 'G' )
				&& !maze[y][x - 1].visited )
			{
				// 4.4.1 enqueue new valid neighbour
                enqueue( maze[y][x - 1], &Q );
                for ( int i = 0; i < count; i++ )
				{// 4.4.2 enqueue previous path
                    enqueue( arr[i], &Q );
                }
            }
        }
        // Northern neighbour //
        if ( y - 1 >= 0 )
		{
            if ( ( maze[y - 1][x].ch == '.'
				|| maze[y - 1][x].ch == 'G' )
				&& !maze[y - 1][x].visited )
			{
                enqueue( maze[y - 1][x], &Q );

                // enqueue previous path
                for ( int i = 0; i < count; i++ )
				{ // enqueue previous path
                    enqueue( arr[i], &Q );
                }
            }
        }
        // Southern neighbour //
        if ( y + 1 < rows )
		{
            if ( ( maze[y + 1][x].ch == '.'
				|| maze[y + 1][x].ch == 'G' )
				&& !maze[y + 1][x].visited )
			{
                enqueue( maze[y + 1][x], &Q );

                // enqueue previous path
                for ( int i = 0; i < count; i++ )
				{// enqueue previous path
                    enqueue( arr[i], &Q );
                }
            }
        }
        // Eastern neighbour //
        if ( x + 1 < columns )
		{
            if ( ( maze[y][x + 1].ch == '.'
				|| maze[y][x + 1].ch == 'G' )
				&& !maze[y][x + 1].visited )
			{
                enqueue( maze[y][x + 1], &Q );

                // enqueue previous path
                for ( int i = 0; i < count; i++ )
				{// enqueue previous path
                    enqueue(arr[i], &Q);
                }
            }
        }

        maze[y][x].visited = true;
	}

	return false;
}


int main( int argc,
	char *argv[] )
{
    char* mazeFilePath = nullptr;
    if ( argc == 2 )
	{
        mazeFilePath = argv[1];
	}
    else
	{
        printf( "Specify the name of the file.\n" );
        return -1;
    }

	if ( solveMazeBFS( mazeFilePath ) )
	{
		printf( "Solution exists!\n" );
	}
	else
	{
		printf( "Solution does not exist.\n" );
	}

	std::system( "pause" );
	return 0;
}
