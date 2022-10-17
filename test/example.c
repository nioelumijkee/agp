/**
 * Copyright (C) 2022 Nioelumijke
 * All rights reserved.
 * See LICENSE file.
 */

/**
   parse argumens(example) 
*/

#include "argparse.h"

int main(int argc, char *argv[])
{
  int i;

  /* for arguments */
  int a_a;
  int a_b;
  int a_c;
  int a_d;
  int a_e;
  int a_f;
  int a_h;
  const char *v_d[ARGPARSE_MAX_ARG];
  const char *v_e[ARGPARSE_MAX_ARG];
  const char *v_f[ARGPARSE_MAX_ARG];

  /* options description */
  t_argparse_options argopt[] = {
    /* flag-short flag-long exist-var var description */
    ARGPARSE_INFO("Usage:"),
    ARGPARSE_INFO("Options without arguments:"),
    ARGPARSE_BOOL('a', bool-a, &a_a,      "bool (a)"),
    ARGPARSE_BOOL('b', -,      &a_b,      "bool (b)"),
    ARGPARSE_BOOL('-', bool-c, &a_c,      "bool (c)"),
    ARGPARSE_INFO("Options with arguments:"),
    ARGPARSE_STR('d',  str-d,  &a_d, v_d, "strings (d)"),
    ARGPARSE_STR('e',  -,      &a_e, v_e, "strings (e)"),
    ARGPARSE_STR('-',  str-f,  &a_f, v_f, "strings (f)"),
    ARGPARSE_INFO("Default argument:"),
    ARGPARSE_DEF('-',  -,      &a_d, v_d, "defualt (d)"),
    ARGPARSE_INFO("For help:"),
    ARGPARSE_BOOL('h', help,   &a_h,      "print this (h)"),
    ARGPARSE_END(),
  };

  // parse
  int ret = argparse_parse(argopt, argc, argv);
  if (ret != 0)
    {
      return(1);
    }
  else
    {
      if (a_h)
	{
	  argparse_usage(argopt);
	  return(0);
	}
      if (a_a)
	{
	  printf("a");
	  for(i=0; i<a_a; i++)
	    printf(": a ");
	  printf("\n");
	}
      if (a_b)
	{
	  printf("b");
	  for(i=0; i<a_b; i++)
	    printf(": b ");
	  printf("\n");
	}
      if (a_c)
	{
	  printf("c");
	  for(i=0; i<a_c; i++)
	    printf(": c ");
	  printf("\n");
	}
      if (a_d)
	{
	  printf("d");
	  for(i=0; i<a_d; i++)
	    printf(": %s ", v_d[i]);
	  printf("\n");
	}
      if (a_e)
	{
	  printf("e");
	  for(i=0; i<a_e; i++)
	    printf(": %s ", v_e[i]);
	  printf("\n");
	}
      if (a_f)
	{
	  printf("f");
	  for(i=0; i<a_f; i++)
	    printf(": %s ", v_f[i]);
	  printf("\n");
	}
    }
  return (0);
}

