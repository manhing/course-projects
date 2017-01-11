/****************************************************************
 * Description: Methods for Room class for Adventure Game program
 * *************************************************************/

#include "Room.hpp"
#include <algorithm>

//setters
void Room::setRoomName(std::string name)
{
	roomName = name;
}

void Room::setLongDesc(std::string ldesc)
{
	longDesc = ldesc;
}

void Room::setDependentDesc(std::string ddesc)
{
	dependentDesc = ddesc;
}

void Room::setShortDesc(std::string sdesc)
{
	shortDesc = sdesc;
}

void Room::setIsDoorN(bool doorN)
{
	isDoorN = doorN;
}

void Room::setIsDoorE(bool doorE)
{
	isDoorE = doorE;
}

void Room::setIsDoorS(bool doorS)
{
	isDoorS = doorS;
}

void Room::setIsDoorW(bool doorW)
{
	isDoorW = doorW;
}

void Room::setHasVisited(bool visited)
{
	hasVisited = visited;
}

//getters
std::string Room::getRoomName()
{
	return roomName;
}

std::string Room::getLongDesc()
{
	return longDesc;
}

std::string Room::getDependentDesc()
{
	return dependentDesc;
}

std::string Room::getShortDesc()
{
	return shortDesc;
}

bool Room::getIsDoorN()
{
	return isDoorN;
}

bool Room::getIsDoorE()
{
	return isDoorE;
}

bool Room::getIsDoorS()
{
	return isDoorS;
}

bool Room::getIsDoorW()
{
	return isDoorW;
}

std::vector<std::string> Room::getItems()
{
	return items;
}

bool Room::getHasVisited()
{
	return hasVisited;
}

void Room::addItem(std::string item)
{
	items.push_back(item);
}

void Room::removeItem(std::string item)
{	
	//reference: http://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position
	items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

void Room::addFeature(std::string feat)
{
	features.push_back(feat);
}

std::vector<std::string> Room::getFeatures()
{
	return features;
}
