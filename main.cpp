/*******************************************************
 * COMP2012 - 2012/13 Fall
 * Programming Assignment 1
 * File: main.cpp
 
 * MAR Chun Sum (20057384)
 *******************************************************/

#include <iostream>
#include "Polynomial.h"
using namespace std;

int main(void)
{


   poly_pointer a, b, d, e, f;
   a = read_poly("input1.txt");
   cout << "a=";
   print_poly(a);

   b = read_poly("input2.txt");
   cout << "b="; 
   print_poly(b);
cout<<"check"<<endl;
   d = padd(a, b);
   cout << "a+b=";   
   print_poly(d);

   e = pmult(a, b);
   cout << "a*b=";
   print_poly(e);

   f = psubtract(a, b); 
   cout << "a-b=";
   print_poly(f);

   int value = eval(a, 10);
   cout << "a(10)=" << value << endl;

   erase(&a);
   erase(&b);
   erase(&d);
   erase(&e);
   erase(&f); 

  cout<< "finish\n";
   return 0;
};
