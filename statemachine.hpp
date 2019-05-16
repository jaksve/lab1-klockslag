//
// Created by drsve on 2019-05-15.
//

#ifndef GERMS_STATEMACHINE_HPP
#define GERMS_STATEMACHINE_HPP

#include "world.h"
#include <queue>


class state {
public:
    static void set_textures(sf::Texture* groundtex,sf::Texture * germtex,sf::Texture* guntex,sf::Texture* grentex, sf::Texture* walltex, sf::Font* font);
    virtual void handle(sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    bool is_done();
protected:

    struct texture_bank
    {
        texture_bank();
        void set_textures (sf::Texture* groundtex,sf::Texture * germtex,sf::Texture* guntex,sf::Texture* grentex, sf::Texture* walltex, sf::Font* font);
        sf::Texture* walltex;
        sf::Texture* groundtex;
        sf::Texture * germtex;
        sf::Texture* guntex;
        sf::Texture* grentex;
        sf::Font* font;
    };

    static texture_bank texs;
    bool done {false};
};

class menu_state : public state
{
public:
    menu_state();
    void handle (sf::Event & event) override;
    void update() override;
    void render(sf::RenderWindow & window) override;
private:
    sf::Text text;
    sf::Text text2;
    sf::Sprite wallsprite;
    const std::vector<std::string> output{"Player1","P1Germ1",
                                    "P1Germ2","P1Germ3",
                                    "P1Germ4","Player2",
                                    "P2Germ1","P2Germ2",
                                    "P2Germ3","P2Germ4"};
    std::vector<std::string> names{};

    uint8_t anicount{0};
    std::string input;
};

class game_state: public state
{
public:
    game_state();
    void handle (sf::Event & event) override;
    void update() override;
    void render(sf::RenderWindow & window) override;

private:
    ground mark;
    world game_world;


};


/*
class statemachine
{
public:

    statemachine();
    bool game_over();

    void push_state(state& st);

    //state& operator ++();
    state& current_state();

private:
    std::queue<state> ueue;
    bool over;

};
*/

#endif //GERMS_STATEMACHINE_HPP
