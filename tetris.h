#ifndef TETRIS_H
#define TETRIS_H

typedef struct Matrix {

	int n, m; //n - sorok szama, m - oszlopok szama;
	int** matrixa;

}Matrix;

struct koordinata{int x;int y;};

Matrix* Create(int, int);

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

#endif;
