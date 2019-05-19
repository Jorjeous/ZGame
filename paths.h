#include <iostream>

using namespace sf;

int numberZombiePathsWalk = 16;
int numberZombiePathsAttack = 9;
int numberPlayerPathsWalk = 1;
int numberZombie1PathsWalk = 4;
int numberZombie2PathsWalk = 4;
int numberZombie3PathsWalk = 4;
int numberDogPathsWalk = 4;

Texture texture;

const std::string zombie1PathsWalkFullHealth[4] = {
        "pngForGame/zombie2/1/21.png",
        "pngForGame/zombie2/1/22.png",
        "pngForGame/zombie2/1/23.png",
        "pngForGame/zombie2/1/24.png",
};

const std::string zombie1PathsWalkHalfHealth[4] = {
        "pngForGame/zombie2/1/11.png",
        "pngForGame/zombie2/1/12.png",
        "pngForGame/zombie2/1/13.png",
        "pngForGame/zombie2/1/14.png",
};

const std::string zombie1PathsWalkSmallHealth[4] = {
        "pngForGame/zombie2/1/01.png",
        "pngForGame/zombie2/1/02.png",
        "pngForGame/zombie2/1/03.png",
        "pngForGame/zombie2/1/04.png",
};

const std::string zombie2PathsWalkFullHealth[4] = {
        "pngForGame/zombie2/2/21.png",
        "pngForGame/zombie2/2/22.png",
        "pngForGame/zombie2/2/23.png",
        "pngForGame/zombie2/2/24.png",
};

const std::string zombie2PathsWalkHalfHealth[4] = {
        "pngForGame/zombie2/2/11.png",
        "pngForGame/zombie2/2/12.png",
        "pngForGame/zombie2/2/13.png",
        "pngForGame/zombie2/2/14.png",
};

const std::string zombie2PathsWalkSmallHealth[4] = {
        "pngForGame/zombie2/2/01.png",
        "pngForGame/zombie2/2/02.png",
        "pngForGame/zombie2/2/03.png",
        "pngForGame/zombie2/2/04.png",
};

const std::string zombie3PathsWalkFullHealth[4] = {
        "pngForGame/zombie2/3/21.png",
        "pngForGame/zombie2/3/22.png",
        "pngForGame/zombie2/3/23.png",
        "pngForGame/zombie2/3/24.png",
};

const std::string zombie3PathsWalkHalfHealth[4] = {
        "pngForGame/zombie2/3/11.png",
        "pngForGame/zombie2/3/12.png",
        "pngForGame/zombie2/3/13.png",
        "pngForGame/zombie2/3/14.png",
};

const std::string zombie3PathsWalkSmallHealth[4] = {
        "pngForGame/zombie2/3/01.png",
        "pngForGame/zombie2/3/02.png",
        "pngForGame/zombie2/3/03.png",
        "pngForGame/zombie2/3/04.png",
};

const std::string dogPathsWalkFullHealth[4] = {
        "pngForGame/zombie2/dog/1.png",
        "pngForGame/zombie2/dog/2.png",
        "pngForGame/zombie2/dog/3.png",
        "pngForGame/zombie2/dog/4.png",
};

const std::string zombiePathsWalkFullHealth[16] = {
        "pngForGame/zombie/walk/200.png",
        "pngForGame/zombie/walk/201.png",
        "pngForGame/zombie/walk/202.png",
        "pngForGame/zombie/walk/203.png",
        "pngForGame/zombie/walk/204.png",
        "pngForGame/zombie/walk/205.png",
        "pngForGame/zombie/walk/206.png",
        "pngForGame/zombie/walk/207.png",
        "pngForGame/zombie/walk/208.png",
        "pngForGame/zombie/walk/209.png",
        "pngForGame/zombie/walk/210.png",
        "pngForGame/zombie/walk/211.png",
        "pngForGame/zombie/walk/212.png",
        "pngForGame/zombie/walk/213.png",
        "pngForGame/zombie/walk/214.png",
        "pngForGame/zombie/walk/215.png"
};

const std::string zombiePathsWalkHalfHealth[16] = {
        "pngForGame/zombie/walk/100.png",
        "pngForGame/zombie/walk/101.png",
        "pngForGame/zombie/walk/102.png",
        "pngForGame/zombie/walk/103.png",
        "pngForGame/zombie/walk/104.png",
        "pngForGame/zombie/walk/105.png",
        "pngForGame/zombie/walk/106.png",
        "pngForGame/zombie/walk/107.png",
        "pngForGame/zombie/walk/108.png",
        "pngForGame/zombie/walk/109.png",
        "pngForGame/zombie/walk/110.png",
        "pngForGame/zombie/walk/111.png",
        "pngForGame/zombie/walk/112.png",
        "pngForGame/zombie/walk/113.png",
        "pngForGame/zombie/walk/114.png",
        "pngForGame/zombie/walk/115.png"
};

const std::string zombiePathsWalkSmallHealth[16] = {
        "pngForGame/zombie/walk/000.png",
        "pngForGame/zombie/walk/001.png",
        "pngForGame/zombie/walk/002.png",
        "pngForGame/zombie/walk/003.png",
        "pngForGame/zombie/walk/004.png",
        "pngForGame/zombie/walk/005.png",
        "pngForGame/zombie/walk/006.png",
        "pngForGame/zombie/walk/007.png",
        "pngForGame/zombie/walk/008.png",
        "pngForGame/zombie/walk/009.png",
        "pngForGame/zombie/walk/010.png",
        "pngForGame/zombie/walk/011.png",
        "pngForGame/zombie/walk/012.png",
        "pngForGame/zombie/walk/013.png",
        "pngForGame/zombie/walk/014.png",
        "pngForGame/zombie/walk/015.png"
};

const std::string zombiePathsAttackFullHealth[9] = {
        "pngForGame/zombie/attack/20.png",
        "pngForGame/zombie/attack/21.png",
        "pngForGame/zombie/attack/22.png",
        "pngForGame/zombie/attack/23.png",
        "pngForGame/zombie/attack/24.png",
        "pngForGame/zombie/attack/25.png",
        "pngForGame/zombie/attack/26.png",
        "pngForGame/zombie/attack/27.png",
        "pngForGame/zombie/attack/28.png"
};
const std::string zombiePathsAttackHalfHealth[9] = {
        "pngForGame/zombie/attack/10.png",
        "pngForGame/zombie/attack/11.png",
        "pngForGame/zombie/attack/12.png",
        "pngForGame/zombie/attack/13.png",
        "pngForGame/zombie/attack/14.png",
        "pngForGame/zombie/attack/15.png",
        "pngForGame/zombie/attack/16.png",
        "pngForGame/zombie/attack/17.png",
        "pngForGame/zombie/attack/18.png"
};
const std::string zombiePathsAttackSmallHealth[9] = {
        "pngForGame/zombie/attack/00.png",
        "pngForGame/zombie/attack/01.png",
        "pngForGame/zombie/attack/02.png",
        "pngForGame/zombie/attack/03.png",
        "pngForGame/zombie/attack/04.png",
        "pngForGame/zombie/attack/05.png",
        "pngForGame/zombie/attack/06.png",
        "pngForGame/zombie/attack/07.png",
        "pngForGame/zombie/attack/08.png"
};

const std::string playerPathsWalkFullHealth[1] = {
        "pngForGame/player.png"
};

const std::string corpsePath = "pngForGame/blood.png";

std::vector <Texture> textureZombie1PathsWalkFullHealth;
std::vector <Texture> textureZombie1PathsWalkHalfHealth;
std::vector <Texture> textureZombie1PathsWalkSmallHealth;
std::vector <Texture> textureZombie1PathsAttackFullHealth;
std::vector <Texture> textureZombie1PathsAttackHalfHealth;
std::vector <Texture> textureZombie1PathsAttackSmallHealth;

std::vector <Texture> textureZombie2PathsWalkFullHealth;
std::vector <Texture> textureZombie2PathsWalkHalfHealth;
std::vector <Texture> textureZombie2PathsWalkSmallHealth;
std::vector <Texture> textureZombie2PathsAttackFullHealth;
std::vector <Texture> textureZombie2PathsAttackHalfHealth;
std::vector <Texture> textureZombie2PathsAttackSmallHealth;

std::vector <Texture> textureZombie3PathsWalkFullHealth;
std::vector <Texture> textureZombie3PathsWalkHalfHealth;
std::vector <Texture> textureZombie3PathsWalkSmallHealth;
std::vector <Texture> textureZombie3PathsAttackFullHealth;
std::vector <Texture> textureZombie3PathsAttackHalfHealth;
std::vector <Texture> textureZombie3PathsAttackSmallHealth;

std::vector <Texture> textureDogPathsWalkFullHealth;
std::vector <Texture> textureDogPathsAttackFullHealth;

std::vector <Texture> textureZombiePathsWalkFullHealth;
std::vector <Texture> textureZombiePathsWalkHalfHealth;
std::vector <Texture> textureZombiePathsWalkSmallHealth;
std::vector <Texture> textureZombiePathsAttackFullHealth;
std::vector <Texture> textureZombiePathsAttackHalfHealth;
std::vector <Texture> textureZombiePathsAttackSmallHealth;

std::vector <Texture> texturePlayerPaths;

Texture textureCorpse;

void setTextures(){
    //Zombie1
    for(int i = 0; i < numberZombie1PathsWalk; i++){
        texture.loadFromFile(zombie1PathsWalkFullHealth[i]);
        textureZombie1PathsWalkFullHealth.push_back(texture);
        texture.loadFromFile(zombie1PathsWalkHalfHealth[i]);
        textureZombie1PathsWalkHalfHealth.push_back(texture);
        texture.loadFromFile(zombie1PathsWalkSmallHealth[i]);
        textureZombie1PathsWalkSmallHealth.push_back(texture);

        texture.loadFromFile(zombie1PathsWalkFullHealth[0]);
        textureZombie1PathsAttackFullHealth.push_back(texture);
        texture.loadFromFile(zombie1PathsWalkHalfHealth[0]);
        textureZombie1PathsAttackHalfHealth.push_back(texture);
        texture.loadFromFile(zombie1PathsWalkSmallHealth[0]);
        textureZombie1PathsAttackSmallHealth.push_back(texture);
    }

    //Zombie2
    for(int i = 0; i < numberZombie2PathsWalk; i++){
        texture.loadFromFile(zombie2PathsWalkFullHealth[i]);
        textureZombie2PathsWalkFullHealth.push_back(texture);
        texture.loadFromFile(zombie2PathsWalkHalfHealth[i]);
        textureZombie2PathsWalkHalfHealth.push_back(texture);
        texture.loadFromFile(zombie2PathsWalkSmallHealth[i]);
        textureZombie2PathsWalkSmallHealth.push_back(texture);

        texture.loadFromFile(zombie2PathsWalkFullHealth[0]);
        textureZombie2PathsAttackFullHealth.push_back(texture);
        texture.loadFromFile(zombie2PathsWalkHalfHealth[0]);
        textureZombie2PathsAttackHalfHealth.push_back(texture);
        texture.loadFromFile(zombie2PathsWalkSmallHealth[0]);
        textureZombie2PathsAttackSmallHealth.push_back(texture);
    }

    //Zombie3
    for(int i = 0; i < numberZombie3PathsWalk; i++){
        texture.loadFromFile(zombie3PathsWalkFullHealth[i]);
        textureZombie3PathsWalkFullHealth.push_back(texture);
        texture.loadFromFile(zombie3PathsWalkHalfHealth[i]);
        textureZombie3PathsWalkHalfHealth.push_back(texture);
        texture.loadFromFile(zombie3PathsWalkSmallHealth[i]);
        textureZombie3PathsWalkSmallHealth.push_back(texture);

        texture.loadFromFile(zombie3PathsWalkFullHealth[0]);
        textureZombie3PathsAttackFullHealth.push_back(texture);
        texture.loadFromFile(zombie3PathsWalkHalfHealth[0]);
        textureZombie3PathsAttackHalfHealth.push_back(texture);
        texture.loadFromFile(zombie3PathsWalkSmallHealth[0]);
        textureZombie3PathsAttackSmallHealth.push_back(texture);
    }

    //Dog
    for(int i = 0; i < numberDogPathsWalk; i++){
        texture.loadFromFile(dogPathsWalkFullHealth[i]);
        textureDogPathsWalkFullHealth.push_back(texture);

        texture.loadFromFile(dogPathsWalkFullHealth[0]);
        textureDogPathsAttackFullHealth.push_back(texture);
    }

    //Zombie
    for(int i = 0; i < numberZombiePathsWalk; i++){
        texture.loadFromFile(zombiePathsWalkFullHealth[i]);
        textureZombiePathsWalkFullHealth.push_back(texture);
        texture.loadFromFile(zombiePathsWalkHalfHealth[i]);
        textureZombiePathsWalkHalfHealth.push_back(texture);
        texture.loadFromFile(zombiePathsWalkSmallHealth[i]);
        textureZombiePathsWalkSmallHealth.push_back(texture);
    }
    for(int i = 0; i < numberZombiePathsAttack; i++){
        texture.loadFromFile(zombiePathsAttackFullHealth[i]);
        textureZombiePathsAttackFullHealth.push_back(texture);
        texture.loadFromFile(zombiePathsAttackHalfHealth[i]);
        textureZombiePathsAttackHalfHealth.push_back(texture);
        texture.loadFromFile(zombiePathsAttackSmallHealth[i]);
        textureZombiePathsAttackSmallHealth.push_back(texture);
    }

    //Player
    for(int i = 0; i < numberPlayerPathsWalk; i++){
        texture.loadFromFile(playerPathsWalkFullHealth[i]);
        texturePlayerPaths.push_back(texture);
    }

};