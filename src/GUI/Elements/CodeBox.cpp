#include "GUI/Elements/CodeBox.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void CodeBox::Setup()
{
    text.push_back("");
    cursor_line = 1;
    cursor_char = 1;
}
void CodeBox::Update(int _x, int _y, std::string _id, std::string _mID)
{
    for(std::list<std::string>::iterator it=text.begin(); it != text.end(); ++it)
    {
        text1.setString(*it);
        text1.setPosition((float)_x, (float)_y);
        text1.setFont(*dLink->FontGet("$_menuTitle"));
        text1.setCharacterSize(12);
        text1.setScale(1.0,1.0);

        rect.setPosition((float)_x,(float)_y);
        rect.setSize(sf::Vector2f((float)Width,(float)Height));
        rect.setFillColor(sf::Color(20,20,20,150));
        rect.setOutlineThickness(1.0f);
        rect.setOutlineColor(sf::Color(255,255,255,50));
    }
    std::list<std::string>::iterator it = text.begin();
    for(int i = cursor_line; i > 0; i--)
    {
        it++;
    }
    Y = (cursor_line*12);
    X =	(cursor_char*7);

    c.setPosition((float)X,(float)Y);
    c.setSize(sf::Vector2f(7.0,12.0));
    c.setFillColor(sf::Color(20,220,20,150));
    c.setOutlineThickness(1.0f);
    c.setOutlineColor(sf::Color(50,255,50,50));
}
void CodeBox::Render(int _x, int _y, std::string _id, std::string _mID)
{
    dLink->renderWindow->draw(rect);
    dLink->renderWindow->draw(c);
    dLink->renderWindow->draw(text1);

}
void CodeBox::handleEvent(sf::Event* _event, int _x, int _y, std::string _id, std::string _mID)
{
    std::list<std::string>::iterator it = text.begin();
    for(int i = cursor_line; i > 0; i--)
    {
        it++;
    }

    if(isActive)
    {

    }
}
void CodeBox::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}
void CodeBox::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id, std::string _mID)
{

}