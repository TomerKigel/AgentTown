# Import socket module
import socket
import time
from random import random
from threading import Thread
def client_run(id):
    # Create a socket object
    s = socket.socket()

    # Define the port on which you want to connect
    port = 7777

    # connect to the server on local computer
    s.connect(('127.0.0.1', port))

    x = int(random() * 1000)
    y = int(random() * 1000)

    create = "[new id]{new_id:" + str(id) + "\nx:" + str(x)+ "\ny:" + str(y) + "\n}"


    # receive data from the server and decoding to get the string.
    s.send(bytes(create,'utf8'))
    for i in range(0,4):
        time.sleep(int(random() * 5))
        x = int(random() * 1000)
        y = int(random() * 1000)
        move = "[new id]{to:" + str(id) + "\nx:" + str(x) + "\ny:" + str(y) + "\n}"
        s.send(bytes(move,'utf8'))

    # close the connection
    s.close()

threads = []
for i in range(10):
    thread = Thread(target = client_run,args = [i])
    thread.start()
    threads.append(thread)
for i in range(10):
    threads[i].join()
