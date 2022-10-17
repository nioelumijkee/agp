/**
 * Copyright (C) 2022 Nioelumijke
 * All rights reserved.
 * See LICENSE file.
 */

/**
   parse argumens(example) 
*/

#include "agp.h"

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
  const char *v_d[AGP_MAX_ARG];
  const char *v_e[AGP_MAX_ARG];
  const char *v_f[AGP_MAX_ARG];

  /* options description */
  t_agp_options argopt[] = {
    /* flag-short flag-long exist-var var description */
    AGP_INFO("Usage:"),
    AGP_INFO("Options without arguments:"),
    AGP_BOOL(a, bool-a, &a_a,      "bool       (a)"),
    AGP_BOOL(b, -,      &a_b,      "bool       (b)"),
    AGP_BOOL(-, bool-c, &a_c,      "bool       (c)"),
    AGP_INFO("Options with arguments:"),
    AGP_STR(d,  str-d,  &a_d, v_d, "strings    (d)"),
    AGP_STR(e,  -,      &a_e, v_e, "strings    (e)"),
    AGP_STR(-,  str-f,  &a_f, v_f, "strings    (f)"),
    AGP_INFO("Default argument:"),
    AGP_DEF(-,  -,      &a_d, v_d, "default    (d)"),
    AGP_INFO("For help:"),
    AGP_BOOL(h, help,   &a_h,      "print this (h)"),
    AGP_END(),
  };

  // parse
  int ret = agp_parse(argopt, argc, argv);
  if (ret != 0)
    {
      return(1);
    }
  else
    {
      if (a_h)
	{
	  agp_usage(argopt);
	  return(0);
	}
      if (a_a)
	{
	  printf("a: %d\n",a_a);
	}
      if (a_b)
	{
	  printf("b: %d\n",a_b);
	}
      if (a_c)
	{
	  printf("c: %d\n",a_c);
	}
      if (a_d)
	{
	  printf("d: %d",a_d);
	  for(i=0; i<a_d; i++)
	    printf(": %s ", v_d[i]);
	  printf("\n");
	}
      if (a_e)
	{
	  printf("e: %d",a_e);
	  for(i=0; i<a_e; i++)
	    printf(": %s ", v_e[i]);
	  printf("\n");
	}
      if (a_f)
	{
	  printf("f: %d",a_f);
	  for(i=0; i<a_f; i++)
	    printf(": %s ", v_f[i]);
	  printf("\n");
	}
    }
  return (0);
}

