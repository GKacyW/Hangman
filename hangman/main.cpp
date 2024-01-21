#include <iostream>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "word.h"

using namespace std;
using namespace sf;
void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}
string getWord(const string& filename){
    vector<string> words;
    fstream file(filename, ios_base::in);
    if (file.is_open()) {
        string sa;
        while (getline(file, sa)) {
            //cout << sa << "\n";
            words.push_back(sa);
        }
        file.close();
    }
    if(words.empty()){
        return "NO WORDS FOUND!!!!";
    }
    int x = (rand()%words.size());
    return words.at(x);
}
void loadSprites(vector<Texture> &sprites){
    sf::Texture zero;
    zero.loadFromFile("files/hangman_0.png");

    sf::Texture one;
    one.loadFromFile("files/hangman_1.png");

    sf::Texture two;
    two.loadFromFile("files/hangman_2.png");

    sf::Texture three;
    three.loadFromFile("files/hangman_3.png");

    sf::Texture four;
    four.loadFromFile("files/hangman_4.png");

    sf::Texture five;
    five.loadFromFile("files/hangman_5.png");

    sf::Texture six;
    six.loadFromFile("files/hangman_lose.png");

    sf::Texture seven;
    seven.loadFromFile("files/hangman_win.png");

    sprites.push_back(zero);
    sprites.push_back(one);
    sprites.push_back(two);
    sprites.push_back(three);
    sprites.push_back(four);
    sprites.push_back(five);
    sprites.push_back(six);
    sprites.push_back(seven);

}

int main(){
    bool game_continue = true;
    while(game_continue) {

        RenderWindow welcome(sf::VideoMode(500, 500), "Hangman");
        Font font;
        font.loadFromFile("files/font.ttf");

        sf::Text hello;
        hello.setFont(font);
        hello.setString("   WELCOME TO \n ** HANGMAN **");
        hello.setCharacterSize(50);
        hello.setStyle(sf::Text::Bold);
        hello.setFillColor(Color::Black);
        setText(hello, (500 / 2.0f), 500 / 2.0f - 150);

        sf::Text select;
        select.setFont(font);
        select.setString("1. Words\n2. Animals\n3. Places\n4. Random");
        select.setCharacterSize(25);
        select.setStyle(sf::Text::Bold);
        select.setFillColor(Color::Black);
        setText(select, (500 / 2.0f), 270);

        sf::Text close;
        close.setFont(font);
        close.setString("QUIT");
        close.setCharacterSize(20);
        close.setStyle(sf::Text::Bold);
        close.setFillColor(Color::Black);
        setText(close, 500 / 2.0f, 450);

        RectangleShape b_quit;
        b_quit.setSize(Vector2f(80, 40));
        b_quit.setFillColor(Color::White);
        b_quit.setPosition(210, 430);
        RectangleShape b_words;
        b_words.setSize(Vector2f(150, 30));
        b_words.setFillColor(Color::White);
        b_words.setPosition(185, 210);
        RectangleShape b_animals;
        b_animals.setSize(Vector2f(150, 30));
        b_animals.setFillColor(Color::White);
        b_animals.setPosition(185, 240);
        RectangleShape b_places;
        b_places.setSize(Vector2f(150, 30));
        b_places.setFillColor(Color::White);
        b_places.setPosition(185, 270);
        RectangleShape b_random;
        b_random.setSize(Vector2f(150, 30));
        b_random.setFillColor(Color::White);
        b_random.setPosition(185, 300);


        welcome.clear(Color::White);
        welcome.draw(b_quit);
        welcome.draw(hello);
        welcome.draw(select);
        welcome.draw(close);
        welcome.draw(b_words);
        welcome.display();

        string word;
        string filename;

        Event event;
        while (welcome.isOpen()) {
            while (welcome.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    welcome.close();
                    return 0;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i pos = sf::Mouse::getPosition(welcome);
                    if (b_quit.getGlobalBounds().contains(pos.x, pos.y)) {
                        welcome.close();
                        return 0;
                    }
                    if (b_words.getGlobalBounds().contains(pos.x, pos.y)) {
                        word = getWord("files/words.txt");
                        welcome.close();
                    }
                    if (b_animals.getGlobalBounds().contains(pos.x, pos.y)) {
                        word = getWord("files/animals.txt");
                        welcome.close();
                    }
                    if (b_places.getGlobalBounds().contains(pos.x, pos.y)) {
                        word = getWord("files/places.txt");
                        welcome.close();
                    }
                    if (b_random.getGlobalBounds().contains(pos.x, pos.y)) {
                        int x = (rand() % 3 + 1);
                        if (x == 1) {
                            word = getWord("files/words.txt");
                        } else if (x == 2) {
                            word = getWord("files/animals.txt");
                        } else if (x == 3) {
                            word = getWord("files/places.txt");
                        }
                        welcome.close();
                    }
                }

            }
            welcome.clear(Color::White);
            welcome.draw(b_words);
            welcome.draw(b_animals);
            welcome.draw(b_quit);
            welcome.draw(b_places);
            welcome.draw(b_random);
            welcome.draw(hello);
            welcome.draw(select);
            welcome.draw(close);

            welcome.display();
        }

        vector<Winning_Word> final_word;
        for (char a: word) {
            Winning_Word letter(a, false);
            final_word.push_back(letter);
        }
        RenderWindow game(sf::VideoMode(500, 500), "Hangman");

        vector<Texture> sprites;
        loadSprites(sprites);


        vector<char> player_guess;
        string Guess;
        Text guess;
        guess.setFont(font);
        guess.setCharacterSize(30);
        guess.setFillColor(sf::Color::Magenta);
        guess.setPosition(500 / 2.0f, 390);
        guess.setString("|");

        Text lose_message;
        lose_message.setFont(font);
        lose_message.setCharacterSize(30);
        lose_message.setFillColor(sf::Color::Red);
        setText(lose_message, 70, 370);
        lose_message.setString("OMG! YOU KILLED HIM!1!!");


        string print = "";
        for (Winning_Word a: final_word) {
            if (!a.getGuess()) {
                print += "_ ";
            } else {
                print += a.getCharacter();
            }
        }

        sf::Text display_word;
        display_word.setFont(font);
        display_word.setCharacterSize(30);
        display_word.setFillColor(sf::Color::Black);
        setText(display_word, 50, 300);
        display_word.setString(print);

        int placement = 0;
        Sprite sprite;
        sprite.setTexture(sprites[placement]);
        sprite.setPosition(250, 0);

        vector<char> incorrect;
        vector<char> already_guessed;
        RectangleShape store;
        store.setSize(Vector2f(150, 130));
        store.setOutlineColor(Color::Black);
        store.setOutlineThickness(3);
        store.setPosition(50, 70);

        sf::Text new_game;
        new_game.setFont(font);
        new_game.setString("NEW GAME");
        new_game.setCharacterSize(20);
        new_game.setStyle(sf::Text::Bold);
        new_game.setFillColor(Color::Black);
        setText(new_game, 170, 450);
        setText(close, 340, 450);

        Text wrong;
        wrong.setFont(font);
        wrong.setString("");
        wrong.setCharacterSize(30);
        wrong.setFillColor(Color::Black);
        setText(wrong, 55, 65);

        RectangleShape b_ng;
        b_ng.setSize(Vector2f(130, 40));
        b_ng.setFillColor(Color::White);
        b_ng.setPosition(105, 430);
        // b_quit.setFillColor(Color::Red);
        b_quit.setPosition(300, 430);

       // cout << word << endl;
        game.clear(Color::White);
        game.draw(sprite);
        game.draw(display_word);
        game.draw(guess);
        game.draw(b_ng);
        game.draw(new_game);
        game.display();
        Event e;
        while (game.isOpen()) {
            while (game.pollEvent(e)) {
                if (e.type == sf::Event::Closed) {
                    game.close();
                    return 0;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i pos = sf::Mouse::getPosition(game);
                    if (b_quit.getGlobalBounds().contains(pos.x, pos.y)) {
                        game.close();
                        return 0;
                    }
                    if (b_ng.getGlobalBounds().contains(pos.x, pos.y)) {
                        while(!already_guessed.empty()){
                            already_guessed.pop_back();
                        }
                        while(!final_word.empty()){
                            final_word.pop_back();
                        }
                        while(!incorrect.empty()){
                            incorrect.pop_back();
                        }
                        placement = 0;
                        game.close();
                    }
                }
                if (placement < 6) {
                    if (e.type == sf::Event::KeyPressed) {
                        if (e.key.code == Keyboard::Return) {
                            //cout << "enter" << endl;
                            //cout << player_guess.size() << endl;
                            if (player_guess.size() == 1) {
                                bool found = false;
                                if(!count(already_guessed.begin(), already_guessed.end(), player_guess[0])) {
                                    already_guessed.push_back(player_guess[0]);
                                    for (int i = 0; i < player_guess.size(); i++) {
                                        for (int j = 0; j < final_word.size(); j++) {
                                            if (player_guess[i] == final_word[j].getCharacter()) {
                                                final_word[j].setGuess();
                                                found = true;
                                            }
                                        }
                                    }
                                    if (!found) {

                                        incorrect.push_back(player_guess[0]);
                                        placement += 1;
                                    }
                                }
                            }
                            else if(player_guess.size() > 1){
                                string playerGuess = "";
                                for(char a: player_guess){
                                    playerGuess += a;
                                }
                                //cout << playerGuess << endl;
                                if(playerGuess == word){
                                    placement = 7;
                                    for(int i = 0; i < final_word.size(); i ++){
                                        final_word[i].setGuess();
                                    }
                                }
                                else{
                                    placement += 1;
                                }

                            }
                            Guess = "|";
                            guess.setString(Guess);

                            while (!player_guess.empty()) {
                                player_guess.pop_back();
                            }

                        }


                    }
                    if (e.type == Event::TextEntered) {
                        if (e.text.unicode == '\b') {
                            if (player_guess.empty()) {
                                continue;
                            } else {
                                player_guess.pop_back();
                            }
                        }
                        char a = e.text.unicode;
                        if (isalpha(a)) {
                            player_guess.push_back(tolower(a));

                        }
                        Guess = "";
                        for (char b: player_guess) {
                            Guess += b;
                        }
                        Guess += "|";
                        guess.setString(Guess);
                    }
                }
            }
            print = "";
            if(placement >= 6){
                for (Winning_Word a: final_word) {
                    print += " ";
                    print += a.getCharacter();
                    print += "  ";
                }
            }
            else {
                for (Winning_Word a: final_word) {
                    if (a.getGuess()) {
                        print += " ";
                        print += a.getCharacter();
                        print += "  ";
                    } else {
                        print += "_ ";
                    }
                }
            }

            game.clear(Color::White);

            //printing letters already guessed (incorrect)
            string print_wrong = "";
            int count = 1;
            for(char a: incorrect){
                print_wrong += a;
                if(count%5==0){print_wrong += "\n";}
                else{print_wrong += "  ";}
                count ++;
            }



            display_word.setPosition(50, 300);
            sprite.setTexture(sprites[placement]);
            display_word.setString(print);
            game.draw(close);
            if(placement == 7){
                lose_message.setString("OMG! YOU SAVED HIM!");
            }
            if (placement < 6) { game.draw(guess); }
            else if(placement >= 6) { game.draw(lose_message); }
            game.draw(b_quit);
            game.draw(display_word);
            game.draw(close);
            setText(guess, 500 / 2.0f, 390);
            game.draw(sprite);
            game.draw(store);
            game.draw(b_ng);
            game.draw(new_game);
            wrong.setString(print_wrong);
            game.draw(wrong);
            game.display();
        }
    }

    return 0;


}
