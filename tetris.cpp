#include <iostream>
#include "tetris.h"

using namespace std;

Matrix* Create(int n, int m)
{
	Matrix* a;
	a = new Matrix;
	a->matrixa = new int* [n+1] {};

	for (int i = 0; i <= n; i++)
	{
		a->matrixa[i] = new int[m+1] {};
	}
	a->n = n;
	a->m = m;

	return a;
}

void Destroy(Matrix* a)
{
	for (int i = 0; i <= a->m; i++)
	{
		delete[]a->matrixa[i];
	}
	delete a;
}

int setValue(Matrix* a, int i, int j, int x)
{
	a->matrixa[i][j] = x;
	return x;
}

int getValue(Matrix* a, int i, int j)
{
	return a->matrixa[i][j];
}

void Print(Matrix* a)
{
	for (int i = 1; i <= a->n; i++)
	{
		for (int j = 1; j <= a->m; j++)
		{
			cout << a->matrixa[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Copy(Matrix* a, Matrix* b)
{
	for (int i = 1; i <= a->n; i++)
	{
		for (int j = 1; j <= a->m; j++)
		{
			a->matrixa[i][j] = b->matrixa[i][j];
		}
	}
}

void Sorszerintibejaras(Matrix* a)
{
	for (int i = 1; i <= a->n; i++)
	{
		for (int j = 1; j <= a->m; j++)
		{
			cout << a->matrixa[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Oszlopszerintibejaras(Matrix* a)
{
	for (int j = 1; j <= a->m; j++)
	{
		for (int i = 1; i <= a->n; i++)
		{
			cout << a->matrixa[j][i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


void Elfordit(Matrix* a, int oldal)
{
	for (int i = 1; i <= oldal / 2; i++)
	{
		for (int j = i; j < oldal - i + 1; j++)
		{
			int seged = a->matrixa[i][j];
			a->matrixa[i][j] = a->matrixa[oldal - j + 1][i];
			a->matrixa[oldal - j + 1][i] = a->matrixa[oldal - i + 1][oldal - j + 1];
			a->matrixa[oldal - i + 1][oldal - j + 1] = a->matrixa[j][oldal - i + 1];
			a->matrixa[j][oldal - i + 1] = seged;
		}
	}
}

void Sortorles(Matrix* a, int sor)
{
	for (int i = sor; i < a->n; i++)
	{
		for (int j = 1; j <= a->m; j++)
		{
			a->matrixa[i][j] = a->matrixa[i + 1][j];
		}
	}
	a->n--;
}

void Oszloptorles(Matrix* a, int oszlop)
{
	for (int j = oszlop; j < a->m; j++)
	{
		for (int i = 1; i <= a->n; i++)
		{
			a->matrixa[i][j] = a->matrixa[i][j + 1];
		}
	}
	a->m--;
}

void ElforditCounterClockvise(Matrix* a, int oldal)
{
	int ind = oldal;
	Matrix* seged = Create(a->n, a->m);

	for (int i = 1; i <= oldal; i++)
	{
		for (int j = 1; j <= oldal; j++)
		{
			seged->matrixa[i][j] = a->matrixa[j][ind];
		}
		ind--;
	}
	Copy(a, seged);
}
bool Bennevane(Matrix *a,int x)
{
    for(int i=1;i<=a->n;i++)
    {
        for(int j=1;j<=a->m;j++)
        {
            if(a->matrixa[i][j]==x)
            {
                return true;
            }
        }
    }

}

