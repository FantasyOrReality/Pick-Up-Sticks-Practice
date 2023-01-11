#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main()
{
#pragma region Setup


    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::None);

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

    //player sprite
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);

    //grass sprite
    sf::Sprite grassSprite;
    grassSprite.setTexture(grassTexture);

    //grass sprite vector
    std::vector<sf::Sprite> grassSpriteVector;
    for (int i = 0; i <= 5; i++)
    {
        grassSpriteVector.push_back(grassSprite);
    }

    //position
    playerSprite.setPosition(sf::Vector2f(0.0f, 100.0f));

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

        //player sprite
        window.draw(playerSprite);

        //display
        window.display();

#pragma endregion

   
        
        
    }

    return 0;
}