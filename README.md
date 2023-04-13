# dclanebus

This is a small sample snap that is just meant to use a few features for the sake of exercising them and keeping an example to work with

apps:
    dclanebus_server        this is a server that provides the dbus name 'org.dclane.Dave' and responds to messages sent to it by echoing back the word that was sent to it.

    dclanebus_client        this is a client that will send a message to the dbus well known name 'org.dclane.Dave'
                            it runs as a daemon when the app is installed

    the dbus interfaces (dclanebus-client plug, dclanebus-server slot) do not need to be directly connected with 'snap-connect'. each of them just connects to dbus.
    (the slotting interface would need to be approved for autoconnection in the store)

    conf                    this app runs dclanebus_conf.py
                                this script opens '/etc/dclanebus.conf'
                                But actually because of a LAYOUT, it really opens $SNAP_COMMON/etc/dclanebus.conf, which is provided by the snap

    unixecho                this uses 'unix_socket_server.c' and binds on /tmp/dclusock
                            it will echo back whatever is written to it

                            NOTE: /tmp/dclusock is actually going to be at /tmp/snap-private-tmp/snap.dclanebus/tmp/dclusock
                            connect to it with netcat (eg: 'nc -U /tmp/snap-private-tmp/snap.dclanebus/tmp/dclusock')

    unixecho-abstract       uses an abstract unix domain socket rather than a filesystem backed one
                            does not work. note to self: look at snappy-debug for clues (currently unsolved)


