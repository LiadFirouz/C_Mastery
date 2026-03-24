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
void add_comp(complex a, complex b);
void sub_comp(complex a, complex b);
void mult_comp_real(complex a, double d);
void mult_comp_img(complex a, double d);
void mult_comp_comp(complex a, complex b);
void abs_comp(complex n);


#endif