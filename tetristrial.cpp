#include <stdio.h>
#include <iostream>
#include <string>
#include <ncurses.h>

std::string tetrimino[13];
int nFieldHeight = 12;
int nFieldWidth = 15;
int linecount = 0;
int nCurrentPiece = 5;
int nCurrentX = nFieldWidth/2;
int nCurrentY = 0;
char input;

void draw(unsigned char* p);
bool doesPieceFit(unsigned char* p, int currentx, int currenty, int piecey, int piecex);
void movePiece(char input);
void checkLine(unsigned char* pField);

unsigned char* pField = nullptr;

//Draw Field
void draw(unsigned char* p){
    for(int y = 0; y < nFieldHeight; y++){
        for(int x = 0; x < nFieldWidth; x++){
            printw("%c",p[y * nFieldWidth + x]);
        }
        printw("\n");
    }
    //Draw Piece
    for(int py = 0; py < 4; py++){
        for(int px = 0; px < 4; px++){
            if(tetrimino[nCurrentPiece][py * 4 + px] == 'X'){
                mvaddch(nCurrentY + py, nCurrentX + px, 'X');
            }
        }
    }
}

//doesPiceFit
bool doesPieceFit(unsigned char* p, int newX, int newY){
    for(int py = 0; py < 4; py++){
        for(int px = 0; px < 4; px++){
            if(newX + px == nFieldWidth - 1 && tetrimino[nCurrentPiece][py * 4 + px] == 'X'){ // Check for right boundry
                return false;
            }
            if(newX + px == 0 && tetrimino[nCurrentPiece][py * 4 + px] == 'X'){ // Check for left boundry
                return false;
            }
            if(pField[(newY + py) * nFieldWidth +(newX + px)] != ' ' && tetrimino[nCurrentPiece][py * 4 + px] == 'X'){ // Check for other pieces and ground
                for(int y = 0; y < 4; y++){
                    for(int x = 0; x < 4; x++){
                        if(tetrimino[nCurrentPiece][y * 4 + x] == 'X'){
                            pField[(nCurrentY + y) * nFieldWidth + (nCurrentX + x)] = 'X';
                        }
                    }
                }
                nCurrentY = 0;
                nCurrentX = nFieldWidth / 2;
                //nCurrentPiece = nCurrentPiece + 1;
                return false;
            }
        }
    }
    return true;
}

//movePiece
void movePiece(char input){
    if(input == 'd' && doesPieceFit(pField, nCurrentX + 1, nCurrentY)){
        nCurrentX = nCurrentX + 1;
    }
    if(input == 'a' && doesPieceFit(pField, nCurrentX - 1, nCurrentY)){
        nCurrentX = nCurrentX - 1;
    }
    if(input == 's' && doesPieceFit(pField, nCurrentX, nCurrentY + 1)){
        nCurrentY = nCurrentY + 1;
    }
    if(input == 'w' && doesPieceFit(pField, nCurrentX, nCurrentY - 1)){
        nCurrentY = nCurrentY - 1;
    }
    if(input == 'r'){
        if(nCurrentPiece == 0){
            nCurrentPiece = 5;
            return;
        }
        if(nCurrentPiece == 5){
            nCurrentPiece = 0;
            return;
        }
        if(nCurrentPiece == 1){
            nCurrentPiece = 7;
            return;
        }
        if(nCurrentPiece == 7){
            nCurrentPiece = 6;
            return;
        }
        if(nCurrentPiece == 6){
            nCurrentPiece = 8;
            return;
        }
        if(nCurrentPiece == 8){
            nCurrentPiece = 1;
            return;
        }
        if(nCurrentPiece == 2){
            nCurrentPiece = 11;
            return;
        }
        if(nCurrentPiece == 11){
            nCurrentPiece = 10;
            return;
        }
        if(nCurrentPiece == 10){
            nCurrentPiece = 9;
            return;
        }
        if(nCurrentPiece == 9){
            nCurrentPiece = 2;
            return;
        }
        if(nCurrentPiece == 4){
            nCurrentPiece = 12;
            return;
        }
        if(nCurrentPiece == 12){
            nCurrentPiece = 4;
            return;
        }
    }
}

void checkLine(unsigned char* pField){
    for(int y = nFieldHeight - 2; y > 0; y--){
        for(int x = 1; x < nFieldWidth - 1; x++){
            if(pField[y * nFieldWidth + x] == 'X'){
                linecount = linecount + 1;
            }
            if(linecount == nFieldWidth - 2){ //If line is full, shift all lines above the full line -1 downwards
                for(int yShift = y; yShift > 0; yShift--){
                    for(int cx = 1; cx < nFieldWidth - 1; cx++){
                        pField[yShift * nFieldWidth + cx] = pField[(yShift - 1) * nFieldWidth + cx]; 
                    }
                }
            }
        }
        linecount = 0;
    }
}

int main(){

    //Assets
    tetrimino[0].append("..X.");
    tetrimino[0].append("..X.");
    tetrimino[0].append("..X.");
    tetrimino[0].append("..X.");

    tetrimino[1].append(".XXX");
    tetrimino[1].append("..X.");
    tetrimino[1].append("....");
    tetrimino[1].append("....");

    tetrimino[2].append("..X.");
    tetrimino[2].append("..X.");
    tetrimino[2].append(".XX.");
    tetrimino[2].append("....");

    tetrimino[3].append(".XX.");
    tetrimino[3].append(".XX.");
    tetrimino[3].append("....");
    tetrimino[3].append("....");

    tetrimino[4].append(".XX.");
    tetrimino[4].append("..XX");
    tetrimino[4].append("....");
    tetrimino[4].append("....");

    //Rotated Assets
    tetrimino[5].append("....");
    tetrimino[5].append("....");
    tetrimino[5].append("XXXX");
    tetrimino[5].append("....");

    tetrimino[6].append("....");
    tetrimino[6].append("..X.");
    tetrimino[6].append(".XXX");
    tetrimino[6].append("....");

    tetrimino[7].append("...X");
    tetrimino[7].append("..XX");
    tetrimino[7].append("...X");
    tetrimino[7].append("....");

    tetrimino[8].append(".X..");
    tetrimino[8].append(".XX.");
    tetrimino[8].append(".X..");
    tetrimino[8].append("....");

    tetrimino[9].append("....");
    tetrimino[9].append("....");
    tetrimino[9].append("XXX.");
    tetrimino[9].append("..X.");

    tetrimino[10].append("....");
    tetrimino[10].append("..XX");
    tetrimino[10].append("..X.");
    tetrimino[10].append("..X.");

    tetrimino[11].append(".X..");
    tetrimino[11].append(".XXX");
    tetrimino[11].append("....");
    tetrimino[11].append("....");

    tetrimino[12].append("..X.");
    tetrimino[12].append(".XX.");
    tetrimino[12].append(".X..");
    tetrimino[12].append("....");
    
    pField = new unsigned char[nFieldHeight * nFieldWidth]; // Create and fill field #         #
    for(int y = 0; y < nFieldHeight; y++){
        for(int x = 0; x < nFieldWidth; x++){
            pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? '#' : ' ';
        }
    }

    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    while(input !='x'){
        draw(pField);
        //checkLine(pField);
        move(nFieldHeight, 0);
        printw("%i", nCurrentY);
        refresh();
        input = getch();
        movePiece(input);
        checkLine(pField);
        clear();
    }
    endwin();
}