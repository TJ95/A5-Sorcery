#ifndef player_hpp
#define player_hpp

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "subject.h"
#include "observer.h"
#include "textdisplay.h"

class Card;

class Player: public Observer, public Subject {
    int life = 20;
    int magic = 3;
    int current_magic;
    
    std::vector<std::shared_ptr<Card>> Hand; //the hand, with a maximum number of 5 cards
    std::vector<std::shared_ptr<Card>> Deck; //a default deck will be provided if no deck file
    std::vector<std::shared_ptr<Card>> Graveyard; //Graveyard will contain the Spell played,
    //  out of charge Rituals
    //  died Minions
    std::vector<std::shared_ptr<Card>> Board; //the board, where the Cards will be played
    //  Board[1] ~ Board[5] are Minion slots
    //  Board[6] is the Ritual slot
public:
    //Player(std::string deckname); //ctor for Player
    void LifeModify(int n);
    void MagicModify(int n);
    void CurMagicModify(int n);
    void CurMagicSet(int n);
    void play(int card); //plays a minion/ritual
    void play(int card, int targ, Player* p); //plays a targeted Spell/Enchant
    std::shared_ptr<Card> getBoard (int slot);
    void draw(int time); //draw adds the first element of Deck to Hand
    //  while removing that element from Deck
    void discard(int i);
    void bury(); //bury looks for dead minion adds a Card to Graveyard
    void attack(int i);
    void forfeit(); //forfeit sets the Player's life to 0
    void endTurn(); //endTurn passes the active Player's turn
    void inspect(int i);
    bool isLost(); //checks if the Player's life has become 0
    
    void notify() override; //the other player should call this for triggered ability checks
    
    // more to add..
};

#endif /* player_hpp */
