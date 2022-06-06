// Library importation
#include "masterlib.h"


// This function will be use while snapping the piece to the grid 
void reset_grid(int gridlocation[SIZE][SIZE])
{
    // We go trough the grid and check for non-anchored piece, if they aren't we change their value to zero
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            if(gridlocation[i][j] != 2)
            {
                gridlocation[i][j] = 0;
            }
        }
    }
}

// This function will remove complete line from the gridlocation array
void remove_lines(int gridlocation[SIZE][SIZE], gamestatus *gamestat)
{
    int full = 0;
    int nb_f_lines = 0;

    // Create an array that'll check if there's any full lines
    for(int i = 0; i < SIZE; i++)
    {
        full = 1;
        for(int j = 0; j < SIZE; j++)
        {
            // If only one value is different of zero we cancel the clearing process
            if(gridlocation[i][j] == 0)
            {
                full = 0;
            }
        }

        // Clear the whole line by changing each value to zero
        if(full == 1)
        {
            // Increment the number of full lines
            nb_f_lines++;
            for(int j = 0; j < SIZE; j++)
            {
                gridlocation[i][j] = 0;
            }
            
            // We go through the grid to applie somekind of gravity to the reset of the pieces
            for(int w = i - 1; w >= 0; w--)
            {
                for(int j = 0; j < SIZE; j++)
                {
                    gridlocation[w + 1][j] = gridlocation[w][j];
                }
            } 
        }
    }

    // Increment the player score in function of how many lines you did clear at once
    for(int i = 0; i < nb_f_lines; i++)
    {
        gamestat->party_score += 500;
    }
}

// This function will change the current grid int value to characters for it to be more user-friendly
char gridskin(int value)
{
    return (value > 0) ? '@' : ' ';
}

void create_grid(int anchor_piece, int gridlocation[SIZE][SIZE], int difficulty)
{
    // Initialize variables
    char gridcolor[3] = {};

    // Clear the screen each time we loop
    printf("\033[H\033[2J");

    // First we create the collums
    printf("\n\n");
    for(int i = 0; i < SIZE; i++)
    {
        printf(" %c   ", 'A' + i);
    }

    printf("\n");

    // Now we create the global look of our grid
    for(int i = 0; i < SIZE; i++)
    {
        printf("\n");

        for(int j = 0; j < SIZE; j++)
        {
            add_color(gridlocation, difficulty, i, j);
            printf(" %c", gridskin(gridlocation[i][j]));

            // Create the grid color
            switch(difficulty)
            {
                case 0:
                strcpy(gridcolor,"33");
                break;

                case 1:
                strcpy(gridcolor, "32");
                break;

                case 2:
                strcpy(gridcolor, "33");
                break;
            }
            
            color(gridcolor);

            printf("  |");

            // If the current grid location equals to one, we anchore it to the grid
            if(anchor_piece == 1 && gridlocation[i][j] == 1)
            {
                gridlocation[i][j] = 2;
            }
        }
        
        // Reset the game color to white
        color("37");
    }
}

// Check if the middle lines aren't already full
void has_loose(int gridlocation[SIZE][SIZE], gamestatus *gamestat)
{
    for(int j = 4; j <= 7; j++)
    {
        if(gridlocation[0][j] == 1)
        {
            gamestat->bLoose = 1;
        }
    }
}
