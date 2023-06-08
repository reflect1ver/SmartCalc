#include "s21_calculator.h"

double calc(const char *Input) {
  double rez = 0;
  char Out[511];
  int len = 0;
  len = forward(Input, Out);
  rez = reverse(Out, len, 0);
  return rez;
}

double Y_calc(const char *Out, int len, double X) {
  double rez = 0;
  rez = reverse(Out, len, X);
  return rez;
}

int forward(const char *m, char *Out) {
  My_Stack *t;
  My_Stack *Op = NULL;
  char a;
  int k = 0, l = 0;
  char cas;
  while (m[k] != '\0') {
    if ((m[k] >= '0' && m[k] <= '9') || m[k] == '.' || m[k] == 'X' ||
        m[k] == 'x') {
      while ((m[k] >= '0' && m[k] <= '9') || m[k] == '.' || m[k] == 'X' ||
             m[k] == 'x') {
        Out[l++] = m[k];
        k++;
      }
      k--;
      Out[l++] = ' ';
    } else if (m[k] == '(') {
      Op = InChar(Op, m[k]);
    } else if (m[k] == ')') {
      while ((Op->c) != '(') {
        Op = OutChar(Op, &a);
        if (Op == NULL) {
          a = '\0';
        }
        Out[l++] = a;
        Out[l++] = ' ';
      }
      t = Op;
      Op = Op->next;
      free(t);
    } else if (m[k] == '+' || m[k] == '-' || m[k] == '*' || m[k] == '/' ||
               m[k] == '^' || m[k] == 's' || m[k] == 'c' || m[k] == '~' ||
               m[k] == 'm' || m[k] == 't' || m[k] == 'a' || m[k] == 'l') {
      cas = what_case(m, &k);
      while (Op != NULL && Priority(Op->c) >= Priority(cas)) {
        Op = OutChar(Op, &a);
        Out[l++] = a;
        Out[l++] = ' ';
      }
      Op = InChar(Op, cas);
    }
    k++;
  }
  while (Op != NULL) {
    Op = OutChar(Op, &a);
    Out[l++] = a;
    if (Op != NULL) {
      Out[l++] = ' ';
    }
  }
  Out[l] = '\0';
  return l;
}

double reverse(const char *m, int l, double x) {
  double Res[4];
  int k = 0;
  double rez = 0;
  double prom = 0;
  int buf = 0;
  int math = 0;
  for (int i = 0; i < l; i++) {
    if (m[i] >= '0' && m[i] <= '9') {
      buf = i;
      while (m[buf + 1] >= '0' && m[buf + 1] <= '9') {
        buf++;
      }
      prom = m[buf] - 48;
      i = buf;
      while (buf != 0 && m[buf - 1] >= '0' && m[buf - 1] <= '9') {
        math = m[buf - 1] - 48;
        for (int p = 0; p < i - buf + 1; p++) {
          math = 10 * math;
        }
        prom = prom + math;
        buf--;
      }
      Res[k++] = prom;
    } else if (m[i] == 'X' || m[i] == 'x') {
      Res[k++] = x;
    } else if (m[i] == '.') {
      buf = i + 1;
      while (m[buf] >= '0' && m[buf] <= '9') {
        Res[k - 1] = Res[k - 1] + (m[buf] - 48) * (pow(10, i - buf));
        buf++;
      }
      i = buf - 1;
    } else if (m[i] == '+' || m[i] == '-' || m[i] == '*' || m[i] == '/' ||
               m[i] == '^' || m[i] == 's' || m[i] == 'c' || m[i] == '~' ||
               m[i] == 'm' || m[i] == 't' || m[i] == 'o' || m[i] == 'i' ||
               m[i] == 'a' || m[i] == 'q' || m[i] == 'l' || m[i] == 'g') {
      switch (m[i]) {
      case '+':
        rez = Res[k - 2] + Res[k - 1];
        Res[k - 2] = rez;
        k = k - 1;
        break;
      case '-':
        rez = Res[k - 2] - Res[k - 1];
        Res[k - 2] = rez;
        k = k - 1;
        break;
      case '*':
        rez = Res[k - 2] * Res[k - 1];
        Res[k - 2] = rez;
        k = k - 1;
        break;
      case '/':
        rez = Res[k - 2] / Res[k - 1];
        Res[k - 2] = rez;
        k = k - 1;
        break;
      case '^':
        rez = pow(Res[k - 2], Res[k - 1]);
        Res[k - 2] = rez;
        k = k - 1;
        break;
      case 'm':
        rez = (int)Res[k - 2] % (int)Res[k - 1];
        Res[k - 2] = rez;
        k = k - 1;
        break;

      case '~':
        rez = Res[k - 1] * (-1);
        Res[k - 1] = rez;
        break;
      case 's':
        rez = sin(Res[k - 1]);
        Res[k - 1] = rez;
        break;
      case 'c':
        rez = cos(Res[k - 1]);
        Res[k - 1] = rez;
        break;
      case 't':
        rez = tan(Res[k - 1]);
        Res[k - 1] = rez;
        break;
      case 'o':
        rez = acos(Res[k - 1]);
        Res[k - 1] = rez;
        break;
      case 'i':
        rez = asin(Res[k - 1]);
        Res[k - 1] = rez;
        break;
      case 'a':
        rez = atan(Res[k - 1]);
        Res[k - 1] = rez;
        break;
      case 'q':
        rez = sqrt(Res[k - 1]);
        Res[k - 1] = rez;
        break;
      case 'l':
        rez = log(Res[k - 1]);
        Res[k - 1] = rez;
        break;
      case 'g':
        rez = log10(Res[k - 1]);
        Res[k - 1] = rez;
        break;
      }
    }
  }
  return rez;
}

int Priority(char c) {
  int prior = 0;
  switch (c) {
  case '~':
    prior = 6;
    break;
  case 's':
    prior = 5;
    break; // sin
  case 'c':
    prior = 5;
    break; // cos
  case 't':
    prior = 5;
    break; // tan
  case 'o':
    prior = 5;
    break; // acos
  case 'i':
    prior = 5;
    break; // asin
  case 'a':
    prior = 5;
    break; // atan
  case 'q':
    prior = 5;
    break; // sqrt
  case 'l':
    prior = 5;
    break; // ln
  case 'g':
    prior = 5;
    break; // log
  case '^':
    prior = 4;
    break;
  case '*':
    prior = 3;
    break;
  case '/':
    prior = 3;
    break;
  case 'm':
    prior = 3;
    break; // mod
  case '+':
    prior = 2;
    break;
  case '-':
    prior = 2;
    break;
  case '(':
    prior = 1;
    break;
  }
  return prior;
}

My_Stack *InChar(My_Stack *p, char s) {
  My_Stack *t = malloc(sizeof(My_Stack));
  t->c = s;
  t->next = p;
  return t;
}

My_Stack *OutChar(My_Stack *p, char *s) {
  My_Stack *t = p;
  *s = p->c;
  p = p->next;
  free(t);
  return p;
}

char what_case(const char *m, int *i) {
  char cas = '(';
  if (m[*i] == '+') {
    cas = '+';
  } else if (m[*i] == '-') {
    cas = '-';
  } else if (m[*i] == '*') {
    cas = '*';
  } else if (m[*i] == '/') {
    cas = '/';
  } else if (m[*i] == '^') {
    cas = '^';
  } else if (m[*i] == '~') {
    cas = '~';
  } else if (m[*i] == 's' && m[*i - 1] != 'a' && m[*i + 1] == 'i') {
    cas = 's';
    *i = *i + 2; // sin
  } else if (m[*i] == 's' && m[*i + 1] == 'q') {
    cas = 'q';
    *i = *i + 3; // sqrt
  } else if (m[*i] == 'c' && m[*i - 1] != 'a' && m[*i + 1] == 'o') {
    cas = 'c';
    *i = *i + 2; // cos
  } else if (m[*i] == 'm') {
    cas = 'm';
    *i = *i + 2; // mod
  } else if (m[*i] == 't' && m[*i - 1] != 'a' && m[*i + 1] == 'a') {
    cas = 't';
    *i = *i + 2; // tan
  } else if (m[*i] == 'a' && m[*i + 1] == 'c') {
    cas = 'o';
    *i = *i + 3; // acos
  } else if (m[*i] == 'a' && m[*i + 1] == 's') {
    cas = 'i';
    *i = *i + 3; // asin
  } else if (m[*i] == 'a' && m[*i + 1] == 't') {
    cas = 'a';
    *i = *i + 3; // atan
  } else if (m[*i] == 'l' && m[*i + 1] == 'n') {
    cas = 'l';
    *i = *i + 1; // ln
  } else if (m[*i] == 'l' && m[*i + 1] == 'o') {
    cas = 'g';
    *i = *i + 2; // log
  }
  return cas;
}

double annuitet(double p, double sum, int srok) {
  double plat;
  double coef;
  coef = (p / 1200 * pow(1 + p / 1200, srok)) / (pow(1 + p / 1200, srok) - 1);
  plat = coef * sum;
  return plat;
}

double diff(double p, double sum, int srok, double *first, double *last) {
  double rez = 0;
  double buf = sum;

  *first = (sum * (p / 100) * 30) / 365 + sum / srok;
  *last = ((sum - (srok - 1) * sum / srok) * (p / 100) * 30) / 365 + sum / srok;

  while (buf > 0) {
    rez = rez + (buf * (p / 100) * 30) / 365 + sum / srok;
    buf = buf - sum / srok;
  }
  return rez;
}