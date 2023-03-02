#!/bin/env python3

import sys

if len(sys.argv) < 2:
    name = "<no name>"
else:
    name = sys.argv[1]


from dasbus.connection import SessionMessageBus
bus = SessionMessageBus()


proxy = bus.get_proxy(
    "org.dclane.Dave",
    "/org/dclane/Dave"
)

print("Response: {}".format(proxy.Hello(name)))


