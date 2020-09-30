from socket import *
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('',serverPort))
ipOffers = ['192.168.1.1','192.168.1.2','192.168.1.3','192.168.1.4','192.168.1.5']
macsAssigned = ['','','','','']
nextFreeIP = 0;

discover = "DISCOVER"
offer = "OFFER"
request = "REQUEST"
ack = "ACKNOWLEDGE"
decline = "DECLINE"
alreadyAssigned = "ASSIGNED"
release = "RELEASE"
renew = "RENEW"

print ('The server is ready')


while 1:
    message, clientAddress = serverSocket.recvfrom(2048)
    mac, clientAddress = serverSocket.recvfrom(2048)
    decMes = message.decode().upper()
    decMac = mac.decode().lower()

    print ("server recieves " + decMes + " message from " + decMac)

    if (discover == decMes or renew == decMes):
        serverSocket.sendto(decMac.encode(), clientAddress)
        for m in macsAssigned:
            if (m == decMac):
                serverSocket.sendto(alreadyAssigned.encode(), clientAddress)
                serverSocket.sendto(ipOffers[nextFreeIP].encode(), clientAddress)
                print ("server sends already assigned message to " + decMac)
            nextFreeIP = (nextFreeIP + 1) % 5

        if (macsAssigned[nextFreeIP] == decMac):
            continue
        
        nextFreeIP = 0
        for m in macsAssigned:
            if (m == ''):
                break
            nextFreeIP = (nextFreeIP + 1) % 5

        serverSocket.sendto(offer.encode(), clientAddress)
        serverSocket.sendto(ipOffers[nextFreeIP].encode(), clientAddress)
        print ("server sends offer message to " + decMac)
        
    elif (request == decMes):
        ipRequest, clientAddress = serverSocket.recvfrom(2048)
        decIP = ipRequest.decode()
        decMac = mac.decode().lower()
        serverSocket.sendto(decMac.encode(), clientAddress)
        nextFreeIP = 0
        for i in ipOffers:
            if (i == decIP):
                break
            nextFreeIP = (nextFreeIP + 1) % 5;
        
        if (macsAssigned[nextFreeIP] == ''):
            macsAssigned[nextFreeIP] = decMac
            serverSocket.sendto(ack.encode(), clientAddress)
            print ("server sends acknowledge message to " + decMac)
        else:
            nextFreeIP = 0
            for m in macsAssigned:
                if (m == ''):
                    break
                nextFreeIp = (nextFreeIP + 1) % 5
            serverSocket.sendto(offer.encode(), clientAddress)
            print ("server sends offer message to " + decMac)
        serverSocket.sendto(ipOffers[nextFreeIP].encode(), clientAddress)
    elif (release == decMes):
        nextFreeIP = 0
        for m in macsAssigned:
            if (m == decMac):
                macsAssigned[nextFreeIP] = ''
                message = "ip released"
                break
            nextFreeIP += 1
            if (nextFreeIP == 5):
                message = "ip already released"
        serverSocket.sendto(decMac.encode(), clientAddress)
        serverSocket.sendto(message.encode(), clientAddress)
        print ("server sends " + message + " to " + decMac)
    
serverSocket.close()
