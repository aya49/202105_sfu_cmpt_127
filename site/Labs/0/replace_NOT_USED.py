#!/usr/local/bin/python

srcfile = "Lab0.html"
semester = "1197"
instructor = "alavergn"

def replace(srcfile):
    import os

    try:
        fl = open(srcfile)
        dat = fl.read()
        fl.close()
    except:
        dat = ""

    username = "<your-username>"
    if os.environ.has_key("REMOTE_USER"): 
        username = os.environ["REMOTE_USER"]

    dat = dat.replace('$USER', username)
    dat = dat.replace('$SEMESTER', semester)
    dat = dat.replace('$INSTRUCTOR', instructor)
    return "Content-type: text/html\n\n"+dat

