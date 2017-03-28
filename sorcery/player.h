#ifndef player_hpp
#define player_hpp

#include <iostream>
#include <vector>
#include <string>
#include "subject.h"
#include "observer.h"
#include "TextDisplay.c"

class Card;

class Player: public Observer, public Subject {
    int life; // default value 20
    int magic; // default value 3
    
    std::vector<Card*> Hand; //the hand, with a maximum number of 5 cards
    std::vector<Card*> Deck; //a hard-coded deck will be provided if no deck file
    std::vector<Card*> Graveyard; //Graveyard will contain the Spell played,
    //  out of charge Rituals
    //  died Minions
    std::vector<Card*> Board; //the board, where the Cards will be played
    //  Board[1] ~ Board[5] are Minion slots
    //  Board[6] is the Ritual slot
public:
    //Player(std::string deckname); //ctor for Player
    void play(int Cardno); //plays a Minion/Ritual/Non-targeted Spell
    //  /active non-targeted Minion ability
    void play(int CardOne, int CardTwo); //plays a targeted Spell/Minion ability
    void LifeModify();
    void MagicModify();
    void draw(); //draw adds the first element of Deck to Hand
    //  while removing that element from Deck
    void bury(); //bury adds a Card to Graveyard
    void forfeit(); //forfeit sets the Player's life to 0
    void endTurn(); //endTurn passes the active Player's turn
    void inspect();
    bool isLost(); //checks if the Player's life has become 0
    
    void notify() override; //the other player should call this for triggered ability checks
    
    // more to add..
};

#endif /* player_hpp */
