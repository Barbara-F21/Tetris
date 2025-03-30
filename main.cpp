#include <iostream>
#include <graphics.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdio.h>
#include "tetris.h"

using namespace std;

void Destroy(Matrix* a);
int setValue(Matrix*, int, int, int);
int getValue(Matrix*, int, int);
void Print(Matrix*);
void Copy(Matrix* a, Matrix* b);
void Sorszerintibejaras(Matrix*);
void Oszlopszerintibejaras(Matrix*);
void Sortorles(Matrix*,int sor);
void Oszloptorles(Matrix*,int oszlop);
void Elfordit(Matrix*,int n);
void ElforditCounterClockvise(Matrix* a, int oldal);
bool Bennevane(Matrix *a,int x);


void rajzolnegyzet(int szin,int i,int j)
{
    setfillstyle(SOLID_FILL,szin);
    rectangle(i*35+10,j*35+10,i*35+45,j*35+45);
    floodfill(i*35+11,j*35+11,WHITE);
}

void rajzolgat(Matrix *a)
{
    for(int i=1;i<=20;i++)
    {
        for(int j=1;j<=10;j++)
        {
            if(a->matrixa[i][j]>0)
            {
                rajzolnegyzet(a->matrixa[i][j],j,i);
            }
        }
    }
}

void keret(Matrix *a)
{
    for(int i=0;i<=11;i++)
    {
        a->matrixa[0][i]=-1;
        a->matrixa[21][i]=-1;
    }
    for(int i=1;i<=21;i++)
    {
        a->matrixa[i][0]=-1;
        a->matrixa[i][11]=-1;
    }
}
void kiir(Matrix *a)
{
    for(int i=0;i<=21;i++)
    {
        for(int j=0;j<=11;j++)
        {
            cout<<a->matrixa[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void torolasor(Matrix *a,int sor)
{
    for(int i=sor;i>=2;i--)
    {
        for(int j=1;j<=10;j++)
        {
            a->matrixa[i][j]=a->matrixa[i-1][j];
        }
    }
}

void sormegtelt(Matrix *a,int &score,bool &frissul)
{
    int db=0;
    frissul=false;
    for(int i=20;i>=1;i--)
    {
        db=0;
        for(int j=1;j<=10;j++)
        {
            if(a->matrixa[i][j]!=0)
            {
                db++;
            }
        }
        if(db==10)
        {
            score=score+1;
            frissul=true;
            torolasor(a,i);
            i++;
        }
    }
}

bool mindenkoordinatajo(Matrix *a,koordinata *koordinatak)
{
    int i=1;
    bool t=true;
    while(i<=4 && t)
    {
        if(a->matrixa[koordinatak[i].y+1][koordinatak[i].x]!=0)// mivel az Oy tengely a fuggoleges, ezert a sornak az y felel meg, az Ox pedig vizszintes, így az oszlopnak az x felel meg;
        {
            return false;
        }
        i++;
    }
    return true;
}

bool ureselsosor(Matrix *a)
{
    int j=3;
    while(j<=7 && a->matrixa[1][j]==0)
    {
        j++;
    }
    if(j>7) return true;
     else return false;
}

void keretje()
{
    setfillstyle(SOLID_FILL,3);
    for(int i=0;i<22;i++)
    {
       rectangle(10,10+i*35,45,45+i*35);
       rectangle(395,10+i*35,430,45+i*35);
       floodfill(11,11+i*35,WHITE);
       floodfill(396,11+i*35,WHITE);
    }
    for(int i=1;i<11;i++)
    {
        rectangle(10+i*35,10,45+i*35,45);
        rectangle(10+i*35,745,45+i*35,780);
        floodfill(11+i*35,11,WHITE);
        floodfill(11+i*35,746,WHITE);
    }
}
void elfordul_1(koordinata *koordinatak,int k,int eltolx,int eltoly)//.#.
{
    k=k%4+1;
    switch (k)
    {
        case 1:{koordinatak[1]={1+eltolx,2+eltoly};koordinatak[2]={2+eltolx,1+eltoly};koordinatak[3]={2+eltolx,2+eltoly};koordinatak[4]={3+eltolx,2+eltoly};break;}
        case 2:{koordinatak[1]={1+eltolx,2+eltoly};koordinatak[2]={2+eltolx,1+eltoly};koordinatak[3]={2+eltolx,2+eltoly};koordinatak[4]={2+eltolx,3+eltoly};break;}
        case 3:{koordinatak[1]={1+eltolx,2+eltoly};koordinatak[2]={2+eltolx,2+eltoly};koordinatak[3]={2+eltolx,3+eltoly};koordinatak[4]={3+eltolx,2+eltoly};break;}
        case 4:{koordinatak[1]={2+eltolx,1+eltoly};koordinatak[2]={2+eltolx,2+eltoly};koordinatak[3]={2+eltolx,3+eltoly};koordinatak[4]={3+eltolx,2+eltoly};break;}
    }
}
void elfordul_2(koordinata *koordinatak,int k,int eltolx,int eltoly)//vobal
{
    k=k%2+1;
    switch (k)
    {
        case 1:{koordinatak[1]={1+eltolx,1+eltoly};koordinatak[2]={2+eltolx,1+eltoly};koordinatak[3]={3+eltolx,1+eltoly};koordinatak[4]={4+eltolx,1+eltoly};break;}
        case 2:{koordinatak[1]={1+eltolx,1+eltoly};koordinatak[2]={1+eltolx,2+eltoly};koordinatak[3]={1+eltolx,3+eltoly};koordinatak[4]={1+eltolx,4+eltoly};break;}
    }
}
void elfordul_3(koordinata *koordinatak,int k,int eltolx,int eltoly)//_#
{
    k=k%4+1;
    switch (k)
    {
        case 1:{koordinatak[1]={1+eltolx,2+eltoly};koordinatak[2]={2+eltolx,2+eltoly};koordinatak[3]={3+eltolx,1+eltoly};koordinatak[4]={3+eltolx,2+eltoly};break;}
        case 2:{koordinatak[1]={1+eltolx,1+eltoly};koordinatak[2]={2+eltolx,1+eltoly};koordinatak[3]={2+eltolx,2+eltoly};koordinatak[4]={2+eltolx,3+eltoly};break;}
        case 3:{koordinatak[1]={1+eltolx,2+eltoly};koordinatak[2]={1+eltolx,3+eltoly};koordinatak[3]={2+eltolx,2+eltoly};koordinatak[4]={3+eltolx,2+eltoly};break;}
        case 4:{koordinatak[1]={2+eltolx,1+eltoly};koordinatak[2]={2+eltolx,2+eltoly};koordinatak[3]={2+eltolx,3+eltoly};koordinatak[4]={3+eltolx,3+eltoly};break;}

    }
}
void elfordul_4(koordinata *koordinatak,int k,int eltolx,int eltoly)//#_
{
    k=k%4+1;
    switch (k)
    {
        case 1:{koordinatak[1]={1+eltolx,1+eltoly};koordinatak[2]={1+eltolx,2+eltoly};koordinatak[3]={2+eltolx,2+eltoly};koordinatak[4]={3+eltolx,2+eltoly};break;}
        case 2:{koordinatak[1]={2+eltolx,1+eltoly};koordinatak[2]={2+eltolx,2+eltoly};koordinatak[3]={2+eltolx,3+eltoly};koordinatak[4]={3+eltolx,1+eltoly};break;}
        case 3:{koordinatak[1]={1+eltolx,2+eltoly};koordinatak[2]={2+eltolx,2+eltoly};koordinatak[3]={3+eltolx,2+eltoly};koordinatak[4]={3+eltolx,3+eltoly};break;}
        case 4:{koordinatak[1]={1+eltolx,3+eltoly};koordinatak[2]={2+eltolx,1+eltoly};koordinatak[3]={2+eltolx,2+eltoly};koordinatak[4]={2+eltolx,3+eltoly};break;}
    }
}

void elfordul_5(koordinata *koordinatak,int k,int eltolx,int eltoly)//negyzet
{
   koordinatak[1]={1+eltolx,1+eltoly};koordinatak[2]={1+eltolx,2+eltoly};koordinatak[3]={2+eltolx,1+eltoly};koordinatak[4]={2+eltolx,2+eltoly};
}

void elfordul_6(koordinata *koordinatak,int k,int eltolx,int eltoly)// forditva z
{
    k=k%2+1;
    switch (k)
    {
        case 1:{koordinatak[1]={1+eltolx,2+eltoly};koordinatak[2]={2+eltolx,2+eltoly};koordinatak[3]={2+eltolx,3+eltoly};koordinatak[4]={3+eltolx,3+eltoly};break;}
        case 2:{koordinatak[1]={1+eltolx,2+eltoly};koordinatak[2]={1+eltolx,3+eltoly};koordinatak[3]={2+eltolx,1+eltoly};koordinatak[4]={2+eltolx,2+eltoly};break;}
    }
}

void elfordul_7(koordinata *koordinatak,int k,int eltolx,int eltoly)// z
{
    k=k%2+1;
    switch (k)
    {
        case 1:{koordinatak[1]={1+eltolx,3+eltoly};koordinatak[2]={2+eltolx,2+eltoly};koordinatak[3]={2+eltolx,3+eltoly};koordinatak[4]={3+eltolx,2+eltoly};break;}
        case 2:{koordinatak[1]={1+eltolx,1+eltoly};koordinatak[2]={1+eltolx,2+eltoly};koordinatak[3]={2+eltolx,2+eltoly};koordinatak[4]={2+eltolx,3+eltoly};break;}
    }
}

void modositaskoordinatakon(koordinata *koordinatak,int k,int eltolx,int eltoly,int alakjel)
{
    switch(alakjel)
    {
        case 1:{ elfordul_1(koordinatak,k,eltolx,eltoly);break;}
        case 2:{ elfordul_2(koordinatak,k,eltolx,eltoly);break;}
        case 3:{ elfordul_3(koordinatak,k,eltolx,eltoly);break;}
        case 4:{ elfordul_4(koordinatak,k,eltolx,eltoly);break;}
        case 5:{ elfordul_5(koordinatak,k,eltolx,eltoly);break;}
        case 6:{ elfordul_6(koordinatak,k,eltolx,eltoly);break;}
        case 7:{ elfordul_7(koordinatak,k,eltolx,eltoly);break;}
    }
}

void rajzolkoordinatakszerint(koordinata *koordinatak,int szin)
{
    for(int i=1;i<=4;i++)
    {
        setfillstyle(SOLID_FILL,szin);
        rectangle(koordinatak[i].x*35+10,koordinatak[i].y*35+10,koordinatak[i].x*35+45,koordinatak[i].y*35+45);
        floodfill(koordinatak[i].x*35+11,koordinatak[i].y*35+11,WHITE);
    }
}

void randomizal(int &mivolt,koordinata *koordinatak,int &alakjel)
{
    int k=rand()%7+1;
    switch(k)
    {
        case 1:{elfordul_1(koordinatak,0,4,0);alakjel=1;mivolt=5;break;}
        case 2:{elfordul_2(koordinatak,0,4,0);alakjel=2;mivolt=11;break;}
        case 3:{elfordul_3(koordinatak,0,4,0);alakjel=3;mivolt=14;break;}
        case 4:{elfordul_4(koordinatak,0,4,0);alakjel=4;mivolt=1;break;}
        case 5:{elfordul_5(koordinatak,0,4,0);alakjel=5;mivolt=9;break;}
        case 6:{elfordul_6(koordinatak,0,4,0);alakjel=6;mivolt=4;break;}
        case 7:{elfordul_7(koordinatak,0,4,0);alakjel=7;mivolt=2;break;}
    }
}

void Torolbuffer()
{
    while (kbhit())
    {
        getch();
    }
}

void frissitpont(int pontok,char *b)
{
    string pontokString = to_string(pontok);
    strcpy(b, pontokString.c_str());
}

void pontszam(char *b)
{
    settextstyle(10,0,4);
    outtextxy(500,200,"TETRIS");
    settextstyle(3,0,5);
    outtextxy(480,300,"SCORE");
    outtextxy(550,340,b);
}


//magenta -> 5
//yellow -> 14
//red -> 4
//green -> 2
//lightcyan -> 11
//kek -> 1
//light blue -> 9

int legkisebbkoordinata(koordinata *koordinatak)
{
    int min=100;
    for(int i=1;i<=4;i++)
    {
        if(min>koordinatak[i].x)
        {
            min=koordinatak[i].x;
        }
    }
    return min;
}
int legnagyobbkoordinata(koordinata *koordinatak)
{
    int max=0;
    for(int i=1;i<=4;i++)
    {
        if(max<koordinatak[i].x)
        {
            max=koordinatak[i].x;
        }
    }
    return max;
}

void firstframe()
{
    settextstyle(10,0,5);
    outtextxy(260,330,"PLAY");
    settextstyle(3,0,4);
    outtextxy(70,400,"Press a button to start the game!");
}

void lastframe(int score,char *b)
{
    settextstyle(10,0,5);
    outtextxy(70,330,"GAME OVER!");
    settextstyle(3,0,4);
    frissitpont(score,b);
    outtextxy(120,400,"Final Score");
    outtextxy(200,440,b);
}

void foresz(koordinata *koordinatak, Matrix *a)
{
    int k=0,jobrabalra=0;
    int page=0;
    int mivolt=0,alakjel=0;
    int score=0;
    char *b=new char[20]{};
    bool g=false;
    int i=0;

    frissitpont(score,b);

    int min=0;
    int max=0;

    while(ureselsosor(a))
    {
        k=0;
        jobrabalra=0;
        randomizal(mivolt,koordinatak,alakjel);
        g=false;i=0;

        do
       {
          setactivepage(page);
          setvisualpage(1-page);

          delay(300);
          cleardevice();
          keretje();
          rajzolgat(a);
          pontszam(b);

          if(GetAsyncKeyState(VK_SPACE))
         {
             k++;
             modositaskoordinatakon(koordinatak,k,4+jobrabalra,i,alakjel);
             if(!mindenkoordinatajo(a,koordinatak))
             {
                 k--;
                 modositaskoordinatakon(koordinatak,k,4+jobrabalra,i,alakjel);
             }
         }
          else
         {

             if(GetAsyncKeyState(VK_LEFT))
             {
                 min=legkisebbkoordinata(koordinatak);
                 if(min>1)
                 jobrabalra--;
             }
             else
             {
                 if(GetAsyncKeyState(VK_RIGHT))
                {
                    max=legnagyobbkoordinata(koordinatak);
                    if(max<10)
                    jobrabalra++;
                }
             }
             modositaskoordinatakon(koordinatak,k,4+jobrabalra,i,alakjel);
         }

         rajzolkoordinatakszerint(koordinatak,mivolt);

         page=1-page;
         i++;
       }while(mindenkoordinatajo(a,koordinatak));

         for(int j=1;j<=4;j++)
        {
             a->matrixa[koordinatak[j].y][koordinatak[j].x]=mivolt;
        }
       sormegtelt(a,score,g);
       if(g)
       {
           frissitpont(score,b);
       }
       system("cls");
       kiir(a); // azert nem a matrixos print, mert altalaban 1-estol indexelunk ott, itt meg a keret miatt 0-tol.
    }
    setvisualpage(1-page);

    lastframe(score,b);
}

int main()
{
    srand(time(NULL));

    Matrix *a=Create(22,12);
    keret(a);

    initwindow(700,790);

    koordinata *koordinatak;
    koordinatak=new koordinata[5];

    firstframe();
    getch();
    foresz(koordinatak,a);

    Torolbuffer();
    getch();
    closegraph();

    delete []koordinatak;
    Destroy(a);

    return 0;
}
