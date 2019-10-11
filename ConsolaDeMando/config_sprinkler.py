#Tested with Python 3.6.6 and CoAPThon3
from coapthon.client.helperclient import HelperClient

#Change this IP address with the one listed as Interface 0: eth, Link local address LL64
# or the one listed as Interface 1: 6LoWPAN,  Unique local address
#host = "fe80::260:37ff:fe00:fa5d"
host = "fd01::3ead:8026:6468:33f6:97bb"
port = 5683
path ="configctr"

client = HelperClient(server=(host, port))
response = client.post(path, "30000")
print(response.pretty_print())
client.stop()