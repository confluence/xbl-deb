#!/usr/bin/python

old = "1.1.5"
new = "1.1.6"

for i in [ ["Makefile.in" , old         , new         ], \
           ["Makefile"    , old         , new         ], \
           ["Xbl.iafa"    , old         , new         ], \
           ["Xbl.lsm"     , old         , new         ], \
           ["bl.c"        , old         , new         ], \
           ["xbl-README"  , old         , new         ], \
           ["xbl-man.html", "xbl " + old, "xbl " + new], \
           ["xbl.html"    , old         , new         ], \
           ]:

    print "Read", i[0]
    f = open(i[0], "r")
    content = f.read()
    f.close()

    print "Replace", i[1], "by", i[2]
    content = content.replace(i[1], i[2])

    print "Write", i[0]
    f = open(i[0], "w")
    f.write(content)
    f.close()
