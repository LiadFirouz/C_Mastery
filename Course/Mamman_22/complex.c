#include "complex.h"
#include <stdio.h>
#include <math.h>

void read_comp(complex *c, double r, double i)
{
    c->real = r;
    c->imaginary = i;
}

void print_comp(complex c)
{
    printf("%.2f+(%.2f)i\n", c.real, c.imaginary);
}

void add_comp(complex a, complex b)
{
    complex c;
    read_comp(&c, a.real + b.real, a.imaginary + b.imaginary);
    print_comp(c);
}

void sub_comp(complex a, complex b)
{
    complex c;
    read_comp(&c, a.real - b.real, a.imaginary - b.imaginary);
    print_comp(c);
}

void mult_comp_real(complex a, double d)
{
    complex c;
    read_comp(&c, a.real * d, a.imaginary * d);
    print_comp(c);
}

void mult_comp_img(complex a, double d)
{
    complex c;
    read_comp(&c, (a.imaginary * d * (-1)), a.real * d);
    print_comp(c);
}

void mult_comp_comp(complex a, complex b)
{
    complex c;
    read_comp(&c, ((a.real * b.real) - (a.imaginary * b.imaginary)), (a.real * b.imaginary) + (a.imaginary * b.real));
    print_comp(c);
}

void abs_comp(complex c)
{
    double a = sqrt(c.real * c.real + c.imaginary * c.imaginary);
    printf("%.2f\n", a);
}
