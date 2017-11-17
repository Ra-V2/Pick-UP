//naglowki bibliotek
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include "main.h"

//kolorki
#define RED 7500
#define BLUE 7501
#define GREEN 7502
#define YELLOW 7503
#define PINK 7504
#define BLACKBACK 7505

//zmienne globalne coord
pointONmap human;
pointONmap coin;
pointONmap score;
pointONmap timer;
pointONmap trap;

//enum sterowanie
enum edirection {STOP=0, LEFT, RIGHT, UP, DOWN};
edirection dir;

//glowna funkcja
int main()
{
    //losowosc
    srand( time( NULL ) );

    bool hardcoreMODE = 0;
    bool menuON = 1;

    menu(menuON, hardcoreMODE);
    return 0;
}

 //menu gry
 void menu(bool & menuON, bool & hardcoreMODE)
 {
    using namespace std;

    while(menuON)
    {
    dir = STOP;
    bool gameON = 1;
    system("cls");
    COLOR(YELLOW);
    cout << "\t#####################\n\t#      PICK UP      #\n\t#####################\n\n";
    COLOR(RED);
    cout << "1. Play!\n";
    COLOR(BLUE);
    cout << "2. Controls\n";
    COLOR(GREEN);
    cout << "3. Credits\n";
    COLOR(YELLOW);
    cout << "4. Options\n";
    COLOR(PINK);
    cout << "5. Exit\n";


    int choice = getch();
    switch(choice)
    {

    case 49:
    gameLoop(gameON, hardcoreMODE);
    break;

    case 50:
    controls();
    break;

    case 51:
    credits();
    break;

    case 52:
    {
        system("cls");
        COLOR(BLUE);
        cout << "HARDCORE MODE\n";
        COLOR(RED);
        cout << "1. ON\n";
        COLOR(GREEN);
        cout << "2. OFF" << endl;

        if(getch()==49)
        hardcoreMODE = 1;

        else
        hardcoreMODE = 0;

        break;
    }

    case 53:
    {
    menuON=0;
    Sleep(100);
    break;
    }

    default:
    {
    Sleep(100);
    break;
    }
    }
    }

 }

 //zmiana koloru
 void COLOR(int color)
 {
     HANDLE colhandle = GetStdHandle(STD_OUTPUT_HANDLE);

     if(color == 7500)
        SetConsoleTextAttribute(colhandle, FOREGROUND_RED);

     if(color == 7501)
        SetConsoleTextAttribute(colhandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

     if(color == 7502)
        SetConsoleTextAttribute(colhandle, FOREGROUND_GREEN);

     if(color == 7503)
        SetConsoleTextAttribute(colhandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

     if(color == 7504)
        SetConsoleTextAttribute(colhandle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

     if(color == 7505)
        SetConsoleTextAttribute(colhandle, 0);

 }

 //funkcja zmieniania kolorkow
 void colorAttack(bool & hardcoreMODE)
 {
     if(hardcoreMODE==0)
     {
     HANDLE attOFFhandle = GetStdHandle(STD_OUTPUT_HANDLE);
     int n = (rand() % 15) + 1;
     SetConsoleTextAttribute(attOFFhandle, n);
     }

     if(hardcoreMODE==1)
     {
     HANDLE attONhandle = GetStdHandle(STD_OUTPUT_HANDLE);
     int n = (rand() % 255) + 1;
     SetConsoleTextAttribute(attONhandle, n);
     }
 }

 //petla gry
void gameLoop(bool & gameON, bool & hardcoreMODE)
{
    //start
    system("cls");
    COLOR(YELLOW);
    std::cout << "\n\n\n\t\tYOU HAVE ";
    COLOR(RED);
    std::cout << "60 SECONDS";
    Sleep(2000);
    system("cls");

    //zmienne COORD
    human.X = 10;
    human.Y = 5;

    coin.X = 12;
    coin.Y = 8;

    trap.X = 9;
    trap.Y = 10;

    score.X = 17;
    score.Y = 11;

    timer.X = 7;
    timer.Y = 11;

    //tablice
    int coinX_ID[81];
    int coinY_ID[81];
    int trapX_ID[15];
    int trapY_ID[15];

    //ruchy i wynik
    int SCORE = 0;
    int MOVES = 0;

    //liczenie powtorzen
    int n = 0;
    int t = 0;
    int limC = 0;

    //zmienne czasu
    int TIMER = 60 * CLOCKS_PER_SEC;
    int timeSTOP = clock();

    //narysowanie mapy
    draw();

    //wylosowanie coin
    for(int n=(rand()%5) + 1; n<6; n++)
        randCoin(coin,human,n,coinX_ID,coinY_ID,trapX_ID,trapY_ID);

    //naryswanie gracza
    changePosition(human);
    COLOR(RED);
    std::cout << "X";

    //ustawienie wyniku
    COLOR(YELLOW);
    changePosition(score);
    std::cout << SCORE;

    //petla gry
    while(gameON)
    {
        clock_t check = clock();

        changePosition(timer);
        COLOR(GREEN);
        std::cout << (check - timeSTOP) / CLOCKS_PER_SEC;

    colorAttack(hardcoreMODE);
    input(gameON, SCORE, MOVES);
    upload(human, coin, SCORE, MOVES, n, t, coinX_ID, coinY_ID, trapX_ID, trapY_ID, limC, gameON);
    Sleep(200);

        if((TIMER+timeSTOP)<check)
        {
        gameON=0;
        endScene(SCORE, MOVES);
        }
    }
}

//zmiana pozycji kursora
void changePosition(pointONmap coordinates)
{
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coordinates );
}

//sterowanie
void input(bool & gameON, int & SCORE, int & MOVES)
{
    if(kbhit())
    {
        switch(getch())
        {
            case 'a':
            dir = LEFT;
            break;

            case 'd':
            dir = RIGHT;
            break;

            case 'w':
            dir = UP;
            break;

            case 's':
            dir = DOWN;
            break;

            case 'x':
            {
            gameON=0;
            endScene(SCORE, MOVES);

            break;
            }
            default:
            dir = STOP;
            break;
        }
    }

}
//rysowanie mapy
void draw()
{
using namespace std;

system("cls");
COLOR(BLUE);
cout << "#####################\n";
cout << "#                   #\n";
cout << "#                   #\n";
cout << "#                   #\n";
cout << "#                   #\n";
cout << "#                   #\n";
cout << "#                   #\n";
cout << "#                   #\n";
cout << "#                   #\n";
cout << "#                   #\n";
cout << "#####################\n";
COLOR(BLUE);
cout << "#";
COLOR(GREEN);
cout << " TIME:";
COLOR(YELLOW);
cout << "    SCORE:   ";
COLOR(BLUE);
cout << "#\n#####################";

}

//losowanie coin
void randCoin(pointONmap & coin, pointONmap & human, int & n, int coinX_ID[], int coinY_ID[], int trapX_ID[], int trapY_ID[])
{

    coin.X = (rand() % 18) + 1;
    coin.Y = (rand() % 9) + 1;

    if(coin.X == human.X && coin.Y == human.Y)
    {

        if(coin.X!=19)
         coin.X++;
        else
         coin.X--;
    }

    for(int k = 0; k<=14; k++)
    {
        if(coin.X == trapX_ID[k] && coin.Y == trapY_ID[k])
        {
        if(coin.X!=19)
         coin.X++;
        else
         coin.X--;
        }
    }

        coinX_ID[n] = coin.X;
        coinY_ID[n] = coin.Y;
        n++;
        changePosition(coin);
        COLOR(YELLOW);
        std::cout << "O";
}

//losowanie trap
void randTrap(pointONmap & trap, pointONmap & human, int & t, int trapX_ID[], int trapY_ID[])
{
    trap.X = (rand() % 18) + 1;
    trap.Y = (rand() % 9) + 1;

    for(int n = 0; n<4; n++)
    {
    if(trap.X + n == human.X && trap.Y + n == human.Y)
    {
        trap.X += 4;
        if(trap.X<1)
            trap.X+=8+n;
        if(trap.X>19)
            trap.X-=8+n;
    }
        if(trap.X - n == human.X && trap.Y + n == human.Y)
    {
        trap.X += 4;
        if(trap.X<1)
            trap.X+=8+n;
        if(trap.X>19)
            trap.X-=8+n;
    }
        if(trap.X + n == human.X && trap.Y - n == human.Y)
    {
        trap.X += 4;
        if(trap.X<1)
            trap.X+=8+n;
        if(trap.X>19)
            trap.X-=8+n;
    }
        if(trap.X - n == human.X && trap.Y - n == human.Y)
    {
        trap.X += 4;
        if(trap.X<1)
            trap.X+=8+n;
        if(trap.X>19)
            trap.X-=8+n;
    }

    }

    trapX_ID[t] = trap.X;
    trapY_ID[t] = trap.Y;
    changePosition(trap);
    COLOR(RED);
    std::cout << "O";
    t++;
}

//aktualizowanie
void upload(pointONmap & human, pointONmap & coin, int & SCORE, int & MOVES, int & n, int & t, int coinX_ID[], int coinY_ID[], int trapX_ID[], int trapY_ID[], int & limC, bool & gameON)
{

//ruchy
switch(dir)
{
using namespace std;
COLOR(YELLOW);
case LEFT:
    {
    changePosition(human);
    cout << " ";
    if(human.X!=1)
    {
        human.X -= 1;
        MOVES++;
    }
    changePosition(human);
    cout << "X";
    changePosition(score);
    break;
    }
case RIGHT:
    {
    changePosition(human);
    cout << " ";
    if(human.X!=19)
    {
        human.X += 1;
        MOVES++;
    }
    changePosition(human);
    cout << "X";
    changePosition(score);
    break;
    }
case UP:
    {
    changePosition(human);
    cout << " ";
    if(human.Y!=1)
    {
        human.Y -= 1;
        MOVES++;
    }
    changePosition(human);
    cout << "X";
    changePosition(score);
    break;
    }
case DOWN:
    {
    changePosition(human);
    cout << " ";
    if(human.Y!=9)
    {
        human.Y += 1;
        MOVES++;
    }
    changePosition(human);
    cout << "X";
    changePosition(score);
    break;
    }

}

    //coin
    if(limC<10)
    {
    int randomC = (rand()%10)+1;
    if(randomC == 5)
    {
        for(int l=(rand()%3) + 1; l<4; l++)
        {
            randCoin(coin, human, n, coinX_ID, coinY_ID,trapX_ID,trapY_ID);
            limC++;
        }
    }
    }

    for(int h = 0; h<=81; h++)
    {

        if(coinX_ID[h]==human.X && coinY_ID[h]==human.Y)
        {
            limC--;
            SCORE++;
            COLOR(YELLOW);
            changePosition(score);
            std::cout << SCORE;
            coinX_ID[h] = 0;
            coinY_ID[h] = 0;
        }
    }

    //trap
    int randomT = (rand()%30)+1;
    if(randomT == 5)
    {
        randTrap(trap, human, t, trapX_ID, trapY_ID);
    }

    for(int h = 0; h<=14; h++)
    {
        if(trapX_ID[h]==human.X && trapY_ID[h]==human.Y)
    {
        gameON = 0;
        endScene(SCORE, MOVES);
    }
    }

}

//sterowanie
void controls()
{
    using namespace std;
    COLOR(YELLOW);
    system("cls");
    cout << "W - UP\n";
    cout << "A - LEFT\n";
    cout << "S - DOWN\n";
    cout << "D - RIGHT\n";
    cout << "x - EXIT\n";

    if(getch())
        Sleep(100);
}

//tworca
void credits()
{
    using namespace std;
    system("cls");
    COLOR(PINK);
    cout << "\t\tGame by";
    COLOR(RED);\
    cout << " RaV2\n";
    if(getch())
    Sleep(100);
}
//wyniki
void endScene(int & SCORE, int & MOVES)
{
    using namespace std;
    COLOR(BLACKBACK);
    system("cls");
    COLOR(YELLOW);
    cout << "\n\n\n\n\tSCORE: " << SCORE;
    COLOR(BLUE);
    cout << "   MOVES: " << MOVES;
    Sleep(3000);
}
