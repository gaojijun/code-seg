import sys

def tell_time():
    sys.exit('hello')

# 1. how to use raise
# 2. sys.exit will throw an exception, it's type is SystemExit.
# 3. SystemExit/KeyboardInterrupt cannot be caught by 'except Exception'

def first_catch():
    try:
        tell_time()
    except:
        print 123
        raise

try:
    first_catch()
except Exception, e:
    print e
except SystemExit, e:
    print 123
    print e


# how to use try ... finally

def f():
    try:
        raise Exception('hello')
    finally:
        print 123


def f2():
    try:
        raise Exception('hello')
    except:
        raise

try:
    f()
except:
    print 234
