// Ilias Tsironis. 18/12/2018. Minesweeper game. //
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int SIZE;	
char game[24][24]; //The secret board//
char displayed[24][24]; //The shown board //

void create_mines (int seed, int SIZE) {
	
	int i, j, m;
	double floating_point;
	if ( seed == 0 ) {
		srand(time(0));
	}
	else {
		srand(seed);
	}
	
	if ( SIZE == 12 || SIZE == 24 ) {
		floating_point = trunc( ( SIZE * SIZE * 20 ) / 200 );
		for (i = 0; i < floating_point; i++ ) {
			j = rand() % SIZE;
			m = rand() % SIZE;
			game[j][m] = '*';
		}
	}
	else if (SIZE == 6) {
		floating_point = trunc( ( SIZE * SIZE * 20 ) / 100 );
		for (i = 0; i < floating_point; i++ ) {
			j = rand() % SIZE;
			m = rand() % SIZE;
			game[j][m] = '*';
		}
	}
}

// Build board used for created random mines */
void build_board(int SIZE, int seed) {
	
	int i, j;
	for(i = 0; i < SIZE; i++) {
		for(j = 0; j < SIZE; j++) {
			game[i][j] = '-';
		}
	}
	// Place mines in this board //
	create_mines(seed, SIZE);
}
void build_gameboard(int SIZE) {
	
	int i, j;
	
	for(i = 0; i < SIZE; i++) {
		for(j = 0; j < SIZE; j++) {
			displayed[i][j] = '-';
		}
	}
}
 // build the first board //
void print_gameboard(int SIZE) {
 
	int col, row;
	printf("  ");
	for(col = 0; col < SIZE; col++) {
		printf("%4d", col + 1);
	}
    printf("\n\n");
	for(row = 0; row < SIZE; row++) {
		printf("%2d", row + 1);
		for(col = 0; col < SIZE; col++) {
			printf("%4c", displayed[row][col]);
		}
		printf("\n");
	}
	printf("\n"); 
}

   // Check for mines //
char check_for_nearby_mines(int r_select, int c_select,int SIZE) {
	
	int i = r_select, j = c_select;
	int nearby_mine_count = 0;
	char C;
	
	if(game[r_select][c_select] == '*') {
		return (0);
	}
	
	if (game[i-1][j-1] == '*') {   
		nearby_mine_count++;  
	}
	if (game[i-1][j] == '*') {    
		nearby_mine_count++;  
	}
	if (game[i-1][j+1] == '*') {    
		nearby_mine_count++;  
	}
	if (game[i][j-1] == '*') {	
		nearby_mine_count++;
	}
	if (game[i][j+1] == '*') {  
		nearby_mine_count++;
	}
	if (game[i+1][j-1] == '*') { 
		nearby_mine_count++;
	}
	if (game[i+1][j] == '*') {
		nearby_mine_count++;  
	}
	if (game[i+1][j+1] == '*') {  
		nearby_mine_count++;  
	}
	C = (char)( ((int)'0') + nearby_mine_count);
	return C;
} 

// Print board after finish game //
void last_board (int SIZE) {
	 
	int col, row, r_select, c_select;
	char mines;
	
	for ( r_select = 0; r_select < SIZE; r_select++ ) {
		for ( c_select = 0; c_select < SIZE; c_select++ ) {
			mines = check_for_nearby_mines(r_select, c_select, SIZE);
			if ( mines == 0 ) {
				game[r_select ][c_select ] = '*';
			}
			else {
				game[r_select ][c_select ] = mines;
			}
		}
	}
	printf("  ");
	for(col = 0; col < SIZE; col++) {
		printf("%4d", col + 1);
	}
    printf("\n\n");
	for(row = 0; row < SIZE; row++) {
		printf("%2d", row + 1);
		for(col = 0; col < SIZE; col++) {
			if ( game[row][col] == 0 ) {
				printf("   *");
			}
			else {
				printf("%4c", game[row][col]);
			}	
		}
		printf("\n");
	}
	printf("\n"); 
	
}


int main(int argc, char *argv[]) {

	unsigned int seed;
	char difficulty, option;
	int SIZE, r_selection, c_selection, mines;

do {	
	printf("\nSeed? ");
	scanf("%d", &seed);
	
	do {
		printf("\n");
		printf("Choose difficulty level:\n");
		printf("EASY (E/e)\n");
		printf("MEDIUM (M/m)\n");
		printf("EXPERT (X/x)\n");
		printf("==> \n");
		scanf(" %c", &difficulty);
	} while ( (difficulty != 'E') && (difficulty!= 'e') && (difficulty != 'm') && (difficulty 		!= 'M') && (difficulty != 'X') && (difficulty != 'x') );
	
	switch (difficulty) {
		case 'e': {
			SIZE = 6;
			
			break;
		}
		case 'E': {
			SIZE = 6;
			break;
		}
		case 'm': {
			SIZE = 12;
			break;
		}
		case 'M': {
			SIZE = 12;
			break;
		}
		case 'x': {
			SIZE = 24;
			break;
		}
		case 'X': {
			SIZE = 24;
			break;
		}
	}
	//Create boards//
	printf("\n");
	build_board(SIZE, seed);
	build_gameboard(SIZE);
	print_gameboard(SIZE);
	printf("\n#\n");
	
	do {
		do {
			printf("Row> ");
			scanf("%d", &r_selection);
			printf("Col> ");
			scanf("%d", &c_selection);
			if ( (r_selection < 1 || r_selection > SIZE ) && r_selection != 0) {
				printf("\nInvalid row. Try again!");
				printf("\n#\n");
			}
			if (c_selection < 1 || c_selection > SIZE) {
				printf("\nInvalid column. Try again!");
				printf("\n#\n");
			}
			if (r_selection == 0) {
				printf("\nGame interrupted.\n");
				goto pace_5;
			} 
		} while(r_selection < 1 || r_selection > SIZE || c_selection < 1 || c_selection >   	SIZE);
		//Mines near selection //
		mines = check_for_nearby_mines(r_selection , c_selection , SIZE);
		if ( mines != 0 ) {
			displayed[r_selection - 1][c_selection - 1] = mines;
		
			game[r_selection - 1][c_selection - 1] = mines;
		}
		else if ( mines == 0 ) {
			game[r_selection - 1][c_selection - 1] = '*';
		}
		print_gameboard(SIZE);
	} 	while ( game[r_selection][c_selection] != '*' );
	
	if (game[r_selection][c_selection] == '*') {
		printf("\nKABOOM!\n");
	}
	else {
		printf("\nCongratulations!\n");
	}
	
	last_board(SIZE);
	
	printf("\n#\n");
	
	pace_5:
		printf("Play again? (y/n)\n");
		scanf(" %c", &option);
} while (option == 'y' || option == 'Y');
	
	return 0;
}



