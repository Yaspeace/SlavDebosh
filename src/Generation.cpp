#include "Generation.h"
#include <iostream>
#include "stdlib.h"
#include <stdio.h>
#include <windows.h>

using namespace std;

Cell** get_mem(size_t m, size_t n) {
	Cell** pa = (Cell**)calloc(m, sizeof(Cell*));
	for (size_t i = 0; i < m; i++)
		pa[i] = (Cell*)calloc(n, sizeof(Cell));
	return pa;
}

Field::Field(int M, int N)
{
	this->M = M;
	this->N = N;
	this->a = get_mem(M,N);
}

void Field::generation()
{
	for (int i = 0; i < this->M; i++)
		for (int j = 0; j < this->N; j++)
			this->a[i][j].terrain = 'g';
	std::random_device rd;
	std::mt19937 mersenne(rd());
	int temp = mersenne() % 6;
	if (temp <= 3)
	{
		Field::make_high();
	}
	Field::make_river();
}

void Field::make_high()
{
	int t1, t2, i = 0;
	std::random_device rd;
	std::mt19937 mersenne(rd());
	int x = mersenne() % (this->M-1);
	int y = mersenne() % (this->N-1);
	int count = mersenne() % (150);
	this->a[x][y].terrain = 'h';
	while (i < count)
	{
		std::random_device rb;
		std::mt19937 mersenne(rb());
		t1 = x - 1 + (mersenne() % 3);
		t2 = y - 1 + (mersenne() % 3);
		if ((t1 < this->M) && (t2 < this->N))
		{
			if ((t1 > 0) && (t2 > 0) && (this->a[t1][t2].terrain != 'h'))
			{
				x = t1;
				y = t2;
				this->a[x][y].terrain = 'h';
				i++;
			}
			else
			{
				std::random_device rc;
				std::mt19937 mersenne(rc());
				x = mersenne() % (this->M - 1);
				y = mersenne() % (this->N - 1);
				this->a[x][y].terrain = 'h';
				i++;
			}
		}
	}
}

void Field::make_river()
{
int t1, t2, i = 0;
std::random_device rd;
std::mt19937 mersenne(rd());
int x = mersenne() % this->M;
int y = mersenne() % this->N;
int count = mersenne() % 100;
this->a[x][y].terrain = 'w';
while (i < count)
{
std::random_device rb;
std::mt19937 mersenne(rb());
int counts = (mersenne() % 3)+1;
int j = 0;
int t = 1;
while ((t + x < this->M) && (j < counts))
{
this->a[x + 1][y].terrain = 'w';
t++;
j++;
}
t = 1;
while ((x - t > 0) && (j<counts))
{
this->a[x-t][y].terrain = 'w';
j++;
t++;
}
do
{
x = x - 1 + (mersenne() % 3);
y = y - 1 + (mersenne() % 3);
} while ((this->M <= x) || (this->N <= y) || (0 >= x) || (0 >= y));
this->a[x][y].terrain = 'w';
i++;
}
}
