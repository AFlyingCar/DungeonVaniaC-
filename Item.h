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
