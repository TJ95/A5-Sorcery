#ifndef player_hpp
#define player_hpp

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "subject.h"
#include "observer.h"
#include "textdisplay.h"
#include "minion.h"
#include "const.h"

class Card;
class Ritual;

class Player: public Observer, public Subject {
    std::string name = "Player";
    int life;
    int magic;
    int current_magic;
    std::shared_ptr<Ritual> shrine; //the ritual slot
    std::vector<std::shared_ptr<Card>> Hand; //the hand, with a maximum number of 5 cards
    std::vector<std::shared_ptr<Card>> Deck; //a default deck will be provided if no deck file
    std::vector<std::shared_ptr<Minion>> Graveyard; //Graveyard will contain dead Minions
    std::vector<std::shared_ptr<Minion>> Board; //the board, where the Minions will be played
    public:
    Player(std::string name);
    void LifeModify(int n);
    void MagicModify(int n);
    void CurMagicModify(int n);
    void CurMagicSet(int n);
    void DeckSet(std::vector<std::shared_ptr<Card>> d);
    void play(int card); //plays a minion
    void play(int card, int targ, Player* p); //plays a targeted Spell/Enchant
    void use(int m, int targ, Player* p);
    std::shared_ptr<Minion> getBoard (int slot);
    std::shared_ptr<Ritual> getR ();
    int getPop();
    void altSummon(std::shared_ptr<Minion> m);
    void rez(Player* p);
    void draw(int time); //draw adds the first element of Deck to Hand
    //  while removing that element from Deck
    void trigger(Player* p, std::string s, int targ, int owner);
    void discard(int i);
    void bury(); //bury looks for dead minion adds a Card to Graveyard
    void buryR();
    void takeback(int i);
    void attack(int i);
    void forfeit(); //forfeit sets the Player's life to 0
    void endTurn(); //endTurn passes the active Player's turn
    void inspect(int i);
    bool isLost(); //checks if the Player's life has become 0
    void shuffle();
    
    void notify() override;
    
    // more to add..
};

#endif /* player_hpp */
