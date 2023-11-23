import xmlrpc.client

proxy = xmlrpc.client.ServerProxy('http://localhost:8000/')

print(str(proxy.sq_rpc(5)))