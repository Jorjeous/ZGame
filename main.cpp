#include "background.cpp"
#include "Light.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Texture textureBullet;
Texture textureCursor0;
Texture textureCursor1;


void setCursor(RenderWindow &window, Sprite &spriteCursor){
    spriteCursor.setScale(0.05f, 0.05f);
    spriteCursor.setOrigin(spriteCursor.getPosition().x + spriteCursor.getTexture()->getSize().x
                                                          * spriteCursor.getScale().x,
                           spriteCursor.getPosition().y + spriteCursor.getTexture()->getSize().y
                                                          * spriteCursor.getScale().y);
}

int main()
{
    VideoMode mode = VideoMode::getDesktopMode();

    setTextures();

    RenderWindow window(VideoMode(mode.width, mode.height), "ZOMBIE ATTACK" /*sf::Style::Fullscreen*/);
    window.setFramerateLimit(60);

    //===        light casting values
	lightlib::ShadowWorld sw;
	sf::Vector2f lineaddingstart;
	bool addingline = false;
	//----
    //---
    sf::View gameView(sf::FloatRect(0, 0, mode.width, mode.height));
    gameView.setCenter(sizeWindow.x*sizeTile/2, sizeWindow.y*sizeTile/2);
    window.setView(gameView);
    sf::View initialView = gameView;

    //create Background
    setBackground(window);
    //Create PlayerSprite

    Sprite spritePlayer(texturePlayerPaths[0]);
    //Create ZombieSprite
    Sprite spriteZombie(textureZombiePathsWalkFullHealth[0]);
    //Create Zombie1Sprite
    Sprite spriteZombie1(textureZombie1PathsWalkFullHealth[0]);
    spriteZombie1.setScale(3, 3);
    //Create Zombie2Sprite
    Sprite spriteZombie2(textureZombie2PathsWalkFullHealth[0]);
    spriteZombie2.setScale(1.5, 1.5);
    //Create Zombie3prite
    Sprite spriteZombie3(textureZombie3PathsWalkFullHealth[0]);
    spriteZombie3.setScale(1.5, 1.5);
    //Create DogSprite
    Sprite spriteDog(textureDogPathsWalkFullHealth[0]);
    //Create BulletSprite
    textureBullet.loadFromFile("pngForGame/bullet.png");
    Sprite spriteBullet(textureBullet);
    //Create MouseSprite
    textureCursor0.loadFromFile("pngForGame/cursor0.png");
    textureCursor1.loadFromFile("pngForGame/cursor1.png");
    Sprite spriteCursor(textureCursor0);
    setCursor(window, spriteCursor);


    //Init Player
    Organism player(playerFullHealth, 100, playerSpeed, speedDrawPlayer, 0, false,
                    texturePlayerPaths, texturePlayerPaths, texturePlayerPaths, numberPlayerPathsWalk, 0.01,
                    texturePlayerPaths, texturePlayerPaths, texturePlayerPaths, numberPlayerPathsWalk, 0.01, spritePlayer);
    player.organism.setPosition((float)sizeWindow.x*sizeTile/2, (float)sizeWindow.y*sizeTile/2);
    Vector2u playerSize = player.organism.getTexture()->getSize();
    player.organism.setOrigin((float)playerSize.x/2, (float)playerSize.y/2);
    player.organism.setScale(0.75, 0.75);

    Bar lifeBar("pngForGame/heart.png", "fonts/font.ttf", Color(255, 0, 0, 255));
    TimeBar timeBar("fonts/font.ttf");


    std::vector<Weapon> bullets;
    std::vector<Organism> zombies;
    std::vector<Organism> zombies1;
    std::vector<Organism> zombies2;
    std::vector<Organism> zombies3;
    std::vector<Organism> dogs;
    std::vector<Corpse> dead;

    textureCorpse.loadFromFile(corpsePath);

    Clock clock;
    Clock clock6;

    float timeBuffer1 = 0;
    float timeBuffer2 = 0;
    float timeBuffer3 = 0;
    float timeBuffer4 = 0;
    float timeBuffer5 = 0;

    while (window.isOpen())
    {

        Event event;

        //window.setVerticalSyncEnabled(true);
        window.setMouseCursorVisible(false);

        Time time = clock.restart();
        Time time6 = clock6.getElapsedTime();

        timeBuffer1 += time.asSeconds();
        timeBuffer2 += time.asSeconds();
        timeBuffer3 += time.asSeconds();
        timeBuffer4 += time.asSeconds();
        timeBuffer5 += time.asSeconds();


//        if(time6.asSeconds() > 30){
//            break;
//        }

//1
        time6 = clock6.getElapsedTime();
        std::cout << " 1: "<< time6.asSeconds();


        if(timeBuffer1 > timeProducementZombie){
            timeBuffer1 -= timeProducementZombie;

            //Create zombie
            Organism zombie(zombieFullHealth, 100, zombieSpeed, speedDrawZombie, zombieDamage, true,
                            textureZombiePathsWalkFullHealth, textureZombiePathsWalkHalfHealth, textureZombiePathsWalkSmallHealth, numberZombiePathsWalk, 0.001,
                            textureZombiePathsAttackFullHealth, textureZombiePathsAttackHalfHealth, textureZombiePathsAttackSmallHealth, numberZombiePathsAttack, 0.001,
                            spriteZombie);
            zombie.organism.setPosition(rand() % (sizeWindow.x * sizeTile), rand() % (sizeWindow.y * sizeTile));
            Vector2u enemySize = zombie.organism.getTexture()->getSize();
            zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);

            zombies.push_back(zombie);
        }
        if(timeBuffer2 > timeProducementZombie1){
            timeBuffer2 -= timeProducementZombie1;

            Organism zombie(zombie1FullHealth, 100, zombie1Speed, speedDrawZombie1, zombie1Damage, true,
                            textureZombie1PathsWalkFullHealth, textureZombie1PathsWalkHalfHealth, textureZombie1PathsWalkSmallHealth, numberZombie1PathsWalk, 0.001,
                            textureZombie1PathsAttackFullHealth, textureZombie1PathsAttackHalfHealth, textureZombie1PathsAttackSmallHealth, numberZombie1PathsWalk, 0.001,
                            spriteZombie1);
            zombie.organism.setPosition(rand() % (sizeWindow.x * sizeTile), rand() % (sizeWindow.y * sizeTile));
            Vector2u enemySize = zombie.organism.getTexture()->getSize();
            zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
            zombie.organism.setScale(2, 2);

            zombies1.push_back(zombie);
        }
        if(timeBuffer3 > timeProducementZombie2){
            timeBuffer3 -= timeProducementZombie2;

            Organism zombie(zombie2FullHealth, 100, zombie2Speed, speedDrawZombie2, zombie2Damage, true,
                            textureZombie2PathsWalkFullHealth, textureZombie2PathsWalkHalfHealth, textureZombie2PathsWalkSmallHealth, numberZombie2PathsWalk, 0.001,
                            textureZombie2PathsAttackFullHealth, textureZombie2PathsAttackHalfHealth, textureZombie2PathsAttackSmallHealth, numberZombie2PathsWalk, 0.001,
                            spriteZombie2);
            zombie.organism.setPosition(rand() % (sizeWindow.x * sizeTile), rand() % (sizeWindow.y * sizeTile));
            Vector2u enemySize = zombie.organism.getTexture()->getSize();
            zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
            zombie.organism.setScale(1.6, 1.6);

            zombies2.push_back(zombie);
        }


        if(timeBuffer4 > timeProducementZombie3){
            timeBuffer4 -= timeProducementZombie3;

            Organism zombie(zombie3FullHealth, 100, zombie3Speed, speedDrawZombie3, zombie3Damage, true,
                            textureZombie3PathsWalkFullHealth, textureZombie3PathsWalkHalfHealth, textureZombie3PathsWalkSmallHealth, numberZombie3PathsWalk, 0.001,
                            textureZombie3PathsAttackFullHealth, textureZombie3PathsAttackHalfHealth, textureZombie3PathsAttackSmallHealth, numberZombie3PathsWalk, 0.001,
                            spriteZombie3);
            zombie.organism.setPosition(rand() % (sizeWindow.x * sizeTile), rand() % (sizeWindow.y * sizeTile));
            Vector2u enemySize = zombie.organism.getTexture()->getSize();
            zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
            zombie.organism.setScale(1.6, 1.6);

            zombies3.push_back(zombie);
        }
        if(timeBuffer5 > timeProducementDog){
            timeBuffer5 -= timeProducementDog;

            Organism zombie(dogFullHealth, 100, dogSpeed, speedDrawDog, dogDamage, true,
                            textureDogPathsWalkFullHealth, textureDogPathsWalkFullHealth, textureDogPathsWalkFullHealth, numberZombie2PathsWalk, 0.001,
                            textureDogPathsAttackFullHealth, textureDogPathsAttackFullHealth, textureDogPathsAttackFullHealth, numberZombie2PathsWalk, 0.001,
                            spriteDog);
            zombie.organism.setPosition(rand() % (sizeWindow.x * sizeTile), rand() % (sizeWindow.y * sizeTile));
            Vector2u enemySize = zombie.organism.getTexture()->getSize();
            zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
            zombie.organism.setScale(1.2, 1.2);
            dogs.push_back(zombie);
        }

//2
        time6 = clock6.getElapsedTime();
        std::cout << " 2: "<<time6.asSeconds();


        moveEnemies(gameView, zombies, player, time);
        moveEnemies(gameView, zombies1, player, time);
        moveEnemies(gameView, zombies2, player, time);
        moveEnemies(gameView, zombies3, player, time);
        moveEnemies(gameView, dogs, player, time);

//3
        time6 = clock6.getElapsedTime();
        std::cout <<" 3: "<< time6.asSeconds();




        strikeWeapon(gameView, bullets, zombies, dead);
        strikeWeapon(gameView, bullets, zombies1, dead);
        strikeWeapon(gameView, bullets, zombies2, dead);
        strikeWeapon(gameView, bullets, zombies3, dead);
        strikeWeapon(gameView, bullets, dogs, dead);

//        Strike A1(bullets, zombies);
//        Strike A2(bullets, zombies1);
//        Strike A3(bullets, zombies2);
//        Strike A4(bullets, zombies3);
//        Strike A5(bullets, dogs);

//        sf::Thread thread1(&strikeWeapon, &A1);
//        sf::Thread thread2(&strikeWeapon, &A2);
//        sf::Thread thread3(&strikeWeapon, &A3);
//        sf::Thread thread4(&strikeWeapon, &A4);
//        sf::Thread thread5(&strikeWeapon, &A5);
//
//
//        thread1.launch();
//        thread2.launch();
//        thread3.launch();
//        thread4.launch();
//        thread5.launch();
//
//        thread1.wait();
//        thread2.wait();
//        thread3.wait();
//        thread4.wait();
//        thread5.wait();


//        strikeWeapon(A1);
//        strikeWeapon(A2);
//        strikeWeapon(A3);
//        strikeWeapon(A4);
//        strikeWeapon(A5);


//4
        time6 = clock6.getElapsedTime();
        std::cout << " 4: "<< time6.asSeconds();


        deleteWeapon(gameView, bullets);

        player.rotate(window, Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x,
                window.mapPixelToCoords(sf::Mouse::getPosition(window)).y));
        movePlayer(gameView, player, zombies, zombies1, zombies2, zombies3, dogs,time);

        lifeBar.update(gameView, player);
        timeBar.update(gameView, time6);

//5
        time6 = clock6.getElapsedTime();
        std::cout << " 5: " << time6.asSeconds();


        for(auto &i : zombies)
            i.rotate(window, player.organism.getPosition());
        for(auto &i : zombies1)
            i.rotate(window, player.organism.getPosition());
        for(auto &i : zombies2)
            i.rotate(window, player.organism.getPosition());
        for(auto &i : zombies3)
            i.rotate(window, player.organism.getPosition());
        for(auto &i : dogs)
            i.rotate(window, player.organism.getPosition());

        for(auto &i : bullets)
            i.move(time);


        int j = 0;
        for(auto &i : dead){
            i.update(time);
            if(i.isDisappeared())
                dead.erase(dead.begin() + j);
            j++;
        }


        if(Mouse::isButtonPressed(Mouse::Left)){
            spriteCursor.setTexture(textureCursor1);
        }
        if(Keyboard::isKeyPressed(Keyboard::Space)){

        }

        while (window.pollEvent(event))
        {
            switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				addingline = true;
				lineaddingstart = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				break;
			case sf::Event::MouseButtonReleased:
				if (addingline)
				{
					const sf::Vector2f b = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					sw.addLine(lineaddingstart, b);
					sw.deduplicateLineEndPoints();
					sw.findLineSelfIntersections();
					sw.deduplicateLineSelfIntersectionsPoints();
					addingline = false;
				}//if addingline
				break;
			}//switch event type
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left){
                Weapon bullet = initBullet(window, spriteBullet, player);
                bullets.push_back(bullet);
                spriteCursor.setTexture(textureCursor0);
            }
        }
        
        //adding lines
		sf::VertexArray arr(sf::Lines);
		for (int i = 0; i < sw.getLineCount(); ++i)
		{
			arr.append(sf::Vertex(sw.getLineByIndex(i).first));
			arr.append(sf::Vertex(sw.getLineByIndex(i).second));
		}//for i


//6
        time6 = clock6.getElapsedTime();
        std::cout << " 6: " << time6.asSeconds();


        //update Window
        window.clear();

//        std::cout << "Center:" << gameView.getCenter().x << ", " << gameView.getCenter().y << std::endl;
//        std::cout << "Size:" << gameView.getSize().x << ", " << gameView.getSize().y << std::endl;

        float gameViewLeft = (gameView.getCenter().x - gameView.getSize().x / 2) / sizeTile - 5 ;
        float gameViewRight = (gameView.getCenter().x + gameView.getSize().x / 2) / sizeTile + 5;
        float gameViewUp = (gameView.getCenter().y - gameView.getSize().y / 2) / sizeTile - 5;
        float gameViewDown = (gameView.getCenter().y + gameView.getSize().y / 2) / sizeTile + 5;

        if(gameViewLeft < 0)
            gameViewLeft = 0;
        if(gameViewRight > sizeWindow.x)
            gameViewRight = sizeWindow.x;
        if(gameViewUp < 0)
            gameViewUp = 0;
        if(gameViewDown > sizeWindow.y)
            gameViewDown = sizeWindow.y;

        for(int i = (int)gameViewLeft; i < gameViewRight; i++){
            for(int j = (int)gameViewUp;j < gameViewDown; j++){
                backgroundTypes.at(background[i][j].type).picture.setPosition(i * sizeTile, j * sizeTile);
                window.draw(backgroundTypes.at(background[i][j].type).picture);
            }
        }

        // set Cursor Position
        spriteCursor.setPosition(window.mapPixelToCoords(Mouse::getPosition(window)).x,
                window.mapPixelToCoords(Mouse::getPosition(window)).y);


        for(auto &i : dead){
            if(isInside(gameView, i.corpse, 0))
                window.draw(i.corpse);
        }
        for(auto &i : bullets)
            window.draw(i.weapon);
        for(auto &i : zombies){
            if(isInside(gameView, i.organism, 0))
                window.draw(i.organism);
        }
        for(auto &i : zombies1){
            if(isInside(gameView, i.organism, 0))
                window.draw(i.organism);
        }
        for(auto &i : zombies2){
            if(isInside(gameView, i.organism, 0))
                window.draw(i.organism);
        }
        for(auto &i : zombies3){
            if(isInside(gameView, i.organism, 0))
                window.draw(i.organism);
        }
        for(auto &i : dogs){
            if(isInside(gameView, i.organism, 0))
                window.draw(i.organism);
        }
        
        //======
		lightlib::LightParams par; //view limiter parametrs
		par.radius = 600.f; //view radius
		par.position = player.organism.getPosition();
		const auto pts = sw.computeLightPoints(par);
		lightlib::debugDrawLightPoints(window, par, pts);
		lightlib::debugDrawFloatRect(window, par.aabb());
        //------
                
        
        
        window.draw(player.organism);

        window.draw(lifeBar.sprite);
        window.draw(lifeBar.shape);
        window.draw(lifeBar.text);
        window.draw(timeBar.text);

        window.draw(spriteCursor);
        window.display();

//7
        time6 = clock6.getElapsedTime();
        std::cout << " 7: " << time6.asSeconds();

        gameViewUpdate(gameView, window, player, time);
//8
        time6 = clock6.getElapsedTime();
        std::cout << " 8: " << time6.asSeconds();
        std::cout << "End"<< std::endl;
        std::cout << time.asSeconds()<< std::endl;

        if(player.health <= 0){
            return 0;
        }
    }

    return 0;
}

