#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "iostream"
#include "background.cpp"
#include "objects.h"
#include "shadow.h"

#pragma once

using namespace sf;

enum packetType{
    end = 0,
    bullet,
    bomb,
    feature,
    enemy,
    player,
    map,
    opaque,
    tree
};






struct SendType{
    SendType(){
        type = 0;
    }
    unsigned int type;
};

struct SendBullet{
    SendBullet(){
        position = Vector2f(0, 0);
        direction = Vector2f(0, 0);
        damage = 0;
    }
    SendBullet(Vector2f position1, Vector2f direction1, unsigned int damage1) :
    position(position1),
    direction(direction1),
    damage(damage1){};

    Vector2f position;
    Vector2f direction;
    unsigned int damage;
    bool ShootFired;
};

struct SendBomb{
    SendBomb(){
        position = Vector2f(0, 0);
    }
    SendBomb(Vector2f position1) : position(position1){};

    Vector2f position;
};

struct SendFeature{
    SendFeature(){
        type = 0;
        position = Vector2f(0, 0);
    }
    SendFeature(int type1, Vector2f position1) :
    type(type1),
    position(position1){};

    int type;
    Vector2f position;
};

struct SendEnemy{
    SendEnemy(){
        uniqueNumber = 0;
        position = Vector2f(0, 0);
        health = 0;
        type = 0;
        aim = 0;
    }
    SendEnemy(unsigned int uniqueNumber1, Vector2f position1, float health1, int type1, unsigned int aim1) :
        uniqueNumber(uniqueNumber1),
        position(position1),
        health(health1),
        type(type1),
        aim(aim1){};

    unsigned int uniqueNumber;
    // "1 - 5" = types of enemies
    unsigned int type;
    unsigned int aim;
    Vector2f position;
    float health;
};

struct SendPlayer{
    SendPlayer(){
        type = 0;
        position = Vector2f(0, 0);
        direction = Vector2f(0, 0);
        health = 0;
    }
    SendPlayer(Vector2f position1, Vector2f direction1, float health1, int type1) :
            position(position1),
            direction(direction1),
            health(health1),
            type(type1){};

    unsigned int type;
    Vector2f position;
    Vector2f direction;
    float health;
};

struct SendTree{
    SendTree(){
        position = Vector2f(0, 0);
        type = 0;
    }
    SendTree(Vector2f position1, int type1) :
        position(position1),
        type(type1){};

    Vector2f position;
    int type;
};


//SendPlayer
sf::Packet& operator <<(sf::Packet& packet, const SendPlayer& A)
{
    return packet << A.type << A.health << A.position.x << A.position.y << A.direction.x << A.direction.y;
}
sf::Packet& operator >>(sf::Packet& packet, SendPlayer& A)
{
    return packet >> A.type >> A.health >> A.position.x >> A.position.y >> A.direction.x >> A.direction.y;
}

//SendTree
sf::Packet& operator <<(sf::Packet& packet, const SendTree& A)
{
    return packet << A.position.x << A.position.y << A.type;
}
sf::Packet& operator >>(sf::Packet& packet, SendTree& A)
{
    return packet >> A.position.x >> A.position.y >> A.type;
}

//SendBullet
sf::Packet& operator <<(sf::Packet& packet, const SendBullet& A)
{
    return packet << A.position.x << A.position.y << A.direction.x << A.direction.y << A.ShootFired;
}
sf::Packet& operator >>(sf::Packet& packet, SendBullet& A)
{
    return packet >> A.position.x >> A.position.y >> A.direction.x >> A.direction.y >> A.ShootFired;
}

//SendBomb
sf::Packet& operator <<(sf::Packet& packet, const SendBomb& A)
{
    return packet << A.position.x << A.position.y;
}
sf::Packet& operator >>(sf::Packet& packet, SendBomb& A)
{
    return packet >> A.position.x >> A.position.y;
}

//SendFeature
sf::Packet& operator <<(sf::Packet& packet, const SendFeature& A)
{
    return packet << A.type << A.position.x << A.position.y;
}
sf::Packet& operator >>(sf::Packet& packet, SendFeature& A)
{
    return packet >> A.type >> A.position.x >> A.position.y;
}

//SendEnemy
sf::Packet& operator <<(sf::Packet& packet, const SendEnemy& A)
{
    return packet << A.uniqueNumber << A.health << A.position.x << A.position.y << A.type << A.aim;
}
sf::Packet& operator >>(sf::Packet& packet, SendEnemy& A)
{
    return packet >> A.uniqueNumber >> A.health >> A.position.x >> A.position.y >> A.type >> A.aim;
}


//SendBackground
sf::Packet& operator <<(sf::Packet& packet, const Background& A)
{
    return packet << A.speed << A.crossPlayer << A.crossEnemy << A.crossRay << A.crossWeapon << A.type;
}
sf::Packet& operator >>(sf::Packet& packet, Background& A)
{
    return packet >> A.speed >> A.crossPlayer >> A.crossEnemy >> A.crossRay >> A.crossWeapon >> A.type;
}

//SendOpaque
sf::Packet& operator <<(sf::Packet& packet, const Opaque& A)
{
    return packet << A.position.x << A.position.y << A.size.x << A.size.y;
}
sf::Packet& operator >>(sf::Packet& packet, Opaque& A)
{
    return packet >> A.position.x >> A.position.y >> A.size.x >> A.size.y;
}

//SendType
sf::Packet& operator <<(sf::Packet& packet, const SendType& A)
{
    return packet << A.type;
}
sf::Packet& operator >>(sf::Packet& packet, SendType& A)
{
    return packet >> A.type;
}


void addFeature(std::vector<Feature> &items, Vector2f position, int type){
    if(type == 1){
        Feature feature;
        feature.feature.setTexture(textureHeart);
        feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
        feature.feature.setScale(0.17, 0.17);
        feature.feature.setPosition(position);
        feature.type = 1;
        feature.value = 100;
        feature.timeBuffer = 0;
        items.push_back(feature);

    } else if(type == 2){
        Feature feature;
        feature.feature.setTexture(textureShield);
        feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
        feature.feature.setScale(0.04, 0.04);
        feature.feature.setPosition(position);
        feature.type = 2;
        feature.value = 100;
        feature.timeBuffer = 0;
        items.push_back(feature);

    } else if(type == 3){
        Feature feature;
        feature.feature.setTexture(textureBullet);
        feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
        feature.feature.setScale(0.1, 0.1);
        feature.feature.setPosition(position);
        feature.type = 3;
        feature.value = numberBulletsCage;
        feature.timeBuffer = 0;
        items.push_back(feature);
    } else if(type == 4){
        Feature feature;
        feature.feature.setTexture(textureBomb);
        feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
        feature.feature.setScale(0.035, 0.035);
        feature.feature.setPosition(position);
        feature.type = 4;
        feature.value = numberBombsCage;
        feature.timeBuffer = 0;
        items.push_back(feature);
    }
}

void unpack(sf::Packet &packet, std::vector<Weapon> &bullets, std::vector<Bomb> &bombs, std::vector<Feature> &items,
            std::vector<Organism> &zombies, std::vector<Organism> &zombies1, std::vector<Organism> &zombies2,
            std::vector<Organism> &zombies3, std::vector<Organism> &dogs,std::vector<Opaque> &houses,
            Organism &player1, Organism &player2){
    SendType type;
    SendBullet sendBullet;
    SendBomb sendBomb;
    SendFeature sendFeature;
    SendEnemy sendEnemy;
    SendPlayer sendPlayer;
    SendTree sendTree;
    Background map;
    Opaque opaque;

    int numberBackground = 0;


    while(true){
        packet >> type;

        if(type.type == packetType::end)
            break;

        switch (type.type){
            case packetType::bullet:{
                packet >> sendBullet;
                Weapon bullet;
                bullet.direction = sendBullet.direction;
                bullet.speed = speedBullet;
                bullet.damage = sendBullet.damage;
                if(bullet.damage == shotgunDamage)
                    bullet.weapon = spriteBullet2;
                else
                    bullet.weapon = spriteBullet1;
                bullet.weapon.setPosition(sendBullet.direction);
                //bullet.rotate()
                bullets.push_back(bullet);
                return;
            }

            case packetType::bomb:{
                packet >> sendBomb;
                Bomb bomb;
                bomb.weapon = spriteBomb1;
                bomb.weapon.setPosition(sendBomb.position);
                bomb.timeBuffer = 0;
                bomb.timeExplode = 0;
                bomb.damage = bombDamage;
                bomb.textureNumber = 1;
                bombs.push_back(bomb);
                break;
            }
            case packetType::feature:{
                packet >> sendFeature;
                addFeature(items, sendFeature.position, sendFeature.type);
                break;
            }
            case packetType::enemy:{
                packet >> sendEnemy;
                if(sendEnemy.uniqueNumber <= numberEnemyProduced){
                    for(auto &i : zombies){
                        if(i.uniqueNumber == sendEnemy.uniqueNumber){
                            i.health = sendEnemy.health;
                            i.organism.setPosition(sendEnemy.position);
                        }
                    }
                    for(auto &i : zombies1){
                        if(i.uniqueNumber == sendEnemy.uniqueNumber){
                            i.health = sendEnemy.health;
                            i.organism.setPosition(sendEnemy.position);
                        }
                    }
                    for(auto &i : zombies2){
                        if(i.uniqueNumber == sendEnemy.uniqueNumber){
                            i.health = sendEnemy.health;
                            i.organism.setPosition(sendEnemy.position);
                        }
                    }
                    for(auto &i : zombies3){
                        if(i.uniqueNumber == sendEnemy.uniqueNumber){
                            i.health = sendEnemy.health;
                            i.organism.setPosition(sendEnemy.position);
                        }
                    }
                    for(auto &i : dogs){
                        if(i.uniqueNumber == sendEnemy.uniqueNumber){
                            i.health = sendEnemy.health;
                            i.organism.setPosition(sendEnemy.position);
                        }
                    }
                } else {
                    switch (sendEnemy.type){
                        case 1:{
                            Organism zombie(zombieFullHealth, 100, zombieSpeed, speedDrawZombie, zombieDamage, true,
                                            textureZombiePathsWalkFullHealth, textureZombiePathsWalkHalfHealth, textureZombiePathsWalkSmallHealth, numberZombiePathsWalk, 0.001,
                                            textureZombiePathsAttackFullHealth, textureZombiePathsAttackHalfHealth, textureZombiePathsAttackSmallHealth, numberZombiePathsAttack, 0.001,
                                            spriteZombie);

                            zombie.organism.setPosition(sendEnemy.position);
                            Vector2u enemySize = zombie.organism.getTexture()->getSize();
                            zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
                            zombie.organism.setScale(0.75, 0.75);

                            zombies.push_back(zombie);

                            break;
                        }
                        case 2:{
                            Organism zombie(zombie1FullHealth, 100, zombie1Speed, speedDrawZombie1, zombie1Damage, true,
                                            textureZombie1PathsWalkFullHealth, textureZombie1PathsWalkHalfHealth, textureZombie1PathsWalkSmallHealth, numberZombie1PathsWalk, 0.001,
                                            textureZombie1PathsAttackFullHealth, textureZombie1PathsAttackHalfHealth, textureZombie1PathsAttackSmallHealth, numberZombie1PathsWalk, 0.001,
                                            spriteZombie1);

                            zombie.organism.setPosition(sendEnemy.position);

                            Vector2u enemySize = zombie.organism.getTexture()->getSize();
                            zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
                            zombie.organism.setScale(1.3, 1.3);

                            zombies1.push_back(zombie);

                            break;
                        }

                        case 3:{
                            Organism zombie(zombie2FullHealth, 100, zombie2Speed, speedDrawZombie2, zombie2Damage, true,
                                            textureZombie2PathsWalkFullHealth, textureZombie2PathsWalkHalfHealth, textureZombie2PathsWalkSmallHealth, numberZombie2PathsWalk, 0.001,
                                            textureZombie2PathsAttackFullHealth, textureZombie2PathsAttackHalfHealth, textureZombie2PathsAttackSmallHealth, numberZombie2PathsWalk, 0.001,
                                            spriteZombie2);

                            zombie.organism.setPosition(sendEnemy.position);

                            Vector2u enemySize = zombie.organism.getTexture()->getSize();
                            zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
                            zombie.organism.setScale(1.4, 1.4);

                            zombies2.push_back(zombie);

                            break;
                        }

                        case 4:{
                            Organism zombie(zombie3FullHealth, 100, zombie3Speed, speedDrawZombie3, zombie3Damage, true,
                                            textureZombie3PathsWalkFullHealth, textureZombie3PathsWalkHalfHealth, textureZombie3PathsWalkSmallHealth, numberZombie3PathsWalk, 0.001,
                                            textureZombie3PathsAttackFullHealth, textureZombie3PathsAttackHalfHealth, textureZombie3PathsAttackSmallHealth, numberZombie3PathsWalk, 0.001,
                                            spriteZombie3);

                            zombie.organism.setPosition(sendEnemy.position);

                            Vector2u enemySize = zombie.organism.getTexture()->getSize();
                            zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
                            zombie.organism.setScale(1.4, 1.4);

                            zombies3.push_back(zombie);

                            break;
                        }

                        case 5:{
                            Organism zombie(dogFullHealth, 100, dogSpeed, speedDrawDog, dogDamage, true,
                                            textureDogPathsWalkFullHealth, textureDogPathsWalkFullHealth, textureDogPathsWalkFullHealth, numberZombie2PathsWalk, 0.001,
                                            textureDogPathsAttackFullHealth, textureDogPathsAttackFullHealth, textureDogPathsAttackFullHealth, numberZombie2PathsWalk, 0.001,
                                            spriteDog);
                            zombie.organism.setPosition(sendEnemy.position);

                            Vector2u enemySize = zombie.organism.getTexture()->getSize();
                            zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
                            zombie.organism.setScale(1.0, 1.0);
                            dogs.push_back(zombie);

                            break;
                        }

                    }
                }

            }
            case packetType::player:{
                packet >> sendPlayer;
                if(sendPlayer.type == 0){
                    player1.direction = sendPlayer.direction;
                    player1.health = sendPlayer.health;
                    player1.organism.setPosition(sendPlayer.position);
                } else if(sendPlayer.type == 1){
                    player2.direction = sendPlayer.direction;
                    player2.health = sendPlayer.health;
                    player2.organism.setPosition(sendPlayer.position);
                }
                break;
            }
            case packetType::map:{
                packet >> map;
                background[numberBackground / sizeWindow.x][numberBackground % sizeWindow.x] = map;
                numberBackground++;
                break;
            }
            case packetType::opaque:{
                packet >> opaque;
                houses.push_back(opaque);
                break;
            }
            case packetType::tree:{
                packet >> sendTree;
                switch (sendTree.type){
                    case 1:
                        trees1.push_back(sendTree.position);
                    case 2:
                        trees2.push_back(sendTree.position);
                    case 3:
                        trees3.push_back(sendTree.position);
                    case 4:
                        trees4.push_back(sendTree.position);
                    case 5:
                        trees5.push_back(sendTree.position);
                }
            }

            default:
                return;

        }
    }

    packet.clear();
}

