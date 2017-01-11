/****************************************************
* Description:
*****************************************************/

#include <iostream>
#include <fstream>
#include <string>
//#include <algorithm>

#include "Room.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "Animation.hpp"
#include "Feature.hpp"

void createItems(Item[8], int);
void createFeatures(Feature[30], int);
void createRooms(Room[3][5], int, int);
void moveRoom(Room*, int&, int&, std::string, Player&);
int parseUserCommand(Player&, Room*, Item[8], Feature[30], int&, int &, std::string, Animation);
void displayRoomDesc(Room*, Item[8]);
void displayLongDesc(Room*, Item[8]);
void displayIntro(Animation);
void displayHelpMenu();
int attack(Player&, Room*);
int checkWinGame(Player&);
void eat(Player&, Room*, Item[8]);
int getItemWeight(Item[8], std::string);
void putOnSpacesuit(Player&, std::string, Item[8]);
void restartShip(Player&, std::string , Room*, Feature[30]);
void putOutFire(Player&, std::string, Room*, Animation);
void installPowerCore(Room*, Player&, std::string, Item[8], Feature[30], Animation);
void takeAntidote(Player&);


int main()
{
	Player player; //has constructor to initialize all attributes
	Animation an;
	const int MAX_ITEMS = 8;
	const int MAX_FEATURES = 30;
	const int MAX_X = 3;	//horizontal
	const int MAX_Y = 5;	//vertical
	int i, j;
	Item itemArray[MAX_ITEMS];

	createItems(itemArray, MAX_ITEMS);


	Room roomArray[3][5];

	createRooms(roomArray, MAX_X, MAX_Y);

	Feature featureArray[MAX_FEATURES];

	createFeatures(featureArray, MAX_FEATURES);

	/*******START TEST of ITEM CREATION*************/
/*
	for (j = 0; j < 8; j++)
	{
		std::cout << "item at " << j <<":" << std::endl;
		std::cout << itemArray[j].getItemName() << std::endl;
		std::cout << itemArray[j].getDesc() << std::endl;
		std::cout << itemArray[j].getWeight() << std::endl;

		std::cout << "weight + 10 =" << itemArray[j].getWeight() + 10 << std::endl;
	}

	/*******END TEST of ITEM CREATION*************/


	/*******START TEST of FEATURE CREATION*************/
/*
	for (j = 0; j < 30; j++)
	{
		std::cout << "item at " << j <<":" << std::endl;
		std::cout << featureArray[j].getFeatureName() << std::endl;
		std::cout << featureArray[j].getDesc() << std::endl;
		std::cout << featureArray[j].getDependentDesc() << std::endl;

	}

	/*******END TEST of FEATURE CREATION*************/


////START OF ROOM STATUS TESTING
	/*
	for (i = 0; i < MAX_X; i++)
	{
		for (j = 0; j < MAX_Y; j++)
		{
			std::cout << "room at " << i << "," << j <<":" << std::endl;
			std::cout << roomArray[i][j].getRoomName() << std::endl;
			std::cout << roomArray[i][j].getLongDesc() << std::endl;
			std::cout << roomArray[i][j].getShortDesc() << std::endl;
			std::cout << roomArray[i][j].getIsDoorN() << std::endl;
			std::cout << roomArray[i][j].getIsDoorE() << std::endl;
			std::cout << roomArray[i][j].getIsDoorS() << std::endl;
			std::cout << roomArray[i][j].getIsDoorW() << std::endl;
			std::cout << "hasVisited == " << roomArray[i][j].getHasVisited() << std::endl << std::endl;

			for (int k = 0; k < roomArray[i][j].getFeatures().size(); k++)
				std::cout << "feature: " << roomArray[i][j].getFeatures()[k] << std::endl << std::endl;
		}

	}
	

////*END OF ROOM STATUS TESTING*/



	int currentX = 1; //start at sickbay (1,2)
	int currentY = 2;
	Room *currentRoom;
	currentRoom = &roomArray[currentX][currentY];
	std::string userCommand = "";


	displayIntro(an);
	displayRoomDesc(currentRoom, itemArray);
	roomArray[currentX][currentY].setHasVisited(true);
	
	
/*****************game loop - start***********************/
	do {
		int result = 0;
		//std::cout << "Enter your command separated by spaces: " << std::endl; // for testing purposes
		std::cout << "> ";
		std::getline(std::cin, userCommand);

		//if a direction is inputted
		if (userCommand == "n" || userCommand == "e" || userCommand == "s" || userCommand == "w")
		{
			moveRoom(currentRoom, currentX, currentY, userCommand, player);
			currentRoom = &roomArray[currentX][currentY];
			displayRoomDesc(currentRoom, itemArray);
			currentRoom->setHasVisited(true);
		}
		else
		{
			result = parseUserCommand(player, currentRoom, itemArray, featureArray, currentX, currentY, userCommand, an);
		}


/**************START TEST OF WIN GAME**********/
		/*
		if (userCommand == "switch objs to true")
		{
			std::cout << "switching to true..." << std::endl;
			player.setFireOut(true);
			player.setEngineFueled(true);
			player.setShipStarted(true);
			player.setAlienKilled(true);
			player.setFoodEaten(true);
			player.setSpaceSuitOn(true);
			player.setAntidoteTaken(true);
		}
		
/**************END TEST OF WIN GAME**********/

/**************START TEST OF PLAYER STATUS**********/
	/*
	std::cout << "maxInventoryWeight= " << player.getMaxInventoryWeight() << std::endl;
	std::cout << "currentInventoryWeight= " << player.getCurrentInventoryWeight() << std::endl;
	std::cout << "fireOut= " << player.getFireOut() << std::endl;
	std::cout << "engineFueled= " << player.getEngineFueled() << std::endl;
	std::cout << "shipStarted= " << player.getShipStarted() << std::endl;
	std::cout << "alienKilled= " << player.getAlienKilled() << std::endl;
	std::cout << "foodEaten= " << player.getFoodEaten() << std::endl;
	std::cout << "spaceSuitOn= " << player.getSpaceSuitOn() << std::endl;
	std::cout << "antidoteTaken= " << player.getAntidoteTaken() << std::endl << std::endl;
	
/**************END TEST OF PLAYER STATUS**********/
		if (result == -1) //-1 means player died during attack command
		{
			break;
		}

		//if player went into armory without spacesuit on, he dies.
		if (currentRoom->getRoomName() == "armory" && player.getSpaceSuitOn() == false)
		{
			std::cout << "The lack of atmospheric pressure tore you apart. You died!" << std::endl << std::endl;
			std::cout << "GAME OVER" << std::endl << std::endl;
			break;

		}

	
		if (checkWinGame(player))
		{
			an.end();
			break;
		}

	} while(1); //use CTRL+C to stop loop & program for now

/*****************game loop - end***********************/


	return 0;
}

/**********************************************************
* This function reads in data and populates itemArray with
* that data.
***********************************************************/
void createItems(Item itemArray[8], int num)
{
	std::string line;
	std::string data;
	std::string delimiter = ":";
	std::ifstream infile;
	std::string roomFiles[8] = {"item1.txt", "item2.txt",  "item3.txt", "item4.txt",
								"item5.txt", "item6.txt",  "item7.txt", "item8.txt"};
	int fileIndex = 0;
	
	for (int i = 0; i < num; i++)
	{
		infile.open(roomFiles[fileIndex].c_str());
			
		if(infile)
		{
			std::getline(infile, line);
			line.erase(0, line.find(delimiter) + delimiter.length());
			if (!line.empty() && line[line.length() - 1] == '\r')
			{
				line.erase(line.length() - 1);
			}
			itemArray[i].setItemName(line);

			std::getline(infile, line);
			line.erase(0, line.find(delimiter) + delimiter.length());
			if (!line.empty() && line[line.length() - 1] == '\r')
			{
				line.erase(line.length() - 1);
			}
			itemArray[i].setDesc(line);

			std::getline(infile, line);
			line.erase(0, line.find(delimiter) + delimiter.length());
			if (!line.empty() && line[line.length() - 1] == '\r')
			{
				line.erase(line.length() - 1);
			}
			itemArray[i].setWeight(line[0] - 48); //ASCII is 48 less than decimal

		}
		else
		{
			std::cout << "Could not open file: " << roomFiles[i].c_str() << std::endl;
		}

		infile.close();

		fileIndex++;
	}
}

void createFeatures(Feature featureArray[30], int num)
{
	std::string line;
	std::string data;
	std::string delimiter = ":";
	std::ifstream infile;
	std::string roomFile = "features.txt";
	

	infile.open(roomFile.c_str());
		
	if(infile)
	{
		for (int i = 0; i < num; i++)
		{
			std::getline(infile, line);
			line.erase(0, line.find(delimiter) + delimiter.length());
			if (!line.empty() && line[line.length() - 1] == '\r')
			{
				line.erase(line.length() - 1);
			}
			featureArray[i].setFeatureName(line);

			std::getline(infile, line);
			line.erase(0, line.find(delimiter) + delimiter.length());
			if (!line.empty() && line[line.length() - 1] == '\r')
			{
				line.erase(line.length() - 1);
			}
			featureArray[i].setDesc(line);

			std::getline(infile, line);
			line.erase(0, line.find(delimiter) + delimiter.length());
			if (!line.empty() && line[line.length() - 1] == '\r')
			{
				line.erase(line.length() - 1);
			}
			featureArray[i].setDependentDesc(line);
		}
	}
	else
	{
		std::cout << "Could not open file: " << roomFile.c_str() << std::endl;
	}

	infile.close();

}

/**********************************************************
* This function reads in data and populates roomArray with
* that data.
***********************************************************/
void createRooms(Room roomArray[3][5], int x, int y)
{
	std::string line;
	std::string data;
	std::string delimiter = ":";
	std::ifstream infile;
	std::string roomFiles[15] = {"room00.txt", "room01.txt",  "room02.txt", "room03.txt", "room04.txt",
								"room10.txt", "room11.txt",  "room12.txt", "room13.txt", "room14.txt",
								"room20.txt", "room21.txt",  "room22.txt", "room23.txt", "room24.txt"};
	
	int fileIndex = 0;
	
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{			
			infile.open(roomFiles[fileIndex].c_str());
			
			if(infile)
			{
				std::getline(infile, line);
				line.erase(0, line.find(delimiter) + delimiter.length());
				if (!line.empty() && line[line.length() - 1] == '\r')
				{
					line.erase(line.length() - 1);
				}
				roomArray[i][j].setRoomName(line);
				
				std::getline(infile, line);
				line.erase(0, line.find(delimiter) + delimiter.length());
				if (!line.empty() && line[line.length() - 1] == '\r')
				{
					line.erase(line.length() - 1);
				}
				roomArray[i][j].setLongDesc(line);

				std::getline(infile, line);
				line.erase(0, line.find(delimiter) + delimiter.length());
				if (!line.empty() && line[line.length() - 1] == '\r')
				{
					line.erase(line.length() - 1);
				}
				roomArray[i][j].setDependentDesc(line);
				
				std::getline(infile, line);
				line.erase(0, line.find(delimiter) + delimiter.length());
				if (!line.empty() && line[line.length() - 1] == '\r')
				{
					line.erase(line.length() - 1);
				}
				roomArray[i][j].setShortDesc(line);

				//add item
				std::getline(infile, line);
				line.erase(0, line.find(delimiter) + delimiter.length());
				if (!line.empty() && line[line.length() - 1] == '\r')
				{
					line.erase(line.length() - 1);
				}
				if (line != "") //if it is an empty string, don't add anything to the vector
				{
					roomArray[i][j].addItem(line);
				}
				
				std::getline(infile, line);
				line.erase(0, line.find(delimiter) + delimiter.length());
				if (!line.empty() && line[line.length() - 1] == '\r')
				{
					line.erase(line.length() - 1);
				}
				if(line.compare("true") == 0)
				{
					roomArray[i][j].setIsDoorN(true);
				}
				else
				{
					roomArray[i][j].setIsDoorN(false);
				}
				
				
				std::getline(infile, line);
				line.erase(0, line.find(delimiter) + delimiter.length());
				if (!line.empty() && line[line.length() - 1] == '\r')
				{
					line.erase(line.length() - 1);
				}
				if(line.compare("true") == 0)
				{
					roomArray[i][j].setIsDoorE(true);
				}
				else
				{
					roomArray[i][j].setIsDoorE(false);
				}
				
				std::getline(infile, line);
				line.erase(0, line.find(delimiter) + delimiter.length());
				if (!line.empty() && line[line.length() - 1] == '\r')
				{
					line.erase(line.length() - 1);
				}
				if(line.compare("true") == 0)
				{
					roomArray[i][j].setIsDoorS(true);
				}
				else
				{
					roomArray[i][j].setIsDoorS(false);
				}
				
				std::getline(infile, line);
				line.erase(0, line.find(delimiter) + delimiter.length());
				if (!line.empty() && line[line.length() - 1] == '\r')
				{
					line.erase(line.length() - 1);
				}
				if(line.compare("true") == 0)
				{
					roomArray[i][j].setIsDoorW(true);
				}
				else
				{
					roomArray[i][j].setIsDoorW(false);
				}

				//add feature 1
				std::getline(infile, line);
				line.erase(0, line.find(delimiter) + delimiter.length());
				if (!line.empty() && line[line.length() - 1] == '\r')
				{
					line.erase(line.length() - 1);
				}
				if (line != "") //if it is an empty string, don't add anything to the vector
				{
					roomArray[i][j].addFeature(line);
				}

				//add feature 2
				std::getline(infile, line);
				line.erase(0, line.find(delimiter) + delimiter.length());
				if (!line.empty() && line[line.length() - 1] == '\r')
				{
					line.erase(line.length() - 1);
				}
				if (line != "") //if it is an empty string, don't add anything to the vector
				{
					roomArray[i][j].addFeature(line);
				}


				
				roomArray[i][j].setHasVisited(false); //sets all rooms to not visited

				infile.close();
			}
			else
			{
				std::cout << "Could not open file: " << roomFiles[j].c_str() << std::endl;
			}

			fileIndex++;
		}	
	}
	
}


/************************************************************************
* This function increments or decrements either the currentX or currentY
* variables to navigate through the rooms.
************************************************************************/
void moveRoom(Room *currentRoom, int &currentX, int &currentY, std::string d, Player &player) 
{
	
	// move south
	if (d == "s" && currentRoom->getIsDoorS() == true) {
		currentY--;
	}

	// move north
	else if (d == "n" && currentRoom->getIsDoorN() == true) {

		//check to see if he has id card in order to access the bridge
		if (currentRoom->getRoomName() == "lounge")
		{
			bool hasIdCard = false;

			for (int i = 0; i < player.getItems().size(); i++)
			{
				if (player.getItems()[i] == "id card")
				{
					hasIdCard = true;
				}
			}
			//if currently in the lounge and has indentification card, player can to go bridge
			if (hasIdCard)
			{
				currentY++;
			}
			else 
			{
				std::cout << std::endl << "You cannot enter the bridge without your id card in your inventory." << std::endl;
			}

		}
		else
		{
			currentY++;
		}
	}

	// move east
	else if (d == "e" && currentRoom->getIsDoorE() == true) {
		currentX++;
	}

	// move west
	else if (d == "w" && currentRoom->getIsDoorW() == true) {
		currentX--;
	}
	else
		std::cout << std::endl << "No door in that direction" << std::endl;

}

int parseUserCommand(Player &player, Room *currentRoom, Item itemArray[8], Feature featureArray[30], int &currentX, int &currentY, std::string command, Animation an)
{
	//one-worded commands	
	if (command == "help")
	{
		displayHelpMenu();
		return 0;
	}
	else if (command == "quit")
	{
		std::cout << std::endl << "You have quit the game. Your progress will not be saved." << std::endl << std::endl;
		return -1;
	}
	else if (command == "attack")
	{
		int result;
		result = attack(player, currentRoom); //-1 means player died
		return result;
	}
	else if (command == "eat")
	{
		eat(player, currentRoom, itemArray);
		return 0;
	}
	else if (command == "look")
	{
		displayLongDesc(currentRoom, itemArray);
		return 0;
	}
	else if (command == "inventory")
	{
		std::cout << std::endl << "Items in inventory: " << std::endl;
		for (int i = 0; i < player.getItems().size(); i++)
		{
			std::cout <<  "  " << player.getItems()[i];
			for (int j = 0; j < 8; j++)
			{	//disaply weight of each item
				if (itemArray[j].getItemName() == player.getItems()[i])
				{
					std::cout << " (" << itemArray[j].getWeight() << ")" << std::endl;
				}
			}
		}
		std::cout << "Current inventory weight: " << player.getCurrentInventoryWeight() << std::endl << std::endl;
		return 0;
	}


	std::string command2 = command;
	std::string delimiter = " ";
	std::string command3;
			
	//two-worded commands
	//parse use command delimited by space. If space found, split into two strings.
	std::size_t found = command.find(delimiter);
  	if (found!=std::string::npos)
  	{
		command.erase(command.find(delimiter), command.length()); //string before first space
		command2.erase(0, command2.find(delimiter) + delimiter.length()); //part after first space
		//std::cout << "command after delimited: " << command << std::endl;
		//std::cout << "command2 after delimited: " << command2 << std::endl;
	}

	if (command == "take")
	{
		bool inRoom = false;

		//check to see if the item exists in room
		for (int j = 0; j < currentRoom->getItems().size(); j++)
		{
			if (currentRoom->getItems()[j] == command2)
				inRoom = true;
		}

		//if exists, add into inventory
		if (inRoom)
		{
			//if the weight of the item plus current weight of items is less than or equal to max weight, then add to inventory
			if (getItemWeight(itemArray, command2) + player.getCurrentInventoryWeight() <= player.getMaxInventoryWeight())
			{
				player.addItem(command2);
				currentRoom->removeItem(command2);
				player.addCurrentInventoryWeight(getItemWeight(itemArray, command2));
				std::cout << std::endl << "You have added " << command2 << " into your inventory." << std::endl << std::endl;
			}
			else
			{
				std::cout << std::endl << "You cannot add more to inventory. Max weight is 5 units." << std::endl << std::endl;
			}
		}
		else
		{
			std::cout << std::endl << "Cannot take " << command2 << "." << std::endl << std::endl;
		}

		return 0;
	}
	else if (command == "drop")
	{
		bool inInventory = false;

		//check to see if the item exists in player's inventory
		for (int k = 0; k < player.getItems().size(); k++)
		{
			if (player.getItems()[k] == command2)
				inInventory = true;
		}

		//if exists, drop into room
		if (inInventory)
		{
			currentRoom->addItem(command2);
			player.removeItem(command2);
			player.subtractCurrentInventoryWeight(getItemWeight(itemArray, command2));
			std::cout << std::endl << "You have removed " << command2 << " from your inventory." << std::endl << std::endl;
		}
		else
		{
			std::cout << std::endl << command2 << " is not in your inventory." << std::endl << std::endl;

		}

		return 0;
	}
	else if (command == "use")
	{
		bool inInventory = false;

		//check to see if item is in inventory
		for (int i = 0; i < player.getItems().size(); i++)
		{
			if(player.getItems()[i] == command2)
			{
				inInventory = true;
			}
		}

		if (inInventory)
		{
			if (command2 == "spacesuit")
			{
				putOnSpacesuit(player, command2, itemArray);
			}
			else if (command2 == "login key")
			{
				restartShip(player, command2, currentRoom, featureArray);
			}
			else if (command2 == "fire extinguisher" || command2 == "extinguisher")
			{
				putOutFire(player, "fire extinguisher", currentRoom, an);
			}
			else if (command2 == "power core")
			{
				installPowerCore(currentRoom, player, command2, itemArray, featureArray, an);
			}
			else if (command2 == "antidote")
			{
				takeAntidote(player);
			}
			else
			{
				std::cout << std::endl << "That is not a valid command." << std::endl << std::endl;
			}
		}
		else
		{
			std::cout << std::endl << command2 << " is not in your inventory." << std::endl << std::endl;		
		}

		return 0;
	}
	

	//three-worded command
	//parse further
	if (!(command == "take" || command == "drop" || command == "use")) //skip two-worded items
	{
		//If space found, split into another two strings.
		found = command2.find(delimiter);
	  	if (found!=std::string::npos)
	  	{
			command3 = command2;
			command2.erase(command2.find(delimiter), command2.length()); //string before first space
			command3.erase(0, command3.find(delimiter) + delimiter.length()); //part after first space
			//std::cout << "command2 after delimited: " << command2 << std::endl;
			//std::cout << "command3 after delimited: " << command3 << std::endl;
		}
	}

	
	if (command == "look" && command2 == "at")
	{
		//std::cout << "look at -" << command3 << "- test." << std::endl;

		bool itemPresent = false;

		//if the item exists in the room
		for (int i = 0; i < currentRoom->getItems().size(); i++)
		{
			if (currentRoom->getItems()[i] == command3)
			{
				//traverse through the itemArray to find the description
				for (int j = 0; j < 8; j++)
				{
					if (itemArray[j].getItemName() == command3)
					{
						std::cout << std::endl << itemArray[j].getDesc() << std::endl << std::endl;
						itemPresent = true;
					}
				}
			}
		}

		//if item was already found, don't go through your inventory
		if (!itemPresent)
		{
			//or if the item exists in inventory
			for (int i = 0; i < player.getItems().size(); i++)
			{
				if (player.getItems()[i] == command3)
				{
					//traverse through the itemArray to find the description
					for (int j = 0; j < 8; j++)
					{
						if (itemArray[j].getItemName() == command3)
						{
							std::cout << std::endl << itemArray[j].getDesc() << std::endl << std::endl;
							itemPresent = true;
						}
					}
				}
			}
		}

		//if item was already found, don't go through the featureArray
		if (!itemPresent)
		{
			//or if the feature exists in the room
			for (int i = 0; i < currentRoom->getFeatures().size(); i++)
			{
				if (currentRoom->getFeatures()[i] == command3)
				{
					//traverse through the featureArray to find the description
					for (int j = 0; j < 30; j++)
					{
						if (featureArray[j].getFeatureName() == command3)
						{
							std::cout << std::endl << featureArray[j].getDesc() << std::endl;
							itemPresent = true;

							//if feature has dependent description
							if(!(featureArray[j].getDependentDesc() == ""))
							{
								std::cout << featureArray[j].getDependentDesc() << std::endl;
							}
							std::cout << std::endl;
						}
					}
				}
			}
		}

		//if it wasn't found as an item or a feature
		if (!itemPresent)
		{
			std::cout << std::endl << "Cannot look at " << command3 << "." << std::endl << std::endl;
		}

		return 0;
	}


	std::cout << std::endl << "That is not a valid command." << std::endl << std::endl;

	return 0;
}


/*********************************************************************
* This function displays a description each time the players navigates
* to a new room.
**********************************************************************/
void displayRoomDesc(Room *currentRoom, Item itemArray[8])
{
	std::cout << std::endl;

	//if the room has been visted before, show only a short description
	if (currentRoom->getHasVisited() == true)
	{
		std::cout << currentRoom->getShortDesc() << std::endl;
		//display dependent description if not empty
		if (currentRoom->getDependentDesc() != "")
		{
			std::cout << currentRoom->getDependentDesc() << std::endl;
		}
	}
	else
	{	
		//if the room has not been visited before, display the long description
		std::cout << currentRoom->getLongDesc() << std::endl;

		//display dependent description if not empty
		if (currentRoom->getDependentDesc() != "")
		{
			std::cout << currentRoom->getDependentDesc() << std::endl;
		}
	}
	std::cout << std::endl;


	//loop to display room features
	std::cout << "Features in room: " << std::endl;
	for (int i = 0; i < currentRoom->getFeatures().size(); i++)
	{
		std::cout << "  " << currentRoom->getFeatures()[i] << std::endl;
	}
	std::cout << std::endl;

	//loop to display items in room
	std::cout << "Items in room: " << std::endl;
	for (int i = 0; i < currentRoom->getItems().size(); i++)
	{
		std::cout << "  " << currentRoom->getItems()[i];
		for (int j = 0; j < 8; j++)
		{
			if (itemArray[j].getItemName() == currentRoom->getItems()[i])
			{
				std::cout << " (" << itemArray[j].getWeight() << ")" << std::endl;
			}
		}
	}
	std::cout << std::endl;
}

void displayLongDesc(Room *currentRoom, Item itemArray[8])
{
	std::cout << std::endl;

	//if the room has not been visited before, display the long description
	std::cout << currentRoom->getLongDesc() << std::endl;

	//display dependent description if not empty
	if (currentRoom->getDependentDesc() != "")
	{
		std::cout << currentRoom->getDependentDesc() << std::endl;
	}
	
	std::cout << std::endl;


	//loop to display room features
	std::cout << "Features in room: " << std::endl;
	for (int i = 0; i < currentRoom->getFeatures().size(); i++)
	{
		std::cout << "  " << currentRoom->getFeatures()[i] << std::endl;
	}
	std::cout << std::endl;

	//loop to display items in room
	std::cout << "Items in room: " << std::endl;
	for (int i = 0; i < currentRoom->getItems().size(); i++)
	{
		std::cout << "  " << currentRoom->getItems()[i];
		for (int j = 0; j < 8; j++)
		{
			if (itemArray[j].getItemName() == currentRoom->getItems()[i])
			{
				std::cout << " (" << itemArray[j].getWeight() << ")" << std::endl;
			}
		}
	}
	std::cout << std::endl;
}


/*********************************************************************
* This function displays the opening introduction.
**********************************************************************/
void displayIntro(Animation an)
{
	an.title();
	std::cout << std::endl << "You see your son running on the sand and your wife standing near. She turns her head back towards you and calls your name. You try to speak but no sound can be heard. They are smiling and enjoying themselves. As you try to move closer they seem to get further and further away. The faster you run the quicker the memory starts to fade and all you see is a white light..." << std::endl << std::endl;
	std::cout << "A bright light shines on your face as you lie in your cryogenic sleep pod. Cracks run down the glass cover and you pound your fists against the glass until the lid frees open. You are wet, cold, and naked. There are scrubs folded in the corner of the room and you rush to cover yourself. All the other pods are empty and the room was abandoned in a hurry. It's quiet, almost too quiet. You notice a red flashing light coming through the windows to the north, south and west. Something isn’t right. Where is everyone? They said you wouldn’t wake up until the spaceship arrived at the fleet training station." << std::endl << std::endl;
	std::cout << "Type ‘help’ to display the help menu." << std::endl << std::endl;
}


/*********************************************************************
* This function first tests to see if the player is on the bridge;
* if so, the alienKilled objective is marked as true and the 
* dependent description is also over written with an empty string.
**********************************************************************/
int attack(Player &player, Room *currentRoom)
{
	bool hasBlaster = false;

	for (int j = 0; j < player.getItems().size(); j++)
	{
		if (player.getItems()[j] == "blaster")
		{
			hasBlaster = true;
		}
	}
	std::cout << std::endl;

	if (currentRoom->getRoomName() == "bridge" && player.getAlienKilled() == false && hasBlaster == true)
	{

		if (player.getFoodEaten() == false)
		{
			std::cout << "You weren't strong enough to defeat the alien. You died!" << std::endl << std::endl;
			std::cout << "GAME OVER" << std::endl << std::endl;
			return -1;
		}
		else
		{
			player.setAlienKilled(true);
			currentRoom->setDependentDesc("");
		}

		std::cout << "You killed the alien." << std::endl << std::endl;
	}
	else
	{
		std::cout << "Cannot attack. You either do not have a weapon or there is nothing to attack." << std::endl << std::endl;
	}

	return 0;
}


/*********************************************************************
* This function displays a help menu that lists available
* commands for use in the game.
**********************************************************************/
void displayHelpMenu()
{
	std::cout << std::endl;
	std::cout << "Help Menu" << std::endl << std::endl;
	std::cout << "List of available commands: " << std::endl;
	std::cout << "  n, e, s, w - use to navigate through rooms" << std::endl;
	std::cout << "  look - display long-form description" << std::endl;
	std::cout << "  look at <feature or item> - displays description or explanation" << std::endl;
	std::cout << "  attack - can be used when weapon is in your inventory" << std::endl;
	std::cout << "  eat - can be used when food is in your inventory" << std::endl;
	std::cout << "  take <item> - add item into your inventory" << std::endl;
	std::cout << "  drop <item> - remove item from your inventory" << std::endl;
	std::cout << "  inventory - lists item(s) in inventory" << std::endl;
	std::cout << "  use <item> - use an item in your inventory" << std::endl;
	std::cout << "  help - display help menu" << std::endl;
	std::cout << "  quit - ends game without saving" << std::endl;
	std::cout << "All commands should be typed in lowercase." << std::endl;
	std::cout << "Max inventory weight is set to 5 units." << std::endl;
	std::cout << std::endl;
}


/*********************************************************************
* This function checks to see if all objectives were accomplished
* and if they are, returns 1.
**********************************************************************/
int checkWinGame(Player &player)
{
	if (player.getFireOut() == true &&
		player.getEngineFueled() == true &&
		player.getShipStarted() == true &&
		player.getAlienKilled() == true &&
		player.getFoodEaten() == true &&
		player.getSpaceSuitOn() == true)
	{
		std::cout << std::endl << "CONGRATULATIONS! You have won the game!" << std::endl << std::endl;
		return 1;
	}
	
	return 0;
}


void eat(Player &player, Room *currentRoom, Item itemArray[8])
{
	bool hasFood = false;
	//if player has food in inventory
	for (int i = 0; i < player.getItems().size(); i++)
	{
		if (player.getItems()[i] == "food")
		{
			hasFood = true;
		}
	}

	if (hasFood)
	{
		player.setFoodEaten(true);
		player.removeItem("food");//remove food from game if eaten
		player.subtractCurrentInventoryWeight(getItemWeight(itemArray, "food"));
		std::cout << std::endl << "You have eaten food. You have regained your strength." <<std::endl << std::endl;
	}
	else
	{
			std::cout << std::endl << "You have no food in inventory to eat." <<std::endl << std::endl;
	}
}

int getItemWeight(Item itemArray[8], std::string itemName)
{
	int weight;

	for (int j = 0; j < 8; j++)
	{
		if (itemArray[j].getItemName() == itemName)
		{
			weight = itemArray[j].getWeight();
		}
	}

	return weight;
}

void putOnSpacesuit(Player &player, std::string command2, Item itemArray[8])
{
	player.setSpaceSuitOn(true);
	std::cout << std::endl << "You have put on the spacesuit and can enter any room without worrying about the atmosphere." << std::endl << std::endl;
	player.removeItem(command2);
	player.subtractCurrentInventoryWeight(getItemWeight(itemArray, command2));
}

void restartShip(Player &player, std::string command2, Room *currentRoom, Feature featureArray[30])
{
	if (currentRoom->getRoomName() == "bridge" && player.getShipStarted() == false)
	{
		if (player.getEngineFueled() == true) //if the engine has power core
		{
			player.setShipStarted(true);
			std::cout << std::endl << "You have restarted the ship." << std::endl << std::endl;
			//set terminal's dependent description to empty string
			for (int i = 0; i < 30; i++)
			{
				if (featureArray[i].getFeatureName() == "terminal")
				{
					featureArray[i].setDependentDesc("");
				}
			}
		}
		else
		{
			std::cout << std::endl << "The engine needs power before the ship can be restarted." << std::endl << std::endl;
		}
	}
	else
	{
		if (currentRoom->getRoomName() != "bridge")
		{
			std::cout << std::endl << "You cannot use " << command2 << "." << std::endl << std::endl;
		}

		else 
		{
			std::cout << std::endl << "The ship has already been restarted." << std::endl << std::endl;
		}
	}

}

void putOutFire(Player &player, std::string command2, Room *currentRoom, Animation an)
{
	if (currentRoom->getRoomName() == "galley" && player.getFireOut() == false)
	{
		an.putOutFire();
		player.setFireOut(true);
		std::cout << std::endl << "You have saved the ship from burning." << std::endl << std::endl;
		currentRoom->setDependentDesc(""); //remove string about the fire
	}
	else
	{
		std::cout << std::endl << "You cannot use " << command2 << " because there is no fire." << std::endl << std::endl;
	}

}


void installPowerCore(Room *currentRoom, Player &player, std::string command2, Item itemArray[8], Feature featureArray[30], Animation an)
{
	if (currentRoom->getRoomName() == "engine room" && player.getEngineFueled() == false)
	{
		an.addCore();
		player.setEngineFueled(true);
		std::cout << std::endl << "You have installed the power core and the ship can be powered up from the bridge." << std::endl << std::endl;
		player.removeItem(command2);
		player.subtractCurrentInventoryWeight(getItemWeight(itemArray, command2));
		currentRoom->setDependentDesc("");
		//set meter dependent description to empty string
		for (int i = 0; i < 30; i++)
		{
			if (featureArray[i].getFeatureName() == "meter")
			{
				featureArray[i].setDependentDesc("The meter shows that the ship is at full power.");
			}
		}
	}
	else
	{
		std::cout << std::endl << "You cannot use " << command2 << " because you are not in the engine room." << std::endl << std::endl;
	}

}

void takeAntidote(Player &player)
{
	if (player.getAntidoteTaken() == false)
	{
		player.setAntidoteTaken(true);
		std::cout << std::endl << "The antidote has cured you from the alien poison." << std::endl << std::endl;
	}
	else
	{
		std::cout << std::endl << "You have already taken the antidote." << std::endl << std::endl;
	}
}
