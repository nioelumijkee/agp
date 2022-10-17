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
  
  // max length long flag
  int maxl = 0;
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
	  char sf1;
	  char sf2;
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
	  const char *lf;
	  if (opt[i].long_flag[2] == '-')
	    {
	      lf = " ";
	    }
	  else
	    {
	      lf = opt[i].long_flag;
	    }
	  printf("%c%c %-*s   %s\n",
		 sf1,sf2,
		 maxl,
		 lf,
		 opt[i].desc);
	}
    }
}

int
argparse_split_to_char(const char *s, char *v)
{
  int i,j, count;
  char buf[ARGPARSE_MAX_STR_LEN];
  for (i=0, j=0, count=0; s[i]!='\0'; i++)
    {
      if (s[i] == ',')
	{
	  if (j != 0)
	    {
	      buf[j] = '\0';
	      strcpy(&v[count*ARGPARSE_MAX_STR_LEN], buf);
	      count++;
	      j=0;
	      if (count == ARGPARSE_MAX_ARG)
		{
		  return(count);
		}
	    }
	}
      else
	{
	  // max len - 1
	  if (j < ARGPARSE_MAX_STR_LEN-1)
	    {
	      buf[j] = s[i];
	      j++;
	    }
	}
    }
  // last
  if (j != 0)
    {
      buf[j] = '\0';
      strcpy(&v[count*ARGPARSE_MAX_STR_LEN], buf);
      count++;
    }
  return(count);
}

int
argparse_parse(t_argparse_options *opt, int argc, char *argv[])
{
  int a, i, j, l;
  const char *arg;
  int find;
  int seq[ARGPARSE_MAX_ARG];
  int count;

  // disable all
  for (i=0; opt[i].type != ARGPARSE_T_END; i++)
    {
      if (opt[i].type != ARGPARSE_T_INFO)
	{
	  *opt[i].a = 0;
	}
    }

  a = 1;
 next:
  while (a < argc) 
    {
      arg = argv[a];
      l = strlen(arg);
      count = 0;

      // long flag ?
      if (l >= 3 &&
	  arg[0] == '-' &&
	  arg[1] == '-' &&
	  arg[2] != '-' &&
	  arg[2] != '\0')
	{
	  find = 0;
	  for (i=0; opt[i].type != ARGPARSE_T_END; i++)
	    {
	      if (opt[i].type != ARGPARSE_T_INFO && !strcmp(arg, opt[i].long_flag))
		{
		  find = 1;
		  seq[count] = i;
		  count++;
		}
	    }
	  if (find == 0)
	    {
	      ARGPARSE_ERROR("error: not familar flag: %s\n", arg);
	      return(1);
	    }
	}

      //short flag ?
      else if (arg[0] == '-' &&
	       arg[1] != '-' &&
	       arg[1] != '\0')
	{
	  for (j=1; arg[j] != '\0'; j++)
	    {
	      if (arg[j] == '-')
		{
		  ARGPARSE_ERROR("error: not familar flag: %c\n", arg[j]);
		  return(1);
		}
	      find = 0;
	      for (i=0; opt[i].type != ARGPARSE_T_END; i++)
		{
		  if (opt[i].type != ARGPARSE_T_INFO && opt[i].short_flag == arg[j])
		    {
		      find = 1;
		      seq[count] = i;
		      count++;
		    }
		}
	      if (find == 0)
		{
		  ARGPARSE_ERROR("error: not familar flag: %c\n", arg[j]);
		  return(1);
		}
	    }
	}
      else
	{
	  ARGPARSE_ERROR("error: it should be flag: %s\n", arg);
	  return(1);
	}

      // parse seq
      for (i=0; i<count; i++)
	{
	  switch (opt[seq[i]].type)
	    {

	    case ARGPARSE_T_B:
	      *opt[seq[i]].a = 1;
	      break;


	    case ARGPARSE_T_O:
	      if (a == argc-1)
		{
		  ARGPARSE_ERROR("error: need argument for: %s\n", arg);
		  return(1);
		}
	      else
		{
		  char *v = (char *)opt[seq[i]].v;
		  a++;
		  strncpy(v, argv[a],ARGPARSE_MAX_STR_LEN-1);
		  *opt[seq[i]].a = 1;
		  a++;
		  goto next;
		}
	      break;


	    case ARGPARSE_T_M:
	      if (a == argc-1)
		{
		  ARGPARSE_ERROR("error: need argument for: %s\n", arg);
		  return(1);
		}
	      else
		{
		  char *v = (char *)opt[seq[i]].v;
		  a++;
		  *opt[seq[i]].a = argparse_split_to_char(argv[a], v);
		  a++;
		  goto next;
		}
	      break;


	    default:
	      break;
	    }
	}
      a++;
      goto next;
    }
  return (0);
}
