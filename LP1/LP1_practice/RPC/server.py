from xmlrpc.server import SimpleXMLRPCServer

def sq(n):
    return n*n

port = 8000
server = SimpleXMLRPCServer(('localhost',port),logRequests=False)

server.register_function(sq,'sq_rpc')

try:
    print("connected")
    server.serve_forever()
except:
    print("Exit")