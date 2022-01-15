#!/usr/bin/env python3
import cgi
import html

form = cgi.FieldStorage()
text1 = form.getfirst("TEXT_1", "не задано")
text2 = form.getfirst("TEXT_2", "не задано")
text1 = html.escape(text1)
text2 = html.escape(text2)

response = "Content-type: text/html\n"
response += """<!DOCTYPE HTML>
        <html>
        <head>
            <meta charset="utf-8">
            <title>Обработка данных форм</title>
        </head>
        <body>"""

response += "<h1>Обработка данных форм!</h1>"
response += "<p>TEXT_1: {}</p>".format(text1)
response += "<p>TEXT_2: {}</p>".format(text2)

response += """</body>
        </html>"""
print(response)
