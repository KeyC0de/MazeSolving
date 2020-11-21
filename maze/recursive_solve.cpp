#include <stdio.h>
#include <time.h>
//#include "measureWtimeCstyle.h"

#define true  1
#define false 0
#define rows 6
#define columns 6

// '.' = open position
// '#' = blocked
// 'S' = starting position
// 'G' = goal
// '+' = trace path
// 'x' = mark bad path
/*char maze[rows][columns] = {
	"S#####",
	"......",
	"#.#.#.",
	"#.#.#.",
	"#..#.G",
	"##...#"
};*/

char maze[rows][columns] = {
	"S...##",
	"#.#...",
	"#.##.#",
	"..#.##",
	"#...#G",
	"#.#..."
};

void displayMaze(void);
_Bool findPath(int x, int y);


int main(void)
{
//	startTiming();
	printf("*** MAZE - Recursive Solve ***\n");
	displayMaze();
	if (findPath(0, 0) == true)
		printf("Solution path (displayed with '+'s):\n");
	else {
		printf("Maze is unsolvable.\n");
		return -1;
	}

	displayMaze();
//	printf("Time elapsed: %fs\n", measureTimeCStyle());
	return 0;
}


void displayMaze(void)
{
	int i;
	for (i = 0; i < rows; i++)
		printf("%.*s\n", columns, maze[i]);
	printf("\n\n");
	return;
}

// expects starting position
_Bool findPath(int x, int y)
{
	// If (x,y) is out of bounds (outside maze), return false.
	if (x < 0 || x > columns - 1 || y < 0 || y > rows - 1)
		return false;

	// If (x,y) is the goal, return true.
	if (maze[y][x] == 'G')
		return true;

	// If (x,y) is not open, return false.
	if ( (maze[y][x] != '.' || maze[y][x] == '+') && maze[y][x] != 'S')
		return false;

	// Since (x,y) is open, mark (x,y) as part of solution path.
	maze[y][x] = '+';

	// If findPath either North, East, South or West of (x,y) is good, return true.
	if (findPath(x, y - 1) == true)
		return true;
	if (findPath(x + 1, y) == true)
		return true;
	if (findPath(x, y + 1) == true)
		return true;
	if (findPath(x - 1, y) == true)
		return true;

	// If current path was no good unmark x,y as part of solution path.
	maze[y][x] = 'x';

	return false;
}
