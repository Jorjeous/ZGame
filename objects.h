#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "paths.h"

using namespace sf;

Vector2f norm(Vector2f a);
float getLenght(Vector2f a);

const Vector2i sizeWindow = Vector2i(100, 100);

int sizeTile = 20;

unsigned int zombieFullHealth = 300;
unsigned int zombie1FullHealth = 1000;
unsigned int zombie2FullHealth = 200;
unsigned int zombie3FullHealth = 200;
unsigned int dogFullHealth = 100;
unsigned int playerFullHealth = 1000;

unsigned int playerProtection = 200;

unsigned int zombieSpeed = 100;
unsigned int zombie1Speed = 50;
unsigned int zombie2Speed = 100;
unsigned int zombie3Speed = 100;
unsigned int dogSpeed = 150;
unsigned int playerSpeed = 200;

unsigned int zombieDamage = 20;
unsigned int zombie1Damage = 50;
unsigned int zombie2Damage = 10;
unsigned int zombie3Damage = 10;
unsigned int dogDamage = 5;

float speedDrawZombie = 0.05;
float speedDrawZombie1 = 0.1;
float speedDrawZombie2 = 0.2;
float speedDrawZombie3 = 0.2;
float speedDrawDog = 0.1;
float speedDrawPlayer = 0.1;

float timeProducementZombie = 5;
float timeProducementZombie1 = 12;
float timeProducementZombie2 = 15;
float timeProducementZombie3 = 20;
float timeProducementDog = 2;

float bloodDisappearTime = 0.05;


class Corpse{
public:
    Corpse(float angle, Vector2f position, float size){
        texture = textureCorpse;
        corpse.setTexture(texture);
        corpse.setOrigin((float)texture.getSize().x / 2, (float)texture.getSize().y / 2);
        corpse.setScale(size/100, size/100);
        corpse.setRotation(angle);
        corpse.setPosition(position);
        timeBuffer = 0;
        std::cout << std::endl << "New created" << std::endl;
    }
    void update(Time time){
        timeBuffer += time.asSeconds();
        while(timeBuffer > bloodDisappearTime){
            timeBuffer -= bloodDisappearTime;
            if(corpse.getColor().a > 0)
                corpse.setColor(Color(255, 255, 255, corpse.getColor().a - 1));
        }
    }

    bool isDisappeared(){
        return corpse.getColor().a <= 0;
    }

    Sprite corpse;
    Texture texture;
    float timeBuffer;
};

class Path{
public:
    Path(std::vector <Texture> &walkFull,
         std::vector <Texture> &walkHalf,
         std::vector <Texture> &walkSmall,
         int numberwalk, float walktimebuffer,

         std::vector <Texture> &attackFull,
         std::vector <Texture> &attackHalf,
         std::vector <Texture> &attackSmall,
         int numberattack, float attacktimebuffer):

         PathsWalkFullHealth(walkFull),
         PathsWalkHalfHealth(walkHalf),
         PathsWalkSmallHealth(walkSmall),
         numberWalk(numberwalk),
         numberWalkNow(0),
         walkTimeBuffer(walktimebuffer),


         PathsAttackFullHealth(attackFull),
         PathsAttackHalfHealth(attackHalf),
         PathsAttackSmallHealth(attackSmall),
         numberAttack(numberattack),
         numberAttackNow(0),
         attackTimeBuffer(attacktimebuffer),
         pathIterator(0){};

    Path &operator=(const Path &path1){
        PathsWalkFullHealth = path1.PathsWalkFullHealth;
        PathsWalkHalfHealth = path1.PathsWalkHalfHealth;
        PathsWalkSmallHealth = path1.PathsWalkSmallHealth;
        numberWalk = path1.numberWalk;
        numberWalkNow = path1.numberWalkNow;
        walkTimeBuffer = path1.walkTimeBuffer;

        PathsAttackFullHealth = path1.PathsAttackFullHealth;
        PathsAttackHalfHealth = path1.PathsAttackHalfHealth;
        PathsAttackSmallHealth = path1.PathsAttackSmallHealth;
        numberAttack = path1.numberAttack;
        numberAttackNow = path1.numberAttackNow;
        attackTimeBuffer = path1.attackTimeBuffer;

        pathIterator = path1.pathIterator;
    }

    std::vector <Texture> &PathsWalkFullHealth;
    std::vector <Texture> &PathsWalkHalfHealth;
    std::vector <Texture> &PathsWalkSmallHealth;
    int numberWalk;
    int numberWalkNow;
    float walkTimeBuffer;

    std::vector <Texture> &PathsAttackFullHealth;
    std::vector <Texture> &PathsAttackHalfHealth;
    std::vector <Texture> &PathsAttackSmallHealth;
    int numberAttack;
    int numberAttackNow;
    float attackTimeBuffer;

    unsigned int pathIterator;
};

class Background {
public:
    Background(){
        crossEnemy = false;
        crossPlayer = false;
        crossRay = false;
        speed = 1.f;
    }
    Background(bool a){
        crossEnemy = a;
        crossPlayer = a;
        crossRay = a;
        speed = 1.f;
    }
    float speed;          // Ex. you go through the water slower than on grass
    bool crossPlayer;   //  ability for the player.organism to go through this object
    bool crossEnemy;    //  ability for the zombies and other enemies to go through this object
    bool crossRay;
    unsigned int type;           //to compare with others
};

class Organism{
public:
    float health;
    unsigned int fullHealth;
    int protection;
    unsigned int speed;
    float speedDraw;
    int damage;
    bool enemy;
    Path path;
    Sprite organism;

    Organism(
            int health1,
            int protection1,
            unsigned int speed1,
            float speedDraw1,
            int damage1,
            bool enemy1,

            std::vector <Texture> &walkFull,
            std::vector <Texture> &walkHalf,
            std::vector <Texture> &walkSmall,
            int numberwalk, float walktimebuffer,

            std::vector <Texture> &attackFull,
            std::vector <Texture> &attackHalf,
            std::vector <Texture> &attackSmall,
            int numberattack, float attacktimebuffer,

            Sprite &sprite1) :
                    health(health1),
                    fullHealth(health1),
                    protection(protection1),
                    speed(speed1),
                    speedDraw(speedDraw1),
                    damage(damage1),
                    enemy(enemy1),
                    path(walkFull,
                            walkHalf,
                            walkSmall,
                            numberwalk,
                            walktimebuffer,

                            attackFull,
                            attackHalf,
                            attackSmall,
                            numberattack,
                            attacktimebuffer),
                    organism(sprite1){};

    ~Organism(){};

    void attackUpdate(Time time){
        path.attackTimeBuffer += time.asSeconds();
        if(path.attackTimeBuffer >= speedDraw){
            path.attackTimeBuffer -= speedDraw;
            path.numberAttackNow = (path.numberAttackNow + 1) % (path.numberAttack);

            if(path.pathIterator == 0)
                organism.setTexture(path.PathsAttackFullHealth[path.numberAttackNow]);
            else if(path.pathIterator == 1)
                organism.setTexture(path.PathsAttackHalfHealth[path.numberAttackNow]);
            else if(path.pathIterator == 2)
                organism.setTexture(path.PathsAttackSmallHealth[path.numberAttackNow]);
        }
    }
    void walkUpdate(Time time){
        path.walkTimeBuffer += time.asSeconds();
        if(path.walkTimeBuffer >= speedDraw){
            path.walkTimeBuffer -= speedDraw;
            path.numberWalkNow = (path.numberWalkNow + 1) % (path.numberWalk);

            if(path.pathIterator == 0)
                organism.setTexture(path.PathsWalkFullHealth[path.numberWalkNow]);
            else if(path.pathIterator == 1)
                organism.setTexture(path.PathsWalkHalfHealth[path.numberWalkNow]);
            else if(path.pathIterator == 2)
                organism.setTexture(path.PathsWalkSmallHealth[path.numberWalkNow]);
        }
    }

    void rotate(RenderWindow &window, Vector2f rotateAround){
        Vector2f d = rotateAround - organism.getPosition();
        organism.setRotation((atan2f(d.y, d.x)*180-270)/M_PI);
    }

    void move(Time time, Vector2f direction){
        organism.move(speed*time.asSeconds()*norm(direction));
    }

    bool isInsideOrganism(Organism enemy){
        float radiusEnemy = std::min(enemy.organism.getTexture()->getSize().x*enemy.organism.getScale().x*2/5,
                                     enemy.organism.getTexture()->getSize().y*enemy.organism.getScale().y*2/5);
        float radiusMy = std::min(organism.getTexture()->getSize().x*organism.getScale().x*2/5,
                                     organism.getTexture()->getSize().y*organism.getScale().y*2/5);
        Vector2f d = enemy.organism.getPosition() - organism.getPosition();

        if(getLenght(d) < radiusEnemy + radiusMy)
            return true;
        else
            return false;
    }

    Background getPosition(RenderWindow &window, Background **background){

    }
};

class Weapon{
public:
    int damage;
    float speed;
    Vector2f direction;
    Sprite weapon;

    void rotate(RenderWindow &window, Vector2f rotateAround){
        Vector2f d = weapon.getPosition() - rotateAround;
        weapon.setRotation((-atan2f(d.x, d.y)*180)/M_PI);
    }

    void move(Time time){
        weapon.setPosition(weapon.getPosition() + speed * time.asSeconds() * norm(direction));
    }

    bool isInsideOrganism(Organism enemy){
        float radius = std::min(enemy.organism.getTexture()->getSize().x, enemy.organism.getTexture()->getSize().y)/3
                *std::min(enemy.organism.getScale().x, enemy.organism.getScale().y);

        return (weapon.getPosition().x < enemy.organism.getPosition().x + radius)
               && (weapon.getPosition().x > enemy.organism.getPosition().x - radius)
               && (weapon.getPosition().y > enemy.organism.getPosition().y - radius)
               && (weapon.getPosition().y < enemy.organism.getPosition().y + radius);
    }

    Background getPosition(RenderWindow &window, Background **background){

    }
};

class Bar{
public:
    Bar(const std::string &str1, const std::string &str2, Color color){
        texture.loadFromFile(str1);
        sprite.setTexture(texture);
        sprite.setScale(0.3, 0.3);
        shape.setFillColor(color);
        shape.setSize(Vector2f(190, 20));

        font.loadFromFile(str2);
        text.setFont(font);
        text.setCharacterSize(40);
        text.setFillColor(color);
        text.setStyle(Text::Bold | Text::Italic);
    }

    void update(View &gameView, Organism &player){
        sprite.setPosition(gameView.getCenter().x + gameView.getSize().x/2 - 200,
                           gameView.getCenter().y - gameView.getSize().y/2 + 10);
        shape.setPosition(sprite.getPosition().x, sprite.getPosition().y + 80);
        shape.setScale(player.health / playerFullHealth, 1);

        text.setPosition(sprite.getPosition().x + 80, sprite.getPosition().y + 15);
        text.setString(std::to_string((int)(100*player.health / playerFullHealth)) + "%");
    }

    Font font;
    Text text;
    RectangleShape shape;
    Texture texture;
    Sprite sprite;
};

class TimeBar{
public:
    TimeBar(const std::string &str){
        font.loadFromFile(str);
        text.setFont(font);
        text.setCharacterSize(50);
        text.setFillColor(Color(128, 255, 0, 255));
        text.setStyle(Text::Bold | Text::Italic);
        text.setPosition(0, 0);
    }

    void update(View &gameView, Time time){
        text.setPosition(gameView.getCenter().x - gameView.getSize().x/2 + 20,
                         gameView.getCenter().y - gameView.getSize().y/2 + 20);
        text.setString(std::to_string((int)time.asSeconds()/60) + " min  " + std::to_string((int)time.asSeconds() % 60) + " sec");
    }

    Font font;
    Text text;
};

//List of initializations used:
class Strike{
public:
    Strike(std::vector<Weapon> bulletsNew, std::vector<Organism> enemiesNew) : bullets(bulletsNew), enemies(enemiesNew){
    }

    std::vector<Weapon> &bullets;
    std::vector<Organism> &enemies;
};

Vector2f norm(Vector2f a){
    return a / getLenght(a);
}
float getLenght(Vector2f a){
    return sqrt(a.x*a.x + a.y*a.y);
}
