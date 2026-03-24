#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>

// Complex Structer
typedef struct complex
{
    double real;
    double imaginary;
} complex;

void read_comp(complex *c, double r, double i);
void print_comp(complex c);

#endif