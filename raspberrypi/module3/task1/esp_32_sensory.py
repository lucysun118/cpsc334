#!/usr/bin/env python
# -*- coding: utf-8 -*-

#Libraries
import socket    #https://wiki.python.org/moin/UdpCommunication
import pygame
pygame.init()

# set up the drawing window
screen = pygame.display.set_mode([500, 500])

#Parameters
localPort=8888
bufferSize=1024

#Objects
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)  ## Internet,UDP

# function init 
def init():
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1) #enable broadcasting mode
    sock.bind(('', localPort))
    print("UDP server : {}:{}".format(get_ip_address(),localPort))

# function main 
def main():
    while True:
        data, addr = sock.recvfrom(1024) # get data
        data_int = int(data[23:])

        screen.fill((255,255,255))
        
        # draw a solid blue circle
        pygame.draw.circle(screen, (0,0,255), (250,250), data_int//10)

        # flip the display
        pygame.display.flip()

        print(addr)
        print(data)
        print("received message: {} from {}\n".format(data,addr))
        sock.sendto("received ok".encode('utf-8'), addr)  # write data


# function get_ip_address 
def get_ip_address():
    """get host ip address"""
    ip_address = '';
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(("8.8.8.8",80))
    ip_address = s.getsockname()[0]
    s.close()
    return ip_address




if __name__ == '__main__':
    init()
    main()