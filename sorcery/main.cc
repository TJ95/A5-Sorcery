#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "player.hpp"
#include "card.hpp"

using namespace std;

//deck_loader loads from a .deck file and returns a vector containing
//  the name of the cards in the deck
vector<Card*> deck_loader(string deckname) {
    vector<Card*> return_deck;
    string temp;
    ifstream ifs{deckname+".deck"};
    while (getline(ifs,temp)) {
        if (temp == "Air Element") {
            auto cp = make_shared<Card> { new AirElement };
            return_deck.emplace_back(cp);
        } else if (temp == "Earth Element") {
            auto cp = make_shared<Card> { new EarthElement };
            return_deck.emplace_back(cp);
        } else if (temp == "Bone Golem") {
            auto cp = make_shared<Card> { new BoneGolem };
            return_deck.emplace_back(cp);
        } else if (temp == "Potion Seller") {
            auto cp = make_shared<Card> { new PotionSeller };
            return_deck.emplace_back(cp);
        } else if (temp == "Fire Elemental") {
            auto cp = make_shared<Card> { new FireElement };
            return_deck.emplace_back(cp);
        } else if (temp == "Novice Pyromancer") {
            auto cp = make_shared<Card> { new NovicePyromancer };
            return_deck.emplace_back(cp);
        } else if (temp == "Apprentice Summoner") {
            auto cp = make_shared<Card> { new ApprenticeSummoner };
            return_deck.emplace_back(cp);
        } else if (temp == "Master Summoner") {
            auto cp = make_shared<Card> { new MasterSummoner };
            return_deck.emplace_back(cp);
        } else if (temp == "Banish") {
            auto cp = make_shared<Card> { new Banish };
            return_deck.emplace_back(cp);
        } else if (temp == "Unsummon") {
            auto cp = make_shared<Card> { new Unsummon };
            return_deck.emplace_back(cp);
        } else if (temp == "Disenchant") {
            auto cp = make_shared<Card> { new Disenchant };
            return_deck.emplace_back(cp);
        } else if (temp == "Raise Dead") {
            auto cp = make_shared<Card> { new RaiseDead };
            return_deck.emplace_back(cp);
        } else if (temp == "Blizzard") {
            auto cp = make_shared<Card> { new Blizzard };
            return_deck.emplace_back(cp);
        } else if (temp == "Giant Strength") {
            auto cp = make_shared<Card> { new GiantStrenth };
            return_deck.emplace_back(cp);
        } else if (temp == "Enrage") {
            auto cp = make_shared<Card> { new Enrage };
        } else if (temp == "Haste") {
            auto cp = make_shared<Card> { new Haste };
            return_deck.emplace_back(cp);
        } else if (temp == "Magic Fatigue") {
            auto cp = make_shared<Card> { new MagicFatigue };
            return_deck.emplace_back(cp);
        } else if (temp == "Silence") {
            auto cp = make_shared<Card> { new Silence };
            return_deck.emplace_back(cp);
        } else if (temp == "Dark Ritual") {
            auto cp = make_shared<Card> { new DarkRitual };
            return_deck.emplace_back(cp);
        } else if (temp == "Aura of Power") {
            auto cp = make_shared<Card> { new AuraofPower };
            return_deck.emplace_back(cp);
        } else if (temp == "Standstill") {
            auto cp = make_shared<Card> { new Standstill };
            return_deck.emplace_back(cp);
        } else {
            cout << "There is no such card as" << temp << "!" << end;
        }
    }
    return return_deck;
}

int main(int argc, char* argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd, aux;
    int num, num2, num3;
    Player p1("player1");
    Player p2("player2");
    Player* activeP = &p1;
    Player* otherP = &p2;
    
    int turnno = 0;
    bool isTesting = false;
    vector<shared_ptr<Card>> deck1;
    vector<shared_ptr<Card>> deck2;
    ifstream inpt;
    
    //command line arguments
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            string s = argv[i];
            if (s == "-testing") {
                isTesting = true;
                cout << "testing mode actived"<<endl;
            }
            else if (s == "-deck1") {
                deck1 = deck_loader(argv[i+1]);
                i++;
                cout << "deck1 loaded" << endl;
            }
            else if (s == "-deck2") {
                deck1 = deck_loader(argv[i+1]);
                i++;
                cout << "deck2 loaded" << endl;
            }
            else if (s == "-init") {
                aux = argv[i+1];
                inpt = ifstream{aux};
                cout << "init" << endl;
            }
            else if (s == "graphics") {
                cout << "init" << endl;
            }
        }
    }
    
    //load the default deck for players if no deck is given
    if (deck1.size() == 0) deck1 = deck_loader("default");
    if (deck2.size() == 0) deck2 = deck_loader("default");
    
    p1->DeckSet(deck1);
    p2->DeckSet(deck2);
    
    try {
        while (true) {
            if (p1.isLost()||p2.isLost()) {
                if (p1.isLost()) {
                    cout << "p1 won" << endl;
                    break;
                } else {
                    cout << "p2 won" << endl;
                    break;
                }
            }
            if (!( inpt >> cmd )) {
                cin >> cmd;
            }
            
            if (cmd == "help") { //help message
                cout << "Commands:  help -- Display this message." << endl;
                cout << "           end -- End the current player’s turn." << endl;
                cout << "           quit -- End the game."<<endl;
                cout << "           attack minion other-minion -- Orders minion to attack other-minion." << endl;
                cout << "           attack minion -- Orders minion to attack the opponent." << endl;
                cout << "           play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
                cout << "           use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player. inspect minion -- View a minion’s card and all enchantments on that minion." << endl;
                cout << "           hand -- Describe all cards in your hand." << endl;
                cout << "           board -- Describe all cards on the board." << endl;
            }
            else if (cmd == "end") { //end turn
                //EoT trigger
                
                turnno += 1;
                swap(activeP, otherP);
                
                activeP->MagicModify(1);
                activeP->CurMagicSet(1);
                activeP->draw(1);
                //SoT trigger
            }
            else if (cmd == "quit") { //ends the game
                cout << "bye! ;(" << endl;
                break;
            }
            else if ((cmd == "draw")&&(isTesting)) { //draw a card
                cout << "draw" << endl;
                activeP->draw(1);
            }
            else if ((cmd == "discard")&&(isTesting)) { //discard a hand card
                cout << "discard" << endl;
                if (!(inpt>>num)) cin >> num;
                activeP->discard(num);
            }
            else if (cmd == "attack") { //minion attack
                if (inpt>>num) {
                    if (inpt>>num2) {
                        activeP->getBoard(num - 1)->attack(otherP->getBoard(num - 1));
                    } else {
                        activeP->getBoard(num - 1)->attack(otherP);
                    }
                } else {
                    cin >> num;
                    if (cin>>num2) {
                        activeP->getBoard(num - 1)->attck(otherP->getBoard(num - 1));
                    } else {
                        activeP->getBoard(num - 1)->attack(otherP);
                    }
                }
            }
            else if (cmd == "play") { //play a card
                if (isTesting) activeP->CurMagicSet(100);
                if (!(inpt>>num)) {
                    cin >> num;
                    if (cin>>num2) {
                        Player* pp = (num2 == 1)? nullptr:otherP;
                        if ((cin>>aux)&&(aux == "r")) {
                            activeP->play(num, 6, pp);
                        } else {
                            cin >> num3;
                            activeP->play(num, num3, pp);
                        }
                    }
                } else {
                    inpt >> num2;
                    Player* pp = (num2 == 1)? nullptr:otherP;
                    if ((inpt>>aux)&&(aux == "r")) {
                        activeP->play(num, 6, pp);
                    } else {
                        inpt >> num3;
                        activeP->play(num, num3, pp);
                    }
                }
                if (isTesting) activeP->CurMagicSet(0);
            }
            else if (cmd == "use") { //minion ability
                cout << "use" << endl;
            }
            else if (cmd == "inspect") { //description of a card
                cout << "inspect" << endl;
            }
            else if (cmd == "hand") { // show hand
                cout << "hand" << endl;
            }
            else if (cmd == "board") { //show board
                cout << "board" << endl;
            }
            else {
                cout << "invalid command" << endl;
            }
        }
    }
    catch (ios::failure &) {
    }
}
