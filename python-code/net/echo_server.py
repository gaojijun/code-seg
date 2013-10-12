# Echo server program
import socket
import select

HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 50007              # Arbitrary non-privileged port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(5)
listenSock = s.fileno()
while True:
    r, w, e = select.select([listenSock], [], [], 0.5)
    if listenSock not in r:
        continue
    conn, addr = s.accept()
    print 'Connected by', addr
    conn.shutdown(socket.SHUT_WR)
    while 1:
        data = conn.recv(1024)
        if not data: break
        # conn.sendall(data)
    print conn.getsockname()
    conn.close()
s.close()
