#include <iostream>

class Winning_Word{
    char character;
    bool guessed;
public:
    Winning_Word(char character, bool guessed){
        this -> character = character;
        this -> guessed = guessed;
    }
    void setGuess(){
        guessed = true;
    }
    bool getGuess() const{
        return guessed;
    }
    char getCharacter() const{
        return character;
    }
};
