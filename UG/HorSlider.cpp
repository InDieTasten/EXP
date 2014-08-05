#include "HorSlider.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void HorSlider::Setup()
{
    isActive = false;
    moveSlide = false;
}
void HorSlider::Update(DataBank* _dataLink, int _x, int _y)
{
    decBox.setPosition((float)_x, (float)_y);
    decBox.setSize(sf::Vector2f((float)Height, (float)Height));
    decBox.setFillColor(sf::Color(0,0,0,128));
    decBox.setOutlineThickness(1.0f);
    decBox.setOutlineColor(sf::Color(255,0,0,200));

    incBox.setPosition((float)_x + Width-Height, (float)_y);
    incBox.setSize(sf::Vector2f((float)_x + Width - (_x + Width-Height), (float)Height));
    incBox.setFillColor(sf::Color(0,0,0,128));
    incBox.setOutlineThickness(1.0f);
    incBox.setOutlineColor(sf::Color(0,0,255,200));

    bar.setPosition((float)_x+7, (float)_y+Height/2-2);
    bar.setSize(sf::Vector2f((float)_x + Width-7-(_x+7), (float)_y+Height/2+2-(_y+Height/2-2)));
    bar.setFillColor(sf::Color(0,0,0,128));
    bar.setOutlineThickness(1.0f);
    bar.setOutlineColor(sf::Color(120,120,120,200));

    slider.setPosition((float) 2 + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2, (float)_y);
    slider.setSize(sf::Vector2f((float) (-2) + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) + (ratio*(Width-2*Height))/2 - (2 + _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2), (float)_y+Height - (_y)));
    slider.setFillColor(sf::Color(0,0,0,128));
    slider.setOutlineThickness(1.0f);
    slider.setOutlineColor(sf::Color(0,255,0,200));
}
void HorSlider::Render(DataBank* _dataLink)
{
    _dataLink->renderWindow->draw(bar);
    _dataLink->renderWindow->draw(decBox);
    _dataLink->renderWindow->draw(incBox);
    _dataLink->renderWindow->draw(slider);
}
void HorSlider::handleEvent(DataBank* datalink, sf::Event* _event, int _x, int _y, std::string _id)
{
    int mousex = sf::Mouse::getPosition().x;
    if(_event->type == sf::Event::MouseMoved && isActive)
    {
        int mousey = sf::Mouse::getPosition().y;
        hoverSlide = false;
        if(mousey >= _y && mousey <= _y+Height)
        {
            if(mousex >= _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) - (ratio*(Width-2*Height))/2 && mousex <= _x + Height+((ratio*(Width-2*Height))/2) + ((value-min)/(max-min))*(Width-2*Height-(ratio*(Width-2*Height))) + (ratio*(Width-2*Height))/2 - 2)
            {
                hoverSlide = true;
            }
        }
        if(moveSlide)
        {
            int delta = mousex-oldMouseX;
            //translate
            value += (max-min) / ((ratio*(Width-2*Height))/2)*ratio * delta;
            if (value>max)
            {
                value = max;
            }
            if (value<min)
            {
                value = min;
            }
        }
    }
    if(_event->type == sf::Event::MouseButtonReleased && isActive)
    {
        if(moveSlide)
        {
            moveSlide = false;
        }
    }
    if(_event->type == sf::Event::MouseButtonPressed && isActive)
    {
        if(hoverSlide)
        {
            moveSlide = true;
        }
    }
    oldMouseX = mousex;
}
