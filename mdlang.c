#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static char *p;
static char *fname;

static void error(char *fmt, char val) {
  char *err = strcat(fmt, "\n");
  printf(err, val);
  exit(1);
}

static void skip() {
  while (isspace(*p))
    p++;
}

static int eval(int *args) {
  puts("=======");
  puts(p);
  puts("=======");
  skip();

  // Literal numbers
  if (isdigit(*p)) {
    int val = *p++ - '0';
    while (isdigit(*p))
      val = val * 10 + (*p++ - '0');
    return val;
  }

  // Arithmetic operators
  if (strchr("+-*/", *p)) {
    int op = *p++;
    int x = eval(args);
    int y = eval(args);

    switch (op) {
    case '+': return x + y;
    case '-': return x - y;
    case '*': return x * y;
    case '/': return x / y;
    }
  }

  printf("invalid character: %c\n", *p);
  exit(1);
}

int main(int argc, char **argv) {
  FILE *fp;
  fname = argv[1];
  fp = fopen(fname, "r");
  if(fp == NULL) {
      printf("%s file missing\n", fname);
      return -1;
  }
  char str;
  int len = 0;
  char tx[13];
  while((str = fgetc(fp)) != EOF) {
    tx[len] = str;
    len++;
  }
  tx[13] = '\0';

  // count characters
  // int len;
  // fseek(fp,0,SEEK_END);
  // len = ftell(fp);
  // fseek(fp,0,SEEK_SET);

  // char text[13];
  // int chr;
  // int index = 0;
  // while((chr = fgetc(fp)) != EOF) {
  //   text[index] = chr;
  //   index++;
  //   printf("%d\n", index);
  //   printf("%s\n", text);
  //   printf("%c\n", text[index]);
  // }
  // text[13] = '\0';
  // puts("======");
  p = tx;
  while (*p)
    printf("%d\n", eval(0));

  fclose(fp);
  // return 0;
}
