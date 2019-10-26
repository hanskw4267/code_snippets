#include <stdio.h>
#include <time.h>
#include <windows.h>

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