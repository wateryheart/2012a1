/*******************************************************
 * COMP2012 - 2012/13 Fall
 * Programming Assignment 1
 * File: Polynomial.h
  
 * MAR Chun Sum (20057384)
 *******************************************************/

#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_
#endif

#include <iostream>
using namespace std;

/* struct definition for polynomial in singly linked list */
typedef struct poly_node *poly_pointer;

typedef struct poly_node {
  int coef;
  int expon;
  poly_pointer link;
};

/* construct an empty polynomial */
poly_pointer zero();

/* if polynomial a is empty, retrun true, else false */
bool isEmpty(poly_pointer a);

/* erase a polynomial pointed by ptr and deallocate the nodes */
void erase(poly_pointer *ptr);

/* read and create a polynomial from the file of fileName*/
poly_pointer read_poly(const char* fileName);

/* delete the exponential of 0 coefficient */
poly_pointer sub_poly(poly_pointer a);

/* sort the polynomial a in decreasing order of exponent */ 
poly_pointer order_poly(poly_pointer a);

/* print the polynomial */ 
void print_poly(poly_pointer a);

/* Calculate integer power */
int pow(int x, int y);

/* evaluate the polynomial a at value of x */
int eval(poly_pointer a, int x);

/* add two polynoamials, a & b, and return the sum in a third polynomial*/
poly_pointer padd(poly_pointer a, poly_pointer b);

/* subtract polynomial b from polynomial a, return the result in a third polynomial */
poly_pointer psubtract(poly_pointer a, poly_pointer b);

/* multiply polynomial a with polynomial b and return the result in a third polynomial */
poly_pointer pmult(poly_pointer a, poly_pointer b);

