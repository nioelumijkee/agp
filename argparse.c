/**
 * Copyright (C) 2022 Nioelumijke
 * All rights reserved.
 * See LICENSE file.
 */

#include <string.h>
#include "argparse.h"

void
argparse_usage(t_argparse_options *opt)
{
  int i;
  char sf1;
  char sf2;
  const char *a;
  const char *lf;
  int maxl;
  // max length long flag
  maxl = 0;
  for (i=0; opt[i].type != ARGPARSE_T_END; i++)
    {
      if (opt[i].type != ARGPARSE_T_INFO)
	{
	  int l = strlen(opt[i].long_flag);
	  if (l > maxl)
	    maxl = l;
	}
    }
  // print all
  for (i=0; opt[i].type != ARGPARSE_T_END; i++)
    {
      if (opt[i].type == ARGPARSE_T_INFO)
	{
	  printf("%s\n", opt[i].desc);
	}
      else
	{
	  // skip short
	  if (opt[i].short_flag == '-')
	    {
	      sf1 = ' ';
	      sf2 = ' ';
	    }
	  else
	    {
	      sf1 = '-';
	      sf2 = opt[i].short_flag;
	    }
	  // skip long
	  if (opt[i].long_flag[2] == '-')
	    {
	      lf = " ";
	    }
	  else
	    {
	      lf = opt[i].long_flag;
	    }
	  // arg
	  if (opt[i].type == ARGPARSE_T_BOOL)
	    {
	      a = "     ";
	    }
	  else // ARGPARSE_T_STR ARGPARSE_T_DEF
	    {
	      a = "<arg>";
	    }
	  printf("%c%c %-*s %s   %s\n",
		 sf1,sf2,
		 maxl,
		 lf,
		 a,
		 opt[i].desc);
	}
    }
}

int
argparse_parse(t_argparse_options *opt, int argc, char *argv[])
{
  int a, i, j, l;
  const char *arg;
  int find;
  int def;
  int current;
  // find default
  def = -1;
  for (i=0; opt[i].type != ARGPARSE_T_END; i++)
    {
      if (opt[i].type == ARGPARSE_T_DEF)
	{
	  def = i;
	}
    }
  // disable all
  for (i=0; opt[i].type != ARGPARSE_T_END; i++)
    {
      if (opt[i].type != ARGPARSE_T_INFO)
	{
	  *opt[i].a = 0;
	}
    }
  a = 1;
  current = def;
  while (a < argc) 
    {
      arg = argv[a];
      l = strlen(arg);
      // long flag ?
      if (l >= 3 &&
	  arg[0] == '-' &&
	  arg[1] == '-' &&
	  arg[2] != '-')
	{
	  // find
	  find = 0;
	  for (i=0; opt[i].type != ARGPARSE_T_END; i++)
	    {
	      if ((opt[i].type == ARGPARSE_T_BOOL ||
		   opt[i].type == ARGPARSE_T_STR) && 
		  !strcmp(arg, opt[i].long_flag))
		{
		  find = 1;
		  // if bool set
		  if (opt[i].type == ARGPARSE_T_BOOL)
		    {
		      *opt[i].a += 1;
		      current = def;
		    }
		  else
		    {
		      current = i;
		    }
		  break;
		}
	    }
	  if (find == 0)
	    {
	      ARGPARSE_ERROR("error: not familar flag: %s\n", arg);
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
		  ARGPARSE_ERROR("error: not familar flag: %c\n", arg[j]);
		  return(1);
		}
	      // find
	      find = 0;
	      for (i=0; opt[i].type != ARGPARSE_T_END; i++)
		{
		  if ((opt[i].type == ARGPARSE_T_BOOL ||
		       opt[i].type == ARGPARSE_T_STR) && 
		      opt[i].short_flag == arg[j])
		    {
		      find = 1;
		      // if bool set
		      if (opt[i].type == ARGPARSE_T_BOOL)
			{
			  *opt[i].a += 1;
			  current = def;
			}
		      else
			{
			  current = i;
			}
		      break;
		    }
		}
	      if (find == 0)
		{
		  ARGPARSE_ERROR("error: not familar flag: %c\n", arg[j]);
		  return(1);
		}
	    }
	}
      // is this a flag ?
      else if (l >= 1 &&
	       arg[0] == '-')
	{
	  ARGPARSE_ERROR("error: not familar flag: %s\n", arg);
	  return(1);
	}
      // if not flag - set current
      else
	{
	  if (current >= 0)
	    {
	      opt[current].v[*opt[current].a] = arg;
	      *opt[current].a += 1;
	    }
	}
      a++;
    }
  return (0);
}
