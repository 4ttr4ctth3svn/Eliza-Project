#include <SFML/Graphics.hpp>
#include "GUI/Window.hpp"
using namespace ELIZA;

void renderAIText(sf::RenderWindow& window, std::vector<Text> textVect, int index);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "ELIZA");
    sf::View viewport(sf::FloatRect(0.f, 0.f, 800.f, 500.f));
    window.setView(viewport);

    sf::Font font;
    if(!font.loadFromFile("font.ttf")) {
        perror("Could not load font!");
        std::exit(EXIT_FAILURE);
    }

    std::string buffer;
    int index = 0;
    std::vector<Text> textVect;

    Text userText(window, font);
    userText.setSize(20);
    userText.setColor(sf::Color::Black);
    userText.setPosition(0, 21);

    Text aiText(window, font);
    aiText.setSize(20);
    aiText.setColor(sf::Color::Magenta);
    aiText.setString("Buna ziua! Eu sunt ELIZA si voi fi asistentul dumneavoastra.");

    textVect.push_back(aiText);
    renderAIText(window, textVect, index);
    index++;
    textVect.push_back(userText);
    
    AiModel eliza("elisa.txt", "keywords.txt");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    if(event.text.unicode == 8 && !buffer.empty()) {
                        buffer.pop_back();
                        textVect[index].setString(buffer);
                    }
                    else if(event.text.unicode == 13 && !buffer.empty()) {
                        index++;
                        aiText.setString(eliza.raspuns(buffer));
                        buffer = "";
                        aiText.setPosition(0, index * 21);
                        textVect.push_back(aiText);
                        renderAIText(window, textVect, index);
                        index++;
                        userText.setPosition(0, index * 21);
                        textVect.push_back(userText);
                    }
                    else {
                        buffer += static_cast<char>(event.text.unicode);
                        textVect[index].setString(buffer);
                    }
                    break;
                case sf::Event::MouseWheelScrolled:
                    viewport.setCenter(viewport.getCenter().x, viewport.getCenter().y + event.mouseWheelScroll.delta * -5);
                    window.setView(viewport);
                    break;
            }
        }

        window.clear(sf::Color::White);
        for(int i = 0; i <= index; i++) {
            textVect[i].display();
        }
        window.display();
    }
    
    return 0;
}

void renderAIText(sf::RenderWindow& window, std::vector<Text> textVect, int index) {
    int len;
    len = textVect[index].getString().length();

    for(int i = 1; i <= len; i++) {
        window.clear(sf::Color::White);
        for(int i = 0; i < index; i++) {
            textVect[i].display();
        }
        Text displayText = textVect[index];
        displayText.setString(displayText.getString().substr(0, i));
        displayText.display();
        sf::sleep(sf::seconds(0.05));
        window.display();
    }
    // this is used to block all events happening during the rendering process
    sf::Event event;
    while(window.pollEvent(event));
}