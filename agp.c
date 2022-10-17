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
	  printf("%s %-*s %s   %s\n",
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
  int a, i, j, l;
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
	*opt[i].a = 0;
    }
  // main cycle
  need_arg = 0;
  a = 1;
  current = def;
  while (a < argc || need_arg) 
    {
      // test end arguments
      if (need_arg && a == argc)
	{
	  AGP_ERROR("error: end. need argument for: %s\n", last_flag);
	  return(1);
	}
      arg = argv[a];
      l = strlen(arg);
      // need argument
      if (need_arg)
	{
	  // is this a flag ?
	  if (arg[0] == '-')
	    {
	      AGP_ERROR("error: need argument for: %s\n", last_flag);
	      return(1);
	    }
	  opt[current].v[*opt[current].a] = arg;
	  *opt[current].a += 1;
	  need_arg = 0;
	}
      // long flag ?
      else if (l >= 3 &&
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
		      *opt[i].a += 1;
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
	    {
	      AGP_ERROR("error: not familar flag: %s\n", arg);
	      return(1);
	    }
	}
      // short flag ?
      else if (l >= 2 &&
	       arg[0] == '-' &&
	       arg[1] != '-')
	{
	  for (j=1; arg[j] != '\0'; j++)
	    {
	      // skip
	      if (arg[j] == '-')
		{
		  AGP_ERROR("error: not familar flag: %c\n", arg[j]);
		  return(1);
		}
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
			  *opt[i].a += 1;
			  current = def;
			}
		      else
			{
			  // end ?
			  if (j!=l-1)
			    {
			      AGP_ERROR("error: need argument after: %c\n", arg[j]);
			      return(1);
			    }
			  need_arg = 1;
			  current = i;
			  last_flag = arg;
			}
		      break;
		    }
		}
	      if (find == 0)
		{
		  AGP_ERROR("error: not familar flag: %c\n", arg[j]);
		  return(1);
		}
	    }
	}
      // more
      else
	{
	  // is this a flag ?
	  if (arg[0] == '-')
	    {
	      AGP_ERROR("error: not familar flag: %s\n", arg);
	      return(1);
	    }
	  // if not flag - set current
	  opt[current].v[*opt[current].a] = arg;
	  *opt[current].a += 1;
	}
      a++;
    }
  return (0);
}
