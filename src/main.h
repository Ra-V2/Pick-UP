#ifndef MAIN_H
#define MAIN_H
//typ COORD
typedef COORD pointONmap;
//prototypy funckji
void menu(bool & menuON, bool & hardcoreMODE);
void credits(void);
void controls(void);
void gameLoop(bool & gameON, bool & hardcoreMODE);
void input(bool & gameON, int & SCORE, int & MOVES);
void upload(pointONmap & human, pointONmap & coin, int & SCORE, int & MOVES, int & n, int & t, int coinX_ID[], int coinY_ID[], int trapX_ID[], int trapY_ID[], int & limC, bool & gameON);
void draw(void);
void changePosition(pointONmap coordinates);
void COLOR(int color);
void randCoin(pointONmap & coin, pointONmap & human, int & n, int coinX_ID[], int coinY_ID[], int trapX_ID[], int trapY_ID[]);
void randTrap(pointONmap & trap, pointONmap & human, int & t, int trapX_ID[], int trapY_ID[]);
void colorAttack(bool & hardcoreMODE);
void endScene(int & SCORE, int & MOVES);

#endif MAIN_H
