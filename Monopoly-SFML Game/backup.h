/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include "board.h"
using namespace sf;
using namespace std;
int main()
{
    RenderWindow window(sf::VideoMode(1100, 1100), "2D - Monopoly");
    Texture oogabooga;
    oogabooga.loadFromFile("player_piece.png");
    Sprite player;
    player.setTexture(oogabooga);
    player.setPosition(Vector2f(940, 91));
    Texture board;
    Texture bg;
    bg.loadFromFile("green_background.jpg");
    board.loadFromFile("board.jpg");
    Sprite board_s;
    Sprite bg_s;
    board_s.setTexture(board);
    bg_s.setTexture(bg);
    board_s.move(Vector2f(100, 30));
    window.draw(bg_s);
    window.draw(board_s);
    window.draw(player);
    window.display();


    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == sf::Event::MouseButtonPressed) {
                if (Mouse::isButtonPressed(Mouse::Button::Left)) {
                    Vector2i mouse_pos = Mouse::getPosition(window);
                    cout << "X: " << mouse_pos.x << endl;
                    cout << "Y: " << mouse_pos.y << endl;
                }

                else if (Mouse::isButtonPressed(Mouse::Button::Right)) {

                    for (int i = 0; i < 10; i++) {
                        player.move(Vector2f(0, 75));
                        window.draw(bg_s);
                        window.draw(board_s);
                        window.draw(player);
                        window.display();
                        Time t1 = sf::seconds(0.75);
                        sleep(t1);
                        Vector2f pos = player.getPosition();
                        cout << "X COORD: " << pos.x << " | " << "Y COORD: " << pos.y << endl;
                    }
                }
            }
            if (evnt.type == sf::Event::Closed) {
                window.close();
            }
        }
    }


    return 0;
}


*/

/*Button* b_ptr = new Button[4];
	float x = 120;
	float y = 100;
	b_ptr[0].setSize(400, 75);
	b_ptr[0].createButton();
	b_ptr[0].setButtonPosition(Vector2f(x-70, y));
	y += 100;

	for (int i = 1; i < 4; i++) {
		b_ptr[i].setSize(250, 50);
		b_ptr[i].createButton();
		b_ptr[i].setButtonPosition(Vector2f(x, y));
		y += 100;
	}
    for (int i = 0; i < 4; i++) {
		window1.draw(b_ptr[i].getClickable());
	}
    
    
    */


/*Property::Property() {
	price = -1;
    ownedBy=-1;
	isPurchased = NULL;
	isMortgaged = NULL;
	mortgage = -1.0;
	isUtility = NULL;
	rent = -1;
	property_name = nullptr;
	group = nullptr;
	pos.x = 0;
	pos.y = 0;
	propertyID = -1;
}

void Property::setPrice(int p) {
	price = p;
}

void Property::setRent(int r) {
	rent = r;
}

void Property::setPropertyID(int pID) {
	propertyID = pID;
}

void Property::setMortgage(float m) {
	mortgage = m;
}

void Property::setPos(sf::Vector2f pos1) {
	pos.x = pos1.x;
	pos.y = pos1.y;
}

void Property::setPropertyName(char* pn) {
	property_name = pn;
}

void Property::setPropertyGroup(char* pg) {
	group = pg;
}

void Property::setIsUtility(bool f) {
	isUtility = f;
}

int Property::getPrice() {
	return price;
}

int Property::getRent() {
	return rent;
}

sf::Vector2f Property::getPos() {
	return pos;
}

bool Property::getIsUtility() {
	return isUtility;
}

int Property::getPropertyID() {
	return propertyID;
}

char* Property::getPropertyName() {
	return property_name;
}

char* Property::getPropertyGroup() {
	return group;
}

int Property::getTotalPropertySize() {
	return total_properties;
}

Property::~Property(){
	price = -1;
	isPurchased = NULL;
	isMortgaged = NULL;
	mortgage = -1.0;
	isUtility = NULL;
	rent = -1;
	group = nullptr;
	pos.x = 0;
	pos.y = 0;
	property_name = nullptr;
	propertyID = -1;
}
*/


/*else if (Mouse::isButtonPressed(Mouse::Right)){
					adj.y = adj.y + 5;
					header_text[1].setPosition(adj);
					main_window.draw(gui_sprite);
					main_window.draw(gui_head);
					for (int i = 0; i < no_of_buttons; i++) {
						main_window.draw(buttons[i]);
						main_window.draw(main_text[i]);
					}
					main_window.draw(header_text[0]);
					main_window.draw(header_text[1]);
					main_window.display();
					cout << adj.x << " " << adj.y << endl;
				}*/

				/*Texture player_tex;
				   player_tex.loadFromFile("player.png");
				   Sprite player_sprite;
				   player_sprite.setTexture(player_tex);*/