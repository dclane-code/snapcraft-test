#!/usr/bin/env python3

from __future__ import print_function

usage = """Usage:
python3 example-service.py &
python3 example-client.py
python3 example-client.py --exit-service
"""


import sys
from traceback import print_exc

import dbus

if len(sys.argv) < 2:
    name = "<no name>"
else:
    name = sys.argv[1]

def main():
    bus = dbus.SystemBus()

    try:
        remote_object = bus.get_object("org.dclane.SampleService", "/Echo")

        # you can either specify the dbus_interface in each call...
        hello_reply_list = remote_object.HelloWorld(name, dbus_interface = "org.dclane.SampleInterface")
    except dbus.DBusException:
        print_exc()
        print(usage)
        sys.exit(1)

    print(hello_reply_list)


    if sys.argv[1:] == ['--exit-service']:
        iface.Exit()

if __name__ == '__main__':
    main()

