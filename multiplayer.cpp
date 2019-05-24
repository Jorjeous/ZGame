#include "server.cpp"
#include "client.cpp"

#pragma once


void openMultiplayer(WindowSent windowSent){
    const unsigned short serverPort = 7000;
    unsigned short clientPort = 0;


    //works if the game is run on one computer
    //solution:
    //sf::IpAddress ip("192.168.10.62");
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    int number = 0;
    std::cout << "Enter number of player you want to be(1 or 2)" << std::endl;
    std::cin >> number;
//void runClient(WindowSent windowSent, unsigned short serverPort, unsigned short clientPort, sf::IpAddress ServerIp){
    if(number == 1){
        sf::Thread serverThread(&runServer, serverPort);
        std::cout <<"ServerStarted V1" << std::endl;
        //sf::Thread clientThread1(&runClient(windowSent, serverPort, clientPort, ip));
        serverThread.launch();
        sleep(seconds(3.1));
        //clientThread1.launch();
        clientPort = serverPort + number;
        runClient(windowSent, serverPort, clientPort,  ip);
    } else {
        std::cout << "About to run client 2" << std::endl;
        clientPort = serverPort + number;
        runClient(windowSent, serverPort, clientPort,  ip);
    }
}
