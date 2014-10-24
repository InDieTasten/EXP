#ifndef _util_hpp_
#define _util_hpp_

#include <iostream>
#include <sstream>
#include <list>
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <fstream>

namespace util
{
std::string toString(int);
std::string toString(bool);
std::string toString(float);
std::string toString(double);
std::string toString(char*);
std::string toString(std::list<std::string>);
std::string toString(sf::Color);
char getCharAt(std::string, int);

int toInt(std::string);
bool toBool(std::string);
float toFloat(std::string);
double toDouble(std::string);
sf::Color toColor(std::string);

float getMean(std::list<float> _x);
float getMean(std::list<int> _x);

void toStream(std::string, std::ofstream&);
std::string fromStream(std::ifstream&);

}

#endif