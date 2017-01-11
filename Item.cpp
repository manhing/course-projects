/****************************************************************
 * Description: Methods for Item class for Adventure Game program
 * *************************************************************/

#include "Item.hpp"

//setters
void Item::setItemName(std::string name)
{
	itemName = name;
}

void Item::setDesc(std::string description)
{
	desc = description;
}

void Item::setWeight(int w)
{
	weight = w;
}

//getters
std::string Item::getItemName()
{
	return itemName;
}

std::string Item::getDesc()
{
	return desc;
}

int Item::getWeight()
{
	return weight;
}