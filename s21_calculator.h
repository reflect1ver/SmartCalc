#ifndef _SRC_S21_CALCULATOR_H
#define _SRC_S21_CALCULATOR_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
  char c;
  struct Stack *next;
} My_Stack;

double reverse(const char *m, int l, double x);
int forward(const char *m, char *Out);
double diff(double p, double sum, int srok, double *first, double *last);
double annuitet(double p, double sum, int srok);
double calc(const char *Input);
double Y_calc(const char *Out, int len, double X);
int Priority(char c);
My_Stack *InChar(My_Stack *p, char s);
My_Stack *OutChar(My_Stack *p, char *s);
char what_case(const char *m, int *i);

#endif // _SRC_S21_CALCULATOR_H
