#!/usr/bin/python3
#

import random
from subprocess import PIPE, Popen

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


def random_string():
    l = random.randint(1,256)
    alph = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_+=?'
    # error symbols: $#()[]{}&-*<>/\\|'";`~
    s = ''
    for i in range(l):
        s = s + alph[random.randint(0,len(alph)-1)]
    return(s)

def random_symbol():
    alph = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_+=?'
    # error symbols: $#()[]{}&-*<>/\\|'";`~
    s = alph[random.randint(0,len(alph)-1)]
    return(s)


def test_default(amount_tests):
    print("test default option.")
    for t in range(amount_tests):
        args_amount = random.randint(0,max_arg)
        args = []
        for a in range(args_amount):
            args.append(random_string())
        s = './example ' + ' '.join(args)
        err, answer, stderr = run_proc(s)

        if err:
            print("\nerror")
            print(stderr)
            print(s)
            exit()

        # test
        if args != answer['d']:
            print("\nerror")
            print(s, '->', args,'->', answer['d'])
            exit()

        print('.',end='',flush=True)
    print()


def test_default_with_flag(amount_tests):
    print("test default option with flag.")
    for t in range(amount_tests):
        args_amount = random.randint(1,max_arg)
        args = []
        for a in range(args_amount):
            args.append(random_string())
        s = './example -d ' + ' '.join(args)
        err, answer, stderr = run_proc(s)

        if err:
            print("\nerror")
            print(stderr)
            print(s)
            exit()

        # test
        if args != answer['d']:
            print("\nerror")
            print(s, '->', args,'->', answer['d'])
            exit()

        print('.',end='',flush=True)
    print()

def test_bool_short(amount_tests):
    print("test bool short options.")
    for t in range(amount_tests):
        args_amount = random.randint(0,100)
        args = []
        count_a = 0
        count_b = 0
        err_out = 0
        for a in range(args_amount):
            r = random.randint(0, 4)
            if r == 0:
                b = ' -a'
                count_a += 1
            elif r == 1:
                b = ' -b'
                count_b += 1
            elif r == 2:
                b = ' -aa'
                count_a += 2
            elif r == 3:
                b = ' -bb'
                count_b += 2
            elif r == 4:
                b = ' -ab'
                count_a += 1
                count_b += 1
            elif r == 5:
                b = ' -ba'
                count_a += 1
                count_b += 1
            else:
                b = random_symbol()
                if b != 'a' and b != 'b':
                    err_out = 1
            args.append(b)
        s = './example ' + ''.join(args)
        err, answer, stderr = run_proc(s)

        if err and err_out:
            pass
        elif err:
            print("\nerror")
            print(stderr)
            print(s)
            exit()
        elif answer['a'] != count_a or answer['b'] != count_b:
            print("\nerror")
            print(s)
            print(count_a, count_b)
            print(answer['a'], answer['b'])
            exit()

        print('.',end='',flush=True)
    print()


if __name__ == '__main__':
    amount_tests = 1000
    test_default(amount_tests)
    test_default_with_flag(amount_tests)
    test_bool_short(amount_tests)
