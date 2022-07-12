#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// size of grid
int l = 16;
int hx, hy, mx, my, premx, premy; 


// we use this function to set manhattan distance
int getDist(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2 ) + abs(y1 - y2 );
}

void setGrid(char grid[l][l])
{

    // firstly all values are empty
    int i;
    int j;
    for( i=0; i<l; i++)
    {
        for(j=0; j<l; j++)
        {
            grid[i][j] = '_';
        }
    }
  
    // we lay the walls as in the example picture
    int rc[27][2] = {{2, 2}, {3, 2}, {0, 8}, {1, 8}, {2, 8}, {2, 7},
        {2, 9}, {2, 13}, {3, 13}, {5, 6}, {5, 7}, {5, 8}, {6, 6}, {9, 3}, {9, 4},
        {9, 5}, {10, 5}, {8, 10}, {9, 10}, {10, 10}, {11, 10}, {11, 11}, {12, 2}, {13, 2}, {14, 2}, {14, 3}, {14, 4}};
  
  	
  	
    for(i=0; i<27; i++)
    {
        grid[rc[i][0]][rc[i][1]] = 'W';
    }
  
    // princess is here
    grid[7][0] = 'A';
  
    while(1)
    {
        hx = rand() % l;
        hy = rand() % l;        //starting position for hero
        if(getDist(hx, hy, 7, 0) >= 16) //Generates a random location away from 16 units for the hero
        {
            // set it hero
            grid[hx][hy] = 'T';
            break;
        }
    }
    
    while(1)
    {
        mx = rand() % l; //starting position for monster
        my = rand() % l;
        if(getDist(mx, my, hx, hy) >= 16)
        {
            // set it police
            grid[mx][my] = 'P';
            break;
        }
    }
  
    // previous location of police
    premx = -1;
    premy = -1;
}

// print the grid 
void printGrid(char grid[l][l])
{
	int i;
	int j;
	
    for(i=0; i<l; i++)
    {
        for(j=0; j<l; j++)
        {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

// take input for move from player
void getMove(char grid[l][l])
{
    int move, x = hx, y = hy;
    while(1)
    {
        printf("Enter move - 1 for left, 3 for right, 5 for up and 2 for down(Don't forget to press enter key after'): ");
        scanf("%d", &move);
  
        // get the trap value
        if(move == 1) // left
            y--;
        else if(move == 3) // right
            y++;
        else if(move == 5) // up
            x--;
        else if(move == 2) // down
            x++;
        else
            continue; // invalid option
  
        // check for validity
        if((x>=0 && x<l) && (y>=0 && y<l) && grid[x][y]!='W')
        {
            // update location of thief
            grid[hx][hy] = '_';
            hx = x;
            hy = y;
            grid[hx][hy] = 'T';
            return;
        }
    }
}

// computer's move
void computerMove(char grid[l][l], int difficulty)
{
    int move, x = mx, y = my;
  
    // easy move
    if(difficulty == 0)
    {
        // loop till a valid moving location is found
        while(1)
        {
            x = mx;
            y = my;
            // generate a random between 0 and 4
            move = rand() % 4;
            if(move == 1) // left
                y--;
            else if(move == 3) // right
                y++;
            else if(move == 5) // up
                x--;
            else // down
                x++;
  
            // move to required location
            if((x>=0 && x<l) && (y>=0 && y<l) &&
                !(premx == x && premy == y) && grid[x][y]!='W')
            {
                break;
            }
        }
    }
    else
    {
        // difficult level
        // get manhattan distance for all 4 choices
        int dl = 100, dr = 100, du = 100, dd = 100, minD = 100, count = 0;
        // directions which have the same distance
        char dir[4];
  
        // left
        if(my > 0 && !(premx == mx && premy == (my-1)) && grid[mx][my-1]!='W')
        {
            dl = getDist(mx, my-1, hx, hy);
            if(dl < minD)
            {
                minD = dl;
            }
        }
        // right
        if(my < 15 && !(premx == mx && premy == (my+1)) && grid[mx][my+1]!='W')
        {
            dr = getDist(mx, my+1, hx, hy);
            if(dr < minD)
            {
                minD = dr;
            }
        }
        // up
        if(mx > 0 && !(premx == (mx-1) && premy == my) && grid[mx-1][my]!='W')
        {
            du = getDist(mx-1, my, hx, hy);
            if(du < minD)
            {
                minD = du;
            }
        }
        // down
        if(mx < 15 && !(premx == (mx+1) && premy == my) && grid[mx+1][my]!='W')
        {
            dd = getDist(mx+1, my, hx, hy);
            if(dd < minD)
            {
                minD = dd;
            }
        }
        // count all directions which have minimum distance
        if(dl == minD)
            dir[count++] = 'l';
        if(dr == minD)
            dir[count++] = 'r';
        if(du == minD)
            dir[count++] = 'u';
        if(dd == minD)
            dir[count++] = 'd';
  
        // randomly select a direction from optimal options
        move = rand() % count;
        if(dir[move] == 'l') // left
            y--;
        else if(dir[move] == 'r') // right
            y++;
        else if(dir[move] == 'u') // up
            x--;
        else // down
            x++;
    }
  
    // update location of police
    grid[mx][my] = '_';
    premx = mx;
    premy = my;
    mx = x;
    my = y;
    grid[mx][my] = 'P';
}

int main()
{
    // to seed the random generator
    srand(time(0));
  
    // required variables
    char choice[10], grid[l][l], move;
    int difficulty;
  
    while(1)
    {
        setGrid(grid);
  
        // ask player the difficulty level
        printf("Enter mode of game - 0 for easy and 1 for hard: ");
        scanf("%d", &difficulty);
  
        // now loop till end of game
        while(1)
        {
            // print the grid
            printGrid(grid);
            grid[7][0] = 'A';
  
            // player's turn, take input till valid
            getMove(grid);
  
            // check if reached the princess or at monster's trap
            if(hx==7 && hy==0)
            {
                printf("Congratulations! You can kiss the princess.");
                break;
            }
            if(hx==mx && hy==my)
            {
                printf("You became lunch for the monster!");
                break;
            }
  
            // computer's turn
            computerMove(grid, difficulty);
  
            // check for overlap of monster and hero
            if(hx==mx && hy==my)
            {
                printf("You became lunch for the monster!");
                break;
            }
  
        }
  
        // ask user to play another game
        printf("Do you want to play again? (y/n): ");
        scanf("%s", choice);
        if(choice[0] == 'Y' || choice[0] == 'y')
            continue;
        break;
    }

    return 0;
}
