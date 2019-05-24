#include "background.h"
#include "init.h"
#include "draw.h"
#include "thread"
#include "pages.h"
#include "wave.h"
#include "shadows.h"
#include "endGame.h"
#include <SFML/Network.hpp>
#include "network.h"

#pragma once
using namespace std;

void CatchBullet(unsigned short portBulletServer)
{int i = 0;
    sf::UdpSocket socket;
    sf::Packet packet;
    sf::Packet packet1;
    sf::Packet packet2;
    sf::IpAddress ipClient1;
    sf::IpAddress ipClient2;
    unsigned short portClient1;
    unsigned short portClient2;


    SendBullet B1; //Used to send and receive Bullets info
    SendBullet B2; //Used to send and receive Bullets info

    if (socket.bind(portBulletServer) != sf::Socket::Done)
        return;
    std::cout <<"2'd SERVER_V1:"<< "Server is listening to port " << portBulletServer << ", waiting for a message... " << std::endl;
    //get Ip and port 1 player
    if (socket.receive(packet1, ipClient1, portClient1) != sf::Socket::Done)
        return;
    packet1.clear();

    std::cout <<"2'd SERVER:"<< "Message received from client1 " << ipClient1 << std::endl;

    // Send an answer to the 1 player
    if (socket.send(packet1, ipClient1, portClient1) != sf::Socket::Done)
        return;
    std::cout <<"2'd SERVER:" << "Message sent to the client1:" << std::endl;


    //get Ip and port 2 player
    if (socket.receive(packet2, ipClient2, portClient2) != sf::Socket::Done)
        return;
    packet2.clear();
    std::cout << "2'd SERVER:"<<"Message received from client2 " << ipClient2 << std::endl;


    // Send an answer to the 2 player
    if (socket.send(packet2, ipClient2, portClient2) != sf::Socket::Done)
        return;
    std::cout<<"2'd SERVER:" << "Message sent to the client2:" << std::endl;


    while(true)
    {
        int i=0;
        socket.receive(packet1, ipClient1, portClient1);
        packet1 >> B1;
        socket.receive(packet2, ipClient2, portClient2);
        packet2 >> B2;
        if(B2.ShootFired)
        {
            cout << endl << "2'd Ser---------" <<endl << B2.ShootFired << endl;
            //break;
        }

        //std::cout << std::endl <<"InfoRec B1__" << B1.ShootFired << std::endl;
        //std::cout <<"InfoRec B2__" << B2.ShootFired << std::endl << std::endl;

        //packet1 << P1;
        //packet2 << P2;

        socket.send(packet2, ipClient1, portClient1);
        socket.send(packet1, ipClient2, portClient2);
        packet1.clear();
        packet2.clear();


        if (B1.ShootFired == 5345)
            break;
    }


}


void runServer(unsigned short serverPort){
// Create a socket to receive a message from anyone
    sf::UdpSocket socket;
    sf::IpAddress ipClient1;
    sf::IpAddress ipClient2;
    unsigned short portClient1;
    unsigned short portClient2;
    unsigned short portBulletDelta = 5;
    sf::Packet packet1;
    sf::Packet packet2;

    SendPlayer P1; //Used to send and receive players info
    SendPlayer P2; //Used to send and receive players info

    sf::Thread catchBulletThread(&CatchBullet, (serverPort + portBulletDelta));

    if (socket.bind(serverPort) != sf::Socket::Done)
        return;
    catchBulletThread.launch();
    std::cout <<"SERVER_V4:"<< "Server is listening to port " << serverPort << ", waiting for a message... " << std::endl;

    //get Ip and port 1 player

    if (socket.receive(packet1, ipClient1, portClient1) != sf::Socket::Done)
        return;
    packet1.clear();
    std::cout <<"SERVER:"<< "Message received from client1 " << ipClient1 << std::endl;

    // Send an answer to the 1 player
    if (socket.send(packet1, ipClient1, portClient1) != sf::Socket::Done)
        return;
    std::cout <<"SERVER:" << "Message sent to the client1:" << std::endl;


    //get Ip and port 2 player
    if (socket.receive(packet2, ipClient2, portClient2) != sf::Socket::Done)
        return;
    packet2.clear();
    std::cout << "SERVER:"<<"Message received from client2 " << ipClient2 << std::endl;


    // Send an answer to the 2 player
    if (socket.send(packet2, ipClient2, portClient2) != sf::Socket::Done)
        return;
    std::cout<<"SERVER:" << "Message sent to the client2:" << std::endl;


while(1)
{
    int i=0;
    socket.receive(packet1, ipClient1, portClient1);
    packet1 >> P1;
    //packet1 >> B1;
    socket.receive(packet2, ipClient2, portClient2);
    packet2 >> P2;

    socket.send(packet2, ipClient1, portClient1);
    socket.send(packet1, ipClient2, portClient2);
    packet1.clear();
    packet2.clear();



}
