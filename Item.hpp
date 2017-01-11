/**********************************************************************
 * Description: Header file for Item class for Adventure Game program
 * *******************************************************************/


#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>


class Item
{
	private:
		std::string itemName;
		std::string desc;  //for "look at" command
		int weight;


	public:
		//setters
		void setItemName(std::string);
		void setDesc(std::string);
		void setWeight(int);


		//getters
		std::string getItemName();
		std::string getDesc();
		int getWeight();



};



#endif