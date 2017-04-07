#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    //Variable
    char answer[3], option[15], text[100];
    int numberOption, i, j, k, letter = 97;
    
    printf("Bienvenido al codificador de Polybius\n\n");
    
    do
    {
        //Main menu
        printf("Elija una opcion:\n1.-Codificar\n2.-Decodificar\n3.-Salir\n");
        do
        {
            fflush(stdin);
            gets(option);
            if(strcmp("1",option) != 0 && strcmp("2",option) != 0 && strcmp("3",option) != 0)
                printf("Error %s nos es una respuesta valida, elija entre las opciones 1, 2 y 3\n\a",option);
        }while((strcmp("1",option) != 0 && strcmp("2",option) != 0 && strcmp("3",option) != 0));

        //Casting values
        if(strcmp("1",option) == 0)
        {
           numberOption = 1;
        }
        if(strcmp("2",option) == 0)
        {
           numberOption = 2;
        }
        if(strcmp("3",option) == 0)
        {
           numberOption = 3;
        }


        //Different options
        switch(numberOption)
        {
            case 1:

            //Cleans text array
            for(i = 0; i < 100; i++)
            {
                text[i] = "\0";
            }

            letter = 97;
            system("clear");
            printf("Codificar\n\nIngresa el texto:\n\n");
            fflush(stdin);
            gets(text);

            //Major proccesing

             

            //Create array for indexes
            int indexes[5];

            //Create square for lowercase
            int square[5][5];
            srand(time(NULL));
            int r = rand() % 2;
            int aux = r;

            //Shifts between using numbers or letters as indexes
            if(aux == 0)
            {
                //Index are letters
                r = rand() % (118 + 1 - 97) + 97;
                for(i = 0; i < 5; i++)
                {
                    indexes[i] = r;
                    r++;
                }
            }
            if(aux == 1)
            {
                //Index are numbers
                r = rand() % (5 + 1 - 0) + 0;
                for(i = 0; i < 5; i++)
                {
                    indexes[i] = r;
                    r++;
                }
            }
            printf("\n\nSe utilizo el siguiente cuadro\n\n   ");
            for(i = 0; i < 5; i++)
            {
                if(aux == 0)
                {
                    printf(" \033[22;34m%c  \033[0m",indexes[i]);
                }
                else
                {
                    printf("\033[22;34m%d   \033[0m",indexes[i]);
                }
            }

            for(i = 0; i < 5; i++)
            {
                for(j = 0; j  < 5; j++)
                {
                    if(i == 1 && j == 3)
                    {
                        square[i][j] = letter;
                        letter = letter +2;
                    }
                    else
                    {
                        square[i][j] = letter;
                        letter++;
                    }
                }
            }

            //Print square for lowercase
            printf("\n\n");//___|___|___|___|___|
            for(i = 0; i < 5; i++)
            {
                if(aux == 0)
                {
                    printf("\033[22;34m%c   \033[0m",indexes[i]);
                }
                else{
                    printf("\033[22;34m%d  \033[0m",indexes[i]);
                }
                for(j = 0; j < 5; j++)
                {
                    if(i == 1 && j ==3)
                    {
                        printf("ij  ");
                    }
                    else
                    {
                        printf("%c   ",square[i][j]);
                    }
                }
                printf("\n");
            }


            //Starts encoding
            printf("\nEl texto codificado es:\n\n");
            for(k = 0; k < 100; k++)
            {
                for(i = 0; i < 5; i++)
                {
                    for(j = 0; j < 5; j++)
                    {
                        //In case there're upper cases
                        if(text[k] <= 90 && text[k] >= 65)
                        {
                            text[k] = text[k] + 32;
                        }
                        
                        //In case there's a J we count it as a I'
                        if(text[k] == 106)
                        {
                            text[k] = 105;
                        }
                        if(text[k] == square[i][j])
                        {
                            if(aux == 0)
                            {
                                printf("%c%c",indexes[i],indexes[j]);
                            }
                            else
                            {
                                printf("%d%d",indexes[i],indexes[j]);
                            }
                        }
                    }
                }
            }
            printf("\n");


            break;

            case 2:

            //Cleans text array
            for(i = 0; i < 100; i++)
            {
                text[i] = "\0";
            }

            system("clear");
            printf("Decodificar\n\nIngresa el codigo:\n\n");
            fflush(stdin);
            gets(text);

            int solutionIndex[5];
            int auxiliary = 0, temp = 0;
            int duplicated;

            //Clear all the rubish from the array
            for(i = 0; i < 5; i++)
            {
                solutionIndex[i] = 0;
            }

            //Here we take as many letters available as possible
            for(i = 0; i < 100; i++)
            {
                for(j = 0; j < 5; j++)
                {
                    //printf("Evaluando letra %d con valor %d en posicion %d\n",text[i],solutionIndex[j],j);
                    if(text[i] == solutionIndex[j])
                    {
                        duplicated = 1;
                        break;
                    }
                    else
                    {
                        duplicated = 0;
                    }
                }
                if(duplicated == 0)
                {
                    //printf("Se agregó a la letra %d en la posicion %d\n",text[i],auxiliary);
                    solutionIndex[auxiliary] = text[i];
                    auxiliary++;
                }
                if(auxiliary == 5)
                break;
            }

            /*
            for(i = 0; i < 5; i++)
            {
                printf("%d\n",solutionIndex[i]);
            }*/

            //Once we hava all of them, we sort them
            for (i = 1; i < 5; i++)
            {
                for (j = 0 ; j < (5 - i); j++)
                {
                    if (solutionIndex[j] >= solutionIndex[j+1])
                    {
                        temp = solutionIndex[j];
                        solutionIndex[j] = solutionIndex[j+1];
                        solutionIndex[j+1] = temp;
                    }
                }
            }

            /*Print solutionIndex for testing purpouses 
            for(i = 0; i < 5; i++)
            {
                printf("%d   ",solutionIndex[i]);
            }*/
         

            //Here we start to print our findings

            //First we create a alphabet
            int abc[5][5];
            letter = 97;

            for(i = 0; i < 5; i++)
            {
                for(j = 0; j  < 5; j++)
                {
                    if(i == 1 && j == 3)
                    {
                        abc[i][j] = letter;
                        letter = letter +2;
                    }
                    else
                    {
                        abc[i][j] = letter;
                        letter++;
                    }
                }
            }

            //Starts decoding
            printf("\nEl texto decodificado es:\n\n");
            for(i = 0; i < 100; i+=2)
            {
                for(j = 0; j < 5; j++)
                {
                    if(text[i] == solutionIndex[j])
                    {
                        for(k = 0; k < 5; k++)
                        {
                            if(text[i+1] == solutionIndex[k])
                            {
                                printf("%c",abc[j][k]);
                            }
                        }
                    }
                }
            }

            //Displays alphabet matrix
            if(text[0] >= 0 && text[0] <= 9)
            {
                aux = 1;
            }
            else{
                aux = 0;
            }
            printf("\n\nSe utilizo el siguiente cuadro\n\n   ");
            for(i = 0; i < 5; i++)
            {
                if(aux == 0)
                {
                    printf(" \033[22;34m%c  \033[0m",solutionIndex[i]);
                }
                else
                {
                    printf("\033[22;34m%d   \033[0m",solutionIndex[i]);
                }
            }

            //Print square for lowercase
            printf("\n\n");//___|___|___|___|___|
            for(i = 0; i < 5; i++)
            {
                if(aux == 0)
                {
                    printf("\033[22;34m%c   \033[0m",solutionIndex[i]);
                }
                else{
                    printf("\033[22;34m%d  \033[0m",solutionIndex[i]);
                }
                for(j = 0; j < 5; j++)
                {
                    if(i == 1 && j ==3)
                    {
                        printf("ij  ");
                    }
                    else
                    {
                        printf("%c   ",abc[i][j]);
                    }
                }
                printf("\n");
            }



            break;

            case 3:
            system("clear");
            printf("Saliendo...\n\n");
            getchar();
        }
        
        //Start over
        if(strcmp("3",option) != 0)// && numberOption != 3)
        {
            printf("\nQuieres codificar/decodificar algo mas? \nSi = 1 \nNo = 2\n");
            do
            {
                fflush(stdin);
                gets(answer);
                if(strcmp("1",answer) != 0 && strcmp("2",answer) != 0)
                    printf("Error %s nos es una respuesta valida, conteste Si = 1 o No = 2\n\a",answer);
            }while(strcmp("1",answer) != 0 && strcmp("2",answer));
            system("clear");
        }
        if(strcmp("2",answer) == 0)
        {
            printf("Saliendo...\n\n");
            getchar();
        }
    }while(strcmp("1",answer) == 0 && numberOption != 3);
}