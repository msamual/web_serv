#!/usr/bin/env python3

import sys
import os
import cgi

# form = cgi.FieldStorage()
# print(type(form))
# print("ARGV:")
# # print(form["TEST"].value)
# # print(form["PECST"].value)
# # print(form["CHPK"].value)
# for i in form.keys():
#     print(i)
response =  "Content-type: text/html\r\n";
tmp = "<html><head>HELLO WORLD</head></html>"
response += "Content-length: " + str(len(tmp)) + "\r\n\r\n";
response += tmp + "\r\n\r\n";

print(response)
# print("Content-Length = " + os.environ.get("Content-Length"))

# body = sys.stdin.read( int(os.environ["Content-Length"]) )

# for i in os.environ.items():
#     print(i)

# print(body);
