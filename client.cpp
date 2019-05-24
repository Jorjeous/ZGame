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

void runClient(WindowSent windowSent, unsigned short serverPort, unsigned short clientPort, sf::IpAddress ServerIp){

    sf::UdpSocket socket;
    sf::UdpSocket socketBulletServer;
    sf::Packet packet;
    sf::Packet BulletPack;
    sf::IpAddress ipServer;

    unsigned short portServer;
    unsigned short portBulletDelta = 5;
    unsigned short portBulletServer = serverPort + portBulletDelta;

    bool Sended = false;
    bool Received = true;
    bool SendedBullet = false;
    bool ReceivedBullet = true;


    struct SendPlayer P; //Used to send and receive players info
    struct SendBullet B; //Used to send and receive Bullets info


    std::cout <<"HI I'm CLIENT_V5_"<<clientPort << std::endl;

    if (socket.bind(clientPort) != sf::Socket::Done)
        return;

    if (socket.send(packet, ServerIp, serverPort) != sf::Socket::Done)
        return;
    std::cout <<"CLIENT_" <<clientPort <<"_Message sent to the server: " << std::endl;

    if (socket.receive(packet, ipServer, portServer) != sf::Socket::Done)
        return;
    std::cout << "CLIENT_" << clientPort << "_Message received from " << portServer << std::endl;

    sleep(seconds(2)); //giving time for 2'd server to start

    if (socket.send(BulletPack, ServerIp, portBulletServer ) != sf::Socket::Done)
        return;

    std::cout << "Cleint_" << clientPort <<"Message sent to SecondServer..."<<portBulletServer << "  awaiting number:" << portServer+portBulletDelta<< endl;
    if (socket.receive(BulletPack, ipServer, portBulletServer) != sf::Socket::Done)
        return;


    std::cout << "CLIENT_" << clientPort << "_Message received from SecondServer" << ipServer << std::endl;

    srand(time(NULL));
    //musicAll.music[numberMusicGame].play();
    hard =windowSent.hard;

    float resolution = windowSent.mode.height / windowSent.mode.width;
    float thickness = 0.05;





    View gameView(sf::FloatRect(0, 0, windowSent.mode.width, windowSent.mode.height));
    //View minimapView;
    //FloatRect rect(1-minimapSize - thickness, 1-minimapSize - thickness, minimapSize, minimapSize);
    //minimapView.setViewport(rect);

    std::vector<Weapon> bullets;
    std::vector<Bomb> bombs;
    std::vector<Organism> zombies;
    std::vector<Organism> zombies1;
    std::vector<Organism> zombies2;
    std::vector<Organism> zombies3;
    std::vector<Organism> dogs;
    std::vector<Corpse> dead;
    std::vector<Feature> items;
    std::vector<Opaque> houses;
    std::vector<ConvexShape> trapezes;

    setTextures();
    setBackground(houses);

    std::cout << "Zomb " << sizeof(Organism)<< std::endl;

    //MinimapThread minimapThread;
    //Thread thread(&setMinimap, &minimapThread);
    //thread.launch();

    //Create PlayerSprite
    Sprite spritePlayer(texturePlayerPaths[0]);
    Sprite spritePlayer2(texturePlayerPaths[0]);
    spritePlayer2.setScale(2, 2);
    spritePlayer.setScale(2, 2);
    //Create ZombieSprite
    Sprite spriteZombie(textureZombiePathsWalkFullHealth[0]);
    //Create Zombie1Sprite
    Sprite spriteZombie1(textureZombie1PathsWalkFullHealth[0]);
    spriteZombie1.setScale(3, 3);
    //Create Zombie2Sprite
    Sprite spriteZombie2(textureZombie2PathsWalkFullHealth[0]);
    spriteZombie2.setScale(1.5, 1.5);
    //Create Zombie3Sprite
    Sprite spriteZombie3(textureZombie3PathsWalkFullHealth[0]);
    spriteZombie3.setScale(1.5, 1.5);
    //Create DogSprite
    Sprite spriteDog(textureDogPathsWalkFullHealth[0]);
    //Create BulletSprite
    textureBullet1.loadFromFile(pathToDirectory + "pngForGame/bullet1.png");
    Sprite spriteBullet1(textureBullet1);
    textureBullet2.loadFromFile(pathToDirectory + "pngForGame/bullet2.png");
    Sprite spriteBullet2(textureBullet2);
    //Create BombSprite
    textureBomb1.loadFromFile(pathToDirectory + "pngForGame/bomb1.png");
    Sprite spriteBomb1(textureBomb1);
    textureBomb2.loadFromFile(pathToDirectory + "pngForGame/bomb2.png");
    Sprite spriteBomb2(textureBomb2);
    //Create items Textures
    textureHeart.loadFromFile(pathToDirectory + "pngForGame/heart.png");
    textureShield.loadFromFile(pathToDirectory + "pngForGame/shield.png");
    textureBullet.loadFromFile(pathToDirectory + "pngForGame/bullets.png");
    textureBomb.loadFromFile(pathToDirectory + "pngForGame/bombs.png");
    //Create MouseSprite
    Sprite spriteCursor(textureCursor0);
    setCursor(windowSent.window, spriteCursor);
    //Create Location Texture
    textureLocation.loadFromFile(pathToDirectory + "pngForGame/location.png");
    Sprite location(textureLocation);
    location.setOrigin(location.getTexture()->getSize().x / 2.0, location.getTexture()->getSize().y);
    location.setScale(2, 2);


    //Init Player
    texturePlayerInWater.loadFromFile(pathToDirectory + "pngForGame/playerInWater.png");

    Organism player(playerFullHealth, playerFullProtection, playerSpeed, speedDrawPlayer, 0, false,
                    texturePlayerPaths, texturePlayerPaths, texturePlayerPaths, numberPlayerPathsWalk, 0.01,
                    texturePlayerPaths, texturePlayerPaths, texturePlayerPaths, numberPlayerPathsWalk, 0.01, spritePlayer);


    Organism player2(playerFullHealth, playerFullProtection, playerSpeed, speedDrawPlayer, 0, false,
                    texturePlayerPaths, texturePlayerPaths, texturePlayerPaths, numberPlayerPathsWalk, 0.01,
                    texturePlayerPaths, texturePlayerPaths, texturePlayerPaths, numberPlayerPathsWalk, 0.01, spritePlayer2);


    while(true){
        int j = 0;
        player.organism.setPosition(700+j, 700+j);
        player2.organism.setPosition((800 + 100 + j), 900+j);
        if(player.getPosition().crossEnemy && player2.getPosition().crossEnemy  )
            break;
        j++;
    }
    Vector2u playerSize = player.organism.getTexture()->getSize();

    player.organism.setOrigin((float)playerSize.x/2, (float)playerSize.y/2);
    player.organism.setScale(1, 1);

    player2.organism.setOrigin((float)playerSize.x/2, (float)playerSize.y/2);
    player2.organism.setScale(1, 1);


    ////Create shadow
    Texture textureShadow;
    textureShadow.loadFromFile(pathToDirectory + "pngForGame/shadow.png");
    Sprite spriteShadow(textureShadow);
    spriteShadow.setOrigin(spriteShadow.getTexture()->getSize().x / 2, spriteShadow.getTexture()->getSize().y / 2);
    spriteShadow.setColor(Color(255, 255, 255, 180));
    spriteShadow.setPosition(player.organism.getPosition());
    spriteShadow.setScale(0.5, 0.5);

    gameView.setCenter(player.organism.getPosition());


    //create bars
    Bar lifeBar(pathToDirectory + "pngForGame/heart.png", pathToDirectory + "fonts/font.ttf", Color(255, 0, 0, 255), 0.3);
    TimeBar timeBar(pathToDirectory + "fonts/font.ttf");
    Bar shieldBar(pathToDirectory + "pngForGame/shield.png", pathToDirectory + "fonts/font.ttf", Color(131, 131, 157, 255), 0.09);
    Bar bulletBar(pathToDirectory + "pngForGame/bullets.png", pathToDirectory + "fonts/font.ttf", Color(255, 204, 0, 255), 0.17);
    Bar bombBar(pathToDirectory + "pngForGame/bombs.png", pathToDirectory + "fonts/font.ttf", Color(25, 51, 77, 255), 0.07);
    Bar bubbleBar(pathToDirectory + "pngForGame/bubble.png", pathToDirectory + "fonts/font.ttf", Color(51, 255, 255, 255), 0.08);
    bubbleBar.value = fullBubbles;


    textureCorpse.loadFromFile(corpsePath);

    Clock clock;
    Clock clockPause;
    Clock clock6;

    float timeBuffer6 = 0;
    float timeBuffer7 = 0;
    float timeBuffer8 = 0;
    float timeBuffer9 = 0;
    float timeBufferBombInit = 0;
    float timebufferMinimapInit = 0;
    float timeBufferMinimap = 0;

    bool minimap = false;
    Time time,time6, timePause;
    timePause = clock6.restart();

    Draw A(windowSent.window, gameView, zombies, zombies1, zombies2, zombies3, dogs, dead, bullets, bombs, items, trapezes,
           player, player2,
           lifeBar, bubbleBar, shieldBar, bulletBar, bombBar, timeBar, spriteCursor, spriteShadow);


    //update Window

    while (windowSent.window.isOpen())
    {
        windowSent.window.setView(gameView);

        Event event;

        time = clock.restart();
        time6 = clock6.getElapsedTime();

        timeBuffer6 += time.asSeconds();
        timeBuffer7 += time.asSeconds();
        timeBuffer8 += time.asSeconds();
        timeBuffer9 += time.asSeconds();
        timeBufferBombInit += time.asSeconds();
        timeBufferMinimap += time.asSeconds();
        timebufferMinimapInit += time.asSeconds();

        //std::cout << time.asSeconds()<< std::endl;

//1
        time6 = clock6.getElapsedTime();
        //std::cout << " 1: "<< time6.asSeconds();


        //updateMusic(timeBuffer6, timeBuffer7, player, gameView, zombies, zombies1, zombies2, zombies3, dogs);

//2
        time6 = clock6.getElapsedTime();
        //std::cout << " 2: "<<time6.asSeconds();

        //moveAllEnemies(zombies, zombies1, zombies2, zombies3, dogs, player, time);

//3
        time6 = clock6.getElapsedTime();
        //std::cout <<" 3: "<< time6.asSeconds();

        updateBomb(bombs, time);

        strikeAllWeapon(gameView, bullets, zombies, zombies1, zombies2,
                        zombies3, dogs, dead, items);

        strikeAllBomb(bombs, zombies, zombies1, zombies2, zombies3,
                      dogs, dead, items);

        deleteWeapon(gameView, bullets, time);

        deleteBomb(bombs);

//4
        time6 = clock6.getElapsedTime();
        //std::cout << " 4: "<< time6.asSeconds();

        player.rotate(Vector2f(windowSent.window.mapPixelToCoords(sf::Mouse::getPosition(windowSent.window)).x,
                               windowSent.window.mapPixelToCoords(sf::Mouse::getPosition(windowSent.window)).y));
        //
        //
        // here we about to send
        //
        //
        movePlayer(gameView, player, zombies, zombies1, zombies2, zombies3, dogs, time, bubbleBar, clientPort);



        ///Data Exchange;

        P.position.x = player.organism.getPosition().x;
        P.position.y = player.organism.getPosition().y;
        P.direction.x = windowSent.window.mapPixelToCoords(sf::Mouse::getPosition(windowSent.window)).x;
        P.direction.y = windowSent.window.mapPixelToCoords(sf::Mouse::getPosition(windowSent.window)).y;
        P.type =  1;
        P.health = player.health;

            packet.clear();
            BulletPack.clear();
            packet << P;//sended our player;

            BulletPack << B;//sended Bullet



            ////Bullet data
            if (((SendedBullet == false) && (ReceivedBullet == true))||B.ShootFired) {
                if (socket.send(BulletPack, ServerIp, portBulletServer) != sf::Socket::Done)
                    return;
                SendedBullet  = true;
                ReceivedBullet = false;
                //std::cout << std::endl << "Fired...." << B.ShootFired << std::endl;
                BulletPack.clear();
            }

            if ((SendedBullet == true) && (ReceivedBullet == false)) {
                BulletPack.clear();
                if (socket.receive(BulletPack, ipServer, portBulletServer) != sf::Socket::Done)
                    return;

                BulletPack >> B; //rec Bullet
                ReceivedBullet = true;
                SendedBullet = false;





//                Weapon bullet;              //= initBullet(windowSent.window, spriteBullet2, player2, pistolDamage, 0);
//
//                bullet.weapon.setPosition(B.position.x, B.position.y);
//                bullet.damage = B.damage;
//                bullet.direction.y = B.direction.y;
//                bullet.direction.x = B.direction.x;
                //bullet.weapon.setPosition(player2.organism.getPosition());
                if(B.ShootFired == true) {
                    Weapon bullet = initBullet(windowSent.window, spriteBullet2, player2, pistolDamage, 0);
                    bullet.direction.y = B.direction.y;
                    bullet.direction.x = B.direction.x;

                    bullets.push_back(bullet);

                    //bullets.push_back(bullet);
                    std::cout << "B_oX" << B.direction.x <<"|||B_oY" << B.direction.y <<std::endl << std::endl;
                }
                B.ShootFired = false;

            }












        /////Player position data rec & snd
            if (((Sended == false) && (Received == true))) {
                if (socket.send(packet, ServerIp, serverPort) != sf::Socket::Done)
                    return;
                Sended = true;
                Received = false;

                packet.clear();
            }
            if ((Sended == true) && (Received == false)) {
                packet.clear();
                if (socket.receive(packet, ipServer, portServer) != sf::Socket::Done)
                    return;

                packet     >> P; //receiv
                //BulletPack >> B; //reveiv Bullet
                Received = true;
                Sended = false;


                player2.organism.setPosition(P.position.x, P.position.y);
                player2.direction.x = P.direction.x;
                player2.direction.y = P.direction.y;
                player2.health = P.health;
                player2.rotate(Vector2f(player2.direction.x, player2.direction.y));



            }




            packet.clear();
            BulletPack.clear();







        setShadow(houses, trapezes, player.organism.getPosition());
        //spriteShadow.setPosition(player.organism.getPosition());

        //std::cout << "Shad " << sizeof(trapezes[0].getTexture())<< std::endl;

        updateFeatures(items, player, time, bulletBar, bombBar);

//5
        time6 = clock6.getElapsedTime();
        //std::cout << " 5: " << time6.asSeconds();


        for(auto &i : zombies)
            i.rotate(player.organism.getPosition());
        for(auto &i : zombies1)
            i.rotate(player.organism.getPosition());
        for(auto &i : zombies2)
            i.rotate(player.organism.getPosition());
        for(auto &i : zombies3)
            i.rotate(player.organism.getPosition());
        for(auto &i : dogs)
            i.rotate(player.organism.getPosition());

        int j = 0;
        for(auto &i : bullets){
            if(!i.move(time))
                bullets.erase(bullets.begin() + j);
            else
                j+=2;
        }

        j = 0;
        for(auto &i : dead){
            i.update(time);
            if(i.isDisappeared())
                dead.erase(dead.begin() + j);
            else
                j++;
        }

        j = 0;
        for(auto &i : items){
            i.update(time);
            if(i.isDisappeared())
                items.erase(items.begin() + j);
            else
                j++;
        }

        updateCursor(windowSent.window, spriteCursor);
        gameViewUpdate(gameView, windowSent.window, player, time);

        timeBar.update(gameView, time6 - timePause);

        //pause the game
        if(Keyboard::isKeyPressed(Keyboard::Space) && timeBuffer9 > 0.3){
            timeBuffer9 = 0;
            clockPause.restart();
            soundsAll.stop();

            sleep(seconds(0.3));
            while(!Keyboard::isKeyPressed(Keyboard::Space)){
                sleep(seconds(0.01));
            }
            clock.restart();
            timePause += clockPause.getElapsedTime();
        }

        if(Keyboard::isKeyPressed(Keyboard::Tab) && timebufferMinimapInit > 0.2){
            timebufferMinimapInit = 0;
            if(minimap)
                minimap = false;
            else
                minimap = true;
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            //thread.terminate();

            clearAll(zombies, zombies1, zombies2, zombies3, dogs, bullets, bombs, dead, items, houses, trapezes);
            musicAll.music[numberMusicGame].pause();

            return;
        }

        while (windowSent.window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                //thread.terminate();
                windowSent.window.close();
            }

            if (event.type == event.MouseButtonReleased)
                spriteCursor.setTexture(textureCursor0);
            if (event.type == event.MouseButtonPressed)
                spriteCursor.setTexture(textureCursor1);

            if (event.type == Event::MouseWheelScrolled){
                if(timeBufferBombInit > 0.2 && bombBar.value > 0){
                    timeBufferBombInit = 0;
                    Bomb bomb = initBomb(windowSent.window, spriteBomb1, bombDamage);
                    if(background[(int)(bomb.weapon.getPosition().x / sizeTile)][(int)(bomb.weapon.getPosition().y / sizeTile)].crossEnemy &&
                       background[(int)(bomb.weapon.getPosition().x / sizeTile)][(int)(bomb.weapon.getPosition().y / sizeTile)].type != 18){
                        bombBar.value--;
                        bombs.push_back(bomb);
                    }

                }
            }

            if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left){
                //soundsAll.sound[0].play();
                Weapon bullet = initBullet(windowSent.window, spriteBullet2, player, pistolDamage, 0);
                //B.position = bullet.weapon.getPosition();
                B.position.x = player.organism.getPosition().x;
                B.position.y = player.organism.getPosition().x;
                B.direction.x = bullet.direction.x;
                B.direction.y = bullet.direction.y;
                B.damage = pistolDamage;
                B.ShootFired = true;

                std::cout << "sending B|X : " << B.direction.x << " B|Y : "<<B.direction.y << std::endl;

                //
                //
                //
                //need to push 2 player's bullets
                bullets.push_back(bullet);
            }

            if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right && bulletBar.value > 0){
                //soundsAll.sound[1].play();
                bulletBar.value--;
                Weapon bullet = initBullet(windowSent.window, spriteBullet1, player, shotgunDamage, shotgunAngle);
                bullets.push_back(bullet);
                bullet = initBullet(windowSent.window, spriteBullet1, player, shotgunDamage, -shotgunAngle);
                bullets.push_back(bullet);
                bullet = initBullet(windowSent.window, spriteBullet1, player, shotgunDamage, 2*shotgunAngle);
                bullets.push_back(bullet);
                bullet = initBullet(windowSent.window, spriteBullet1, player, shotgunDamage, -2*shotgunAngle);
                bullets.push_back(bullet);
                bullet = initBullet(windowSent.window, spriteBullet1, player, shotgunDamage, 3*shotgunAngle);
                bullets.push_back(bullet);
                bullet = initBullet(windowSent.window, spriteBullet1, player, shotgunDamage, -3*shotgunAngle);
                bullets.push_back(bullet);
                bullet = initBullet(windowSent.window, spriteBullet1, player, shotgunDamage, 0);
                bullets.push_back(bullet);
            }
        }


        //6
        time6 = clock6.getElapsedTime();
        //std::cout << " 6: " << time6.asSeconds() << "Shoot..." << B.ShootFired;



        ////
        ////
        ////
        //A.player2.health = P.health;
        //A.player2.organism.setPosition(500, 500);
        //windowSent.window.draw(player2.organism);
        //windowSent.window.draw(player.organism);
        drawGameview(A);
        packet.clear();
        ////
        //7
        time6 = clock6.getElapsedTime();
        //std::cout << " 7: " << time6.asSeconds();

        //createWave(windowSent.window, windowSent.mode, gameView, time6, time, spriteZombie, spriteZombie1, spriteZombie2, spriteZombie3, spriteDog,
        //          zombies, zombies1, zombies2, zombies3, dogs);



        //minimap Update & Draw
        //drawMinimap(windowSent.window, gameView, minimapView, minimap, player, location, minimapThread.sprite, thickness);

        windowSent.window.display();

//8
        time6 = clock6.getElapsedTime();
        //std::cout << " 8: " << time6.asSeconds();

        //std::cout << "End"<< std::endl;


        if(player.health <= 0){
            //thread.terminate();
            clearAll(zombies, zombies1, zombies2, zombies3, dogs, bullets, bombs, dead, items, houses, trapezes);
            soundsAll.stop();
            endGame(windowSent.window, gameView, time6 - timePause, spriteCursor);

            return;
        }
       // std::cout << "8" << std::endl;
    }



}
