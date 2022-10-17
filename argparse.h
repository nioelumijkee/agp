/**
 * Copyright (C) 2022 Nioelumijke
 * All rights reserved.
 * See LICENSE file.
 */

#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <stdio.h>

enum argparse_type {
  ARGPARSE_T_INFO,
  ARGPARSE_T_B,
  ARGPARSE_T_O,
  ARGPARSE_T_M,
  ARGPARSE_T_END,
};

#define ARGPARSE_INFO(DESC)           {ARGPARSE_T_INFO, '-', NULL,    NULL, NULL, DESC}
#define ARGPARSE_BOOL(SH,LN,A,DESC)   {ARGPARSE_T_B,    SH,  "--"#LN, A,    NULL, DESC}
#define ARGPARSE_ONE(SH,LN,A,V,DESC)  {ARGPARSE_T_O,    SH,  "--"#LN, A,    V,    DESC}
#define ARGPARSE_MANY(SH,LN,A,V,DESC) {ARGPARSE_T_M,    SH,  "--"#LN, A,    V,    DESC}
#define ARGPARSE_END()                {ARGPARSE_T_END,  '-', NULL,    NULL, NULL, NULL}

#define ARGPARSE_ERROR(S,B) { fprintf(stderr,S,B); }

#define ARGPARSE_MAX_STR_LEN 100
#define ARGPARSE_MAX_ARG 16

typedef struct _argparse_options {
  const char type;
  const char short_flag;
  const char *long_flag;
  char *a;
  void *v;
  const char *desc;
} t_argparse_options;


void argparse_usage(t_argparse_options *opt);
int argparse_parse(t_argparse_options *opt, int argc, char *argv[]);

#endif // ARGPARSE_H
