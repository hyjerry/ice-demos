#!/usr/bin/env python
# **********************************************************************
#
# Copyright (c) 2003-2018 ZeroC, Inc. All rights reserved.
#
# **********************************************************************

import signal, sys, Ice

Ice.loadSlice('Filesystem.ice')
import Filesystem

# Recursively display the contents of directory "dir"
# in tree fashion. For files, show the contents of
# each file. The "depth" parameter is the current
# nesting level (for indentation).

def listRecursive(dir, depth):
    indent = ''
    depth = depth + 1
    for i in range(depth):
        indent = indent + '\t'

    contents = dir.list()

    for node in contents:
        subdir = Filesystem.DirectoryPrx.checkedCast(node)
        file = Filesystem.FilePrx.uncheckedCast(node)
        sys.stdout.write(indent + node.name() + " ")
        if subdir:
            print("(directory):")
            listRecursive(subdir, depth)
        else:
            print("(file):")
            text = file.read()
            for line in text:
                print(indent + "\t" + line)

with Ice.initialize(sys.argv) as communicator:

    #
    # This function must be called within the same scope as the communicator.
    #
    signal.signal(signal.SIGINT, lambda signum, frame: communicator.destroy())

    try:
        #
        # Create a proxy to the root directory
        #
        obj = communicator.stringToProxy("RootDir:default -h localhost -p 10000")

        #
        # Downcast the proxy to a Directory proxy
        #
        rootDir = Filesystem.DirectoryPrx.checkedCast(obj)

        #
        # Recursively list the contents of the root directory
        #
        print("Contents of root directory:")
        listRecursive(rootDir, 0)
    except Ice.CommunicatorDestroyedException:
        pass
