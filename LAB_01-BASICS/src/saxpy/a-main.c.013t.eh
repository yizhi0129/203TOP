
;; Function saxpy (saxpy, funcdef_no=4, decl_uid=4386, cgraph_uid=5, symbol_order=4)

void saxpy (int * res, const int * x, const int * y, int a, int size)
{
  int i;

  i = 0;
  goto <D.4392>;
  <D.4391>:
  _1 = (long unsigned int) i;
  _2 = _1 * 4;
  _3 = x + _2;
  _4 = *_3;
  _5 = a * _4;
  _6 = (long unsigned int) i;
  _7 = _6 * 4;
  _8 = y + _7;
  _9 = *_8;
  _10 = (long unsigned int) i;
  _11 = _10 * 4;
  _12 = res + _11;
  _13 = _5 + _9;
  *_12 = _13;
  i = i + 1;
  <D.4392>:
  if (i < size) goto <D.4391>; else goto <D.4389>;
  <D.4389>:
  return;
}



;; Function main (main, funcdef_no=5, decl_uid=4393, cgraph_uid=6, symbol_order=5)

int main ()
{
  int i;
  int i;
  int a;
  int * y;
  int * x;
  int * res;
  int size;
  int D.4413;

  size = 100;
  a = 2;
  _1 = (long unsigned int) size;
  _2 = _1 * 4;
  res = malloc (_2);
  _3 = (long unsigned int) size;
  _4 = _3 * 4;
  y = malloc (_4);
  i = 0;
  goto <D.4405>;
  <D.4404>:
  _5 = (long unsigned int) size;
  _6 = _5 * 4;
  x = malloc (_6);
  _7 = (long unsigned int) i;
  _8 = _7 * 4;
  _9 = x + _8;
  _10 = i + 50;
  *_9 = _10;
  _11 = (long unsigned int) i;
  _12 = _11 * 4;
  _13 = y + _12;
  *_13 = i;
  i = i + 1;
  <D.4405>:
  if (i < size) goto <D.4404>; else goto <D.4402>;
  <D.4402>:
  saxpy (res, x, y, a, size);
  i = 0;
  goto <D.4409>;
  <D.4408>:
  _14 = (long unsigned int) i;
  _15 = _14 * 4;
  _16 = res + _15;
  _17 = *_16;
  printf ("res[%d] = %d ; ", i, _17);
  _18 = i + 1;
  _19 = _18 % 10;
  if (_19 == 0) goto <D.4411>; else goto <D.4412>;
  <D.4411>:
  __builtin_putchar (10);
  <D.4412>:
  i = i + 1;
  <D.4409>:
  if (i <= 99) goto <D.4408>; else goto <D.4406>;
  <D.4406>:
  D.4413 = 1;
  goto <D.4414>;
  D.4413 = 0;
  goto <D.4414>;
  <D.4414>:
  return D.4413;
}

