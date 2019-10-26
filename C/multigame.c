#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include "cs1010.h"
#include <stdlib.h>

#define max_length 3

struct SnakeNode
{
    int x;
    int y;
    struct SnakeNode *next;
};

struct Food
{
    int x;
    int y;
    int isEaten;
};

void Gotoxy(int column,int row);
int CreateScoreFile();
void CreateSnake(struct SnakeNode **snake);
void Graphics(struct SnakeNode *snake,struct Food food,int score,int highscore);
int isSnake(int x,int y,struct SnakeNode *snake);
void CreateFood(struct Food *food,struct SnakeNode *snake);
int GetSnakeSize(struct SnakeNode *snake);
struct SnakeNode * GetListItem(struct SnakeNode *snake,int index);
int lose(struct SnakeNode *snake);
void SaveScore(int score);
void Physics(struct SnakeNode **snake,int *direction,struct Food *food,int *score,int *highscore,int *endgame);
void DestroySnake(struct SnakeNode **snake);
void getcode(char code[]);
bool checkcode(char code[], char guess[]);

char map[20][50] = {"##################################################",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "#                                                #",
                    "##################################################"};

int main()
{
    char game;
    printf("Which Game do you want to play??? :\n");
    printf("1. Mastermind\n");
    printf("2. Snake\n");
    scanf("%c", &game);
    if(game == '1')
    {
        bool try_again = true;
        char code[4];
        printf("Welcome to Mastermind!!\n");
        printf("You have 8 guesses to guess the code\n");
        printf("4 digits of numbers 0, 1, 2, 3, 4, 5\n ");
        //loop to continously as for a guess and checks it till guess is correct
        while (try_again == true)
        {
            printf("\nCode generated\n");
            printf("Good luck! Start guessing now\n");
            try_again = false;
            char again, hint;
            bool correct = false; //variable to store if user guessed correct
            long guess_count = 0;
            long lastt = 10;

            getcode(code);
            do
            {
                guess_count += 1;
                char *guess = cs1010_read_word();
                if (strlen(guess) != 4 )
                {
                    printf("Your guess need 4 digits!!!\n");
                    guess_count -= 1;
                    continue;
                }
                correct = checkcode(code, guess);
                free(guess);
                if(correct == false)
                {
                    printf("Wrong, %ld guesses left\n", 8-guess_count);
                }
                if(guess_count % 3 == 0)
                {
                    printf("Need an hint???  [y/n]: \n");
                    scanf("%c", &hint);
                    if(hint == 'y')
                    {
                        long t = rand()%3;
                        printf("the correct code consists of,");
                        for(long i = 0; i <= 3; i+=1)
                        {
                            if (i != t && i != lastt)
                            printf("*");
                            else
                            printf("%c", code[i]);
                        }
                        printf("\n\n");
                        lastt = t;
                        continue;
                    }
                    else
                    {
                        continue;
                    }
                }
            } while (correct == false && guess_count < 8);

            if(correct == true)
            {
                printf("Correct, congratulations!!!\n");
                printf("%ld wrong guesses\n", guess_count);
            }
            else
            {
                printf("Sorry, you ran out of guesses...\n");
                printf("Correct code was ");
                printf("%c%c%c%c", code[0], code[1], code[2], code[3]);
            }
            printf("\n\n New game? [y/n] : ");
            scanf("%c", &again);
            if(again == 'y')
            {
                try_again = true;
                again = 'n';
            }
            printf("\n");
        }  
        return 0;
    }

    else
    {
        int endgame = 0;
        int gamespeed = 25;
        int score = 0;
        int highscore = 0;
        int direction = 1;
        struct SnakeNode *snake = NULL;
        struct Food food;

        food.isEaten = 1;

        srand(time(NULL));

        highscore = CreateScoreFile();

        CreateSnake(&snake);

        do
        {
            CreateFood(&food,snake);
            Graphics(snake,food,score,highscore);
            Sleep(gamespeed);
            system("CLS");
            Physics(&snake,&direction,&food,&score,&highscore,&endgame);
        }while(endgame == 0);

        DestroySnake(&snake);

        return 0;
    }
}

void Gotoxy(int column,int row)
{
    COORD c;

    c.X = column;
    c.Y = row;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int CreateScoreFile()
{
    FILE *scfile;
    int highscore = 0;

    scfile = fopen("Score file.txt","r");

    if(scfile == NULL)
    {
        scfile = fopen("Score file.txt","w");
        fprintf(scfile,"%d",highscore);
    }
    else
    {
        fscanf(scfile,"%d",&highscore);
    }

    fclose(scfile);

    return highscore;
}

void CreateSnake(struct SnakeNode **snake)
{
    struct SnakeNode *hnext = NULL;
    struct SnakeNode *hprev = NULL;

    int x = 27;
    int y = 10;
    int size = 0;

    *snake = (struct SnakeNode *)malloc(sizeof(struct SnakeNode));

    (*snake)->x = x;
    (*snake)->y = y;
    (*snake)->next = NULL;

    hprev = *snake;
    hnext = (*snake)->next;

    while(hnext != NULL || size < 4)
    {
        x--;

        hnext = (struct SnakeNode *)malloc(sizeof(struct SnakeNode));

        hnext->x = x;
        hnext->y = y;
        hnext->next = NULL;

        hprev->next = hnext;
        hprev = hnext;

        hnext = hnext->next;

        size++;
    }
}

void Graphics(struct SnakeNode *snake,struct Food food,int score,int highscore)
{
    int x,y;
    struct SnakeNode *temp = NULL;

    for(y=0;y<20;y++)
    {
        for(x=0;x<50;x++)
        {
            printf("%c",map[y][x]);
        }

        printf("\n");
    }

    Gotoxy(food.x,food.y);
    printf("$");

    temp = snake;

    while(temp != NULL)
    {
        Gotoxy(temp->x,temp->y);
        printf("*");

        temp = temp->next;
    }

    Gotoxy(0,20);
    printf("\nScore: %d",score);

    if(score <= highscore)
    {
        printf(" ------ Highscore: %d",highscore);
    }
    else
    {
        printf(" ------ Highscore: %d",score);
    }
}

int isSnake(int x,int y,struct SnakeNode *snake)
{
    struct SnakeNode *temp = NULL;

    temp = snake;

    while(temp != NULL)
    {
        if(temp->x == x && temp->y == y)
        {
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}

void CreateFood(struct Food *food,struct SnakeNode *snake)
{
    if(food->isEaten)
    {
        food->x = rand()%48+1;
        food->y = rand()%18+1;
        food->isEaten = 0;

        do
        {
            if(isSnake(food->x,food->y,snake))
            {
                food->x = rand()%48+1;
                food->y = rand()%18+1;
            }
        }while(isSnake(food->x,food->y,snake));
    }
}

struct SnakeNode * GetListItem(struct SnakeNode *snake,int index)
{
    int i;
    struct SnakeNode *node = NULL;

    node = snake;

    for(i=0;i<index;i++)
    {
        node = node->next;
    }

    return node;
}

int GetSnakeSize(struct SnakeNode *snake)
{
    int size = 0;

    while(snake != NULL)
    {
        size++;
        snake = snake->next;
    }

    return size;
}

int lose(struct SnakeNode *snake)
{
    struct SnakeNode *iterator;

    iterator = snake->next;

    while(iterator != NULL)
    {
        if(snake->x == iterator->x && snake->y == iterator->y)
        {
            return 1;
        }

        iterator = iterator->next;
    }

    return 0;
}

void SaveScore(int score)
{
    FILE *savscore;
    int filescore;

    savscore = fopen("Score file.txt","r");

    if(savscore != NULL)
    {
        fscanf(savscore,"%d",&filescore);

        if(score > filescore)
        {
            fclose(savscore);

            savscore = fopen("Score file.txt","w");

            fprintf(savscore,"%d",score);
        }
    }

    fclose(savscore);
}

void Physics(struct SnakeNode **snake,int *direction,struct Food *food,int *score,int *highscore,int *endgame)
{
    int i;
    struct SnakeNode *lnode = NULL;
    struct SnakeNode *fnode = NULL;
    struct SnakeNode *nnode = NULL;

    if(GetAsyncKeyState(VK_RIGHT))
    {
        if(*direction != 3)
        {
            *direction = 1;
        }
    }
    else if(GetAsyncKeyState(VK_LEFT))
    {
        if(*direction != 1)
        {
            *direction = 3;
        }
    }
    else if(GetAsyncKeyState(VK_UP))
    {
        if(*direction != 2)
        {
            *direction = 4;
        }
    }
    else if(GetAsyncKeyState(VK_DOWN))
    {
        if(*direction != 4)
        {
            *direction = 2;
        }
    }

    if(*direction == 1)
    {
        for(i=GetSnakeSize(*snake)-1;i>0;i--)
        {
            lnode = GetListItem(*snake,i);

            fnode = GetListItem(*snake,i-1);

            lnode->x = fnode->x;
            lnode->y = fnode->y;
        }

        (*snake)->x = (*snake)->x + 1;

        if((*snake)->x > 48)
        {
            (*snake)->x = 1;
        }
    }
    else if(*direction == 3)
    {
        for(i=GetSnakeSize(*snake)-1;i>0;i--)
        {
            lnode = GetListItem(*snake,i);

            fnode = GetListItem(*snake,i-1);

            lnode->x = fnode->x;
            lnode->y = fnode->y;
        }

        (*snake)->x = (*snake)->x - 1;

        if((*snake)->x < 1)
        {
            (*snake)->x = 48;
        }
    }
    else if(*direction == 4)
    {
        for(i=GetSnakeSize(*snake)-1;i>0;i--)
        {
            lnode = GetListItem(*snake,i);

            fnode = GetListItem(*snake,i-1);

            lnode->x = fnode->x;
            lnode->y = fnode->y;
        }

        (*snake)->y = (*snake)->y - 1;

        if((*snake)->y < 1)
        {
            (*snake)->y = 18;
        }
    }
    else
    {
        for(i=GetSnakeSize(*snake)-1;i>0;i--)
        {
            lnode = GetListItem(*snake,i);

            fnode = GetListItem(*snake,i-1);

            lnode->x = fnode->x;
            lnode->y = fnode->y;
        }

        (*snake)->y = (*snake)->y + 1;

        if((*snake)->y > 18)
        {
            (*snake)->y = 1;
        }
    }

    if(lose(*snake))
    {
        *endgame = 1;
        Graphics(*snake,*food,*score,*highscore);
        SaveScore(*score);
        Beep(250,250);
        Sleep(2000);
    }

    if((*snake)->x == (*food).x && (*snake)->y == (*food).y)
    {
        (*food).isEaten = 1;

        *score = *score + 10;

        Beep(1000,25);

        lnode = GetListItem(*snake,GetSnakeSize(*snake)-1);

        nnode = (struct SnakeNode *)malloc(sizeof(struct SnakeNode));

        nnode->x = lnode->x;
        nnode->y = lnode->y;
        nnode->next = NULL;

        lnode->next = nnode;
    }
}

void DestroySnake(struct SnakeNode **snake)
{
    struct SnakeNode *temp = NULL;

    while(*snake != NULL)
    {
        temp = *snake;
        *snake = (*snake)->next;
        free(temp);
    }
}

bool checkcode(char code[], char guess[])
{
    //variables to store number of black and white pegs
    long black_pegs = 0;
    long white_pegs = 0;

    //arrays to store if variables have been checked
    bool checked_code[4] = {false};
    bool checked_guess[4] = {false};

    //check for pegs with correct color and position
    for (long i = 0; i <= max_length; i += 1)
    {
        if (code[i] == guess[i])
        {
            black_pegs += 1;
            checked_code[i] = true;
            checked_guess[i] = true;
        }
    }

    //checks for pegs with correct color but wrong position
    for (long k = 0; k <= max_length; k += 1)
    {
        for (long m = 0; m <= max_length; m += 1)
        {
            if ((m != k) && (code[k] == guess[m]) && !checked_code[k] && !checked_guess[m])
            {
                white_pegs += 1;
                checked_code[k] = true;
                checked_guess[m] = true;
            } 
        }
    }

    //prints black and white pegs
    cs1010_print_long(black_pegs);
    cs1010_print_string(" ");
    cs1010_print_long(white_pegs);
    cs1010_println_string("");

    //check if guess is all correct
    if(black_pegs == 4 && white_pegs == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void getcode(char code[])
{
    srand(time(NULL));
    char colors[6] = {'0', '1', '2', '3', '4', '5'};
    for (long t = 0; t <= 3; t += 1)
    {
        code[t] = colors[rand()%5];
    }
}