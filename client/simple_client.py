# Import socket module
import socket
import time
from threading import Thread

# Create a socket object
s = socket.socket()

# Define the port on which you want to connect
port = 7777

# connect to the server on local computer
s.connect(('127.0.0.1', port))

# receive data from the server and decoding to get the string.
s.send(bytes("[new id]{new_id:1\nx:100\ny:100\n}",'utf8'))
time.sleep(2)
s.send(bytes("[new id]{to:1\nx:200\ny:200\n}",'utf8'))

# close the connection
s.close()
