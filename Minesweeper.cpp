//Date Created-17th April

#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include<dos.h>

#define RMAX 15
#define CMAX 15
#define REPLACE_PERCENT 10

int urow, ucol;

int calculator(int board[RMAX][CMAX], int i, int j){
    int a, b, c, d, mines=0;
    a=i-1;
    b=i+1;
    d=j+1;
    while(a<=b){
        c=j-1;
        while(c<=d){
            if(board[a][c]==9)
                mines++;
            c++;
        }
        a++;
    }
    return mines;
}

void initInputFeeder(int board[RMAX][CMAX], int urow, int ucol){
    int i, j, result;
    for(i=0; i<urow; i++){
        for(j=0; j<ucol; j++){
            if(board[i][j] != 9)
                board[i][j]=calculator(board, i, j);
        }
    }
}

void foundZero(int board[RMAX][CMAX], int checker[RMAX][CMAX], int x, int y){
    if(checker[x][y] == 0 && board[x][y] != 9 && x >= 0 && x < urow && y >= 0 && y < ucol){
        checker[x][y] = 1;
        if(board[x][y] == 0){
            foundZero(board, checker, x, y-1);          //left
            foundZero(board, checker, x, y+1);          //right
            foundZero(board, checker, x-1, y-1);        //top left
            foundZero(board, checker, x-1, y);          //top
            foundZero(board, checker, x-1, y+1);        //top right
            foundZero(board, checker, x+1, y-1);        //bottom left
            foundZero(board, checker, x+1, y);          //bottom
            foundZero(board, checker, x+1, y+1);        //bottom right
        }
    }
}

void printBoard(int board[RMAX][CMAX], int checker[RMAX][CMAX], int urow, int ucol){
    int i, j, k;
    cout<<"\t";
    for(k=0; k<ucol; k++)
        cout<<k+1<<"  ";
    cout<<"\n\n";
    for(i = 0; i < urow; i++){
        cout<<i+1<<"\t";
        for(j=0; j< ucol; j++){
            if(checker[i][j]==1){
                if(board[i][j]==9){
                    cout<<"*";
                }
                else
                    cout<<board[i][j];

                //spacing compensation for double digit columns
                if(j<9)
                    cout<<"  ";
                else
                    cout<<"   ";
            }
            else{
                cout<<".  ";
            }
        }
        cout<<"\n";
    }
}

void restart();

void main(){
    srand(time(NULL));
    int board[RMAX][CMAX]={0}, checker[RMAX][CMAX]={0}, randomn, k=0, i, j, mines, moves=0;
    initInputLabel:
    clrscr();
    cout<<"Enter number of rows: ";
    cin>>urow;
    if(urow>RMAX){
        cout<<"Please enter valid number of rows...";
        getch();
        goto initInputLabel;
    }
    cout<<"\nEnter number of cols: ";
    cin>>ucol;
    if(ucol>CMAX){
        cout<<"Please enter valid number of columns...";
        getch();
        goto initInputLabel;
    }
    mines=(int)( (REPLACE_PERCENT/100.0) * (urow*ucol)); //current replace percent is 10.0
    
    //increase mines by 1 only if percent is odd or urow X ucol is odd
    if(REPLACE_PERCENT%2!=0 || (urow*ucol)%2!=0)
        mines++;

    clrscr();
    while(k < mines){
        i=rand() % urow;
        j=rand() % ucol;
        if(board[i][j]==9)
            continue;
        board[i][j]=9;
        k++;
    }
    initInputFeeder(board, urow, ucol);
    //input
    int flag=1, x, y;
    char input[8], reply;
    while(flag==1){ //flag becomes 0 only when game over becomes true or user selects exit
        if(mines==0){
            clrscr();
            cout<<"\n\n\n\n\n\t\t\t\t  GAME OVER\n\n";
            cout<<"\t\t\t Congratulations!!! You Won...\n\n\n";
            cout<<"\t\t\t\t  Moves = "<<moves;
            break;
        }
        clrscr();
        cout<<"Mines= "<<mines<<"\nMoves= "<<moves<<endl;
        cout<<"\n";
        printBoard(board, checker, urow, ucol);
        cout<<"\n1. Input";
        cout<<"\n2. Flag a mine";
        cout<<"\n3. Exit";
        cout<<"\n>>";
        reply=getch();
        switch(reply){
            case '1':
                inputLabel:
                clrscr();
                cout<<"Mines= "<<mines<<"\nMoves= "<<moves<<endl;
                cout<<"\n";
                printBoard(board, checker, urow, ucol);
                cout<<"\nEnter row number: ";
                cin>>x;
                if(x>urow){
                    cout<<"Row number out of bounds";
                    getch();
                    goto inputLabel;
                }
                cout<<"Enter column number: ";
                cin>>y;
                if(y>ucol){
                    cout<<"Column number out of bounds";
                    getch();
                    goto inputLabel;
                }
                x--;y--;moves++;
                if(board[x][y]==0){
                    foundZero(board, checker, x, y);
                }else{
                    checker[x][y]=1;
                }
                clrscr();
                cout<<"Mines= "<<mines<<"\nMoves= "<<moves<<endl;
                cout<<"\n";
                printBoard(board, checker, urow, ucol);
                if(board[x][y]==9){
                    cout<<"\n\nGame Over!!! You stepped on a mine :(";
                    flag=0;
                }
                break;
            case '2':
                flagMineLabel:
                clrscr();
                cout<<"Mines= "<<mines<<"\nMoves= "<<moves<<endl;
                cout<<"\n";
                printBoard(board, checker, urow, ucol);
                cout<<"\nEnter row number: ";
                cin>>x;
                if(x>urow){
                    cout<<"Row number out of bounds";
                    getch();
                    goto flagMineLabel;
                }
                cout<<"Enter column number: ";
                cin>>y;
                if(y>ucol){
                    cout<<"Column number out of bounds";
                    getch();
                    goto flagMineLabel;
                }
                x--;y--;moves++;
                clrscr();
                if(board[x][y]==9){
                    cout<<"Mines= "<<mines<<" - 1"<<"\nMoves= "<<moves<<endl;
                    cout<<"\n";
                    checker[x][y]=1;
                    printBoard(board, checker, urow, ucol);
                    cout<<"\nYou found a mine";
                    mines--;
                    delay(2500);
                /*}else if(board[x][y]==0){
                    foundZero(board, checker, x, y); */
                }else{
                    checker[x][y]=1;
                    cout<<"Mines= "<<mines<<"\nMoves= "<<moves<<endl;
                    cout<<"\n";
                    printBoard(board, checker, urow, ucol);
                }
                break;
            case '3':
                cout<<"Thanks for Playing!!!";
                getch();
                exit(0);
            default:
                cout<<"Please enter a valid option";
                getch();
        }
    }
    cout<<"\n\n\n\nDo you want to play again? Y/y: ";
    cin>>reply;
    if(reply=='Y'||reply=='y')
        restart();
}

void restart(){
    main();
}