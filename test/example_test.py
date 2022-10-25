#!/usr/bin/python3
#

import random
from subprocess import PIPE, Popen
import time

flags           = {'a':0,
                   'b':0,
                   'c':0,
                   'd':[],
                   'e':[],
                   'f':[]}
opt_default     = {'d':'d'}
opt_bool_short  = {'a':'a',
                   'b':'b'}
opt_bool_long   = {'a':'--bool-a',
                   'c':'--bool-c'}
opt_str_short   = {'d':'d',
                   'e':'e'}
opt_str_long    = {'d':'--str-d',
                   'f':'--str-f'}

max_arg = 32

def run_proc(cmd):
    p = Popen(cmd, shell=True, stdout=PIPE, stderr=PIPE)
    stdout, stderr = p.communicate()
    answer = {}
    if stderr:
        err = True
    else:
        err = False
        s = stdout.decode().strip().split('\n')
        for i in s:
            i = i.strip().split(':')
            flag = i[0]
            try:
                if flag == 'd' or flag == 'e' or flag == 'f':
                    strings = []
                    for j in i[2:]:
                        strings.append(j.strip())
                    answer[flag] = strings
                else:
                    count = int(i[1].strip())
                    answer[flag] = count
            except:
                print('*'*80)
                print('\nerror parse out:')
                print('*'*80)
                print(cmd)
                print('*'*80)
                print(s)
                exit()
    return(err, answer, stderr)


def random_string(l):
    alph = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_+='
    # error symbols: $#()[]{}&-*
    s = ''
    for i in range(l):
        s = s + alph[random.randint(0,len(alph)-1)]
    return(s)


def test_default():
    print("test default option.")
    amount_tests = 1000
    for t in range(amount_tests):
        args_amount = random.randint(0,max_arg)
        args = []
        for a in range(args_amount):
            rs = random_string(random.randint(1,1000))
            args.append(rs)
        s = './example ' + ' '.join(args)
        err, answer, stderr = run_proc(s)

        # test
        if err:
            print("\nerror")
            print(stderr)
            print(s, '->', answer)
            exit()

        if args != answer['d']:
            print("\nerror")
            print(s, '->', args,'->', answer['d'])
            exit()

        print('.',end='',flush=True)
        time.sleep(0.001)
    print()


if __name__ == '__main__':
    test_default()
