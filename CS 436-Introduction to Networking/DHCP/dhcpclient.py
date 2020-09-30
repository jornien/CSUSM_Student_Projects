from socket import *
import uuid

mac = hex(uuid.getnode())
discover = "DISCOVER"
offer = "OFFER"
request = "REQUEST"
ack = "ACKNOWLEDGE"
decline = "DECLINE"
alreadyAssigned = "ASSIGNED"

serverName = '192.168.1.77'
serverPort = 12000

print ('client is ready')

clientSocket = socket(AF_INET, SOCK_DGRAM)
clientSocket.sendto(discover.encode(), (serverName, serverPort))
clientSocket.sendto(mac.encode(), (serverName, serverPort))
ip = ''
while 1:
    mymac, serverAddress = clientSocket.recvfrom(2048)
    message, serverAddress = clientSocket.recvfrom(2048)
    ip, serverAddress = clientSocket.recvfrom(2048)

    decMac = mymac.decode().lower()
    decMes = message.decode().upper()
    decIP = ip.decode().upper()
    if (decMac == mac):
        if (decMes == offer):
            print ("client offered " + decIP + " from server")
            clientSocket.sendto(request.encode(), serverAddress)
            clientSocket.sendto(mac.encode(), serverAddress)
            clientSocket.sendto(decIP.encode(), serverAddress)
        elif (decMes == alreadyAssigned):
            print("client has already been assigned " + decIP)
            ip = decIP
            break
        elif (decMes == ack):
            print("server has assigned " + decIP + " to client")
            ip = decIP
            break
        else:
            print ("ERROR: unrecognized message")
            exit()

while 1:
    print ("enter an option")
    print ("release")
    print ("renew")
    print ("quit")
    message = input('')
    message = message.upper()
    if(message == "RELEASE"):
        clientSocket.sendto(message.encode(), (serverName, serverPort))
        clientSocket.sendto(mac.encode(), (serverName, serverPort))
        while 1:
            mymac, serverAddress = clientSocket.recvfrom(2048)
            if(mymac.decode().lower() == mac):
                break
        message, serverAddress = clientSocket.recvfrom(2048)
        print(message.decode())
    elif(message == "RENEW"):
        clientSocket.sendto(message.encode(), (serverName, serverPort))
        clientSocket.sendto(mac.encode(), (serverName, serverPort))
        while 1:
            mymac, serverAddress = clientSocket.recvfrom(2048)
            message, serverAddress = clientSocket.recvfrom(2048)
            ip, serverAddress = clientSocket.recvfrom(2048)

            decMac = mymac.decode().lower()
            decMes = message.decode().upper()
            decIP = ip.decode().upper()
            if (decMac == mac):
                if (decMes == offer):
                    print ("client offered " + decIP + " from server")
                    clientSocket.sendto(request.encode(), serverAddress)
                    clientSocket.sendto(mac.encode(), serverAddress)
                    clientSocket.sendto(decIP.encode(), serverAddress)
                elif (decMes == alreadyAssigned):
                    print("client has already been assigned " + decIP)
                    ip = decIP
                    break
                elif (decMes == ack):
                    print("server has assigned " + decIP + " to client")
                    ip = decIP
                    break
                else:
                    print ("ERROR: unrecognized message")
                    exit()
    elif(message == "QUIT"):
        clientSocket.sendto(message.encode(), (serverName, serverPort))
        clientSocket.sendto(mac.encode(), (serverName, serverPort))
        break
            
clientSocket.close()
