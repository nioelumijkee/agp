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

#define AGP_INFO(DESC)          {AGP_T_INFO, "--",   NULL,    NULL, DESC}
#define AGP_BOOL(SH,LN,V,DESC)  {AGP_T_BOOL, "-"#SH, "--"#LN, V,    DESC}
#define AGP_STR(SH,LN,V,DESC)   {AGP_T_STR,  "-"#SH, "--"#LN, V,    DESC}
#define AGP_DEF(SH,LN,V,DESC)   {AGP_T_DEF,  "-"#SH, "--"#LN, V,    DESC}
#define AGP_END()               {AGP_T_END,  "--",   NULL,    NULL, NULL}

#define AGP_ERROR(S,B) { fprintf(stderr,S,B); return(1); }

#define AGP_MAX_ARG 32

typedef struct _agp_val {
  int         count;
  const char *a[AGP_MAX_ARG];
} t_agp_val;

typedef struct _agp_options {
  const char  type;
  const char *short_flag;
  const char *long_flag;
  t_agp_val  *v;
  const char *desc;
} t_agp_options;


void agp_usage(t_agp_options *opt);
int agp_parse(t_agp_options *opt, int argc, char *argv[]);

#endif // AGP_H
