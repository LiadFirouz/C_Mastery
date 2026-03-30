/*
 * complex.c
 * * Implementation of the mathematical operations for complex numbers.
 * Uses the DRY (Don't Repeat Yourself) principle by utilizing read_comp
 * and print_comp inside the arithmetic functions.
 */
#include "complex.h"
#include <stdio.h>
#include <math.h>

/* Assigns new real and imaginary values to a complex variable by reference */
void read_comp(complex *c, double r, double i)
{
    c->real = r;
    c->imaginary = i;
}

/* Prints a complex number strictly in the format: real+(imaginary)i */
void print_comp(complex c)
{
    printf("%.2f+(%.2f)i\n", c.real, c.imaginary);
}

/* Addition: (a+bi) + (c+di) = (a+c) + (b+d)i */
void add_comp(complex a, complex b)
{
    complex c;
    read_comp(&c, a.real + b.real, a.imaginary + b.imaginary);
    print_comp(c);
}

/* Subtraction: (a+bi) - (c+di) = (a-c) + (b-d)i */
void sub_comp(complex a, complex b)
{
    complex c;
    read_comp(&c, a.real - b.real, a.imaginary - b.imaginary);
    print_comp(c);
}

/* Multiplication by a real scalar: d * (a+bi) = (da) + (db)i */
void mult_comp_real(complex a, double d)
{
    complex c;
    read_comp(&c, a.real * d, a.imaginary * d);
    print_comp(c);
}

/* Multiplication by an imaginary scalar: di * (a+bi) = (-db) + (da)i */
void mult_comp_img(complex a, double d)
{
    complex c;
    read_comp(&c, (a.imaginary * d * (-1)), a.real * d);
    print_comp(c);
}

/* Multiplication of two complex numbers: (a+bi) * (c+di) = (ac-bd) + (ad+bc)i */
void mult_comp_comp(complex a, complex b)
{
    complex c;
    read_comp(&c, ((a.real * b.real) - (a.imaginary * b.imaginary)), (a.real * b.imaginary) + (a.imaginary * b.real));
    print_comp(c);
}

/* * Absolute value (magnitude): |a+bi| = sqrt(a^2 + b^2)
 * Note: Returns a pure real number, hence prints directly as a double.
 */
void abs_comp(complex c)
{
    double a = sqrt(c.real * c.real + c.imaginary * c.imaginary);
    printf("%.2f\n", a);
}
