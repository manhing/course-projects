/**********************************************************************
 * Description: Header file for Feature class for Adventure Game program
 * *******************************************************************/


#ifndef FEATURE_HPP
#define FEATURE_HPP

#include <string>


class Feature
{
	private:
		std::string featureName;
		std::string desc;
		std::string dependentDesc;

	public:
		//setters
		void setFeatureName(std::string);
		void setDesc(std::string);
		void setDependentDesc(std::string);


		//getters
		std::string getFeatureName();
		std::string getDesc();
		std::string getDependentDesc();

};



#endif