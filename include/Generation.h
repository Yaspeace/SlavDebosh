#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include "Unit.h"
#include "Building.h"
#include "Resourse.h"

struct Cell
{
	char terrain;
	char flora;
	Resourse *resourse = 0;
	bool isChosen = false;
};

Cell** get_mem(size_t m, size_t n);

class Field
{
public:
	int M;
	int N;
	Cell** a;
//public:
	Field(int M,int N);
	void generation();
	void output_field();
	Unit* GetChosenUnit();
private:
	void make_high();
	void make_river();
};
