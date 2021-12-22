#!/usr/bin/env python3

import sys
import os
import cgi

form = cgi.FieldStorage()
print(type(form))
print("ARGV:")
# print(form["TEST"].value)
# print(form["PECST"].value)
# print(form["CHPK"].value)
for i in form.keys():
    print(i)


print("ENV:")
# print("Content-Length = " + os.environ.get("Content-Length"))

# body = sys.stdin.read( int(os.environ["Content-Length"]) )

for i in os.environ.items():
    print(i)

# print(body);
