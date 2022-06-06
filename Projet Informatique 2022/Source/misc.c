// Library importation
#include "masterlib.h"


// If there's an error in the game we'll need to crash it to prevent corruption
void forcecrash(char message[200])
{
    printf("\n%s", message);
    exit(1);
}

void initialise_score(FILE *my_file)
{
    // Initialise the variables
    char name[70];
    char colon[3] = ": ";
    char current_char;

    // Ask the player his name
    printf("\nVeuillez rentrer votre prenom: ");
    do
    {
        scanf("%s", &name);
    } while (name == NULL);

    // Concatenate the colon and the name for a better result
    strcat(name, colon);

    // We go to the end of the file to add the new name of the player
    while(current_char != EOF)
    {
        current_char = fgetc(my_file);
    }

    // Add the player name to the end of the file
    fputs(name, my_file);
}

void set_score(FILE *myfile, gamestatus *gamestat)
{
    // Initialize variables
    char final_score[20];
    char end_row[2] = {"\n"};

    // Add a final message for the player
    printf("\nFin de partit, votre score e tait de: %d", gamestat->party_score);
    printf("\nNe vous en faites pas, il sera sauvegarde pour la prochaine partie, A plus tard !");

    // Add the player score to the score file
    sprintf(final_score, "%d", gamestat->party_score);
    strcat(final_score, end_row);
    fputs(final_score, myfile);
    
}

// This function will add a specific color in function of the grid value and the difficulty  
void add_color(int gridlocation[SIZE][SIZE], int difficulty, int i, int j)
{
    char color1[3] = {};
    char color2[3] = {};

    // Change the game color in function of difficulty
    
    switch (difficulty)
    {
        case 0:
        strcpy(color1, "31");
        strcpy(color2, "32");
        break;

        case 1:
        strcpy(color1, "33");
        strcpy(color2, "34");
        break;

        case 2:
        strcpy(color1, "35");
        strcpy(color2, "36");
        break;
    }

    gridlocation[i][j] == 2 ? color(color1) : color(color2);
}

// This function will return the current time in second, that it is when called
int retrieve_time()
{
    time_t current_time;
    time(&current_time);
    return current_time;
}