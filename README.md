### argparse

Simple implementation of command line argument parsing. There are two kinds of flags, with and without arguments. Each flag can have a short and long name. You can (should) also assign a default option when the program is invoked without flags. The meaning of this library is simplicity and clarity.

To use it, you need to include a header file and add an object file to the linker. Next, need to declare the necessary variables and describe the structure with options.

``` c++
  /* for arguments */
  int a_a;
  int a_b;
  int a_c;
  int a_d;
  int a_e;
  int a_f;
  int a_h;
  const char *v_d[ARGPARSE_MAX_ARG];
  const char *v_e[ARGPARSE_MAX_ARG];
  const char *v_f[ARGPARSE_MAX_ARG];

  /* options description */
  t_argparse_options argopt[] = {
    /* flag-short flag-long exist-var var description */
    ARGPARSE_INFO("Usage:"),
    ARGPARSE_INFO(""),
    ARGPARSE_INFO("Options without arguments:"),
    ARGPARSE_BOOL('a', bool-a, &a_a,      "bool a"),
    ARGPARSE_BOOL('b', -,      &a_b,      "bool b"),
    ARGPARSE_BOOL('-', bool-c, &a_c,      "bool c"),
    ARGPARSE_INFO("Options with arguments:"),
    ARGPARSE_STR('d',  str-d,  &a_d, v_d, "strings d"),
    ARGPARSE_STR('e',  -,      &a_e, v_e, "strings e"),
    ARGPARSE_STR('-',  str-f,  &a_f, v_f, "strings f"),
    ARGPARSE_INFO("Default argument:"),
    ARGPARSE_DEF('-',  -,      &a_d, v_d, "defualt option(set \'d\')"),
    ARGPARSE_INFO("For help:"),
    ARGPARSE_BOOL('h', help,   &a_h,      "print this."),
    ARGPARSE_END(),
  };
```
And(Returns zero on success and one on error).

``` c++
  int ret = argparse_parse(argopt, argc, argv);
```

Check all variables a_* in a loop. If the flag was set, then their value is non-zero and in options with string arguments, variables v_* contain references to the passed arguments.

Source of inspiration: [cofyc/argparse](https://github.com/cofyc/argparse)
