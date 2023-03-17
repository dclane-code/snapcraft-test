#!/bin/env python3

with open("/etc/dclanebus.conf", "r") as conf:
    print(conf.read(), end='')

