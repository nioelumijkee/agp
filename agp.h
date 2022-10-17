/**
 * Copyright (C) 2022 Nioelumijke
 * All rights reserved.
 * See LICENSE file.
 */

#ifndef AGP_H
#define AGP_H

#include <stdio.h>

enum agp_type {
  AGP_T_INFO,
  AGP_T_BOOL,
  AGP_T_STR,
  AGP_T_DEF,
  AGP_T_END,
};

#define AGP_INFO(DESC)          {AGP_T_INFO, "--",   NULL,    NULL, NULL, DESC}
#define AGP_BOOL(SH,LN,A,DESC)  {AGP_T_BOOL, "-"#SH, "--"#LN, A,    NULL, DESC}
#define AGP_STR(SH,LN,A,V,DESC) {AGP_T_STR,  "-"#SH, "--"#LN, A,    V,    DESC}
#define AGP_DEF(SH,LN,A,V,DESC) {AGP_T_DEF,  "-"#SH, "--"#LN, A,    V,    DESC}
#define AGP_END()               {AGP_T_END,  "--",   NULL,    NULL, NULL, NULL}

#define AGP_ERROR(S,B) { fprintf(stderr,S,B); }

#define AGP_MAX_ARG 64

typedef struct _agp_options {
  const char type;
  const char *short_flag;
  const char *long_flag;
  int  *a;
  const char **v;
  const char *desc;
} t_agp_options;


void agp_usage(t_agp_options *opt);
int agp_parse(t_agp_options *opt, int argc, char *argv[]);

#endif // AGP_H
