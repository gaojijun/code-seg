import threading
import datetime
import time

def tell_time():
    print '%s%s' % (datetime.datetime.now(), '\n')
    
class t_Thread(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)

    def run(self):
        tell_time()

# create thread by inherit
t1 = t_Thread()
print t1.name
t1.start()

# create thread by target
t2 = threading.Thread(target=tell_time)
print t2.name
t2.start()

def sleeps():
    print 'sleep start!'
    time.sleep(2)
    print 'sleep end!'

# wait for thead to complete
t3 = threading.Thread(target=sleeps)
print '\nmain thread'
print t3.name
t3.start()
t3.join()
print 'main thread'
