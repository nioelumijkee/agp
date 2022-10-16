/* parse argumens */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* #include "argparse.h" */

enum argparse_type {
  ARGTYPE_HELP,
  ARGTYPE_B,
  ARGTYPE_I,
  ARGTYPE_F,
  ARGTYPE_S,
  ARGTYPE_IA,
  ARGTYPE_FA,
  ARGTYPE_SA,
  ARGTYPE_END,
};

#define ARGOPT_HELP(DESC)         {ARGTYPE_HELP, '-', NULL,    NULL, NULL, DESC}
#define ARGOPT_B(SH,LN,A,DESC)    {ARGTYPE_B,    SH,  "--"#LN, A,    NULL, DESC}
#define ARGOPT_I(SH,LN,A,V,DESC)  {ARGTYPE_I,    SH,  "--"#LN, A,    V,    DESC}
#define ARGOPT_F(SH,LN,A,V,DESC)  {ARGTYPE_F,    SH,  "--"#LN, A,    V,    DESC}
#define ARGOPT_S(SH,LN,A,V,DESC)  {ARGTYPE_S,    SH,  "--"#LN, A,    V,    DESC}
#define ARGOPT_IA(SH,LN,A,V,DESC) {ARGTYPE_IA,   SH,  "--"#LN, A,    V,    DESC}
#define ARGOPT_FA(SH,LN,A,V,DESC) {ARGTYPE_FA,   SH,  "--"#LN, A,    V,    DESC}
#define ARGOPT_SA(SH,LN,A,V,DESC) {ARGTYPE_SA,   SH,  "--"#LN, A,    V,    DESC}
#define ARGOPT_END()              {ARGTYPE_END,  '-', NULL,    NULL, NULL, NULL}

#define ARGPARSE_ERROR(S,B) { fprintf(stderr,S,B); }

#define ARGPARSE_MAX_STR_LEN 100
#define ARGPARSE_MAX_ARG 16

typedef struct _argparse_options {
  char type;
  const char short_flag;
  const char *long_flag;
  char *a;
  void *v;
  const char *desc;
} t_argparse_options;


void argparse_usage(t_argparse_options *opt);
int argparse_parse(t_argparse_options *opt, int argc, char *argv[]);

void argparse_usage(t_argparse_options *opt)
{
  int i;

  // max length long flag
  int maxl = 0;
  for (i=0; opt[i].type != ARGTYPE_END; i++)
    {
      if (opt[i].type != ARGTYPE_HELP)
	{
	  int l = strlen(opt[i].long_flag);
	  if (l > maxl)
	    maxl = l;
	}
    }

  // print all
  for (i=0; opt[i].type != ARGTYPE_END; i++)
    {
      if (opt[i].type == ARGTYPE_HELP)
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

int argparse_isint(const char *s)
{
  int i;
  for (i=0; s[i] != '\0'; i++)
    {
      if (s[i] < '0' || s[i] > '9')
	{
	  return(0);
	}
    }
  return(1);
}

int argparse_isfloat(const char *s)
{
  int i;
  for (i=0; s[i] != '\0'; i++)
    {
      if ((s[i] < '0' || s[i] > '9') && s[i] != '.')
	{
	  return(0);
	}
    }
  return(1);
}


int argparse_split_to_int(const char *s, int *v)
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
	      v[count] = atoi(buf);
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
	  buf[j] = s[i];
	  j++;
	}
    }
  // last
  if (j != 0)
    {
      buf[j] = '\0';
      v[count] = atoi(buf);
      count++;
    }
  return(count);
}


int argparse_split_to_float(const char *s, float *v)
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
	      v[count] = atof(buf);
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
	  buf[j] = s[i];
	  j++;
	}
    }
  // last
  if (j != 0)
    {
      buf[j] = '\0';
      v[count] = atof(buf);
      count++;
    }
  return(count);
}

int argparse_split_to_char(const char *s, char *v)
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
	  buf[j] = s[i];
	  j++;
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

int argparse_parse(t_argparse_options *opt, int argc, char *argv[])
{
  int a, i, j, l;
  const char *arg;
  int find;
  int seq[ARGPARSE_MAX_ARG];
  int count;
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
	  for (i=0; opt[i].type != ARGTYPE_END; i++)
	    {
	      if (opt[i].type != ARGTYPE_HELP && !strcmp(arg, opt[i].long_flag))
		{
		  seq[count] = i;
		  count++;
		}
	    }
	}
      //short flag ?
      else if (arg[0] == '-' &&
	       arg[1] != '-' &&
	       arg[1] != '\0')
	{
	  for (j=1; arg[j] != '\0'; j++)
	    {
	      find = 0;
	      for (i=0; opt[i].type != ARGTYPE_END; i++)
		{
		  if (opt[i].type != ARGTYPE_HELP && opt[i].short_flag == arg[j])
		    {
		      find = 1;
		      seq[count] = i;
		      count++;
		    }
		}
	      // nothing found familiar flags
	      if (find == 0)
		{
		  ARGPARSE_ERROR("error: not familar flags: %s\n", arg);
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
	    case ARGTYPE_B:
	      *opt[seq[i]].a = 1;
	      a++;
	      break;


	    case ARGTYPE_I:
	      if (a == argc-1)
		{
		  ARGPARSE_ERROR("error: need argument for: %s\n", arg);
		  return(1);
		}
	      else
		{
		  *opt[seq[i]].a = 1;
		  int *v = (int *)opt[seq[i]].v;
		  a++;
		  if (argparse_isint(argv[a]))
		    {
		      *v = atoi(argv[a]);
		      a++;
		      goto next;
		    }
		  else
		    {
		      ARGPARSE_ERROR("error: need int argument for: %s\n", arg);
		      return(1);
		    }
		}
	      break;


	    case ARGTYPE_F:
	      if (a == argc-1)
		{
		  ARGPARSE_ERROR("error: need argument for: %s\n", arg);
		  return(1);
		}
	      else
		{
		  *opt[seq[i]].a = 1;
		  float *v = (float *)opt[seq[i]].v;
		  a++;
		  if (argparse_isfloat(argv[a]))
		    {
		      *v = atof(argv[a]);
		      a++;
		      goto next;
		    }
		  else
		    {
		      ARGPARSE_ERROR("error: need float argument for: %s\n", arg);
		      return(1);
		    }
		}
	      break;


	    case ARGTYPE_S:
	      if (a == argc-1)
		{
		  ARGPARSE_ERROR("error: need argument for: %s\n", arg);
		  return(1);
		}
	      else
		{
		  *opt[seq[i]].a = 1;
		  char *v = (char *)opt[seq[i]].v;
		  a++;
		  strcpy(v, argv[a]);
		  a++;
		  goto next;
		}
	      break;


	    case ARGTYPE_IA:
	      if (a == argc-1)
		{
		  ARGPARSE_ERROR("error: need argument for: %s\n", arg);
		  return(1);
		}
	      else
		{
		  int *v = (int *)opt[seq[i]].v;
		  a++;
		  *opt[seq[i]].a = argparse_split_to_int(argv[a], v);
		  a++;
		  goto next;
		}
	      break;


	    case ARGTYPE_FA:
	      if (a == argc-1)
		{
		  ARGPARSE_ERROR("error: need argument for: %s\n", arg);
		  return(1);
		}
	      else
		{
		  float *v = (float *)opt[seq[i]].v;
		  a++;
		  *opt[seq[i]].a = argparse_split_to_float(argv[a], v);
		  a++;
		  goto next;
		}
	      break;


	    case ARGTYPE_SA:
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
    }
  return (0);
}




int main(int argc, char *argv[])
{
  int i;

  char arg_b=0;
  char arg_c=0;
  char arg_i=0;  int   v_i;
  char arg_f=0;  float v_f;
  char arg_s=0;  char  v_s[ARGPARSE_MAX_STR_LEN];
  char arg_ia=0; int   v_ia[ARGPARSE_MAX_ARG];
  char arg_fa=0; float v_fa[ARGPARSE_MAX_ARG];
  char arg_sa=0; char  v_sa[ARGPARSE_MAX_ARG][ARGPARSE_MAX_STR_LEN];

  t_argparse_options argopt[] = {
    /* flag-short flag-long exist-var var description */
    ARGOPT_HELP("Usage:"),
    ARGOPT_HELP(""),
    ARGOPT_HELP("Basic options:"),
    ARGOPT_B('b',      boolean,         &arg_b,         "description boolean                   (no arguments)"),
    ARGOPT_B('c',      another-boolean, &arg_c,         "description another boolean           (no arguments)"),
    ARGOPT_I('i',      intgr,           &arg_i,  &v_i,  "description integer                   (int)"),
    ARGOPT_F('f',      flt,             &arg_f,  &v_f,  "description float                     (float)"),
    ARGOPT_S('s',      str,             &arg_s,  &v_s,  "description string                    (string)"),
    ARGOPT_S('-',      str-no-shrt,     &arg_s,  &v_s,  "description string without short flag (string)"),
    ARGOPT_S('w',      -,               &arg_s,  &v_s,  "description string without long flag  (string)"),
    ARGOPT_HELP(""),
    ARGOPT_HELP("Group options:"),
    ARGOPT_IA('I',     intgr-array,     &arg_ia, &v_ia, "description integer array             (int,int,...)"),
    ARGOPT_FA('F',     flt-array,       &arg_fa, &v_fa, "description float array               (float,float,...)"),
    ARGOPT_SA('S',     str-array,       &arg_sa, &v_sa, "description string array              (string,string,...)"),
    ARGOPT_END(),
  };

  // parse
  int ret = argparse_parse(argopt, argc, argv);
  if (ret != 0)
    {
      argparse_usage(argopt);
    }
  else
    {
      if (arg_b)
	{
	  printf("boolean is set\n");
	}
      if (arg_c)
	{
	  printf("another boolean is set\n");
	}
      if (arg_i)
	{
	  printf("integer is set: %d\n", (int)v_i);
	}
      if (arg_ia)
	{
	  for (i=0; i<arg_ia; i++)
	    printf("integer array is set: %d\n", (int)v_ia[i]);
	}
      if (arg_f)
	{
	  printf("float is set: %g\n", (float)v_f);
	}
      if (arg_fa)
	{
	  for (i=0; i<arg_fa; i++)
	    printf("float array is set: %g\n", (float)v_fa[i]);
	}
      if (arg_s)
	{
	  printf("string is set: %s\n", v_s);
	}
      if (arg_sa)
	{
	  for (i=0; i<arg_sa; i++)
	    printf("string array is set: %s\n", v_sa[i]);
	}
    }



  return 0;
}
