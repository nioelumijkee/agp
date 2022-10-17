#!/usr/bin/python3
#

import random
from subprocess import PIPE, Popen

opt_default = []
opt_bool_short = []
opt_bool_long = []
opt_str_short = []
opt_str_long = []

def parse_options():
    print('-'*80)
    print("parse options.")

    cmd = "./example --help"
    p = Popen(cmd, shell=True, stdout=PIPE, stderr=PIPE)
    stdout, stderr = p.communicate()
    if stderr:
        print("error test: parse_options")
        print (stderr.decode())
        exit(0)
    s = stdout.decode().split('\n')
    opt = []
    for i in s:
        i = i.split()
        if len(i) > 1:
            if (i[0] == '<arg>'):
                flag = i[-1].replace('(','').replace(')','')
                opt_default = [' ', flag]
            elif (i[-1][0] == '('):
                opt.append(i)
    opt_bool = []
    opt_str = []
    for i in opt:
        flag = ''
        flag = i[-1].replace('(','').replace(')','')
        # str
        if "<arg>" in i:
            b = []
            for j in i:
                if len(j) == 2 and j[0] == '-':
                    opt_str_short.append([j[1], flag])
                elif j[0] == '-':
                    opt_str_long.append([j, flag])
        # bool
        else:
            b = []
            for j in i:
                if len(j) == 2 and j[0] == '-':
                    opt_bool_short.append([j[1], flag])
                elif j[0] == '-':
                    opt_bool_long.append([j, flag])

    print("default option:")
    print(opt_default)
    print("options bool short:")
    for i in opt_bool_short: print(i)
    print("options bool long:")
    for i in opt_bool_long: print(i)
    print("options str short:")
    for i in opt_str_short: print(i)
    print("options str long:")
    for i in opt_str_long: print(i)


def test_options():
    print('-'*80)
    print("test options.")
    
    for i in range(100):
        n = random.randint(0, 32)
        a = []
        for j in range(n):
            c = random.randint(0, 100) > 50 # chanse 50%
            # if c:
            #     a.append(





def test_arguments():
    print('-'*80)
    print("test arguments.")

if __name__ == '__main__':
    parse_options()
    test_options()
    test_arguments()
