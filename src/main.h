#pragma once
#ifndef MAIN_H
#define MAIN_H


const char polar[] = { "polar" };
const char cartesian[] = { "cartesian" };

typedef struct {
	const char* face; // define pointer face   
	const char* suit; // define pointer suit
	unsigned int face_number; // Define o número da face da carta
	unsigned int suit_number; // Define o número do naipe
	char* mode;
} Card; // end struct card    

typedef struct {
	double a;
	double b;
} Cart;

typedef struct {
	double r;
	double g;
} Pol;

typedef union {
	Cart	cart;
	Pol		pol;
} Cplx;

typedef struct {
	Cplx s;
	char* mode;
} CplxNum;


#endif // MAIN_H

long double recpower(long double base, long int exp);