#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue_llist.h"
#include "myMath.h"
#include "fileWorking.h"

#define true  1
#define false 0

void displayMaze (size_t rows, size_t columns, qType array[rows][columns]);
_Bool solveMazeBFS(char *fileName);


void arr_alloc (size_t x, size_t y, qType(**ptr)[x][y])
{
    *ptr = malloc( sizeof(qType[x][y]) ); // allocate a true 2D array
    assert(*ptr != NULL);
}


int main(int argc, char **argv)
{
    char *mazeFile = NULL;
    if (argc == 2)
        mazeFile = argv[1];
    else {
        printf("Specify the name of the file.\n");
        return -1;
    }

	if (solveMazeBFS(mazeFile))
		printf("Solution exists!\n");
	else
		printf("Solution does not exist.\n");

	return 0;
}


// Solves a given maze
_Bool solveMazeBFS(char *fileName)
{
    // Read amount of rows and columns from the file which depicts the maze
    size_t rows     = countLinesOfFile  (fileName);
    size_t columns  = countColumnsOfFile(fileName);

    //printf("\nrows = %d columns = %d\n", rows, columns); // for debugging

    // declare a pointer to an array of type qType (the type that will rests inside the queue
    // with number of rows and columns evaluated at runtime
    qType (*maze)[rows][columns];
    // allocate this array on the heap. Although this is now a true 2d array, which is contiguously allocated
    // This is NOT a typical malloc approach of pointers to pointers to qType(s)
    arr_alloc(rows, columns, &maze);
    // Now maze will (point to /) hold the container for the given maze and all its attributes

    // 1. Create & Initialize Queue
	Queue Q;
	initQueue(&Q);

    // 2. Now read maze from file and store it in "maze"
    FILE *fp = fopen(fileName, "r");
    if (fp) {
        size_t x = 0, y = 0;
        //size_t length = 0;
        char ch;

        // 3. Populate maze char array with file contents
        while((ch = (char)fgetc(fp)) != EOF) {
            // CR and LF characters are captured together (if working on Windows environment)
            // and counted as one char using '\n'
            if (ch == '\n') {
                y++; x = 0;
            }
            else {
                (*maze)[y][x].ch = ch;
                (*maze)[y][x].horizCoord = x;
                (*maze)[y][x].vertCoord = y;
                (*maze)[y][x].visited = false;
                (*maze)[y][x].inPath = false;

                // Enqueue starting position
                if ((*maze)[y][x].ch == 'S')
                    enqueue((*maze)[y][x], &Q);

                x++;
            }
            //length++; // length of file (including '\n' & special characters)
        } // O(rows * columns)

        fclose(fp);
    }

    printf("*** MAZE - Iteration ***\n");
	displayMaze(rows, columns, *maze);

    qType current;  // current square
    int y, x;       // current coordinates in the maze

    // 4. Iteration
	while (!isEmpty(&Q)) {
        // 4.1 Dequeue Node(s) from the Queue, until we reach a start Node which denotes the end of that path
        current = peek(&Q);

        qType arr[rows * columns]; // hopefully it is big enough
        int count = 0; // array element count
        do {
            arr[count] = dequeue(&Q);
        } while (arr[count++].ch != 'S');

        // 4.2 If we reached the goal stop the iteration
        if (current.ch == 'G'){
            // 4.2.1 Mark correct path, those squares until the first 'S' square
            while(--count) {
                qType temp = arr[count];
                (*maze)[temp.vertCoord][temp.horizCoord].inPath = true;
            }

            displayMaze(rows, columns, *maze);  // display the solution
            free(maze);                         // free the entire array
            return true;    // job done
        }


        x = current.horizCoord;
        y = current.vertCoord;
        // 4.4 Examine the Von Neumann neighborhood of the current square in the maze.
        //     Enqueue squares not visited previously
        //     (with Bounds checking - for each neighbour)

        // Western neighbour //
        if (x - 1 >= 0) { // bounds checking
            if ( ((*maze)[y][x - 1].ch == '.' || (*maze)[y][x - 1].ch == 'G') && !(*maze)[y][x - 1].visited) {
                enqueue((*maze)[y][x - 1], &Q);        // 4.4.1 enqueue new valid neighbour

                for (int i = 0; i < count; i++) {   // 4.4.2 enqueue previous path
                    enqueue(arr[i], &Q);
                }
            }
        }
        // Northern neighbour //
        if (y - 1 >= 0) {
            if ( ((*maze)[y - 1][x].ch == '.' || (*maze)[y - 1][x].ch == 'G') && !(*maze)[y - 1][x].visited) {
                enqueue((*maze)[y - 1][x], &Q);

                // enqueue previous path
                for (int i = 0; i < count; i++) { // enqueue previous path
                    enqueue(arr[i], &Q);
                }
            }
        }
        // Southern neighbour //
        if (y + 1 < rows) {
            if ( ((*maze)[y + 1][x].ch == '.' || (*maze)[y + 1][x].ch == 'G') && !(*maze)[y + 1][x].visited) {
                enqueue((*maze)[y + 1][x], &Q);

                // enqueue previous path
                for (int i = 0; i < count; i++) { // enqueue previous path
                    enqueue(arr[i], &Q);
                }
            }
        }
        // Eastern neighbour //
        if (x + 1 < columns) {
            if ( ((*maze)[y][x + 1].ch == '.' || (*maze)[y][x + 1].ch == 'G') && !(*maze)[y][x + 1].visited) {
                enqueue((*maze)[y][x + 1], &Q);

                // enqueue previous path
                for (int i = 0; i < count; i++) { // enqueue previous path
                    enqueue(arr[i], &Q);
                }
            }
        }

        (*maze)[y][x].visited = true;
	}

	return false;
}


// '.' = open position
// '#' = blocked
// 'S' = starting position
// 'G' = goal
// '=' = trace correct path

//// traverse rows with y = vertical Coordinate   ////
//// &     columns with x = horizontal Coordinate ////
void displayMaze (size_t rows, size_t columns, qType arr[rows][columns])
{
    size_t y, x;
	for (y = 0; y < rows; y++) {
        for (x = 0; x < columns; x++) {
            if (arr[y][x].inPath && arr[y][x].ch != 'S')
                arr[y][x].ch = '=';
            printf("%c", arr[y][x].ch);
        }
        printf("\n");
	}
	printf("\n\n");
}
