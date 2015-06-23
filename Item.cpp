#include "Item.h"

Item::Item(std::string newName):
	m_name(newName),
	m_attributes()
{}
Item::~Item(){}

/*
Add an attribute to the item
*/
void Item::addAttribute(std::string key, int value){
	if(!doesContainAttribute(key))
		m_attributes.emplace(key,value);
}

attrList Item::getAllAttributes(){
	return m_attributes;
}

int Item::getItemAttribute(std::string key){
	return m_attributes.at(key);
}

void Item::setItemAttribute(std::string key, int value){
	m_attributes.at(key) = value;
}

bool Item::doesContainAttribute(std::string key){
	return m_attributes.count(key) == 1;
}

std::string Item::getName(){
	return m_name;
}
