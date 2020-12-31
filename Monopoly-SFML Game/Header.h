#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Property {
private:
	int price;
	//-1 for Bank. Each player has their unique ID. This ID is 1 digit and assigned to the player at the start of the game.
	bool isPurchased;
	bool isMortgaged;
	//Owned by initialized by -1.
	int ownedBy;
	int propertyID;
	int ownerID;
	float mortgage;
	bool isUtility;
	int rent;
	char* group;
	char* property_name;
	static const int total_properties = 28; //14
	sf::Vector2f pos; //determines the x and y coordinate of the property on the board.
	int house;
	int hotel;
	bool electricity;
	bool wifi;
	bool gas;
	int shops;
public:
	Property();
	int getPrice();
	int getRent();
	float getMortgage();
	Vector2f getPos(); //position of the property on the board.
	void updateRent();
	bool getIsUtility();
	bool getIsPurchased();
	bool getIsMortgaged();
	int getPropertyID();
	char* getPropertyName();
	char* getPropertyGroup();
	static int getTotalPropertySize();
	bool isGasEnabled();
	bool isElectricityEnabled();
	bool isWifiEnabled();
	int getOwnerID();
	bool getShop();
	int getHouseNumber();
	//setters
	void setPrice(int);
	void setRent(int);
	void setMortgage(float);
	void setPos(sf::Vector2f); //leave
	void setIsUtility(bool);
	void setIsPurchased(bool);
	void setIsMortgaged(bool);
	void setPropertyID(int);
	void setPropertyName(char*);
	void setPropertyGroup(char*);
	void addHouse();
	void addHotel();
	void addElectricity();
	void addGasConnection();
	void addWifi();
	void setOwnerID(int);
	void addShops();
	//returns the index/ID number of the property to be accessed

	//no set functions as all the data is read from the text file propertydate();
	~Property();
};

class Player {
private:
	static int id_count;
	int playerID;
	int money;
	int property_count;
	Property* ownedProperties;
	Vector2f position;
	Texture player_tex;
	int jailed_on_turn;
	bool isBankrupt;
	bool isInJail;

public:
	Player();
	Sprite player_sprite;
	static int no_of_players;
	int getPlayerID();
	int getPlayerMoney();
	Property* getOwnedProperties();
	void setMoney(int);
	void increasePropertyCount();
	void addNewProperty(Property);
	int getPropertyCount();
	void upgradePropertyFinancials(Property);
	Sprite getPlayerSprite();
	Vector2f getPosition();
	void setBankruptcy();
	bool getBankruptcy();
	bool getIsInJail();
	void setIsInJail(bool);
	void setJailedOnTurn(int);
	void downgradePropertyFinancials(Property);
	int getJailedOnTurn();
	void resetHouseNumber();
	friend ostream& operator<<(ostream& out, Player obj);
	~Player();

};

class GUI {
private:
	RenderWindow main_window;
	Texture gui_tex;
	Sprite gui_sprite;
	RectangleShape gui_head;
	RectangleShape* buttons;
	Font main_font;
	Text* main_text;
	Text* header_text;
	const int no_of_buttons = 4;
public:
	GUI();
	void displayGUI(Player&, Property*, Player*);
	void createButtons(Vector2f);
	void createButtonText(RectangleShape*);
	Color getGroupColor();
	void viewPropertyInfo(RectangleShape, int, Property*);
	void manageProperty(int, Property*, Player&);
	void buyProperty(Property&, Player&);
	void onClickAddHouse(Player&, Property&);
	void onClickAddWifi(Player&, Property&);
	void onClickAddElectricity(Player&, Property&);
	void onClickAddGasConnection(Player&, Property&);
	void onClickPayRent(Player&, Player*, Property&);
	//NOTE TO SELF: COMPLETE ON 11 JUNE 2020.
	void onClickAddShop(Player&, Property&);
	void onClickAddHotel(Player&, Property); //open gui giving choice to either subtract 3 houses or pay price
};

class Movement {
public:
	static void move(sf::Sprite*, Player*, sf::RenderWindow&, int, int, int, int); //add int for turn no
	static void moveDown(sf::Sprite*, Player*, sf::RenderWindow&, int, int, int, int);
	static void moveRight(sf::Sprite*, Player*, sf::RenderWindow&, int, int, int, int);
	static void moveUp(sf::Sprite*, Player*, sf::RenderWindow&, int, int, int, int);
	static void moveLeft(sf::Sprite*, Player*, sf::RenderWindow&, int, int, int, int);
};

class Board {
private:
	int turn;
	Texture* main_tex;
	Sprite* main_sprite;
	const int x = 3;
	Property* data;
	int higher_turn;
public:
	Board();
	int getX();
	Sprite* getSprites();
	void loadPropertyInfo();
	static int generateDiceNumber();
	static void displayGUI(Sprite, Property*);
	static int searchPropertyByPos(Vector2f, Property*);
	Property* getPropertyData();
	void checkTurn(int);
	int getActiveTurn();
	void incrementTurn();
	static void viewPlayerInfoGUI(Player*, int);
	static bool checkJail(Player&);
	static bool checkMisc(Player&);
	void checkIsInJail(Player* arr, int&);
	static void checkPlayerBankruptcy(Player&, Property&, int);
	static bool checkParking(Player&);
	static bool checkPropertyTax(Player&);
	static bool checkChance(Player&);
	static bool checkLuck(Player&);
	static void removePlayer(int, Player*&, int&);
	void checkIsBankrupt(Player*&, int&);
	~Board();
};