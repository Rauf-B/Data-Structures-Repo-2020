#include <SFML/Graphics.hpp>
#include <iostream>
#include "Header.h"

int main()
{
    int y = 0;
    cout << "PLEASE ENTER THE NUMBER OF PLAYERS FOR THIS GAME (2-5)\n";
    cin >> y;
    if (y < 2 || y > 5) {
        while (y < 2 || y > 5) {
            cout << "WRONG CHOICE ENTERED. 2-5 PLAYERS ALLOWED ONLY!\n";
            cin >> y;
        }
    }

    GUI g1;
    RenderWindow window(sf::VideoMode(1100, 1100), "2D - Monopoly");
    Board game;
    Sprite* temp;
    int player_no = y;
    Player* p1 = new Player[player_no];



     //public static int of class player
    for (int i = 0; i < player_no; i++) {
        p1[i].player_sprite.setPosition(Vector2f(882, 95));
    }

    //p1[1].player_sprite.setPosition(Vector2f(882, 95));
    //player_sprite.setPosition(Vector2f(882, 699));
    temp = game.getSprites();
    for (int i = 0; i < game.getX(); i++) {
        window.draw(temp[i]);
    }
    for (int i = 0; i < player_no; i++) {
        window.draw(p1[i].getPlayerSprite());
    }
    window.display();
    game.loadPropertyInfo();
    Property* data = game.getPropertyData();




    //implement a bit of movement
    //Vector2f adj = temp[2].getPosition();
    while (window.isOpen()) {
        Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == Event::MouseButtonPressed) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    Vector2i pos = Mouse::getPosition();
                    if (pos.x >= 1440 && pos.x <= 1478) {
                        if (pos.y >= 45 && pos.y <= 119) {
                                game.checkIsBankrupt(p1, player_no);
                                int dice = Board::generateDiceNumber();
                                game.checkTurn(player_no);
                                int temp1 = game.getActiveTurn();
                                game.checkIsInJail(p1, temp1);
                                cout << "NOTIFICATION: Player " << p1[temp1].getPlayerID() << " has rolled the dice and got number " << dice << "!" << endl;
                                Movement::move(temp, p1, window, dice, 3, temp1, player_no); //replace with dice
                                g1.displayGUI(p1[temp1], data, p1);
                                //this condition needs drawing
                                if (Board::checkJail(p1[temp1])) {
                                    p1[temp1].setJailedOnTurn(game.getActiveTurn());
                                    for (int i = 0; i < game.getX(); i++) {
                                        window.draw(temp[i]);
                                    }
                                    for (int i = 0; i < player_no; i++) {
                                        window.draw(p1[i].getPlayerSprite());
                                    }
                                    window.display();
                                }
                                game.incrementTurn();
                        }
                    }

                    if (pos.x >= 1406 && pos.x <= 1478) {
                        if (pos.y >= 235 && pos.y <= 358) {
                            game.viewPlayerInfoGUI(p1, player_no);
                        }
                    }

                   // cout << pos.x << " " << pos.y << endl;
                    //cout << p1[0];

                }

                else if (Mouse::isButtonPressed(Mouse::Right)) {    
                    Vector2i pos = Mouse::getPosition();
                   // cout << pos.x << " " << pos.y << endl;
                }
            }
            if (evnt.type == evnt.Closed) {
                window.close();
            }
        }
    }

    return 0;
}
