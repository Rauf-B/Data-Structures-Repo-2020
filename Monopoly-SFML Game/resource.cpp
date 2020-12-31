#include "Header.h"
#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>

int Player::id_count = 0;
int Player::no_of_players = 1;
Player::Player() {
	jailed_on_turn = -191312;
	playerID = id_count;
	money = 5000;
	property_count = 0;
	ownedProperties = nullptr;
	id_count++;
	player_tex.loadFromFile("player.png");
	player_sprite.setTexture(player_tex);
	isBankrupt = false;
	isInJail = false;
}

int Player::getPlayerID() {
	return playerID;
}

int Player::getPlayerMoney() {
	return money;
}

void Player::setMoney(int x) {
	money = x;
}

void Player::increasePropertyCount() {
	property_count++;
}

Player::~Player() {
	playerID = -10000;
	money = -100000;
	property_count = -10000;
	ownedProperties = nullptr;
	id_count = -1000;
}

Sprite Player::getPlayerSprite() {
	return player_sprite;
}

Vector2f Player::getPosition() {
	return player_sprite.getPosition();
}

Property* Player::getOwnedProperties() {
	return ownedProperties;
}

int Player::getPropertyCount() {
	return property_count;
}

void Player::addNewProperty(Property p) {
	Property* temp = ownedProperties;
	ownedProperties = nullptr;
	increasePropertyCount();
	ownedProperties = new Property[property_count];
	for (int i = 0; i < property_count-1; i++) {
		ownedProperties[i] = temp[i]; //OK
	}

	ownedProperties[property_count-1] = p;
	
	cout << "NOTIFICATION: New property has been added in the ownership of the player.\n";
}

void Player::setBankruptcy() {
	isBankrupt = true;
}

bool Player::getBankruptcy() {
	return isBankrupt;
}

void Player::upgradePropertyFinancials(Property p1) {
	int temp = p1.getPropertyID();
	for (int i = 0; i < property_count; i++) {
		if (ownedProperties[i].getPropertyID() == temp) {
			ownedProperties[i] = p1;
			return;
		}
	}
}

bool Player::getIsInJail() {
	return isInJail;
}

void Player::setIsInJail(bool flag) {
	isInJail = flag;
}

void Player::setJailedOnTurn(int x) {
	jailed_on_turn = x;
}

int Player::getJailedOnTurn() {
	return jailed_on_turn;
}


void Player::downgradePropertyFinancials(Property p1) {
	int j = 0;
	Property* data = ownedProperties;
	bool found = false;
	delete[]ownedProperties;
	ownedProperties = nullptr;
	int index = 0;
	for (int i = 0; i < property_count && found == false; i++) {
		if (p1.getPropertyID() == data[i].getPropertyID()) {
			index = i;
			found = true;
		}
	}
	Property* temp = new Property[property_count - 1];
	//TWO CASES.
	if ((property_count - 1) == 0){
		cout << "NOTIFICATION: " << playerID << " has no more properties left!\n";
		property_count = 0;
		return;
	}
	else {
		
		if ((property_count - 1) == index) {
			for (int i = 0; i < index; i++) {
				temp[i] = data[i];
			}
		}
		else {
			for (int i = 0; i < property_count; i++) {
				if (i == index) {

				}
				else {
					temp[j] = data[i];
					j++;
				}

			}
		}
		ownedProperties = temp;
		property_count = j;
	}
}




ostream& operator << (ostream& out, Player obj) {
	Property* temp = obj.getOwnedProperties();
	cout << "PLAYER INFO\n";
	cout << "PLAYER ID: " << obj.getPlayerID() << endl;
	cout << "PLAYER MONEY: " << obj.getPlayerMoney() << endl;
	cout << "Properties Owned: " << endl;
	for (int i = 0; i < obj.getPropertyCount(); i++) {
		cout << temp[i].getPropertyName() << " " << temp[i].getRent() << endl;
	}
	return out;
}

void Movement::move(sf::Sprite* main_sprite, Player* player, sf::RenderWindow& window, int n, int c, int t, int pn) {
	Vector2f temp_pos;
	temp_pos = player[t].getPosition();
	if (temp_pos.y < 850 && temp_pos.x == 882) {
		moveDown(main_sprite, player, window, n, c, t, pn);
	}
	else if (temp_pos.y == 850 && temp_pos.x > 107) {
		moveLeft(main_sprite, player, window, n, c, t, pn);
	}
	else if (temp_pos.x == 107 && temp_pos.y > 95) {
		moveUp(main_sprite, player, window, n, c, t, pn);
	}

	else if (temp_pos.y == 95 && temp_pos.x < 882) {
		moveRight(main_sprite, player, window, n, c, t, pn);
	}

}

void Movement::moveDown(sf::Sprite* main_sprite, Player* player, sf::RenderWindow& window, int n, int c, int t, int pn) {
	for (int i = 0; i < n; i++) {
		sf::Vector2f pos = player[t].getPosition();
		//850 is the position of jail.
		if (pos.y == 850) {
			moveLeft(main_sprite, player, window, (n - i), c, t, pn);
			return;
		}
		//player.move(sf::Vector2f(0, 75.5));
		player[t].player_sprite.move(Vector2f(0, 75.5));
		for (int j = 0; j < c; j++) {
			window.draw(main_sprite[j]);
		}
		for (int i = 0; i < pn; i++) {
			window.draw(player[i].player_sprite);
		}
		sf::Time t1 = sf::seconds(0.75);
		sf::sleep(t1);
		window.display();
		//cout << pos.x << " " << pos.y << endl;
	}


}

void Movement::moveLeft(sf::Sprite* main_sprite, Player* player, sf::RenderWindow& window, int n, int c, int t, int pn) {
	for (int i = 0; i < n; i++) {
		sf::Vector2f pos = player[t].getPosition();
		if (pos.x == 107 && pos.y == 850) {
			moveUp(main_sprite, player, window, (n - i), c, t, pn);
			return;
		}
		player[t].player_sprite.move(sf::Vector2f(-77.5, 0));
		for (int j = 0; j < c; j++) {
			window.draw(main_sprite[j]);
		}
		for (int i = 0; i < pn; i++) {
			window.draw(player[i].player_sprite);
		}
		sf::Time t1 = sf::seconds(0.75);
		sf::sleep(t1);
		window.display();
		//cout << pos.x << " " << pos.y << endl;
	}

}

void Movement::moveUp(sf::Sprite* main_sprite, Player* player, sf::RenderWindow& window, int n, int c, int t, int pn) {
	for (int i = 0; i < n; i++) {
		sf::Vector2f pos = player[t].getPosition();
		if (pos.y == 95) {
			moveRight(main_sprite, player, window, (n - i), c, t, pn);
			return;
		}
		player[t].player_sprite.move(Vector2f(0, -75.5));
		for (int j = 0; j < c; j++) {
			window.draw(main_sprite[j]);
		}
		for (int i = 0; i < pn; i++) {
			window.draw(player[i].player_sprite);
		}
		sf::Time t1 = sf::seconds(0.75);
		sf::sleep(t1);
		window.display();
		//cout << pos.x << " " << pos.y << endl;
	}
}

void Movement::moveRight(sf::Sprite* main_sprite, Player* player, sf::RenderWindow& window, int n, int c, int t, int pn) {
	for (int i = 0; i < n; i++) {
		sf::Vector2f pos = player[t].getPosition();
		if (pos.y == 95 && pos.x == 882) {
			moveDown(main_sprite, player, window, (n - i), c, t, pn);
			return;
		}
		player[t].player_sprite.move(sf::Vector2f(77.5, 0));
		for (int j = 0; j < c; j++) {
			window.draw(main_sprite[j]);
		}
		for (int i = 0; i < pn; i++) {
			window.draw(player[i].player_sprite);
		}
		sf::Time t1 = sf::seconds(0.75);
		sf::sleep(t1);
		window.display();
		//cout << pos.x << " " << pos.y << endl;
	}

}


Board::Board() {
	turn = 0;
	main_tex = nullptr;
	main_sprite = nullptr;
	main_tex = new Texture[3];
	main_sprite = new Sprite[3];
	higher_turn = 0;
	int j = 0;

	main_tex[0].loadFromFile("green_background.jpg");
	main_tex[1].loadFromFile("board.jpg");
	main_tex[2].loadFromFile("util.jpg");

	for (int i = 0; i < x; i++) {
		main_sprite[i].setTexture(main_tex[i]);
	}
	main_sprite[1].move(Vector2f(50, 50)); //set the position
	main_sprite[2].move(Vector2f(950, 10));
	Vector2f test = main_sprite[1].getPosition();
	cout << "GAME PROCESS: Board has been created..\n";
	data = nullptr;
}

int Board::getX() {
	return x;
}

Sprite* Board::getSprites() {
	return main_sprite;
}


Board::~Board() {
	delete[]main_tex;
	delete[]main_sprite;
	main_tex = nullptr;
	main_sprite = nullptr;
}

void Board::loadPropertyInfo() {
	float x = 0.0, y = 0.0;
	ifstream fin;
	data = new Property[Property::getTotalPropertySize()];
	fin.open("propertylisting.txt");
	if (fin) {
		for (int i = 0; i < Property::getTotalPropertySize(); i++) {
			int a = 0, b = 0;
			char* str = new char[999];
			char* str1 = new char[999];

			fin >> a;
			data[i].setPropertyID(a);
			fin >> str;
			data[i].setPropertyName(str);
			fin >> a;
			data[i].setPrice(a);
			fin >> a;
			data[i].setRent(a);
			fin >> a;
			data[i].setIsUtility(a);
			fin >> str1;
			data[i].setPropertyGroup(str1);
			fin >> x;
			fin >> y;
			data[i].setPos(sf::Vector2f(x, y));
		}
	}
	else {
		cout << "ERROR: propertylisting.txt could not be opened.\n";
	}
}

int Board::generateDiceNumber() {
	int x = 0;
	srand((unsigned)time(0));
	while (x > 6 || x == 0) {
			x = (rand() % 10) + 1;

	}
	return x;
}

int Board::searchPropertyByPos(Vector2f target_pos, Property* data) {
	int index = -1;
	for (int i = 0; i < Property::getTotalPropertySize(); i++) {
		if (data[i].getPos() == target_pos) {
			index = i;
			return index;
		}
	}
	//introduce a condition in the function value being returned to check if index is -1. -1 means error.
	return index;
}

void Board::displayGUI(Sprite player, Property* data) {
	Vector2f target_pos = player.getPosition();
	int index = Board::searchPropertyByPos(target_pos, data);
	char* str = data[index].getPropertyName();
	int size = 18;
	float x = 122, y = 10;
	RenderWindow window1(sf::VideoMode(413, 500), str);
	Text* txt = new Text[2];
	RectangleShape c1;
	Font f_main;
	f_main.loadFromFile("arial.ttf");
	for (int i = 0; i < 2; i++) {
		txt[i].setFont(f_main);
		txt[i].setFillColor(Color::Black);
		txt[i].setCharacterSize(size);
		txt[i].Bold;
		txt[i].setPosition(c1.getPosition());
		txt[i].move(x, y);
		size += 5;
		y += 45;
	}
	txt[0].setString("TITLE DEED");
	txt[1].setString(str);

	Texture bg;
	bg.loadFromFile("gui_bg.jpg");
	Sprite gui;
	gui.setTexture(bg);
	window1.draw(gui);
	window1.draw(c1);
	for (int i = 0; i < 2; i++)
		window1.draw(txt[i]);
	window1.display();

	while (window1.isOpen()) {
		Event evnt;
		while (window1.pollEvent(evnt)) {
			if (evnt.type == Event::MouseButtonPressed) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					Vector2i pos = Mouse::getPosition();
					cout << "X: " << pos.x << "\n" << "Y: " << pos.y << "\n";
				}
			}
			if (evnt.type == evnt.Closed) {
				window1.close();
			}
		}
	}
}

Property* Board::getPropertyData() {
	return data;
}

void Board::checkTurn(int pn) {
	if (turn >= pn) {
		higher_turn++;
		turn = 0;
		//cout << "NOTIFICATION: Turn resetted to player 1" << endl;
	}
}

int Board::getActiveTurn() {
	return turn;
}

void Board::incrementTurn() {
	turn++;
}

void Board::viewPlayerInfoGUI(Player* arr, int player_no) {
	//Evaluate the number of players and decide the spacing accordingly.
	int spacing = 0;
	int text_spacing = 0;

	switch (player_no) {
	case 2:
		spacing = 500;
		break;
	case 3:
		spacing = 300;
		break;
	case 4:
		spacing = 250;
		break;
	case 5:
		spacing = 170;
		break;
	default:
		spacing = 170;
	}
	float x = 50, y = 50;
	RectangleShape* ptr = new RectangleShape[player_no];

	for (int i = 0; i < player_no; i++) {
		ptr[i].setSize(Vector2f(150, 50));
		ptr[i].setFillColor(Color::White);
		ptr[i].setOutlineColor(Color::Black);
		ptr[i].setOutlineThickness(1);
		ptr[i].setPosition(Vector2f(x, y));
		ptr[i].setFillColor(Color::Blue);
		x = x + spacing;
	}

	RectangleShape test;
	int no = 1;
	int info_count = player_no * 3;
	Font main;
	main.loadFromFile("arial.ttf");
	Text* text_ptr = new Text[player_no];
	Text* info_ptr = new Text[info_count];
	Text* title_ptr = new Text[info_count];
	for (int i = 0; i < player_no; i++) {
		text_ptr[i].setCharacterSize(20);
		text_ptr[i].setFont(main);
		text_ptr[i].setFillColor(Color::White);
		text_ptr[i].Bold;
		text_ptr[i].setString("Player " + to_string(no));
		text_ptr[i].setPosition(ptr[i].getPosition());
		no++;
	}
	//add information regarding the player HERE.
	Vector2f* initial_pos = new Vector2f[player_no];
	for (int i = 0; i < player_no; i++) {
		initial_pos[i] = text_ptr[i].getPosition();
	}

	for (int i = 0; i < info_count; i++) {
		title_ptr[i].setCharacterSize(14);
		info_ptr[i].setCharacterSize(13);
		title_ptr[i].setFont(main);
		info_ptr[i].setFont(main);
		title_ptr[i].setFillColor(Color::White);
		info_ptr[i].setFillColor(Color::White);
		title_ptr[i].Bold;
		info_ptr[i].Bold;
	}

	int temp = 0;
	int limit = 1;
	for (int j = 0; j < player_no; j++) {
		text_spacing = 50;
		temp = limit;
		limit = limit * 2;
		for (int i = 0; i < 3; i++) {
			info_ptr[i].setPosition(Vector2f(initial_pos[j].x, initial_pos[j].y + text_spacing));
			text_spacing += 50;
		}
	}





	RenderWindow window;
	window.create(VideoMode(900, 600), "View Player Info");
	Texture local_tex;
	local_tex.loadFromFile("info.jpg");
	Sprite local_sprite;
	local_sprite.setTexture(local_tex);
	window.draw(local_sprite);
	for (int i = 0; i < player_no; i++) {
		window.draw(ptr[i]);
	}
	for (int i = 0; i < player_no; i++) {
		window.draw(text_ptr[i]);
	}


	window.display();


	Vector2f adj = test.getPosition();

	while (window.isOpen()) {
		Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == Event::MouseButtonPressed) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					adj.x = adj.x + 50;
					test.setPosition(adj);
					window.draw(local_sprite);
					window.draw(test);
					window.display();
					cout << adj.x << " " << adj.y << endl;
				}
				else if (Mouse::isButtonPressed(Mouse::Right)) {
					adj.y = adj.y + 50;
					test.setPosition(adj);
					window.draw(local_sprite);
					window.draw(test);
					window.display();
				}
			}

			if (evnt.type == evnt.Closed) {
				window.close();
			}
		}
	}

}

bool Board::checkJail(Player &client) {
	bool flag = false;
	Vector2f jail_pos(107, 95);
	if (client.getPosition() == jail_pos) {
		client.player_sprite.setPosition(Vector2f(882, 850));
		client.setIsInJail(true);
		cout << "NOTIFICATION: CAUGHT IN JAIL! SKIP TWO (2) TURNS NOW!\n";

		return true;
	}
	return false;

}


void Board::checkIsInJail(Player *arr, int &index) {
	bool flag = false;
	if (arr[index].getIsInJail()) {
		if ((higher_turn - arr[index].getJailedOnTurn()) == 2) {
			arr[index].setIsInJail(false);
		}
		else {
			index += 1;
			turn += 1;
			cout << "NOTIFICATION: " << arr[index].getPlayerID() << " is in jail!\n";
		}
	}
}

bool Board::checkMisc(Player& client) {
	Vector2f temp = client.player_sprite.getPosition();
	if (!(temp.x == 882 && temp.y == 397)) {
		return false;
	}
	else {
		cout << client;
		int x = 0;
		Property* arr = client.getOwnedProperties();

		if (client.getPropertyCount() == 0) {
			cout << "NOTIFICATION: No properties to deduct tax from!" << endl;
			return true;
		}

		else {
			for (int i = 0; i < client.getPropertyCount(); i++) {
				x = arr[i].getPrice() + x;
			}

			x = 0.20 * x;

			if (temp.x == 882 && temp.y == 397) {
				cout << "INITIAL MONEY " << client.getPlayerMoney() << endl;
				client.setMoney(client.getPlayerMoney() - x);
				cout << "AFTER DEDUCTION " << client.getPlayerMoney() << endl;
				cout << "NOTIFICATION: Land Tax of " << x << " has been deducted from Player " << client.getPlayerID() << endl;
			}
		}
		return true;
	}

}
	
void Board::checkPlayerBankruptcy(Player& client, Property& target, int cash) {
	if (client.getPlayerMoney() == 0) {
		if (client.getPropertyCount() == 0) {
			client.setBankruptcy(); //sets bankruptcy for a person with no property and no money.
		}
		cout << "Player " << client.getPlayerID() << " has no money and no property. Player is now bankrupt!\n";
		return;
	}
	int x = 0;
	int y = 0;
	Property* temp = client.getOwnedProperties();
	int i = 0;
	int h = 0;
	//IF HAS PROPERTY
	while (client.getPropertyCount() > 0){
		h = client.getPropertyCount();
		//check and sell property one by one and then compare
		x = temp[i].getPrice();
		y = temp[i].getHouseNumber();
		if (y > 0) {
			x = x + (y * 100);
			client.setMoney(x);
			//downgrade property financials
			client.downgradePropertyFinancials(target);
			target.setOwnerID(-1231); //reset ownedship
		}
		else {
			client.setMoney(x);
			client.downgradePropertyFinancials(target);
			cout << client;
			target.setOwnerID(-1231);
		}
		i++;
		
	}


}

bool Board::checkParking(Player& client) {
	Vector2f pos(107, 95);
	if (client.getPosition() == pos) {
		return true;
	}

	return false;
}


void Board::removePlayer(int id, Player* &clients, int& size){
	Player* arr = nullptr;
	arr = clients;
	int index = 123;
	int j = 0;
	clients = nullptr;
	clients = new Player[size - 1];
	for (int i = 0; i < size; i++) {
		if (arr[i].getPlayerID() == id) {
			index = i;
		}
	}

	for (int i = 0; i < size; i++) {
		if (i == index) {

		}
		else {
			clients[j] = arr[i];
			j++;
		}
	}
	size = size - 1;

}

void Board::checkIsBankrupt(Player*& clients, int &size) {
	for (int i = 0; i < size; i++) {
		if (clients[i].getBankruptcy()) {
			Board::removePlayer(clients[i].getPlayerID(), clients, size);
			return;
		}
	}

}

bool Board::checkPropertyTax(Player& p1) {
	Vector2f pos(727, 95);
	if (!(p1.getPosition() == pos)) {
		return false;
	}
	else {
		cout << p1;
		cout << endl;
		int y = 0, x = 0, z = 0;
		Property* temp = p1.getOwnedProperties();
		for (int i = 0; i < p1.getPropertyCount(); i++) {
			y = temp[i].getPrice() + y;
			x = temp[i].getHouseNumber() + x;
			z = int(temp[i].getShop()) + z;
		}
		y = int(y * 0.10);
		x = (x * 10) * 0.20;
		int total = x + y + z;
		cout << "NOTIFICATION: TOTAL TAX OF " << total << " HAS BEEN DEDUCTED!\n";
		p1.setMoney(p1.getPlayerMoney() - (total));
		cout << p1;
		return true;
	}
}

bool Board::checkChance(Player& client) {
	Vector2f *positions = new Vector2f[2];
	positions[0].x = 882;
	positions[1].x = 107;
	positions[0].y = 623.5;
	positions[1].y = 774.5;

	bool found = false;

	for (int i = 0; i < 2; i++) {
		if (client.getPosition() == positions[i]) {
			found = true;
		}
	}

	if (found) {
		char** ptr = new char* [15];
		for (int i = 0; i < 15; i++) {
			ptr[i] = new char[999];
		}
		fstream fin;
		int i = 0;
		fin.open("communitychest.txt");
		if (!fin) {
			cout << "File cannot be opened!\n";
		}
		else {
			while (!fin.eof()) {
				for (int i = 0; i < 15; i++) {
				}
			}
		}
	}


	return 0;
}