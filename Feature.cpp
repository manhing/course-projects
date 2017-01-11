/********************************************************************
 * Description: Methods for Feature class for Adventure Game program
 * ******************************************************************/

#include "Feature.hpp"

//setters
void Feature::setFeatureName(std::string name)
{
	featureName = name;
}

void Feature::setDesc(std::string d)
{
	desc = d;
}

void Feature::setDependentDesc(std::string dep)
{
	dependentDesc = dep;
}


//getters
std::string Feature::getFeatureName()
{
	return featureName;
}

std::string Feature::getDesc()
{
	return desc;
}

std::string Feature::getDependentDesc()
{
	return dependentDesc;
}