#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

using namespace sf;

int sizePlayer = 64;

class Background {
public:
	int speed;          // Ex. you go through the water slower than on grass
	bool crossPlayer;   //  ability for the player.organism to go through this object
	bool crossEnemy;    //  ability for the zombies and other enemies to go through this object
	Sprite picture;
};

class Organism {
public:
	int health;
	int protection;
	float speed;
	int damage;
	Sprite organism;
};

class Weapon {
public:
	int damage;
	float speed;
	Vector2f direction;
	Sprite weapon;
};

bool isInsideOfBorder(RenderWindow &window, Organism player, int sideOfBorder);
void movePlayer(RenderWindow &window, Organism &player, Time time);
void rotatePlayer(RenderWindow &window, Organism &player);
void moveWeapon(RenderWindow &window, std::vector <Weapon> &bullets, Time time);
void setBackground(RenderWindow &window, Background *background) {

}

int main()
{
	RenderWindow window(VideoMode(1200, 1200), "ZOMBIE ATTACK"/*, sf::Style::Fullscreen*/);
	window.setFramerateLimit(60);

	//create Background
	Background background[20][20];
	Texture textureGrass;
	Texture textureRiver;
	textureGrass.loadFromFile("C:/Users/George/Desktop/programming/SFML2/TestSFML/src/grass.png");
	textureRiver.loadFromFile("C:/Users/George/Desktop/programming/SFML2/TestSFML/src/river.png");
	Sprite grass(textureGrass);
	Sprite river(textureRiver);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (j == 3) {
				background[i][j].picture = river;
				background[i][j].picture.setPosition(i * 33, j * 33);
			}
			else
			{
				background[i][j].picture = grass;
				background[i][j].picture.setPosition(i * 33, j * 33);
			}
		}
	}

	//Create player
	Texture texturePlayer;
	texturePlayer.loadFromFile("C:/Users/George/Desktop/programming/SFML2/TestSFML/src/roof.png");
	Sprite spritePlayer(texturePlayer);
	spritePlayer.setPosition(330, 330);
	Organism player;
	player.organism = spritePlayer;
	player.speed = 200.f;
	Vector2u playerSize = player.organism.getTexture()->getSize();
	player.organism.setOrigin(playerSize.x / 2, playerSize.y / 2);

	//Create Weapon
	Texture textureWeapon;
	textureWeapon.loadFromFile("C:/Users/George/Desktop/programming/SFML2/TestSFML/src/river.png");
	Sprite spriteWeapon(textureWeapon);
	std::vector<Weapon> bullets;

	Clock clock;
	Event event;

	while (window.isOpen())
	{
		//Time time = clock.getElapsedTime();
		Time time = clock.restart();

		rotatePlayer(window, player);
		movePlayer(window, player, time);
		moveWeapon(window, bullets, time);

		if (Mouse::isButtonPressed(Mouse::Left)) {

		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {

		}


		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
				Weapon bullet;
				bullet.weapon = spriteWeapon;
				bullet.weapon.setPosition(player.organism.getPosition());
				bullet.direction = Vector2f(Mouse::getPosition(window).x - player.organism.getPosition().x,
					Mouse::getPosition(window).y - player.organism.getPosition().y);
				printf("%f %f\n", bullet.direction.x, bullet.direction.y);
				bullet.direction /= (float)(sqrt((double)bullet.direction.x*bullet.direction.x + bullet.direction.y*bullet.direction.y));
				bullet.speed = 1000;
				bullet.damage = 1;
				bullets.push_back(bullet);
				printf("%f %f\n", bullet.direction.x, bullet.direction.y);
			}
		}

		//update Window
		window.clear();
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++)
				window.draw(background[i][j].picture);
		}
		for (auto i : bullets)
			window.draw(i.weapon);
		window.draw(player.organism);
		window.display();
	}

	return 0;
}

void moveWeapon(RenderWindow &window, std::vector <Weapon> &bullets, Time time) {
	for (auto &i : bullets)
		i.weapon.setPosition(i.weapon.getPosition() + i.speed * time.asSeconds() * i.direction);


}

void rotatePlayer(RenderWindow &window, Organism &player) {
	Vector2i mousePosition = Mouse::getPosition(window);
	Vector2f d = Vector2f(mousePosition.x, mousePosition.y) - player.organism.getPosition();
	player.organism.setRotation((atan2f(d.y, d.x) * 180 - 180) / 3.14);
}

void movePlayer(RenderWindow &window, Organism &player, Time time) {
	if (Keyboard::isKeyPressed(Keyboard::Up) && isInsideOfBorder(window, player, 1)
		|| Keyboard::isKeyPressed(Keyboard::W) && isInsideOfBorder(window, player, 1)) {
		player.organism.setPosition(player.organism.getPosition() + player.speed*time.asSeconds()*Vector2f(0, -1));
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) && isInsideOfBorder(window, player, 3)
		|| Keyboard::isKeyPressed(Keyboard::S) && isInsideOfBorder(window, player, 3)) {
		player.organism.setPosition(player.organism.getPosition() + player.speed*time.asSeconds()*Vector2f(0, 1));
	}
	if (Keyboard::isKeyPressed(Keyboard::Left) && isInsideOfBorder(window, player, 4)
		|| Keyboard::isKeyPressed(Keyboard::A) && isInsideOfBorder(window, player, 4)) {
		player.organism.setPosition(player.organism.getPosition() + player.speed*time.asSeconds()*Vector2f(-1, 0));
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && isInsideOfBorder(window, player, 2)
		|| Keyboard::isKeyPressed(Keyboard::D) && isInsideOfBorder(window, player, 2)) {
		player.organism.setPosition(player.organism.getPosition() + player.speed*time.asSeconds()*Vector2f(1, 0));
	}
}

bool isInsideOfBorder(RenderWindow &window, Organism player, int sideOfBorder) {    //  1
	switch (sideOfBorder) {                                                  //  4 2
	case 0: {                                                            //   3
		if (isInsideOfBorder(window, player, 1) && isInsideOfBorder(window, player, 2)
			&& isInsideOfBorder(window, player, 3) && isInsideOfBorder(window, player, 4))
			return true;
		else
			return false;
	}
	case 1: {
		if (player.organism.getPosition().y - player.organism.getTexture()->getSize().y / 2 > 0)
			return true;
		else
			return false;
	}
	case 2: {
		if (player.organism.getPosition().x + player.organism.getTexture()->getSize().x / 2 < window.getSize().x)
			return true;
		else
			return false;
	}
	case 3: {
		if (player.organism.getPosition().y + player.organism.getTexture()->getSize().y / 2 < window.getSize().y)
			return true;
		else
			return false;
	}
	case 4: {
		if (player.organism.getPosition().x - player.organism.getTexture()->getSize().x / 2 > 0)
			return true;
		else
			return false;
	}
	default:
		return false;
	}
}
