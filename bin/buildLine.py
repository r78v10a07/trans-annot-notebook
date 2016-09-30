#!/usr/bin/env python

import sys
import os
import re

from subprocess import call

STR_LIMIT = sys.argv[1]
ids_file = sys.argv[2]
rtabs = re.compile('[ \t\n\r:]+')

query = ""
with open(ids_file, "r") as ids:
    for line in ids:
        fields = rtabs.split(line)
        id = fields[0]
        if len(query) + len(id) + 2 > int(STR_LIMIT):
            print(query)
            query = id
        else:
            if query == "":
                query = id
            else:
                query = query + " " + id
    print(query)
