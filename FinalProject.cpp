
/************************
Student Name:           Bikramjeet Singh
Student No:				040955651
Assignment name:		Memory Game
Course Name and Number:	C++ Programming  CST8219
Lab Section:			302
Professor Name:         Eric Torunski
Due Date:				7th August 2020
Submission Date:		7th August 2020
File:                   FinalProject.cpp
***********************/
using namespace std;
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "buttons.h"


using namespace sf;

#define ROW             5                   // number of row
#define COL             4                   // number of col
#define MATCH_NUM      (ROW * COL / 2)      // number of matched card
#define CARD_NUM       (ROW * COL)          // totalnumber of card


// Game Objects

// sf
const sf::Color colorArray[MATCH_NUM] = { Color::Cyan, Color::Blue, Color::Green, Color::Red,
                                 Color::Yellow, Color::Magenta, Color::Color(200, 100, 100),
                                 Color::Color(100, 200, 100), Color::Color(100, 100, 200),
                                 Color::Color(100, 100, 100)
};

const sf::String strCardName[MATCH_NUM] = { "res/card/1.png", "res/card/2.png" , "res/card/3.png" , 
                                        "res/card/4.png" , "res/card/5.png" , "res/card/6.png",
                                        "res/card/7.png" , "res/card/8.png" , "res/card/9.png",
                                        "res/card/10.png" ,
};

const Color backgroudColor = Color::Color(1, 30, 208);

//RenderWindow window(VideoMode(410, 470), "Cards Game");
RenderWindow window(VideoMode(340, 570), "Bikramjeet Singh Cards Game");
RectangleShape shape(Vector2f(50, 80));
Event event;
Text timetext, numclicktext, foundtext, wontext;
Font font;
Clock clockk;
Music musicClick, musicMatch, musicEnd;
Button btnAgain, btnQuit;
// std
vector<pair<double, double > >allpos;
vector<int> randcols;
vector<int> check(CARD_NUM, 0);
vector<int> fin(CARD_NUM, 0);

Texture texture, textureBackground;
Sprite  sCard, sCardBackground;
Texture texture0[MATCH_NUM];
Sprite  sCard0[MATCH_NUM];

double incx = 0.0, incy = 0.0;
int numclick = 0, curvis = 0, found = 0, countup = 0;
bool bClick;
bool bMatch;
/*************************************************
*  drawBackground
**************************************************/
void drawBackground() {
    sf::Texture texture;

    if (!texture.loadFromFile("background.png"))
        return;
    sf::Sprite sprite(texture);

    // Draw the sprite
    window.draw(sprite);
}

/***********************************************************
* gen
*  Function to Genrate shapes
************************************************************/
void gen(int ex, int wy)
{
    for (int x = 0; x < ex; x++)
    {
        for (int y = 0; y < wy; y++)
        {
            allpos.push_back(make_pair(40.f + incx, 40.f + incy));
            incx += 70.0;
        }

        incx = 0.0;
        incy += 100.0;
    }
}

/***********************************************************
* Init
*  Function to do process before the game loop start
************************************************************/
int Init()
{
    randcols.clear();
    
    // genrate random colors indcies
    for (int y = 0; y < 2; y++)
        for (int x = 0; x < MATCH_NUM; x++) randcols.push_back(x);
    
    srand(unsigned(time(0)));

    random_shuffle(randcols.begin(), randcols.end());

    // generate board
    gen(ROW, COL);

    if (!font.loadFromFile("font.ttf")) return -1;
    if (!musicClick.openFromFile("click.ogg")) return -1;
    if (!musicMatch.openFromFile("match.ogg")) return -1;
    if (!musicEnd.openFromFile("end.ogg")) return -1;

    bClick = false;
    bMatch = false;


    check.clear();
    fin.clear();

    for (int i = 0; i < CARD_NUM; i++) {
        check.push_back(0);
        fin.push_back(0);
    }

    found = 0;
    numclick = 0;
    curvis = 0; found = 0; countup = 0;
}

/***********************************************************
* drawShape
*  Function to draw shapes
************************************************************/
void drawShape()
{
    drawBackground();
    
    for (int i = 0; i < CARD_NUM; i++)
    {
        
        // check whether card is matched or is clicked
        if (check[i] || fin[i]) {
            //shape.setPosition(allpos[i].first, allpos[i].second);
            //shape.setFillColor(colorArray[randcols[i]]);
            //shape.setOutlineColor(Color::White);
            //shape.setOutlineThickness(2.0f);
            //window.draw(shape);

            sCard0[randcols[i]].setPosition(allpos[i].first, allpos[i].second);
            window.draw(sCard0[randcols[i]]);

            if (fin[i]) {
                sCardBackground.setPosition(allpos[i].first-2, allpos[i].second-2);
                window.draw(sCardBackground);
            }

            
        }
        else {
            sCard.setPosition(allpos[i].first, allpos[i].second);
 
            window.draw(sCard);
        }

    }

}

/***********************************************************
* twoCards
*  Function to know if the two cards are the same or not
* param: int
************************************************************/
void twoCards(int i)
{

    curvis = 0;
    
    for (int ii = 0; ii < CARD_NUM; ii++)
    {
        // check if the two cards are the same
        if (check[ii] && ii != i)
        {
            if (colorArray[randcols[i]] != colorArray[randcols[ii]])
                check[i] = 0, check[ii] = 0;
            else {
                fin[i] = 1, fin[ii] = 1, found++;
                bMatch = true;
            }
        }
        else if (check[ii] && ii == i) check[i] = 0, check[ii] = 0;
    }

}

/***********************************************************
* clickOnCard
*   Function to trace the cards when clicked on them
************************************************************/
void clickOnCard()
{
    double ex = event.mouseButton.x;
    double wy = event.mouseButton.y;
    
    for (int i = 0; i < CARD_NUM; i++)
    {
        // the click is on card
        if (ex >= allpos[i].first && ex <= allpos[i].first + 50 &&
            wy >= allpos[i].second <= wy && wy <= allpos[i].second + 100)
        {
            
            // when the card is not matched
            if (!fin[i] ) {
               
                bClick = true;
                //shape.setPosition(allpos[i].first, allpos[i].second);
                //shape.setFillColor(colorArray[randcols[i]]);
                check[i] = 1;

                //window.draw(shape);

                sCard0[randcols[i]].setPosition(allpos[i].first, allpos[i].second);
                window.draw(sCard0[randcols[i]]);

                numclick++;
                curvis++;
            }
            
            // two cards clicked
            if (curvis == 2)
            {
                //bClick = false;
                window.clear();
                drawBackground();
                drawShape();
                
                window.display();
                // wait one second then call twoCards
                sleep(milliseconds(1000));
                twoCards(i);
            }

            break;
        }
    }
}

/***********************************************************
* gameOverScreen
*   Show the Game Over and Number of Moves
*     and play again, quit buttons
************************************************************/
void gameOverScreen()
{
    string cl = "MOVES: " + to_string(numclick);
    
    bClick = false;
    bMatch = false;

    musicClick.pause();
    musicMatch.pause();

    sleep(milliseconds(1000));

    musicEnd.play();
    window.clear();

    drawBackground();
   
    wontext.setFont(font);
    wontext.setString("GAME OVER");
    wontext.setColor(sf::Color::Yellow);
    wontext.setCharacterSize(60);
    wontext.setPosition(50.f, 100.f);
    window.draw(wontext);
    
    // Number of clicks
    numclicktext.setFont(font);
    numclicktext.setString(cl);
    numclicktext.setColor(Color::Yellow);
    numclicktext.setCharacterSize(50);
    numclicktext.setPosition(80.f, 200.f);
    window.draw(numclicktext);

    // Draw buttons
    window.draw(btnAgain.Sprite);
    window.draw(btnAgain.Label);
    window.draw(btnQuit.Sprite);
    window.draw(btnQuit.Label);

}

/*
* loadCardImages
*   Load the Images used in the card game
*/
void loadCardImages() {
    // card texture load
    if (!texture.loadFromFile("card.png"))
        return ;

    // set card sprite
    sCard.setTextureRect(IntRect(0, 0, 50, 80));
    sCard.setTexture(texture, false);
    // card background texture load
    if (!textureBackground.loadFromFile("res/card/background.png"))
        return;

    // set background card sprite
    sCardBackground.setTextureRect(IntRect(0, 0, 55, 85));
    sCardBackground.setTexture(textureBackground, false);


    for (int i = 0; i < MATCH_NUM; i++) {
        // card figure texture load
        if (!texture0[i].loadFromFile(strCardName[i]))
            return;
        
        // set figure card sprite
        sCard0[i].setTextureRect(IntRect(0, 0, 50, 80));
        sCard0[i].setTexture(texture0[i], false);
    }
}

int main()
{
    bool flag = true;
    Time second(milliseconds(0));

    loadCardImages();
    Init();

    // Create buttons 
    btnAgain.setLabel("Play Again"); // Has to run before button is creaated
    btnAgain.Create();
    btnAgain.setPosition(110.f, 300.f);

    btnQuit.setLabel("Quit"); // Has to run before button is creaated
    btnQuit.Create();
    btnQuit.setPosition(110.f, 390.f);
    

    while (window.isOpen())
    {
        window.clear();
        
        // play mode
        if (flag) {
            drawBackground();
            drawShape();
        }
        
        // number of matched card is MATCH_NUM
        if (found == MATCH_NUM) { 
            flag = false;
            gameOverScreen();
        }
        
        // card is clicked 
        if (bClick)
        {
            musicMatch.pause();
            musicClick.setPlayingOffset(second);
            musicClick.play();
            bClick = false;
        }

        // two card is matched
        if (bMatch) {
            musicClick.pause();
            musicMatch.setPlayingOffset(second);
            musicMatch.play();
            bMatch = false;

        }
      
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == Mouse::Left) {
                
                // play mode
                if (flag) clickOnCard();
                
                // playAgain button is clicked
                if ( !flag && btnAgain.isPressed(2) == true) {
                    Init();
                    flag = true;
                }
                // quit button is clicked
                if (!flag && btnQuit.isPressed(2) == true) {
                    window.close();
                }
            }

            if (event.type == sf::Event::MouseMoved) { // When mouse is moved
                // Handle elements
                if (btnAgain.withinBounds(event.mouseMove.x, event.mouseMove.y) == true) {}
                if (btnQuit.withinBounds(event.mouseMove.x, event.mouseMove.y) == true) {}
            }
           
        }

        window.display();
    }
    
    return EXIT_SUCCESS;
}
