/******************************************************************
 * Description: Methods for Player class for Adventure Game program
 * ****************************************************************/

#include "Player.hpp"
#include <algorithm>

//constructor
Player::Player()
{
	maxInventoryWeight = 5;
	currentInventoryWeight = 0;
	fireOut = false;
	engineFueled = false;
	shipStarted = false;
	alienKilled = false;
	foodEaten = false;
	spaceSuitOn = false;
	antidoteTaken = false;
}

//setters
void Player::setMaxInventoryWeight(int w)
{
	maxInventoryWeight = w;
}

void Player::addCurrentInventoryWeight(int w)
{
	currentInventoryWeight += w;
}

void Player::subtractCurrentInventoryWeight(int w)
{
	currentInventoryWeight -= w;
}

void Player::setFireOut(bool f)
{
	fireOut = f;
}

void Player::setEngineFueled(bool e)
{
	engineFueled = e;
}

void Player::setShipStarted(bool s)
{
	shipStarted = s;
}

void Player::setAlienKilled(bool a)
{
	alienKilled = a;
}

void Player::setFoodEaten(bool f)
{
	foodEaten = f;
}

void Player::setSpaceSuitOn(bool s)
{
	spaceSuitOn = s;
}

void Player::setAntidoteTaken(bool a)
{
	antidoteTaken = a;
}



//getters
int Player::getMaxInventoryWeight()
{
	return maxInventoryWeight;
}

int Player::getCurrentInventoryWeight()
{
	return currentInventoryWeight;
}

std::vector<std::string> Player::getItems()
{
	return items;
}

bool Player::getFireOut()
{
	return fireOut;
}

bool Player::getEngineFueled()
{
	return engineFueled;
}

bool Player::getShipStarted()
{
	return shipStarted;
}

bool Player::getAlienKilled()
{
	return alienKilled;
}

bool Player::getFoodEaten()
{
	return foodEaten;
}

bool Player::getSpaceSuitOn()
{
	return spaceSuitOn;
}

bool Player::getAntidoteTaken()
{
	return antidoteTaken;
}


//item storage
void Player::addItem(std::string item)
{
	items.push_back(item);
}

void Player::removeItem(std::string item)
{
	//reference: http://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
	items.erase(std::remove(items.begin(), items.end(), item), items.end());
}