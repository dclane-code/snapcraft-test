#!/bin/env python3

import sys
print("path = {}".format(sys.path))
#print("pythonpath = {}".format(sys.pythonpath))

from dasbus.server.interface import dbus_interface
from dasbus.typing import Str


@dbus_interface("org.dclane.Dave")
class Dave(object):

    def Hello(self, name: Str) -> Str:
        print("msg recv'd")
        return "Hello {}!".format(name)

print(Dave.__dbus_xml__)


from dasbus.connection import SessionMessageBus
bus = SessionMessageBus()

bus.publish_object("/org/dclane/Dave", Dave())
bus.register_service("org.dclane.Dave")

from dasbus.loop import EventLoop
loop = EventLoop()
loop.run()
