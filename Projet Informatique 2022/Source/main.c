// Library importation
#include "masterlib.h"

void main()
{
    // Initialise the random seed
    srand(time(NULL));

    // Initialise the overall color
    color("37");
    
    // Initialise game variable
    char current_char;
    char input_temp[50];
    int gridlocation[SIZE][SIZE] = {0};
    tetromino currentpiece;
    gamestatus gamestat;

    // Set the variables default value
    gamestat.bLoose = 0;
    gamestat.party_score = 0;

    // Ask the player the difficulty of the game
    do
    {
        printf("\nVeuillez rentrer la difficulte que vous voulez !");
        printf("\n0: Facile\n1: Intermediaire\n2: Difficile");
        printf("\nChoix: ");

        scanf("%s", &input_temp);
        gamestat.difficulty_setting = atoi(input_temp);
    }while(gamestat.difficulty_setting < 0 || gamestat.difficulty_setting > 2);

    // Set the timer time in function of the difficulty
    int answer_time[3] = {5, 2, 1};
    gamestat.answer_time = answer_time[gamestat.difficulty_setting];
    
    // Retrive the score file 
    FILE *my_file = NULL;
    my_file = fopen("other/score.txt", "r+");

    //Initial entering message
    printf("Bienvenue sur Tetris !\n");
    
    // Show the previous scores
    printf("\nVoici les scores des anciennes parties: \n");
    while (current_char != EOF)
    {
        current_char = fgetc(my_file);
        printf("%c", current_char);
    }
    
    rewind(my_file);
    initialise_score(my_file);


    // Initialise the game loop
    while(gamestat.bLoose == 0)
    {
        create_grid(1, gridlocation, gamestat.difficulty_setting);
        spawn_piece(&currentpiece);
        snap_piece(gridlocation, &currentpiece, &gamestat);
        remove_lines(gridlocation, &gamestat);
        has_loose(gridlocation, &gamestat);
    }
    
    // Leave the game by saving the score
    set_score(my_file, &gamestat);
    forcecrash("");  
}