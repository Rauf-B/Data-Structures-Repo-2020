#include "Header.h"
#include <iostream>

using namespace std;
GUI::GUI() {
	gui_tex.loadFromFile("gui_bg.jpg");
	gui_sprite.setTexture(gui_tex);
	buttons = new RectangleShape[no_of_buttons];
	header_text = new Text[2];
	main_text = new Text[no_of_buttons];
	main_font.loadFromFile("arial.ttf");
	for (int i = 0; i < no_of_buttons; i++) {
		main_text[i].setFont(main_font);
	}

	int x = 15;

	for (int i = 0; i < 2; i++) {
		header_text[i].setFont(main_font);
		header_text[i].setFillColor(Color::Black);
		header_text[i].setCharacterSize(x);
		x += 10;
	}

	header_text[0].setString("TITLE DEED");
	gui_head.move(17, 25);
}

void GUI::displayGUI(Player& client, Property* data, Player* arr) {
	Vector2f temp = client.player_sprite.getPosition();
	cout << temp.x << " " << temp.y << endl;
	int index = Board::searchPropertyByPos(client.player_sprite.getPosition(), data);
	//manageProperty(index, data, client);
	//cout << data[index].getRent();
	if (index == -1) {
		cout << "No Property Management Menu available for this property." << endl;
		if (Board::checkParking(client)) {
			client.setMoney(client.getPlayerMoney() - 15);
			return;
		}
		else if (Board::checkMisc(client)){
			return;
		}
		else if (Board::checkPropertyTax(client)) {
			return;
		}
		return;
	}

	if (data[index].getIsPurchased() && (data[index].getOwnerID() != client.getPlayerID())) {
		onClickPayRent(client, arr, data[index]);
	}

	//create the color header
	gui_head.setFillColor(Color::Red); //coloring by group - (NEEDS TO BE IMPLEMENTED)
	gui_head.setSize(Vector2f(375, 85));
	gui_head.setOutlineThickness(1);
	gui_head.setOutlineColor(Color::Black);
	//viewPropertyInfo(gui_head, index, data);
	createButtons(gui_head.getPosition());
	//the positions for both the text and buttons etc have been hardwired by using a code that has been attached in instructions.txt
	header_text[0].setPosition(Vector2f(152, 28));
	header_text[1].setPosition(Vector2f(142, 63));
	header_text[1].setString(data[index].getPropertyName());


	main_window.create(VideoMode(413, 500), "Property Management Menu");
	main_window.draw(gui_sprite);
	main_window.draw(gui_head);
	for (int i = 0; i < no_of_buttons-1; i++) {
		main_window.draw(buttons[i]);
		main_window.draw(main_text[i]);
	}
	Text info;
	info = main_text[3];
	info.setString("ACTIVE PLAYER: " + to_string(client.getPlayerID()));



	main_window.draw(header_text[0]);
	main_window.draw(header_text[1]);
	main_window.draw(info);
	main_window.display();

	Vector2f adj;
	adj = header_text[0].getPosition();

	while (main_window.isOpen()) {
		Event evnt;
		while (main_window.pollEvent(evnt)) {
			if (evnt.type == Event::MouseButtonPressed) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					Vector2i pos = Mouse::getPosition();
					cout << "X: " << pos.x << "\n" << "Y: " << pos.y << "\n";
					if (pos.x > (953 - 170) && pos.x < (953 + 170)) {
						if (pos.y > (481 - 25) && pos.y < (481 + 25)) {
							viewPropertyInfo(gui_head, index, data);
						}
					}

					if (pos.x > (953 - 170) && pos.x < (953 + 170)) {
						if (pos.y > (577 - 25) && pos.y < (577 + 25)) {
							//external check to see if the property belongs to the player
							if (client.getPlayerID() != data[index].getOwnerID()) {
								cout << "PROMPT: You do not own this property and hence cannot manage this property!\n";
							}
							else {
								manageProperty(index, data, client);
								main_window.close();
							}
						}
					}

					if (pos.x > (953 - 170) && pos.x < (953 + 170)) {
						if (pos.y > (663 - 25) && pos.y < (663 + 25)) {
							buyProperty(data[index], client);
							sf::Time t1 = sf::seconds(0.25);
							sf::sleep(t1);
							main_window.close();
						}
					}

					/*if (pos.x > (953 - 170) && pos.x < (953 + 170)) {
						if (pos.y > (753 - 25) && pos.y < (753 + 25)) {
							onClickPayRent(client, arr, data[index]);
							sf::Time t1 = sf::seconds(0.25);
							sf::sleep(t1);
							main_window.close();

						}
					}*/

				}
			}

			if (evnt.type == evnt.Closed) {
				main_window.close();
			}
		}
	}

}

void GUI::createButtons(Vector2f initial_pos) {
	/*There are four buttons. 1) View Property Information, Buy Property, Manage Property (access rights will be checked), Pay Fine*/
	Color button_color(0, 191, 255);
	float x = initial_pos.x, y = initial_pos.y;
	y += 95.0;
	x += 40.0;
	for (int i = 0; i < no_of_buttons; i++) {
		buttons[i].setSize(Vector2f(300, 70));
		buttons[i].setFillColor(button_color);
		buttons[i].setPosition(x, y);
		buttons[i].setOutlineThickness(1);
		buttons[i].setOutlineColor(Color::Black);
		y += 90.0;
	}

	createButtonText(buttons);
}

void GUI::createButtonText(RectangleShape* buttons) {
	for (int i = 0; i < no_of_buttons; i++) {
		main_text[i].setPosition(buttons[i].getPosition());
		main_text[i].setCharacterSize(25);
		main_text[i].Bold;
		main_text[i].setFillColor(Color::White);
	}

	main_text[0].setString("View Property Info");
	main_text[1].setString("Manage Property");
	main_text[2].setString("Buy Property");
	main_text[3].setString("Pay Rent/Fine");
}

void GUI::viewPropertyInfo(RectangleShape header, int index, Property* data) {
	RenderWindow info_gui(VideoMode(413, 500), "View Property Info");
	Texture info_tex;
	info_tex.loadFromFile("gui_bg.jpg");
	Sprite info_sprite;
	info_sprite.setTexture(info_tex);

	Text* text_ptr = new Text[3]; //answers to the sub headings
	Text* text_ptr1 = new Text[3]; //PRICE: RENT: etc
	for (int i = 0; i < 3; i++) {
		text_ptr[i].setFont(main_font);
		text_ptr[i].setCharacterSize(20);
		text_ptr[i].setFillColor(Color::Black);
		text_ptr1[i].setFont(main_font);
		text_ptr1[i].setCharacterSize(20);
		text_ptr1[i].setFillColor(Color::Black);
	}


	//ADJUST THIS PART AND MAKE IT ACCORDING TO THE GUI
	text_ptr1[0].setString("PRICE: ");
	text_ptr1[1].setString("RENT: ");
	text_ptr1[2].setString("OWNER: ");
	text_ptr[0].setString(to_string(data[index].getPrice()));
	text_ptr[1].setString(to_string(data[index].getRent()));
	text_ptr[2].setString(to_string(data[index].getOwnerID()));

	//set position through loop for each value
	float x = 50, y = 100;
	Vector2f temp = text_ptr1[0].getPosition();
	cout << temp.x << " " << temp.y << endl;
	for (int i = 0; i < 3; i++) {
		text_ptr1[i].setPosition(x, y);
		text_ptr[i].setPosition(x + 150, y);
		y += 40;
	}
	info_gui.draw(info_sprite);
	for (int i = 0; i < 3; i++) {
		info_gui.draw(text_ptr1[i]);
		info_gui.draw(text_ptr[i]);
	}
	info_gui.display();

	Vector2f adj = text_ptr1[0].getPosition();

	while (info_gui.isOpen()) {
		Event evnt;
		while (info_gui.pollEvent(evnt)) {
			if (evnt.type == Event::MouseButtonPressed) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					Vector2i pos = Mouse::getPosition();
					cout << "X: " << pos.x << "\n" << "Y: " << pos.y << "\n";
				}
			}
			if (evnt.type == evnt.Closed) {
				info_gui.close();
			}
		}
	}

}

void GUI::manageProperty(int index, Property* data, Player &client) {
	if (client.getPlayerID() != data[index].getOwnerID()) {
		cout << "PROMPT: You do not own this property and hence cannot manage this property!\n";
		return;
	}
	else {


		//check if the property is owned by the current person
		RenderWindow manage_gui(VideoMode(413, 500), "Manage Property");
		RectangleShape* local_button = new RectangleShape[6];
		Text* local_text = new Text[6];

		Texture tex;
		tex.loadFromFile("gui_bg.jpg");
		Sprite manage_sprite;
		manage_sprite.setTexture(tex);

		Color button_color(0, 191, 255);

		//add local buttons
		float x = 75, y = 25;
		const int spacing = 75;
		for (int i = 0; i < 6; i++) {
			local_button[i].setSize(Vector2f(250, 55));
			local_button[i].setFillColor(button_color);
			local_button[i].setPosition(Vector2f(x, y));
			local_button[i].setOutlineColor(Color::Black);
			local_button[i].setOutlineThickness(1);
			y += spacing;
		}
		//text assignments for button start here
		local_text[0].setString("Add House");
		local_text[1].setString("Add Shop");
		local_text[2].setString("Add Hotel");
		local_text[3].setString("Add WIFI");
		local_text[4].setString("Add Electricity");
		local_text[5].setString("Add Gas Connection");
		//fill buttons with text

		for (int i = 0; i < 6; i++) {
			local_text[i].setFont(main_font);
			local_text[i].setCharacterSize(20);
			local_text[i].setPosition(local_button[i].getPosition());
		}


		manage_gui.draw(manage_sprite);
		for (int i = 0; i < 6; i++) {
			manage_gui.draw(local_button[i]);
			manage_gui.draw(local_text[i]);
		}

		manage_gui.display();

		//add new house
		//add new hotel
		//auction

		Vector2f current_pos = local_button[0].getPosition();

		while (manage_gui.isOpen()) {


			Event evnt;
			while (manage_gui.pollEvent(evnt)) {
				if (evnt.type == Event::MouseButtonPressed) {
					if (Mouse::isButtonPressed(Mouse::Right)) {
						Vector2i pos = Mouse::getPosition();
						cout << "X: " << pos.x << "\n" << "Y: " << pos.y << "\n";
					}
					else if (Mouse::isButtonPressed(Mouse::Left)) {
					Vector2i pos = Mouse::getPosition();
					if (pos.x > (957 - 130) && pos.x < (957 + 130)) {
						if (pos.y > (380 - 20) && pos.y < (380 + 20)) {
							onClickAddHouse(client, data[index]);
							sf::Time t1 = sf::seconds(0.1);
							sf::sleep(t1);
							manage_gui.close();
						}
					}

					if (pos.x > (957 - 130) && pos.x < (957 + 130)) {
						if (pos.y > (460 - 20) && pos.y < (460 + 20)) {
							onClickAddShop(client, data[index]);
							sf::Time t1 = sf::seconds(0.1);
							sf::sleep(t1);
							manage_gui.close();
						}
					}
					//add shop and hotel

					if (pos.x > (957 - 130) && pos.x < (957 + 130)) {
						if (pos.y > (607 - 20) && pos.y < (607 + 20)) {
							onClickAddWifi(client, data[index]);
							sf::Time t1 = sf::seconds(0.1);
							sf::sleep(t1);
							manage_gui.close();
						}
					}

					if (pos.x > (957 - 130) && pos.x < (957 + 130)) {
						if (pos.y > (677 - 20) && pos.y < (677 + 20)) {
							onClickAddElectricity(client, data[index]);
							sf::Time t1 = sf::seconds(0.1);
							sf::sleep(t1);
							manage_gui.close();
						}
					}

					if (pos.x > (957 - 130) && pos.x < (957 + 130)) {
						if (pos.y > (755 - 20) && pos.y < (755 + 20)) {
							onClickAddGasConnection(client, data[index]);
							sf::Time t1 = sf::seconds(0.1);
							sf::sleep(t1);
							manage_gui.close();
						}
					}


					}
				}
				if (evnt.type == evnt.Closed) {
					manage_gui.close();
				}
			}
		}
	}

}


//need further testing of this one function

void GUI::onClickAddHouse(Player& client, Property &target) {
	if (!strcmp(target.getPropertyGroup(), "UTILITY")) {
		cout << "PROMPT: No house can be added here as this property is of the Utility/Station group!\n";
		return;
	}
	else if (!strcmp(target.getPropertyGroup(), "STATION")) {
		cout << "PROMPT: No house can be added here as this property is of the Utility/Station group!\n";
		return;
	}

	Property* data = client.getOwnedProperties();
	//fetch player owned properties and search group
	bool flag = true;
	int check = 0;
	char* str1 = target.getPropertyGroup();
	
	cout << client.getPropertyCount();

	if (!strcmp("JOHAR", target.getPropertyGroup())) {
		for (int i = 0; i < client.getPropertyCount(); i++) {
			char* str = target.getPropertyGroup();
			if (!strcmp(data[i].getPropertyGroup(), str)) {
				check++;
			}
		}
		if (check != 2) {
			flag = false;
		}
	}
	else {
		for (int i = 0; i < client.getPropertyCount(); i++) {
			char* str = target.getPropertyGroup();
			if (!strcmp(data[i].getPropertyGroup(), str)) {
				check++;
			}
		}

		if (check != 3) {
			flag = false;
		}
	}

	if (!flag) {
		cout << "PROMPT: You cannot add a house since you do not own the WHOLE group " << target.getPropertyGroup() << endl;
	}
	else {
		//if ownership over group exists, then check if houses being added are unanimous
		Property* temp = new Property[4];
		int j = 0;
		for (int i = 0; i < client.getPropertyCount(); i++) {
			if (!strcmp(data[i].getPropertyGroup(), target.getPropertyGroup())) {
				temp[j] = data[i];
				j++;
			}
		}

		//check if all houses are placed uniformly
		for (int i = 1; i < check; i++) {
			int storage = temp[i - 1].getHouseNumber();
			if (storage != temp[i].getHouseNumber()) {
				cout << "PROMPT: You cannot add another house as houses are not uniformly distributed!\n";
				return;
			}
		}

		if ((client.getPlayerMoney() - 100) < 0){
			cout << "PROMPT: Insufficient balance.\n";
			return;
		}
		else {
			client.setMoney(client.getPlayerMoney() - 100);
			target.setRent(target.getRent() + (0.30 * target.getRent()));
			target.addHouse();
			client.upgradePropertyFinancials(target);
			cout << "PROMPT: HOUSE HAS BEEN ADDED for Player no. " << client.getPlayerID() + 1 << endl;
		}
		
	}

}

void GUI::onClickAddWifi(Player &client, Property &target) {
	int temp = client.getPlayerMoney() - 30;
	if (temp < 0) {
		cout << "PROMPT: Insufficient balance, cannot add Wifi facility to the property!\n";
	}
	else {
		//check if already enabled
		if (target.isWifiEnabled()) {
			cout << "PROMPT: This feature has already been enabled!" << endl;
		}
		else {
			target.addWifi();
			int new_rent = target.getRent() + (0.10 * target.getRent());
			target.setRent(new_rent);
			cout << "NOTIFICATION: WIFI enabled for property " << target.getPropertyName() << endl;
			client.upgradePropertyFinancials(target);
			cout << target.getRent() << endl;
		}
	}
}

void GUI::onClickAddElectricity(Player &client, Property& target) {

	int temp = client.getPlayerMoney() - 50;
	if (temp < 0) {
		cout << "PROMPT: Insufficient balance, cannot add Electricity facility to the property!\n";
	}
	else {
		//check if already enabled

		if (target.isElectricityEnabled()) {
			cout << "PROMPT: This feature has already been enabled!" << endl;
		}
		else {
			target.addElectricity();
			cout << "PROMPT: Electricity feature enabled for property " << target.getPropertyName() << endl;
			int new_rent = target.getRent() + (0.20 * target.getRent());
			client.upgradePropertyFinancials(target);
			target.setRent(new_rent);
		}
	}
}

void GUI::onClickAddGasConnection(Player& client, Property &target) {

	int temp = client.getPlayerMoney() - 50;
	if (temp < 0) {
		cout << "PROMPT: Insufficient balance, cannot add Gas facility to the property!\n";
	}
	else {
		//check if already enabled
		if (target.isGasEnabled()) {
			cout << "PROMPT: Gas feature has already been enabled for property "  << target.getPropertyName() << "!" << endl;
		}
		else {
			target.addGasConnection();
			cout << target.isGasEnabled();
			cout << "PROMPT: Gas feature enabled for property " << target.getPropertyName() << endl;
			int new_rent = target.getRent() + (0.20 * target.getRent());
			client.upgradePropertyFinancials(target);
			target.setRent(new_rent);
		}
	}
}

void GUI::buyProperty(Property &target, Player &client) {
	if (target.getIsPurchased()) {
		cout << "PROMPT: The property you are trying to buy already belongs to Player ID " << target.getOwnerID() << endl;
		return;
	}
	else {
		cout << client;
		int temp = client.getPlayerMoney() - target.getPrice();
		if (temp < 0) {
			cout << "PROMPT: You cannot buy this property as you have insufficient balance.\n";
			return;
		}
		else {
			target.setOwnerID(client.getPlayerID());
			cout << "NOTIFICATION: " << target.getPropertyName() << " is now owned by player no. " << target.getOwnerID() << endl;
			//add the property to players properties
			client.addNewProperty(target);
			//adjust the money
			client.setMoney(temp);
			client.upgradePropertyFinancials(target);
			target.setIsPurchased(true);
		}

	}
}

void GUI::onClickPayRent(Player& client, Player* arr, Property& target) {
	//confirm if the player is not the owner.
	if (client.getPlayerID() == target.getOwnerID()) {
		cout << "PROMPT: You are the owner of this property and hence cannot use this button!\n";
	}
	else if (!target.getIsPurchased()) {
		cout << "PROMPT: Unowned property. No requirement to pay rent!\n";
	}

	else {
		int rent = target.getRent();
		int id = target.getOwnerID();
		//check if person is bankrupt
		if ((client.getPlayerMoney() - target.getRent()) < 0) {
			cout << client;
			Board::checkPlayerBankruptcy(client, target, 0);
			//cout << "PROMPT: Player ID " << client.getPlayerID() << " has gone bankrupt!" << endl;
			//client.setBankruptcy();
			return;
		}
		else {
			cout << "BEFORE: " << client;
			cout << "Player " << client.getPlayerID() << " had paid a total of " << target.getRent() << " in rent!";
			client.setMoney(client.getPlayerMoney() - target.getRent());
			cout << "AFTER: " << client << endl;
			for (int i = 0; i < Player::no_of_players; i++) {
				//search for owner of the property
				if (arr[i].getPlayerID() == id) {
					arr[i].setMoney(arr[i].getPlayerMoney() + target.getRent());
				}
			}
		}
	
	}


}

void GUI::onClickAddShop(Player& client, Property &target) {
	//implement payment by cash
	if (!strcmp(target.getPropertyGroup(), "UTILITY")) {
		cout << "PROMPT: No house can be added here as this property is of the Utility/Station group!\n";
		return;
	}
	else if (!strcmp(target.getPropertyGroup(), "STATION")) {
		cout << "PROMPT: No house can be added here as this property is of the Utility/Station group!\n";
		return;
	}

	if ((client.getPlayerMoney() - 300) < 0) {
		cout << "PROMPT: You have insufficient balance for this action!\n";
	}
	else {
		cout << client << endl;
		cout << endl;
		cout << "RENT BEFORE: " << target.getRent() << endl;
		client.setMoney(client.getPlayerMoney() - 300);
		target.addShops();
		int temp = target.getRent() + (0.60 * target.getRent());
		client.upgradePropertyFinancials(target);
		target.setRent(temp);
		cout << endl;
		cout << client;
		cout << "RENT AFTER: " << target.getRent();
	}



}