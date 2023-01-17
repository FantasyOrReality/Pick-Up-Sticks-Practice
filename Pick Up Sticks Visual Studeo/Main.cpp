#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>


int main()
{
#pragma region Setup


    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::None);

    srand(time(NULL));

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("Assets/Player_Stand.png"))
    {
        //error
        std::cout << "Texture load failed for Assets/Player_Stand.png" << std::endl;

    }
    else
    {
        //success
        std::cout << "Texture load successful for Assets/Player_Stand.png" << std::endl;

    }

    sf::Texture grassTexture;
    if (!grassTexture.loadFromFile("Assets/Grass.png"))
    {
        //error
        std::cout << "Texture load failed for Assets/Grass.png" << std::endl;

    }
    else
    {
        //success
        std::cout << "Texture load successful for Assets/Grass.png" << std::endl;

    }

    sf::Texture stickTexture;
    if (!stickTexture.loadFromFile("Assets/Stick.png"))
    {
        //error
        std::cout << "Texture load failed for Assets/Stick.png" << std::endl;

    }
    else
    {
        //success
        std::cout << "Texture load successful for Assets/Stick.png" << std::endl;

    }

    //player sprite
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);

    //grass sprite
    sf::Sprite grassSprite;
    grassSprite.setTexture(grassTexture);

    //stick sprite
    sf::Sprite stickSprite;
    stickSprite.setTexture(stickTexture);

    //grass sprite vector
    std::vector<sf::Sprite> grassSpriteVector;
    for (int i = 0; i <= 5; i++)
    {
        //random grass tint
        grassSprite.setColor(sf::Color(rand() % (255-0), rand() % (255 - 0), rand() % (255 - 0)));

        //random grass scale

        grassSprite.setScale((rand() % (20 - 5)/10.0f),(rand() % (20 - 5))/10.0f);

        //grass position and pushback
        grassSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x - grassTexture.getSize().x), rand() % (window.getSize().y - grassTexture.getSize().y)));
        grassSpriteVector.push_back(grassSprite);
    }

    //stick sprite vector
    std::vector<sf::Sprite> stickSpriteVector;
    
    //random stick position
    stickSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x - stickTexture.getSize().x), rand() % (window.getSize().y - stickTexture.getSize().y)));
    
    //random stick rotation
    stickSprite.setRotation(rand() % (355 - 1));

    stickSpriteVector.push_back(stickSprite);



    //player position
    playerSprite.setPosition(sf::Vector2f(0.0f, 100.0f));

    //player rotation
    //playerSprite.setRotation(270);

    //player scale
    //playerSprite.setScale(3.0f,3.0f);

    //Origin
    playerSprite.setOrigin(playerTexture.getSize().x/2, playerTexture.getSize().y/2);

#pragma endregion



#pragma region Event Polling

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

#pragma endregion



#pragma region Drawing

        //clear
        window.clear(sf::Color(190, 201, 91));

        //grass sprites
        for (int i = 0; i < grassSpriteVector.size(); ++i)
        {
            window.draw(grassSpriteVector[i]);
        }

        //stick sprites
        for (int i = 0; i < stickSpriteVector.size(); ++i)
        {
            window.draw(stickSpriteVector[i]);
        }

        //player sprite
        window.draw(playerSprite);

        //display
        window.display();

#pragma endregion

   
        
        
    }

    return 0;
}