#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <string>
#include <cmath>

//Like a type
enum GameState
{
    RUNNING,        //RUNNING = 0;
    GAME_OVER,      //GAME_OVER = 1;
    NUM_GAME_STATES
};

int main()
{
#pragma region Setup


    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::None);
    window.setVerticalSyncEnabled(true);

    GameState currentState = RUNNING; //assign the value 0 to gameRunning
    bool restartButtonPressed;

    srand(time(NULL));

    //int playerMoveRangeX;
    //int playerMoveRangeY;

    //int randDirection;

    //randDirection = rand() % (100 - 1);

    float xDir = (10 - rand() % 21) / 10.0f;
    float yDir = (10 - rand() % 21) / 10.0f;

    sf::Vector2f direction(xDir, yDir);

    bool blinkPressedPrev = false;

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
    playerSprite.setPosition(sf::Vector2f(0.0f + (400.0f + playerTexture.getSize().x / 2.0f), 400.0f + (playerTexture.getSize().y / 2.0f)));

    
    //count bounces
    int bounceCountA=0;
    int bounceCount1=0;
    int bounceCount2=0;
    int bounceCount3=0;
    



    //randomise 
    

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

    sf::Text timerText;
    timerText.setFont(gameFont);
    timerText.setString("Time Left: ");

    timerText.setFillColor(sf::Color::Black);
    timerText.setOutlineThickness(1.0f);
    timerText.setOutlineColor(sf::Color::White);
    timerText.setStyle(sf::Text::Bold | sf::Text::Italic);
    timerText.setCharacterSize(30);

    timerText.setPosition((float)window.getSize().x - 500.0f, 10.0f);

    sf::Text gameOverText;
    gameOverText.setFont(gameFont);
    gameOverText.setString("Game over!");

    gameOverText.setFillColor(sf::Color::Black);
    gameOverText.setOutlineThickness(1.0f);
    gameOverText.setOutlineColor(sf::Color::White);
    gameOverText.setStyle(sf::Text::Bold | sf::Text::Italic);
    gameOverText.setCharacterSize(30);

    textWidth = gameOverText.getLocalBounds().width;
    gameOverText.setPosition((float)window.getSize().x/2.0f - textWidth/2.0f, (float)window.getSize().y / 2.0f - 300);

    sf::Text restartText;
    restartText.setFont(gameFont);
    restartText.setString("Press Enter to restart");

    restartText.setFillColor(sf::Color::Black);
    restartText.setOutlineThickness(1.0f);
    restartText.setOutlineColor(sf::Color::White);
    restartText.setStyle(sf::Text::Bold | sf::Text::Italic);
    restartText.setCharacterSize(30);

    textWidth = restartText.getLocalBounds().width;
    restartText.setPosition((float)window.getSize().x / 2.0f - textWidth / 2.0f, (float)window.getSize().y / 2.0f + 100);

    sf::Text scoreLabel;

    sf::Text scoreValue1;
    sf::Text scoreValue2;
    sf::Text scoreValue3;

    scoreLabel.setFont(gameFont);

    scoreValue1.setFont(gameFont);
    scoreValue2.setFont(gameFont);
    scoreValue3.setFont(gameFont);



    //Score numbers will be presented like: |score3|score2|score1|
    scoreValue1.setString("0");
    scoreValue2.setString("0");
    scoreValue3.setString("0");


    scoreLabel.setString("Score:");


    //Setting up sound
    sf::SoundBuffer startSFXBuffer;
    startSFXBuffer.loadFromFile("Assets/Start.wav");

    sf::SoundBuffer pickUpSFXBuffer;
    pickUpSFXBuffer.loadFromFile("Assets/Pickup.wav");

    sf::Sound startSFX;
    startSFX.setBuffer(startSFXBuffer);
    startSFX.play();

    sf::Sound pickUpSFX;
    pickUpSFX.setBuffer(pickUpSFXBuffer);

    sf::Music gameMusic;
    gameMusic.openFromFile("Assets/MusicOGG.OGG");
    gameMusic.setLoop(true);
    gameMusic.play();

    //Setting up clocks and time
    sf::Clock deltaTimeClock;
    sf::Clock overallTimeClock;

    sf::Clock gameTimer;
    float gameDuration = 5.0f; //how long the game lasts

    sf::Clock stickSpawnCooldown;
    float stickSpawnRate = 1.0f;

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

        //Get time
        sf::Time deltaTime = deltaTimeClock.restart();
        sf::Time totalTime = overallTimeClock.getElapsedTime();

        //game timer
        float gameTimeFloat = gameTimer.getElapsedTime().asSeconds();
        float remainingTimeFloat = gameDuration - gameTimeFloat;
        std::string timerString = "Time Left: ";
        timerString += std::to_string((int)ceil(remainingTimeFloat));

        //display time passed this game
        timerText.setString(timerString);

        if (remainingTimeFloat <= 0.0f)
        {
            currentState = GAME_OVER;

        }
        else
        {
            currentState = RUNNING;
        }
        //Player 1 controller
        int player1Controller = 1;

        direction.x = 0;
        direction.y = 0;
        if (currentState == RUNNING)
        {
            if (sf::Joystick::isConnected(player1Controller))
            {

                float axisX = sf::Joystick::getAxisPosition(player1Controller, sf::Joystick::X);
                float axisY = sf::Joystick::getAxisPosition(player1Controller, sf::Joystick::Y);

                float deadzone = 10;

                if (abs(axisX > deadzone))
                {
                    direction.x = axisX / 100.0f;
                }
                if (abs(axisY > deadzone))
                {
                    direction.y = axisY / 100.0f;
                }


                direction.x = sf::Joystick::getAxisPosition(player1Controller, sf::Joystick::X) / 100.0f;
                direction.y = sf::Joystick::getAxisPosition(player1Controller, sf::Joystick::Y) / 100.0f;

            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                direction.x = -1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                direction.x = 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                direction.y = -1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                direction.y = 1;
            }



            //Update player position based on movement direction
            float speed = 500;
            // velocity = direction *speed
            sf::Vector2f velocity = direction * speed;
            // distance traveled = velocity*time
            sf::Vector2f distance = velocity * deltaTime.asSeconds();

            sf::Vector2f newPostion = playerSprite.getPosition() + distance;
            playerSprite.setPosition(newPostion);

            bool blinkPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(player1Controller, 0);

            if (blinkPressed && !blinkPressedPrev)
            {
                sf::Vector2f blinkPostion = playerSprite.getPosition() + direction * 100.0f;
                playerSprite.setPosition(blinkPostion);
            }

            blinkPressedPrev = blinkPressed;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                sf::Vector2f mousePositionFloat = (sf::Vector2f)localPosition;


                stickSprite.setPosition(mousePositionFloat);
                stickSprite.setRotation(rand() % (355 - 1));
                stickSpriteVector.push_back(stickSprite);
            }

            if (stickSpawnCooldown.getElapsedTime().asSeconds() >= stickSpawnRate)
            {
                stickSpawnCooldown.restart();
                stickSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x - stickTexture.getSize().x / 2), rand() % (window.getSize().y - stickTexture.getSize().y / 2)));
                stickSprite.setRotation(rand() % (355 - 1));

                stickSpriteVector.push_back(stickSprite);
            }



            /*
            //move in random direction
            int currentPlayerPositionX;
            int currentPlayerPositionY;


            currentPlayerPositionX = playerSprite.getPosition().x;
            currentPlayerPositionY = playerSprite.getPosition().y;
            */


            //if player is touching any edge
            /*if (currentPlayerPositionX == playerTexture.getSize().x / 2 || currentPlayerPositionX == window.getSize().x - playerTexture.getSize().x / 2 || currentPlayerPositionY == playerTexture.getSize().y / 2 || currentPlayerPositionY == window.getSize().y - playerTexture.getSize().y / 2)
            {
                bounceCountA += 1;
                pickUpSFX.play();

                if (bounceCount1 == 9)
                {
                    bounceCount1 = 0;
                    bounceScore1.setString("0");
                }
                else if (bounceCount1 < 9)
                {
                    bounceCount1 += 1;
                    // declaring output string stream
                    std::ostringstream bounceCount1str;

                    // Sending a number as a stream into output
                    // string
                    bounceCount1str << bounceCount1;

                    // the str() converts number into string
                    std::string bounceScore1str = bounceCount1str.str();

                    bounceScore1.setString(bounceScore1str);

                }
                if (bounceCountA > 9)
                {
                    if (bounceCount2 == 9)
                    {
                        bounceCount2 = 0;

                        bounceScore2.setString("0");


                        if (bounceCount3 == 9)
                        {
                            bounceCountA = 0;
                            bounceCount3 = 0;
                            bounceCount1 = 0;
                            bounceCount2 = 0;
                            bounceScore3.setString("0");

                        }
                        else if (bounceCount3 < 9)
                        {
                            bounceCount2 = 0;
                            bounceCountA = 0;
                            bounceCount3 += 1;

                            // declaring output string stream
                            std::ostringstream bounceCount3str;

                            // Sending a number as a stream into output
                            // string
                            bounceCount3str << bounceCount3;

                            // the str() converts number into string
                            std::string bounceScore3str = bounceCount3str.str();

                            bounceScore3.setString(bounceScore3str);

                        }
                    }
                    else if (bounceCount2 < 9)
                    {
                        bounceCountA = 0;
                        bounceCount2 += 1;
                        // declaring output string stream
                        std::ostringstream bounceCount2str;

                        // Sending a number as a stream into output
                        // string
                        bounceCount2str << bounceCount2;

                        // the str() converts number into string
                        std::string bounceScore2str = bounceCount2str.str();

                        bounceScore2.setString(bounceScore2str);
                    }
                }
            */

            /*if the direction variable is < 50
            if (randDirection < 50)
            {
                //change to be above 50
                randDirection = 100;
            }
            //else if the direction variable is > 50
            else if (randDirection > 50)
            {
                //change to be below 50
                randDirection = 1;
            }
        }



                //run x direction
                if (randDirection <= 50)
                {
                    playerMoveRangeX = -20;
                }
                else if (randDirection >= 49)
                {
                    playerMoveRangeX = 20;
                }
                else
                {
                    playerMoveRangeX = 0;
                }

                //run y direction
                if (randDirection >= 50)
                {
                    playerMoveRangeY = -20;
                }
                else if (randDirection <= 49)
                {
                    playerMoveRangeY = 20;
                }
                else
                {
                    playerMoveRangeY = 0;

                }



            playerSprite.setPosition(sf::Vector2f(currentPlayerPositionX + playerMoveRangeX, currentPlayerPositionY + playerMoveRangeX));
            */
        }
        
       
        
        if (currentState == GAME_OVER)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                currentState = RUNNING;
                stickSpriteVector.clear();
                gameTimer.restart();
                playerSprite.setPosition(sf::Vector2f(0.0f + (400.0f + playerTexture.getSize().x / 2.0f), 400.0f + (playerTexture.getSize().y / 2.0f)));

            }

            //Check if player is colliding with sticks
            //TODO: Next week

        }


        scoreValue3.setPosition(180.0f, 0.0f);
        scoreValue2.setPosition(210.0f, 0.0f);
        scoreValue1.setPosition(240.0f, 0.0f);
        //Setting score values per frame
        //Loop to check current score
       

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

        //score counter UI
        window.draw(scoreValue1);
        window.draw(scoreValue2);
        window.draw(scoreValue3);


        window.draw(gameTitle);
        window.draw(timerText);

        if (!currentState)
        {
            window.draw(gameOverText);
            window.draw(restartText);

        }
        //display
        window.display();

#pragma endregion
        //end drawing
   
        
        
    }

    return 0;
}