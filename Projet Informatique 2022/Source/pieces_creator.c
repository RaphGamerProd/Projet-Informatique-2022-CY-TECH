// Library importation
#include "masterlib.h"


// This function check if a squared matrix is full of zero
int null_matrix(int arr[4][4])
{
    int empty = 1;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(arr[i][j] == 1)
            {
                empty = 0;
            }
        }
    }
    return empty;
}


// This function will set values onto another array
void selectpiecearray(int arr1[4][4], int arr2[4][4])
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            arr1[i][j] = arr2[i][j];
        }
    }
}

// This function spawn the piece in the current tetrominos structure
void spawn_piece(tetromino *currentpiece)
{ 
    // Choose a number between 0 and 6
    int rand_nb = rand() % 6;
    int **prandpiece = NULL;

    // These arrays will help us construct the piece
    int i_temp[4][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int cube_temp[4][4] = {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int t_temp[4][4] = {{1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int l_temp[4][4] = {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int j_temp[4][4] = {{1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int z_temp[4][4] = {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int s_temp[4][4] = {{0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    // Copy the chosen piece value into the main array
    switch(rand_nb)
    {
        case 0:
        selectpiecearray(currentpiece->piecetype, i_temp);
        currentpiece->maxrot = 2;
        break;

        case 1:
        selectpiecearray(currentpiece->piecetype, cube_temp);
        currentpiece->maxrot = 1;
        break;

        case 2:
        selectpiecearray(currentpiece->piecetype, t_temp);
        currentpiece->maxrot = 4;
        break;

        case 3:
        selectpiecearray(currentpiece->piecetype, l_temp);
        currentpiece->maxrot = 4;
        break;

        case 4:
        selectpiecearray(currentpiece->piecetype, j_temp);
        currentpiece->maxrot = 4;
        break;

        case 5:
        selectpiecearray(currentpiece->piecetype, z_temp);
        currentpiece->maxrot = 2;
        break;

        case 6:
        selectpiecearray(currentpiece->piecetype, s_temp);
        currentpiece->maxrot = 2;
        break;
    }
}

// This function will return the rotated index of a matrix
void calculate_newrotation(int nb_rotation, int curr_row, int curr_col, int* rotated_row, int* rotated_collumns)
{
    // Find the current value of the grid ranging from 0 to 15 and applie a rotation to the array
    int case_nb = 0;
    switch(nb_rotation)
    {
        // 0 degree rotation
        case 0:
        case_nb = curr_row * 4 + curr_col;
        break;

        // 90 degree rotation
        case 1:
        case_nb = 12 + curr_row - (4 * curr_col);
        break;

        // 180 degree rotation
        case 2:
        case_nb = 15 - (curr_row * 4) - curr_col;
        break;

        // 270 degree rotation
        case 3:
        case_nb = 3 - curr_row + (curr_col * 4);
        break;
    }

    // Convert the new case number into 2D array position (We decompose its value)
    *rotated_row = case_nb / 4;
    *rotated_collumns = case_nb % 4;
}

// This function will rotate the current piece matrix
void rotate_matrix(int nb_rotation, tetromino *currentpiece) 
{
    // Create a new array to stock the new rotation temporary
    int **temppiece = NULL;
    int rotated_row; 
    int rotated_collumns;
    temppiece = malloc(4 * sizeof(int));

    for(int i = 0; i < 4; i++)
    {
        *(temppiece + i) = malloc(4 * sizeof(int));
        // Check if there isn't any tipe of allocation error
        if(*(temppiece + i) == NULL)
        {
            forcecrash("Erreur d'allocation veuillez reessayer");
        }
    }


    // Fill the new array with the new rotation
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            calculate_newrotation(nb_rotation, i, j, &rotated_row, &rotated_collumns);
            temppiece[i][j] = currentpiece->piecetype[rotated_row][rotated_collumns];
        } 

    }

    // Now that the rotation process is done we can recopy the temporary array values into the main one
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            currentpiece->piecetype[i][j] = temppiece[i][j]; 
        }
    }

    // We free the memory at the temporary array location
    free(temppiece);
}


// This function affect the current tetromino into the grid array with a initiale collumn location
void snap_piece(int gridlocation[SIZE][SIZE], tetromino *currentpiece, gamestatus *gamestat)
{
    // These variable will represent if the tetromino touched a surface and its attributes
    char input_temp[50];
    int bcanmove = 1;
    int has_collied = 0;
    int piece_rotation = 70;
    int x = 0;

    unsigned long t1 = 0, t2 = 0;
    int disable_input = 0;

    currentpiece->px = 4;
    currentpiece->py = 0; 
    
    // Check if the matrix of the piece isn't empty
    if(null_matrix(currentpiece->piecetype) == 1)
    {
        forcecrash("Erreur de matrice, elle est actuellement vide :(");
    }


    // Initialise the piece rotation
    rotate_matrix(0, currentpiece);

    // Show a visual representation of the pieces
    printf("\n\nVoici les pieces !\n\n");

    // Print the number of pieces
    printf("\n");
    for(int i = 0; i < currentpiece->maxrot; i++)
    {
        printf("  %d:         ", i);
    }
    printf("\n");


    // Print the previsualisation of the pieces and its new rotation
   for(int i = 0; i < 4; i++)
   {
       // We print each piece line by line
       for(int k = 0; k < currentpiece->maxrot; k++)
       {
           for(int j = 0; j < 4; j++)
           {
               printf("%c ", gridskin(currentpiece->piecetype[i][j]));
           }
           // Each time the current line is finish we rotate it by 90 degrees
           rotate_matrix(1, currentpiece);
           printf("     ");
       }
       printf("\n");


       // Now we are changing the row and reseting the piece to its base rotation
       switch(currentpiece->maxrot)
       {
           case 1:
           rotate_matrix(3, currentpiece);
           break;
           case 2:
           rotate_matrix(2, currentpiece);
           break;
       }
        
   }
    printf("\n");

    // Reset the piece rotation for later usage
    rotate_matrix(0, currentpiece);

    // Choose a rotation
    do
    {
        printf("\nVeuillez choisir une rotation: ");
        scanf("%s", &input_temp);
        piece_rotation = atoi(input_temp);
    } while (piece_rotation < 0 || piece_rotation > 3);
    


    // Applie the rotation to the piece
    rotate_matrix(piece_rotation, currentpiece);
    printf("\n\n");

    // Snap the piece to the closest surface
    do
    {
        // Register player inputs
        if(disable_input == 0)
        {
            printf("\nVous avez %d secondes pour repondre ! ", gamestat->answer_time);
            t1 = retrieve_time();
            do
            {
                printf("\nScore: %d", gamestat->party_score);
                printf("\nStatique-> 0\nGauche-> 1\nDroite-> 2\nChoix: ");
                scanf("%s", &input_temp);
                x = atoi(input_temp);
            }
            while (x < 0 || x > 2);
            t2 = retrieve_time();

            printf("\n%ld ", t2 - t1);


            // Check if the user didn't take too long to answer
            if((t2 - t1) > gamestat->answer_time)
            {
                disable_input = 1;
            }
        }

        bcanmove = 1;

        // Change the value of x according to player input
        switch(x)
        {
            case 1: x = -1;
            break;

            case 2: x = 1;
            break;
        }    


        // Check for lateral collision
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if((currentpiece->piecetype[i][j] == 1 && gridlocation[i + currentpiece->py][j + currentpiece->px + x] == 2))
                {
                    bcanmove = 0;
                    x = 0;
                }
            }
        }


        // If the lateral space is free we increment the lateral position
        if(bcanmove == 1)
        {
            currentpiece->px += x;
        }

        // Change the position of the piece on the board lateraly
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(currentpiece->piecetype[i][j] == 1)
                {
                    gridlocation[i + currentpiece->py][j + currentpiece->px] = currentpiece->piecetype[i][j];
                }
            }
        }

        printf("%d", gamestat->difficulty_setting);
        create_grid(0, gridlocation, gamestat->difficulty_setting);

        // Check the next line for Y Axis collisions
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(currentpiece->piecetype[i][j] == 1 && (currentpiece->py + i > SIZE - 2 || gridlocation[i + currentpiece->py + 1][j + currentpiece->px] == 2))
                {
                    has_collied = 1;
                }                
            }
        } 

        // Refresh the grid each time we move the piece verticaly
        if(has_collied == 0)
        {
            reset_grid(gridlocation); 
            currentpiece->py += 1;
        }

    } while (has_collied == 0);    
}
