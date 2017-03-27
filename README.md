# A5-Sorcery


## TODO List:

### Class: Player

A Player class will contain members like Hand, Board, Deck, Graveyard, HP, Magic. A Player takes care of the moves made by the players (play a card, end the turn, etc).

Deck, Hand, Graveyard, Board fields of Player will be implemented as vectors. Player will have overloaded methods of play: targeted or non-targeted.


### Class: Card

Superclass for cards in the game of sorcery. A card class contains basic information of a card, such as cost and name.

Subclass of Card are Minion, Spell, Ritual, Enchantment and Ability, with Enchantment being the decorator class for Minion. Ability is a special type of cards that makes up the Minions’ active/triggered abilities.


### Class: Display

The display.


## Schedule:

###Mon(Mar.27):

Basic implementations of Player and the game loop (Tianjun)

Deck loading (Tianjun)

The basic gameplay will start off initializing two players, every card in the 2 decks, and the display. Players will have hard-coded default decks if no deck is loaded from deck files.
 
The game loop only breaks when a player’s HP becomes 0 or forfeits. Active player will make as many moves (take cmd) as the player desire / the magic allows. After endTurn is called by the Active player, the game moves on to the other player’s start-of-turn phase and starts taking command that affects the other player, starting with drawing.





### Tue:

Minion(Tina),  Spell(Tianjun), Ability(Tianjun)

When a Spell card is played/a Minion’s ability is triggered, the card’s ability method is called, which accesses the boards through pointers, and then make changes according to the actual ability. Different methods will be implemented to achieve different behaviours when targeted at Player/Minion/Ritual.
 
When  Minion’s attack is targeted at the opponent Player, the HP of the player is reduced.


### Wed:

Gameplay - Minion attacking, etc (Tina)

Enchantment(Tina), Ritual(Tianjun)

Minion’s attack method, when invoked on other Minions, will perform a damage check. After every battle/damage spell, the Players will check the minion’s defense. When Minion1 attacks Minion2, Player1 deduct the attack of Minion2 from Minion1’s defense, while Player2 doing the same for Minion2.
 
If the defense is equal to or less than 0, a new Card* is added to the graveyard, and then the card is destroyed, other wise the deducted defense is displayed on the card. Other ways of a minion leaving the field due to spell/ritual will also be achieved through Player.

Enchantment works as Decorator of the Minion class, ability to recognize Enchantment object should be implemented.

Ritual works similarly to Minion, with a method that deducts charges every turn.


###Thurs

Gameplay&testing (Tina, Tianjun)

Triggers:
 
When an endTurn is called by either player, the game checks both player’s board for the corresponding triggered ability, in the order of end-of-turn then start-of-turn.

When a player summons a Minion or a Minion is added to grave/hand not by drawing, the game checks the entering/leaving board triggers.

Specific Commands  and Display will be added to the game loop and thus complete the basic functionalities.

### Fri-Sat

Testing (Tina, Tianjun)

A testing mode will be added.

### Sun + Mon:

Bonus features (Tina, Tianjun)

UML, Report(Tina, Tianjun)


## Questions:

### How could you design activated abilities in your code to maximize code reuse?

We can have an Abilities class with general types of abilities, and each minion owns 0-2 abilities. The parameters will consist of a general Card type and any additional information if necessary.

### What design pattern would be ideal for implementing Enchantment? Why?

Decorator pattern, because we don’t want to modify the original minion after it is initialized; adding/removing effects to the minion, and inspecting the minion  is also easier to implement with the decorator pattern, as we don’t need to manually delete or add effects to the minion.

### Suppose we found a solution to the space limitations of the current user interface and wanted to allow minions to have any number and combination of activated and triggered abilities. What design patterns might help us achieve this while maximizing code reuse?

As stated in question 1, all abilities belong to the Ability class.
An iterator pattern can be used for the triggered ability. The minion can have a map of triggered abilities, where the key is the condition and the value is the vector of abilities. When the condition is met, the minion’s triggered ability will be iterated and activated.
For active abilities, we can keep an array of abilities.


### How could you make supporting two (or more) interfaces at once easily while requiring minimal changes to the rest of the code

To support multiple interfaces, we can create an observer class for each type of interface, then we only need to add that observer to the subscription list of the original code and have the new observer class handle the rest.

