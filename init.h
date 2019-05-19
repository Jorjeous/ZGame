#include "update.h"

Weapon initBullet(RenderWindow &window, Sprite spriteBullet, Organism player){
    Weapon bullet;
    Vector2f mousePosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x, window.mapPixelToCoords(sf::Mouse::getPosition(window)).y);
    bullet.weapon = spriteBullet;
    bullet.weapon.setPosition(player.organism.getPosition());
    bullet.direction = mousePosition - player.organism.getPosition();

    bullet.direction = norm(bullet.direction);
    bullet.speed = 1500;
    bullet.damage = 50;
    bullet.rotate(window, mousePosition);

    return bullet;
}

