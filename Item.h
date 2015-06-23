/*
 * Header file for the Item class
 * Has dynamic attributes, stored as a key-value pair map
*/
#ifndef _ITEM_H_
#define _ITEM_H_

#include <map>
#include <string>

typedef std::map<std::string,int> attrList; 

class Item{
public:
	Item(std::string newName);
	~Item();
	void addAttribute(std::string key, int value);
	attrList getAllAttributes();
	int getItemAttribute(std::string key);
	void setItemAttribute(std::string key, int value);
	bool doesContainAttribute(std::string key);
	std::string getName();
private:
	attrList m_attributes;
	std::string m_name;
};

#endif

// And before you ask, yes there is a much better way to do this, but I don't feel like it because it's 12:00 right now and I don't want to change this from the original project
