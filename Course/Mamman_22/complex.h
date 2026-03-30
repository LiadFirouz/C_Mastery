/*
 * complex.h
 * * Header file defining the 'complex' structure and the mathematical API.
 * Acts as the blueprint for the complex number math engine.
 */
#ifndef COMPLEX_H
#define COMPLEX_H

/*
 * The complex number structure.
 * Note: Initialization happens at run-time, not compile-time,
 * to strictly comply with the ANSI C89 standard.
 */
typedef struct complex
{
    double real;
    double imaginary;
} complex;

/* Function Prototypes */
void read_comp(complex *c, double r, double i);
void print_comp(complex c);
void add_comp(complex a, complex b);
void sub_comp(complex a, complex b);
void mult_comp_real(complex a, double d);
void mult_comp_img(complex a, double d);
void mult_comp_comp(complex a, complex b);
void abs_comp(complex n);

#endif
