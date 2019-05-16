//
// Created by drsve on 2019-05-15.
//

#include "statemachine.hpp"
state::texture_bank state::texs = state::texture_bank();

void state::set_textures(sf::Texture *groundtex, sf::Texture *germtex, sf::Texture *guntex, sf::Texture *grentex,sf::Texture* walltex,
                         sf::Font *font)
{
    state::texs.set_textures(groundtex,germtex,guntex,grentex,walltex,font);
}

bool state::is_done()
{
    return done;
}

state::texture_bank::texture_bank():groundtex{nullptr},germtex{nullptr},guntex{nullptr},grentex{nullptr},walltex{nullptr},font{nullptr}
{}

void state::texture_bank::set_textures(sf::Texture *groundtex, sf::Texture *germtex, sf::Texture *guntex,
                                       sf::Texture *grentex,sf::Texture* walltex, sf::Font *font)
{
    this->groundtex = groundtex;
    this->germtex = germtex;
    this->guntex = guntex;
    this->grentex = grentex;
    this->walltex = walltex;
    this->font = font;
}


menu_state::menu_state():input{""}
{
    wallsprite.setTexture(*(texs.walltex) );
    wallsprite.setOrigin (texs.walltex->getSize().x / 2.f, texs.walltex->getSize().y / 2.f);
    wallsprite.scale(0.5f,0.5f);
    wallsprite.setPosition (640,360);

    text.setFont(*(texs.font) );
    text.setString("");
    text.setFillColor(sf::Color::Red);

    text2.setFont(*(texs.font) );
    text2.setString("Enter "+output[anicount]+"'s name: ");
    text2.setFillColor(sf::Color::Black);

    text2.setOrigin(0,text.getGlobalBounds().height/2);
    text.setOrigin(text2.getOrigin());
    //sf::Vector2f(720.f, 160.f)
    text2.setPosition(wallsprite.getPosition().x-320.f,wallsprite.getPosition().y-20);
    text.setPosition(text2.getPosition().x+text2.getGlobalBounds().width,text2.getPosition().y);

}

void menu_state::handle(sf::Event &event)
{
    switch(event.type)
    {
        case sf::Event::TextEntered :
            if(event.text.unicode == 8)
                {
                    if(input.size() != 0)
                    {
                        input.erase(input.size()-1);
                    }
                }
            else if (event.text.unicode == 13)
                {
                    names.push_back(input);
                    input="";
                    ++anicount;
                }

            else if( event.text.unicode == 9)
            {
                for(std::string s: names)
                {input += (s+"\n");}
            }
            else if(input.size()<=13)
            {
                input += (char)event.text.unicode;
            }

            if(anicount==10){
                done=true;
            }
            break;

        default:
            break;

    }

}

void menu_state::update()
{
    if(!done)
    {
        text2.setString("Enter "+output[anicount]+"'s name: ");
        text.setString(input);
    }
}

void menu_state::render(sf::RenderWindow &window)
{
    if(window.isOpen())
    {
        window.clear();
        window.draw(wallsprite);
        window.draw(text);
        window.draw(text2);
        window.display();
    }
}

/*
statemachine::statemachine():ueue{},over{false}
{}

void statemachine::push_state(state& st)
{
    ueue.push(std::move(st));
}

state& statemachine::current_state() {
    return ueue.front();
}


state& statemachine::operator++() {

    if(ueue.size() > 1)
    {ueue.pop();}

    else{over = true;}

    return ueue.front();
}


bool statemachine::game_over() {
    return over;
}

*/


game_state::game_state():mark{ground{ world_width, world_height, pixel_size, *(texs.groundtex) } },game_world{&mark}
{
    player player1{sf::Color::Red};
    player player2 {sf::Color::Blue};
    player1.add_germ(sf::Sprite{*texs.germtex},sf::Vector2f{width/2,50.f}, "Greve Jackula" ,font);
    player2.add_germ(sf::Sprite{*texs.germtex},sf::Vector2f{width/4.f,50.f}, "Eminem(not afraid)" ,font);
    player1.add_germ(sf::Sprite{*texs.germtex},sf::Vector2f{width/8.f,50.f},"THANOS",font);
    game_world.add_player(player1);
    game_world.add_player(player2);
}

void game_state::handle (sf::Event & event)
{
    if (event.type == sf::Event::MouseMoved) {
        auto mouse = event.mouseMove;

    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        auto mouse{event.mouseButton};
        // är det vänster musknapp?
        if (mouse.button == sf::Mouse::Button::Left)
        {
            game_world.explosion_at(sf::Vector2f(mouse.x,mouse.y),60.f);

        }
        else if(mouse.button ==sf::Mouse::Button::Right)
        {
            game_world.rotate();
        }
    }
}

void game_state::update()
{

}
