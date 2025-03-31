#include <SFML/Graphics.hpp>

namespace ELIZA
{

class Text
{
private:
    sf::RenderWindow& window;
    sf::Text _text;

public:
    
    Text(sf::RenderWindow& win, sf::Font& font);

    void setString(std::string renderString);

    void setStyle(unsigned int style);

    void setPosition(float x, float y);

    void setSize(unsigned int size);

    void setColor(int r, int g, int b);

    void setColor(sf::Color color);

    void display();

    std::string getString();
};

}