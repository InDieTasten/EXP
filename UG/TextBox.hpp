#ifndef _TextBox_hpp_
#define _TextBox_hpp_

#include <string.h>
#include "DataBank.hpp"


class TextBox
{
	//MEMBERS
private:
	sf::RectangleShape rect;
	char tmp;
	sf::Text text1;
	bool clear;

public:
	std::string text;
	//std::list<sf::Text> text1;
	int X;
	int Y;
	int Height;
	int Width;
	std::string ID;
	bool isActive;
	bool multiline;

	//CONSTRUCTORS

	//DESTRUCTORS

	//METHODS
	void Show();
	void Hide();

	void Setup();
	void Update(DataBank* _dataLink, int _x, int _y,std::string _id);
	void Render(DataBank* _dataLink, int _x, int _y, std::string _id);
	void handleEvent(DataBank* _dataLink,sf::Event* _event, int _x, int _y,std::string _id);
};

#endif
