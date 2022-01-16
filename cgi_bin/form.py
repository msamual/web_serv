#!/usr/bin/env python3

import cgi
import html
import sys

sys.stderr.write("____SCRIPT IS WORKING___\n")

form = cgi.FieldStorage()
text1 = form.getfirst("TEXT_1", "no text")
text2 = form.getfirst("TEXT_2", "no text")
text1 = html.escape(text1)
text2 = html.escape(text2)

response = "Content-type: text/html\n"
response += """<!DOCTYPE HTML>
        <html>
        <head>
            <meta charset="utf-8">
            <title>Working with forms</title>
        </head>
        <body>"""

response += "<h1>Working with forms!</h1>"
response += "<p>TEXT_1: {}</p>".format(text1)
response += "<p>TEXT_2: {}</p>".format(text2)

response += """</body>
        </html>"""
print(response)
