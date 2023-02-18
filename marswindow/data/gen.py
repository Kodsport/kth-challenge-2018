#!/usr/bin/python3

import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
mode = cmdlinearg('mode')

if mode == 'start':
    y = 2018 + int(cmdlinearg('k'))
elif mode == 'end':
    y = 10000 - int(cmdlinearg('k'))
else:
    y = random.randint(2017, 10000)
print(y)
