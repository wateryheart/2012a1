/*******************************************************
 * COMP2012 - 2012/13 Fall
 * Programming Assignment 1
 * File: Polynomial.cpp
 
 * MAR Chun Sum (20057384)
 *******************************************************/

#include "Polynomial.h"
#include <fstream>
using namespace std;

/* construct an empty polynomial */
poly_pointer zero()
{
	poly_pointer c;
	c = new poly_node;
	c->coef = 0;
	c->expon = 0;
	c->link = NULL;
	return c;
};

/* if polynomial a is empty, retrun true, else false */
bool isEmpty(poly_pointer a)
{
	if ( a == NULL )
        return true;
	else
		return false;
};

/* erase a polynomial pointed by ptr and deallocate the nodes */
void erase(poly_pointer *ptr)
{
	poly_pointer temp;
	while (*ptr)
	{
		temp = *ptr;
		*ptr = (*ptr)->link;
		delete temp;
	}
};

/* read and create a polynomial from the file of fileName*/
poly_pointer read_poly(const char* fileName)
{
	char content[100], ch;
    int i = 0;
	ifstream file(fileName);
	if (file.is_open()) 
	{
		while (file.get(ch)) //get the content of file into chat array
			content[i++] = ch;

		content[i] = '\0';
		file.close();
	} 
	else 
		cout << "Error: File not found." << endl;

	poly_pointer ptr = zero(); //create a node
	poly_pointer head = ptr;

    if (content[0] != '-') //check the first char is positive or negative
	{
        if (content[0] == 'x')
           ptr->coef = 1;
		else
           ptr->coef = atoi(&content[0]);
    }
	else if (content[0] == '-')
	{
        if (content[1] == 'x')
           ptr->coef = -1;
		else
           ptr->coef = 0 - atoi(&content[1]);
    }

	for (int j = 1; j <= i; j++) //get the clef and expo base on the + and - size
	{
        if (content[j] == '-' || content[j] == '+')
		{
           if (content[j-1] == 'x')
              ptr->expon = 1;
		   else
              ptr->expon = atoi(&content[j-1]);

		   ptr->link = new poly_node();
           ptr->link->link = NULL;
           ptr = ptr->link;

           if (content[j+1] == 'x')
		   {
              if (content[j] == '-')
                 ptr->coef = -1;
              else
                 ptr->coef = 1;
           }
		   else if (content[j+1] != 'x')
		   {
              ptr->coef = atoi(&content[j+1]);
              if (content[j] == '-')
                 ptr->coef = 0 - ptr->coef;
           }
        }
    }
	return head;
}

/* delete the exponential of 0 coefficient */
/*
poly_pointer sub_poly(poly_pointer a)
{
	poly_pointer prev, cur;
	prev = NULL;
	cur = a;
	while (cur != NULL)
	{
		if (cur->coef == 0)
		{
			if (prev == NULL)
			{
				a = cur->link;
				delete cur;
				cur = a;
			}
			else
			{
				prev->link = cur->link;
				delete cur;
				cur = prev->link;
			}
		}
		else
		{
			prev = cur;
			cur = cur->link;
		}
	}
	if (a == NULL)
	{
		a = zero();
	}

	return a;
};
*/

/* sort the polynomial a in decreasing order of exponent */ 
poly_pointer order_poly(poly_pointer a)
{
	poly_pointer prev, cur, head, temp;
	temp = zero();
	head = temp;
	head->coef = a->coef;
	head->expon = a->expon;
	cur = head;
	prev = NULL;
	a = a->link;
	while (a != NULL)
	{
		cur = head;
		prev = NULL;
		while (cur != NULL)
		{
			if (a->expon == cur->expon)
			{
				cur->coef = cur->coef + a->coef;
				break;
			}
			else if (a->expon < cur->expon)
			{
				prev = cur;
				cur = cur->link;
			}
			else
			{
				temp = zero();
				temp->coef = a->coef;
				temp->expon = a->expon;
				temp->link = cur;
				if(prev == NULL)
					head = temp;
				else
					prev->link = temp;
				break;
			}
		}
		if (cur == NULL)
		{
			temp = zero();
			temp->coef = a->coef;
			temp->expon = a->expon;
			temp->link = cur;
			if(prev == NULL)
				head = temp;
			else
				prev->link = temp;
		}
		a = a->link;
	}
	return head;
}

/* print the polynomial */ 
void print_poly(poly_pointer a)
{
	poly_pointer print;
	print = a;
	//print polynomial
	if(print != NULL)
	{
		//check special output
		if (print->coef == 0) //only 1 node with 0 coef
			cout << "0";
		else if (print->coef == 1 && print->expon == 1)
			cout << "X";
		else if (print->coef == -1 && print->expon == 1)
			cout << "-X";
		else if (print->coef == 1 && print->expon != 0)
			cout << "X^" << print->expon;
		else if (print->coef == -1 && print->expon != 0)
			cout << "-X^" << print->expon;
		else if (print->expon == 0)
			cout << print->coef;
		else if (print->expon == 1)
			cout << print->coef << "X";
		else
			cout << print->coef << "X^" << print->expon;
		
		//move pointer to next
		print = print->link;
	}
	while( print != NULL)
	{
		//check special output
		if (print->coef == 0) //only 1 node with 0 coef
			cout << "0";
		else if (print->coef == 1 && print->expon == 1)
			cout << "+X";
		else if (print->coef == -1 && print->expon == 1)
			cout << "-X";
		else if (print->coef == 1 && print->expon != 0)
			cout << "+X^" << print->expon;
		else if (print->coef == -1 && print->expon != 0)
			cout << "-X^" << print->expon;
		else if (print->expon == 0 && print->coef >0)
			cout << "+" <<  print->coef;
		else if (print->expon == 0)
					cout << print->coef;
		else if (print->expon == 1 && print->coef >0)
			cout << "+" << print->coef << "X";
		else if (print->expon == 1)
					cout << print->coef << "X";
		else if (print->coef >0)
			cout <<"+"<< print->coef << "X^" << print->expon;
		else
			cout << print->coef << "X^" << print->expon;

		//move pointer to next
		print = print->link;
	}
	cout << endl;
};

/* Calculate integer power */
int pow(int x, int y) 
{
	if (y == 0) 
		return 1;
	else if (y == 1) 
		return x;
	else
		return x * pow(x, y-1);
}

/* evaluate the polynomial a at value of x */
int eval(poly_pointer a, int x)
{
	int sum = 0;
	while( a != NULL)
	{
		sum = sum + a->coef * pow(x,a->expon);
		a = a->link;
	}
	return sum;
};

/* add two polynoamials, a & b, and return the sum in a third polynomial*/
poly_pointer padd(poly_pointer a, poly_pointer b)
{
	poly_pointer c = NULL;
	poly_pointer temp;
	poly_pointer head = c;
	while (a != NULL && b != NULL)
	{
		temp = new poly_node;
		if (c != NULL)
			c->link = temp;
		else
			head = temp;
		c = temp;
		if (a->expon > b->expon)
		{
			c->coef = a->coef;
			c->expon = a->expon;
			a = a->link;
		}
		else if (a->expon < b->expon)
		{
			c->coef = b->coef;
			c->expon = b->expon;
			b = b->link;
		}
		else if (a->expon == b->expon)
		{
			c->coef = a->coef + b->coef;
			c->expon = a->expon;
			a = a->link;
			b = b->link;
		}

	}
	while (a != NULL && b == NULL)
	{
		temp = new poly_node;
		if (c != NULL)
			c->link = temp;
		else
			head = temp;
		c = temp;
		c->coef = a->coef;
		c->expon = a->expon;
		a = a->link;
	}
	while (a == NULL && b != NULL)
	{
		temp = new poly_node;
		if (c != NULL)
			c->link = temp;
		else
			head = temp;
		c = temp;
		c->coef = b->coef;
		c->expon = b->expon;
		b = b->link;
	}
	//head = sub_poly(head);
	return head;
};

/* subtract polynomial b from polynomial a, return the result in a third polynomial */
poly_pointer psubtract(poly_pointer a, poly_pointer b)
{
	poly_pointer c = NULL;
	poly_pointer temp;
	poly_pointer head = c;
	while (a != NULL && b != NULL)
	{

			temp = new poly_node;
			if (c != NULL)
				c->link = temp;
			else
				head = temp;
			c = temp;
			if (a->expon > b->expon)
			{
				c->coef = a->coef;
				c->expon = a->expon;
				a = a->link;
			}
			else if (a->expon < b->expon)
			{
				c->coef = (-1) * b->coef;
				c->expon = b->expon;
				b = b->link;
			}
			else if (a->expon == b->expon)
			{
				c->coef = a->coef - b->coef;
				c->expon = a->expon;
				a = a->link;
				b = b->link;
			}
	}
	while (a != NULL && b == NULL)
	{
		temp = new poly_node;
		if (c != NULL)
			c->link = temp;
		else
			head = temp;
		c = temp;
		c->coef = a->coef;
		c->expon = a->expon;
		a = a->link;
	}
	while (a == NULL && b != NULL)
	{
		temp = new poly_node;
		if (c != NULL)
			c->link = temp;
		else
			head = temp;
		c = temp;
		c->coef = (-1) * b->coef;
		c->expon = b->expon;
		b = b->link;

	}
	//head = sub_poly(head);
	return head;
};

/* multiply polynomial a with polynomial b and return the result in a third polynomial */
poly_pointer pmult(poly_pointer a, poly_pointer b)
{
	poly_pointer c = NULL; //get a empty polynomial
	bool first = true;
	poly_pointer temp =zero();
	poly_pointer headb= b; //point to head of polynomial b
	poly_pointer head = NULL;

	while (a != NULL) 
	{
		while (b != NULL)
		{
			if (first)
			{
				head = temp;
				head->coef = a->coef * b->coef;
				head->expon = a->expon + b->expon;
				c = head;
				first = false;
			}
			else
			{
				temp =zero();
				c->link = temp;
				c = c->link;
				c->coef = a->coef * b->coef;
				c->expon = a->expon + b->expon;
			}
			b = b->link;
		}
		b = headb; //point b back to it's head
		a= a->link;
	}
	head = order_poly(head);
	//head = sub_poly(head);
	return head;
};

