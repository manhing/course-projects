/**********************************************************************
 * Description: Header file for Room class for Adventure Game program
 * *******************************************************************/


#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>

class Room
{
	private:
		std::string roomName;
		std::string longDesc;
		std::string dependentDesc;
		std::string shortDesc;
		std::vector<std::string> items;
		std::vector<std::string> features;


		//for navigation, we can test to see if current room has a doorway
		bool isDoorN;
		bool isDoorE;
		bool isDoorS;
		bool isDoorW;

		bool hasVisited; // for determining whether to print long or short description

	public:
		//setters
		void setRoomName(std::string);
		void setLongDesc(std::string);
		void setDependentDesc(std::string);
		void setShortDesc(std::string);
		void setIsDoorN(bool);
		void setIsDoorE(bool);
		void setIsDoorS(bool);
		void setIsDoorW(bool);
		void setHasVisited(bool);

		//getters
		std::string getRoomName();
		std::string getLongDesc();
		std::string getDependentDesc();
		std::string getShortDesc();
		std::vector<std::string> getItems();
		std::vector<std::string> getFeatures();
		bool getIsDoorN();
		bool getIsDoorE();
		bool getIsDoorS();
		bool getIsDoorW();
		bool getHasVisited();
		
		void addItem(std::string);
		void removeItem(std::string);

		void addFeature(std::string);

};



#endif
