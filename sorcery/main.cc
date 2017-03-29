#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "player.hpp"
#include "card.hpp"

using namespace std;

//deck_loader loads from a .deck file and returns a vector containing
//  the name of the cards in the deck
vector<string> deck_loader(string deckname) {
    vector<string> return_vector;
    string temp;
    ifstream ifs{deckname+".deck"};
    while (getline(ifs,temp)) {
        return_vector.emplace_back(temp);
    }
    return return_vector;
}

int main(int argc, char* argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd, aux;
    int num;
    int num2;
    Player p1;
    Player p2;
    Player* activeP = &p1;
    Player* otherP = &p2;
    
    int turnno = 0;
    bool isTesting = false;
    vector<string> deck1;
    vector<string> deck2;
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
    
    for (auto n : deck1) {
        cout << n << endl;
    }
    for (auto n : deck2) {
        cout << n << endl;
    }
    
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
                cout << "help" << endl;
            }
            else if (cmd == "end") { //end turn
                cout << "turn end" << endl;
                turnno += 1;
                Player* temp = activeP;
                activeP = otherP;
                otherP = temp;
                activeP->draw(1);
            }
            else if (cmd == "quit") { //ends the game
                cout << "quit" << endl;
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
                cout << "attack" << endl;
                if (!(inpt>>num)) cin >> num;
                if (!(inpt>>num2)) {
                    if (cin >> num2) {
                        activeP->attack(num, num2);
                    } else {
                        auto temp = (activeP->getBoard(num))->getATK();
                        otherP->LifeModify(-temp);
                        (activeP->getBoard(num))->ModifyAct(-1);
                    }
                } else {
                    activeP->attack(num);
                }
            }
            
            else if (cmd == "play") { //play a card
                if (isTesting) {
                    cout << "dopePlay" << endl;
                    activeP->CurMagicSet(100);
                    if (!(inpt>>num)) cin >> num;
                    if (!(inpt>>num2)) {
                        if (cin >> num2) {
                            activeP->play(num, otherP->getBoard(num2));
                        } else if ((cin >> aux)&&(aux == "r")) {
                            activeP->play(num, otherP->getBoard(5));
                        } else {
                            activeP->play(num);
                        }
                    } else {
                        activeP->play(num, otherP->getBoard(num2));
                    }
                    activeP->CurMagicSet(0);
                } else {
                    cout << "play" << endl;
                    if (!(inpt>>num)) cin >> num;
                    if (!(inpt>>num2)) {
                        if (cin >> num2) {
                            activeP->play(num, otherP->getBoard(num2));
                        } else if ((cin >> aux)&&(aux == "r")) {
                            activeP->play(num, otherP->getBoard(5));
                        } else {
                            activeP->play(num);
                        }
                    } else {
                        activeP->play(num, otherP->getBoard(num2));
                    }
                }
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
