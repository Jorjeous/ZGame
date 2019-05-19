#include "objects.h"

bool isInside(Sprite &object, int sideOfBorder);
bool isInside(View &gameView, Sprite &object, int sideOfBorder);
bool isInside(Vector2f coordinates, float xSize, float ySize, int sideOfBorder);
void movePlayer(View &gameView, Organism &player, std::vector<Organism> &enemies1, std::vector<Organism> &enemies2,
                std::vector<Organism> &enemies3, std::vector<Organism> &enemies4, std::vector<Organism> &enemies5,Time time);
void deleteWeapon(View &gameView, std::vector <Weapon> &bullets);
void moveEnemies(View &gameview, std::vector <Organism> &enemies, Organism &player, Time time);
void strikeWeapon(View &gameView, std::vector <Weapon> &bullets, std::vector <Organism> &enemies, std::vector<Corpse> &dead);

float maxmod(float a, float b);

void gameViewUpdate(View &gameView, RenderWindow &window, Organism &player, Time time){

    float gameViewLeft = (gameView.getCenter().x - gameView.getSize().x / 2) ;
    float gameViewRight = (gameView.getCenter().x + gameView.getSize().x / 2);
    float gameViewUp = (gameView.getCenter().y - gameView.getSize().y / 2);
    float gameViewDown = (gameView.getCenter().y + gameView.getSize().y / 2);

    Vector2f CurrentCenter = gameView.getCenter();
    Vector2f TargetCenter = player.organism.getPosition();

    if(isInside(gameView.getCenter(), gameView.getSize().x, gameView.getSize().y, 0)){
        //gameView.setCenter(player.organism.getPosition());
        //view is up
        if(gameViewUp == 0){
            //if(!isInside(TargetCenter, gameView.getSize().x, gameView.getSize().y, 1)){
            if(TargetCenter.y - gameView.getSize().y/2 < 0)
                TargetCenter.y = gameView.getCenter().y;
        }
        //view is down
        if(gameViewDown == sizeWindow.y*sizeTile){
            //if(!isInside(TargetCenter, gameView.getSize().x, gameView.getSize().y, 3)){
            if(TargetCenter.y + gameView.getSize().y/2 > sizeWindow.y*sizeTile)
                TargetCenter.y = gameView.getCenter().y;
        }
        //view is left
        if(gameViewLeft == 0){
            //if(!isInside(TargetCenter, gameView.getSize().x, gameView.getSize().y, 4)){
            if(TargetCenter.x - gameView.getSize().x/2 < 0)
                TargetCenter.x = gameView.getCenter().x;
        }
        //view is right
        if(gameViewRight == sizeWindow.x*sizeTile){
            //if(!isInside(TargetCenter, gameView.getSize().x, gameView.getSize().y, 2)){
            if(TargetCenter.x + gameView.getSize().x/2 > sizeWindow.x*sizeTile)
                TargetCenter.x = gameView.getCenter().x;
        }
        //This variant doesn't work, because tine.asseconds is progressing
        //gameView.setCenter(CurrentCenter + (TargetCenter - CurrentCenter) * (float)exp(-200 * time.asSeconds()));
        gameView.setCenter(CurrentCenter + (TargetCenter - CurrentCenter) * (float)exp(-200 * time.asSeconds()));
        window.setView(gameView);

    } else{
        if(!isInside(gameView.getCenter(), gameView.getSize().x, gameView.getSize().y, 4))
            gameView.setCenter(gameView.getSize().x/2, gameView.getCenter().y);

        if(!isInside(gameView.getCenter(), gameView.getSize().x, gameView.getSize().y, 2))
            gameView.setCenter(sizeWindow.x * sizeTile - gameView.getSize().x/2, gameView.getCenter().y);

        if(!isInside(gameView.getCenter(), gameView.getSize().x, gameView.getSize().y, 1))
            gameView.setCenter(gameView.getCenter().x, gameView.getSize().y/2);

        if(!isInside(gameView.getCenter(), gameView.getSize().x, gameView.getSize().y, 3))
            gameView.setCenter(gameView.getCenter().x, sizeWindow.y * sizeTile - gameView.getSize().y/2 );
    }
}

void strikeWeapon(View &gameView, std::vector <Weapon> &bullets, std::vector <Organism> &enemies, std::vector<Corpse> &dead){

    int numberBullets = 0;
    for(auto &i : bullets){
        int numberEnemies = 0;
        for(auto &k : enemies){

            if(!isInside(gameView, k.organism, 0)){
                numberEnemies++;
                continue;
            }

            if(i.isInsideOrganism(k)){
                k.health -= i.damage;
                bullets.erase(bullets.begin() + numberBullets);

                //DEAD
                if(k.health <= 0){
                    Corpse corpse(k.organism.getRotation(), k.organism.getPosition(), k.organism.getTexture()->getSize().x * k.organism.getScale().x);
                    corpse.corpse.setTexture(textureCorpse);
                    dead.push_back(corpse);

                    enemies.erase(enemies.begin() + numberEnemies);
//                    while(1){
//                        window.draw(corpse.corpse);
//                        window.display();
//                    }

                }
                break;
            }
            numberEnemies++;
        }
        numberBullets++;
    }
}

void moveEnemies(View &gameView, std::vector <Organism> &enemies, Organism &player, Time time){
    for(auto &i :enemies){
        //if(isInside(gameView, i.organism, 0)){
            if(i.health < (float)i.fullHealth*4/5 && i.health > i.fullHealth*1/2){
                i.path.pathIterator = 1;

            } else if(i.health < (float)i.fullHealth*1/3 && i.health > 0){
                i.path.pathIterator = 2;

            }
            if(!player.isInsideOrganism(i) && !i.isInsideOrganism(player)){
                i.path.numberAttackNow = 0;
                i.walkUpdate(time);
                i.move(time, player.organism.getPosition()-i.organism.getPosition());

            } else{
                i.path.numberWalkNow = 0;
                i.attackUpdate(time);
                player.health -= i.damage*time.asSeconds();
            }
        //}
    }
}

void deleteWeapon(View &gameView, std::vector <Weapon> &bullets){
    int j = 0;
    for(auto &i : bullets){
        if(!isInside(gameView, i.weapon, 0)){
            bullets.erase(bullets.begin() + j);
        }
        j++;
    }
}

void movePlayer(View &gameView, Organism &player, std::vector<Organism> &enemies1, std::vector<Organism> &enemies2,
                std::vector<Organism> &enemies3, std::vector<Organism> &enemies4, std::vector<Organism> &enemies5,Time time){
    player.walkUpdate(time);

    //May Add chance to move through zombies
    bool abilityGoRight = true;
    bool abilityGoLeft = true;
    bool abilityGoUp = true;
    bool abilityGoDown = true;

    for(auto &i : enemies1){
        if(!isInside(gameView, i.organism, 0))
            continue;
        if(player.isInsideOrganism(i) || i.isInsideOrganism(player)){
            Vector2f d = i.organism.getPosition() - player.organism.getPosition();

            if((d.x > 0) && (d.x == maxmod(d.x, d.y)))
                abilityGoRight = false;
            if((d.x < 0) && (d.x == maxmod((d.x), d.y)))
                abilityGoLeft = false;
            if((d.y < 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoUp = false;
            if((d.y > 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoDown = false;
        }
    }
    for(auto &i : enemies2){
        if(!isInside(gameView, i.organism, 0))
            continue;
        if(player.isInsideOrganism(i) || i.isInsideOrganism(player)){
            Vector2f d = i.organism.getPosition() - player.organism.getPosition();

            if((d.x > 0) && (d.x == maxmod(d.x, d.y)))
                abilityGoRight = false;
            if((d.x < 0) && (d.x == maxmod((d.x), d.y)))
                abilityGoLeft = false;
            if((d.y < 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoUp = false;
            if((d.y > 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoDown = false;
        }
    }
    for(auto &i : enemies3){
        if(!isInside(gameView, i.organism, 0))
            continue;
        if(player.isInsideOrganism(i) || i.isInsideOrganism(player)){
            Vector2f d = i.organism.getPosition() - player.organism.getPosition();

            if((d.x > 0) && (d.x == maxmod(d.x, d.y)))
                abilityGoRight = false;
            if((d.x < 0) && (d.x == maxmod((d.x), d.y)))
                abilityGoLeft = false;
            if((d.y < 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoUp = false;
            if((d.y > 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoDown = false;
        }
    }
    for(auto &i : enemies4){
        if(!isInside(gameView, i.organism, 0))
            continue;
        if(player.isInsideOrganism(i) || i.isInsideOrganism(player)){
            Vector2f d = i.organism.getPosition() - player.organism.getPosition();

            if((d.x > 0) && (d.x == maxmod(d.x, d.y)))
                abilityGoRight = false;
            if((d.x < 0) && (d.x == maxmod((d.x), d.y)))
                abilityGoLeft = false;
            if((d.y < 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoUp = false;
            if((d.y > 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoDown = false;
        }
    }
    for(auto &i : enemies5){
        if(!isInside(gameView, i.organism, 0))
            continue;
        if(player.isInsideOrganism(i) || i.isInsideOrganism(player)){
            Vector2f d = i.organism.getPosition() - player.organism.getPosition();

            if((d.x > 0) && (d.x == maxmod(d.x, d.y)))
                abilityGoRight = false;
            if((d.x < 0) && (d.x == maxmod((d.x), d.y)))
                abilityGoLeft = false;
            if((d.y < 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoUp = false;
            if((d.y > 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoDown = false;
        }
    }

    int down = 0, right = 0;
    if(Keyboard::isKeyPressed(Keyboard::Up) && isInside(player.organism, 1) && abilityGoUp)
        down--;
    if(Keyboard::isKeyPressed(Keyboard::Down) && isInside(player.organism, 3) && abilityGoDown)
        down++;
    if(Keyboard::isKeyPressed(Keyboard::Left) && isInside(player.organism, 4) && abilityGoLeft)
        right--;
    if(Keyboard::isKeyPressed(Keyboard::Right) && isInside(player.organism, 2) && abilityGoRight)
        right++;

    if(right != 0 || down != 0)
        player.move(time, Vector2f(right, down));
}

bool isInside(View &gameView, Sprite &object, int sideOfBorder){     //   1
    float xSize = (float)object.getTexture()->getSize().x/2 * object.getScale().x;
    float ySize = (float)object.getTexture()->getSize().y/2 * object.getScale().y;

    switch (sideOfBorder){                                                          //  4 2
        case 0:{                                                                    //   3
            return isInside(gameView, object, 1) && isInside(gameView, object, 2)
                   && isInside(gameView, object, 3) && isInside(gameView, object, 4);
        }
        case 1:{
            return object.getPosition().y - ySize > 0;
        }
        case 2:{
            return object.getPosition().x + xSize < gameView.getCenter().x + gameView.getSize().x / 2;
        }
        case 3:{
            return object.getPosition().y + ySize < gameView.getCenter().y + gameView.getSize().y / 2;
        }
        case 4:{
            return object.getPosition().x - xSize > 0;
        }
        default:
            return false;
    }
}

bool isInside(Sprite &object, int sideOfBorder){     //   1
    float xSize = (float)object.getTexture()->getSize().x/2 * object.getScale().x;
    float ySize = (float)object.getTexture()->getSize().y/2 * object.getScale().y;

    switch (sideOfBorder){                                                          //  4 2
        case 0:{                                                                    //   3
            return isInside(object, 1) && isInside(object, 2)
                   && isInside(object, 3) && isInside(object, 4);
        }
        case 1:{
            return object.getPosition().y - ySize > 0;
        }
        case 2:{
            return object.getPosition().x + xSize < sizeWindow.x * sizeTile;
        }
        case 3:{
            return object.getPosition().y + ySize < sizeWindow.y * sizeTile;
        }
        case 4:{
            return object.getPosition().x - xSize > 0;
        }
        default:
            return false;
    }
}

bool isInside(Vector2f coordinates, float xSize, float ySize, int sideOfBorder){
                                                                                    //   1
    switch (sideOfBorder){                                                          //  4 2
        case 0:{                                                                    //   3
            return isInside(coordinates, xSize, ySize, 1) && isInside(coordinates, xSize, ySize, 2)
                   && isInside(coordinates, xSize, ySize, 3) && isInside(coordinates, xSize, ySize, 4);
        }
        case 1:{
            return coordinates.y - ySize / 2 >= 0;
        }
        case 2:{
            return coordinates.x + xSize / 2 <= sizeWindow.x * sizeTile;
        }
        case 3:{
            return coordinates.y + ySize / 2 <= sizeWindow.y * sizeTile;
        }
        case 4:{
            return coordinates.x - xSize / 2 >= 0;
        }
        default:
            return false;
    }
}
//Vector2f findViewCenter(const Sprite &player, View &gameView){
//    Vector2f center = player.getPosition();
//
//    center.x = std::max(center.x, gameView.getSize().x/2);
//    center.y = std::max(center.y, gameView.getSize().y/2);
//
//    center.x = std::min(center.x, sizeWindow.x - gameView.getSize().x/2);
//    center.y = std::min(center.y, sizeWindow.y - gameView.getSize().y/2);
//
//    return center;
//}
Vector2f FindViewCenter(const Sprite& player, sf::View gameView, Vector2f& CurrentCenter, Time time2)
{
    Vector2f Center = player.getPosition();
    CurrentCenter = Center + (CurrentCenter - Center) * exp((-1.1e+0f*time2.asSeconds()));

    return CurrentCenter;
}

float maxmod(float a, float b){
    float moda, modb;

    if(a > 0)
        moda = a;
    else
        moda = -a;
    if(b > 0)
        modb = b;
    else
        modb = -b;

    if(moda > modb)
        return a;
    else
        return b;
}

