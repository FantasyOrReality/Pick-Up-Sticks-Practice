#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

int main()
{
#pragma region Setup


    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::None);
    window.setVerticalSyncEnabled(true);

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
        //grass origin
        grassSprite.setOrigin(grassTexture.getSize().x / 2, grassTexture.getSize().y / 2);

        //random grass tint
        grassSprite.setColor(sf::Color(rand() % (255 - 0), rand() % (255 - 0), rand() % (255 - 0)));

        //random grass scale
        grassSprite.setScale((rand() % (20 - 5) / 10.0f), (rand() % (20 - 5)) / 10.0f);

        //grass position and pushback
        grassSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x - grassTexture.getSize().x / 2), rand() % (window.getSize().y - grassTexture.getSize().y / 2)));
        grassSpriteVector.push_back(grassSprite);
    }

    //stick sprite vector
    std::vector<sf::Sprite> stickSpriteVector;

    //stick origin
    stickSprite.setOrigin(stickTexture.getSize().x / 2, stickTexture.getSize().y / 2);

    //random stick position
    stickSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x - stickTexture.getSize().x / 2), rand() % (window.getSize().y - stickTexture.getSize().y / 2)));

    //random stick rotation
    stickSprite.setRotation(rand() % (355 - 1));

    stickSpriteVector.push_back(stickSprite);



    //player position
    playerSprite.setPosition(sf::Vector2f(0.0f + (playerTexture.getSize().x / 2.0f), 100.0f + (playerTexture.getSize().y / 2.0f)));

    
    //randomise player move direction

    float playerMoveRangeX;
    float playerMoveRangeY;
    int randX;
    int randY;

    /*
    //randomise -x or +x
    randX = rand() % (2 - 1);
    if (randX == 2)
    {
        playerMoveRangeX = 10.0f;
    }
    else
    {
        playerMoveRangeX = -10.0f;

    }

    //randomise -y or +y
    randY = rand() % (2 - 1);
    if (randY == 2)
    {
        playerMoveRangeY = 10.0f;

    }
    else
    {
        playerMoveRangeX = -10.0f;
    }
    */




    //player rotation
    //playerSprite.setRotation(270);

    //player scale
    //playerSprite.setScale(3.0f,3.0f);

    //player origin
    playerSprite.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);

    //Load fonts
    sf::Font gameFont;
    gameFont.loadFromFile("Assets/GameFont.ttf");

    //Create text objects
    sf::Text gameTitle;
    gameTitle.setFont(gameFont);
    gameTitle.setString("Pick Up Sticks");

    gameTitle.setFillColor(sf::Color::Black);
    gameTitle.setOutlineThickness(1.0f);
    gameTitle.setOutlineColor(sf::Color::White);
    gameTitle.setStyle(sf::Text::Bold | sf::Text::Italic);
    gameTitle.setCharacterSize(60);

    float textWidth = gameTitle.getLocalBounds().width;
    gameTitle.setPosition((float)window.getSize().x / 2.0f - textWidth / 2.0f, 10.0f);



    sf::Text scoreLabel;
    sf::Text score;
    scoreLabel.setFont(gameFont);
    score.setFont(gameFont);

    score.setString("000");
    scoreLabel.setString("Score:");


    //Setting up sound
    sf::SoundBuffer startSFXBuffer;
    startSFXBuffer.loadFromFile("Assets/Start.wav");

    sf::Sound startSFX;
    startSFX.setBuffer(startSFXBuffer);
    startSFX.play();

    sf::Music gameMusic;
    gameMusic.openFromFile("Assets/MusicOGG.OGG");
    gameMusic.setLoop(true);
    gameMusic.play();


#pragma endregion
    //end setup


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
        //End events

#pragma region Updates
        /*
        //move in random direction
        float currentPlayerPositionX;
        float currentPlayerPositionY;

        currentPlayerPositionX = playerSprite.getPosition().x;
        currentPlayerPositionY = playerSprite.getPosition().y;

       

       //playerSprite.setPosition(sf::Vector2f(rand() % (currentPlayerPositionX + playerMoveRangeX), rand() % (currentPlayerPositionY + playerMoveRangeY)));
        */


#pragma endregion
        //end updates

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

        //text UI
        window.draw(scoreLabel);

        window.draw(gameTitle);

        //display
        window.display();

#pragma endregion
        //end drawing
   
        
        
    }

    return 0;
}