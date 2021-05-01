#!/usr/local/bin/python

srcfile = "Lab1.html"
semester = "1211"
instructor = "alavergn"

import os

print "Content-type: text/html" 
print

try:
    fl = open(srcfile)
    dat = fl.read()
    fl.close()
except:
    dat = ""

username = "<your-username>"
if os.environ.has_key("REMOTE_USER"): username = os.environ["REMOTE_USER"]


dat = username.join(dat.split("$USER"))
dat = semester.join(dat.split("$SEMESTER"))
dat = instructor.join(dat.split("$INSTRUCTOR"))

print dat


#print "<html><body><p>", form
#print "username == [%s]" % username
#print "</p></body></html>"

