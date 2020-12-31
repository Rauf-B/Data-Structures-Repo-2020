#include "Header.h"

Property::Property() {
	ownerID = -9192312;
	price = -100;
	isMortgaged = false;
	isPurchased = false;
	ownedBy = -100;
	mortgage = 0.0;
	isUtility = false;
	rent = -100;
	group = nullptr;
	property_name = nullptr;
	propertyID = -1;
	house = 0;
	hotel = 0;
	electricity = false;
	gas = false;
	wifi = false;
	shops = 0;
}

//setters
void Property::setPrice(int p) {
	price = p;
}

void Property::setIsPurchased(bool f) {
	isPurchased = f;
}

void Property::setIsMortgaged(bool f) {
	isMortgaged = f;
}

void Property::setRent(int r) {
	rent = r;
}


void Property::setMortgage(float m) {
	mortgage = m;
}

void Property::setIsUtility(bool f) {
	isUtility = f;
}

void Property::setPropertyName(char* pn) {
	property_name = pn;
}

void Property::setPropertyGroup(char* pg) {
	group = pg;
}

void Property::setPos(Vector2f pos1) {
	pos.x = pos1.x;
	pos.y = pos1.y;
}

void Property::setPropertyID(int id) {
	propertyID = id;
}


//getters
int Property::getPrice() {
	return price;
}

bool Property::getIsMortgaged() {
	return isMortgaged;
}

bool Property::getIsPurchased() {
	return isPurchased;
}

float Property::getMortgage() {
	return mortgage;
}

bool Property::getIsUtility() {
	return isUtility;
}

int Property::getRent() {
	return rent;
}

Vector2f Property::getPos() {
	return pos;
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

Property::~Property() {
	price = -113100;
	isMortgaged = false;
	isPurchased = false;
	ownedBy = -1012310;
	mortgage = float(13131.131);
	isUtility = false;
	rent = -1000000;
	group = nullptr;
	property_name = nullptr;
	propertyID = -112312;
}

int Property::getTotalPropertySize() {
	return total_properties;
}

void Property::addHouse() {
	house++;
}

void Property::addHotel() {
	//add condition for removal of three houses.
	hotel++; 
}

void Property::addElectricity() {
	electricity = true;
}

void Property::addGasConnection() {
	gas = true;
}

void Property::addWifi() {
	wifi = true;
}

bool Property::isElectricityEnabled() {
	return electricity;
}

bool Property::isGasEnabled() {
	return gas;
}

bool Property::isWifiEnabled() {
	return wifi;
}

int Property::getOwnerID() {
	return ownerID;
}

void Property::setOwnerID(int id) {
	ownerID = id;
}

int Property::getHouseNumber() {
	return house;
}

void Property::addShops() {
	if (shops == 1) {
		return;
	}
	else {
		shops++;
	}
}

bool Property::getShop() {
	if (shops > 0) {
		return true;
	}
	else {
		return false;
	}
}