#include <iostream>
#include <conio.h>
#include <windows.h>

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGTH, UP, DOWN }; 
eDirection dir;
int tailX[100], tailY[100];
int nTail;

void Draw()
{
    system("cls");
    for (int i = 0; i < width; i++){
        std::cout << "#";
    }
    std::cout << std::endl;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if( j == 0 ){
                std::cout << "#";
            }else
            if( j == x && i == y ){
                std::cout << "O";
            }else
            if( j == fruitX && i == fruitY ){
                std::cout << "F";
            }else
            if( j == (width - 1) ){
                std::cout << "#";
            }else{
                bool print = false;
                for (int k = 1; k <= nTail; k++)
                { 
                    if( j == tailX[k] && i == tailY[k] ){
                        std::cout << "o";
                        print = true;
                    } 
                }
                if(!print){
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < width; i++){
        std::cout << "#";
    }
    std::cout << std::endl;
    std::cout << "Score: " << score;
}

void Logic()
{
    tailX[0] = x;
    tailY[0] = y;
    for (int i = nTail; i > 0; i--)
    {
        tailX[i] = tailX[i-1];
        tailY[i] = tailY[i-1];
    }
    switch(dir){
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGTH:
            x++;
            break;
    }
    if( x > width || x < 0 || y > height || y < 0 ){
        gameOver = true;    
    }
    for (int i = 0; i < nTail; i++)
    {
        if( x == tailX[i] && y == tailY[i] ){
            gameOver = true;
        }
    }
    if( x == fruitX && y == fruitY ){
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void Input()
{
    if( _kbhit()){
        switch (_getch())
        {
            case 'w':
                dir = UP;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGTH;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}


int main()
{
    Setup();
    while( gameOver == false){
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    return 0;
}

