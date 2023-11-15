/**
 * Copyright (C) 2022 Nioelumijke
 * All rights reserved.
 * See LICENSE file.
 */

#include <string.h>
#include "agp.h"

void
agp_usage(t_agp_options *opt)
{
  int i;
  const char *a;
  const char *sf;
  const char *lf;
  int maxl;
  // max length long flag
  maxl = 0;
  for (i=0; opt[i].type != AGP_T_END; i++)
    {
      if (opt[i].type != AGP_T_INFO)
	{
	  int l = strlen(opt[i].long_flag);
	  if (l > maxl)
	    maxl = l;
	}
    }
  // print all
  for (i=0; opt[i].type != AGP_T_END; i++)
    {
      if (opt[i].type == AGP_T_INFO)
	printf("%s\n", opt[i].desc);
      else
	{
	  // skip short
	  if (opt[i].short_flag[1] == '-')
	    sf = "  ";
	  else
	    sf = opt[i].short_flag;
	  // skip long
	  if (opt[i].long_flag[2] == '-')
	    lf = " ";
	  else
	    lf = opt[i].long_flag;
	  // arg
	  if (opt[i].type == AGP_T_BOOL)
	    a = "     ";
	  else // AGP_T_STR AGP_T_DEF
	    a = "<arg>";
	  printf("  %s %-*s %s   %s\n",
		 sf,
		 maxl,
		 lf,
		 a,
		 opt[i].desc);
	}
    }
}

int
agp_parse(t_agp_options *opt, int argc, char *argv[])
{
  int i, j;
  int arg_len;
  int arg_num;
  int find;
  int def;
  int current;
  int need_arg;
  const char *arg;
  const char *last_flag;
  // find default
  def = -1;
  for (i=0; opt[i].type != AGP_T_END; i++)
    {
      if (opt[i].type == AGP_T_DEF)
	{
	  def = i;
	  break;
	}
    }
  // disable all
  for (i=0; opt[i].type != AGP_T_END; i++)
    {
      if (opt[i].type != AGP_T_INFO)
	opt[i].v->count = 0;
    }
  // main cycle
  need_arg = 0;
  arg_num = 1;
  current = def;
  last_flag = opt[def].desc;
  while (arg_num < argc || need_arg) 
    {
      // test end arguments
      if (need_arg && arg_num == argc)
	AGP_ERROR("error: end. need argument for: %s\n", last_flag);
      arg = argv[arg_num];
      arg_len = strlen(arg);
      if (arg_len == 0)
	AGP_ERROR("error: length argument zero: %s\n", argv[arg_num]);
      // need argument
      if (need_arg)
	{
	  // is this a flag ?
	  if (arg[0] == '-')
	    AGP_ERROR("error: need argument for: %s\n", last_flag);
	  if (opt[current].v->count == AGP_MAX_ARG)
	    AGP_ERROR("error: max arguments for: %s\n", last_flag);
	  opt[current].v->a[opt[current].v->count] = arg;
	  opt[current].v->count++;
	  need_arg = 0;
	}
      // long flag ?
      else if (arg_len >= 3 &&
	       arg[0] == '-' &&
	       arg[1] == '-' &&
	       arg[2] != '-')
	{
	  // find
	  find = 0;
	  for (i=0; opt[i].type != AGP_T_END; i++)
	    {
	      if ((opt[i].type == AGP_T_BOOL ||
		   opt[i].type == AGP_T_STR) && 
		  !strcmp(arg, opt[i].long_flag))
		{
		  find = 1;
		  if (opt[i].type == AGP_T_BOOL)
		    {
		      opt[i].v->count++;
		      current = def;
		    }
		  else
		    {
		      need_arg = 1;
		      current = i;
		      last_flag = arg;
		    }
		  break;
		}
	    }
	  if (find == 0)
	    AGP_ERROR("error: not familar flag: %s\n", arg);
	}
      // short flag ?
      else if (arg_len >= 2 &&
	       arg[0] == '-' &&
	       arg[1] != '-')
	{
	  for (j=1; arg[j] != '\0'; j++)
	    {
	      // skip
	      if (arg[j] == '-')
		AGP_ERROR("error: not familar flag: %c\n", arg[j]);
	      // find
	      find = 0;
	      for (i=0; opt[i].type != AGP_T_END; i++)
		{
		  if ((opt[i].type == AGP_T_BOOL ||
		       opt[i].type == AGP_T_STR) && 
		      opt[i].short_flag[1] == arg[j])
		    {
		      find = 1;
		      if (opt[i].type == AGP_T_BOOL)
			{
			  opt[i].v->count++;
			  current = def;
			}
		      else
			{
			  // end ?
			  if (j != arg_len-1)
			    AGP_ERROR("error: need argument after: %c\n", arg[j]);
			  need_arg = 1;
			  current = i;
			  last_flag = arg;
			}
		      break;
		    }
		}
	      if (find == 0)
		AGP_ERROR("error: not familar flag: %c\n", arg[j]);
	    }
	}
      // more
      else
	{
	  // is this a flag ?
	  if (arg[0] == '-')
	    AGP_ERROR("error: not familar flag: %s\n", arg);
	  // if not flag - set current
	  if (opt[current].v->count == AGP_MAX_ARG)
	    AGP_ERROR("error: max arguments for: %s\n", last_flag);
	  opt[current].v->a[opt[current].v->count] = arg;
	  opt[current].v->count++;
	}
      arg_num++;
    }
  return (0);
}
