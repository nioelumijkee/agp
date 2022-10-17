/* parse argumens */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "argparse.h"

int main(int argc, char *argv[])
{
  int i;

  /* for arguments */
  char a_a;
  char a_b;
  char a_c;
  char a_d;
  char a_e;
  char a_f, v_f[ARGPARSE_MAX_STR_LEN];
  char a_g, v_g[ARGPARSE_MAX_STR_LEN];
  char a_k, v_k[ARGPARSE_MAX_STR_LEN];
  char a_l, v_l[ARGPARSE_MAX_ARG][ARGPARSE_MAX_STR_LEN];
  char a_m, v_m[ARGPARSE_MAX_ARG][ARGPARSE_MAX_STR_LEN];
  char a_n, v_n[ARGPARSE_MAX_ARG][ARGPARSE_MAX_STR_LEN];

  t_argparse_options argopt[] = {
    /* flag-short flag-long exist-var var description */
    ARGPARSE_INFO("Usage:"),
    ARGPARSE_INFO(""),
    ARGPARSE_INFO("No arguments options(no arguments):"),
    ARGPARSE_BOOL('a', bool-a, &a_a, "bool a"),
    ARGPARSE_BOOL('b', bool-b, &a_b, "bool b"),
    ARGPARSE_BOOL('c', bool-c, &a_c, "bool c"),
    ARGPARSE_BOOL('d', -,      &a_d, "bool d"),
    ARGPARSE_BOOL('-', bool-e, &a_e, "bool e"),
    ARGPARSE_INFO(""),
    ARGPARSE_INFO("One argument options:"),
    ARGPARSE_ONE('f', one-f, &a_f, &v_f, "one arg. f"),
    ARGPARSE_ONE('g', -,     &a_g, &v_g, "one arg. g"),
    ARGPARSE_ONE('-', one-k, &a_k, &v_k, "one arg. k"),
    ARGPARSE_INFO(""),
    ARGPARSE_INFO("Many arguments options:"),
    ARGPARSE_MANY('l', many-l, &a_l, &v_l, "many arg. l"),
    ARGPARSE_MANY('m', -,      &a_m, &v_m, "many arg. m"),
    ARGPARSE_MANY('-', many-n, &a_n, &v_n, "many arg. n"),
    ARGPARSE_END(),
  };

  // parse
  int ret = argparse_parse(argopt, argc, argv);
  if (ret != 0)
    {
      argparse_usage(argopt);
    }
  else
    {
      if (a_a)
	printf("a\n");
      if (a_b)
	printf("b\n");
      if (a_c)
	printf("c\n");
      if (a_d)
	printf("d\n");
      if (a_e)
	printf("e\n");

      if (a_f)
	printf("f: %s\n", v_f);
      if (a_g)
	printf("g: %s\n", v_g);
      if (a_k)
	printf("k: %s\n", v_k);

      if (a_l)
	{
	  printf("l:");
	  for(i=0; i<a_l; i++)
	    printf(" %s", v_l[i]);
	  printf("\n");
	}

      if (a_m)
	{
	  printf("m:");
	  for(i=0; i<a_m; i++)
	    printf(" %s", v_m[i]);
	  printf("\n");
	}

      if (a_n)
	{
	  printf("n:");
	  for(i=0; i<a_n; i++)
	    printf(" %s", v_n[i]);
	  printf("\n");
	}
    }
  return (0);
}

