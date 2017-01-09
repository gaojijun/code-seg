# http://hihocoder.com/problemset/problem/1050

class Tree(object):
    def __init__(self, city):
        self.city = city
        self.h = 0
        self.parent = None
        self.kids = []

def setHeight(cities):
    for _, c in cities.iteritems():
        if c.kids == []:
            while c.parent:
                if c.parent.h < c.h + 1:
                    c.parent.h = c.h +1 
                    c = c.parent
                else:
                    break

def buildTree(n):
    while n:
        line = raw_input()
        a, b = line.split()
        if a not in cities:
            cities[a] = Tree(a)
        if b not in cities:
            cities[b] = Tree(b)
        a = cities[a]
        b = cities[b]
        b.parent = a
        a.kids.append(b)
        n -= 1

def getAns(cities):
    max = 0
    for k, v in cities.iteritems():
        if len(v.kids) == 0:
            continue
        if len(v.kids) == 1:
            if v.h > max:
                max = v.h
            continue
        a = b = 0
        for i in v.kids:
            if i.h > b:
                if i.h > a:
                    b = a
                    a = i.h
                else:
                    b = i.h
            t = a+b+2
            if t > max:
                max = t
    print max

cities = {}
n = int(raw_input())
n -= 1
buildTree(n)
setHeight(cities)
getAns(cities)
