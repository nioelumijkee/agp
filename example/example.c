/**
 * Copyright (C) 2022 Nioelumijke
 * All rights reserved.
 * See LICENSE file.
 */

//  parse arguments(example) 

#include "agp.h"

int main(int argc, char *argv[])
{
  int i;

  /* for arguments */
  t_agp_val v_a;
  t_agp_val v_b;
  t_agp_val v_c;
  t_agp_val v_d;
  t_agp_val v_e;
  t_agp_val v_f;
  t_agp_val v_h;

  /* options description */
  t_agp_options argopt[] = {
    /* flag-short flag-long exist-var var description */
    AGP_INFO("Usage:"),
    AGP_INFO("Options without arguments:"),
    AGP_BOOL(a, bool-a, &v_a, "bool       (a)"),
    AGP_BOOL(b, -,      &v_b, "bool       (b)"),
    AGP_BOOL(-, bool-c, &v_c, "bool       (c)"),
    AGP_INFO("Options with arguments:"),
    AGP_STR(d,  str-d,  &v_d, "strings    (d)"),
    AGP_STR(e,  -,      &v_e, "strings    (e)"),
    AGP_STR(-,  str-f,  &v_f, "strings    (f)"),
    AGP_INFO("Default argument:"),
    AGP_DEF(-,  -,      &v_d, "default    (d)"),
    AGP_INFO("For help:"),
    AGP_BOOL(h, help,   &v_h, "print this (h)"),
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
      // print help
      if (v_h.count)
	{
	  agp_usage(argopt);
	  return(0);
	}

      // print result
      printf("a: %d\n", v_a.count);
      printf("b: %d\n", v_b.count);
      printf("c: %d\n", v_c.count);

      printf("d: %d",v_d.count);
      for (i=0; i<v_d.count; i++) printf(": %s ", v_d.a[i]);
      printf("\n");

      printf("e: %d",v_e.count);
      for (i=0; i<v_e.count; i++) printf(": %s ", v_e.a[i]);
      printf("\n");

      printf("f: %d",v_f.count);
      for (i=0; i<v_f.count; i++) printf(": %s ", v_f.a[i]);
      printf("\n");
    }
  return (0);
}

