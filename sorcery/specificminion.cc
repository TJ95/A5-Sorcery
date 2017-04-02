#include "minion.h"
#include "specificability.h"
#include "const.h"
class AirElemental: public Minion{
public:
	AirElemental(Player *owner, Player *opp);	
};

class EarthElemental: public Minion{
public:
	EarthElemental(Player *owner, Player *opp);	
};

class BoneGolem: public Minion{
	void initAbilities();
	public:
		BoneGolem(Player *owner, Player *opp);
};

class FireElemental: public Minion{
	void initAbilities();
	public:
		FireElemental(Player *owner, Player *opp);
};

class PotionSeller: public Minion{
	void initAbilities();
	public:
		PotionSeller(Player *owner, Player *opp);
};

class NovicePyromancer: public Minion{
	void initAbilities();
	public:
		NovicePyromancer(Player *owner, Player *opp);
};

class ApprenticeSummoner: public Minion{
	void initAbilities();
	public:
		ApprenticeSummoner(Player *owner, Player *opp);
};

class MasterSummoner: public Minion{
	void initAbilities();
	public:
		MasterSummoner(Player *owner, Player *opp);
};

	AirElemental::AirElemental(Player *owner, Player *opp):Minion(owner,opp){
		this->owner=owner;
	    this->opp=sp;
		attk=1;
		defence=1;
		maxDefence=1;
		name="Air Elemental";
		cost = 0;
	}

	EarthElemental::EarthElemental(Player *owner, Player *opp):Minion(owner,opp){
	this->owner=owner;
	    this->opp=sp;
		attk=4;
		defence=4;
		maxDefence=4;
		name="Earth Elemental";
		cost = 3;
	}
	BoneGolem::BoneGolem(Player *owner, Player *opp):Minion(owner,opp){
	this->owner=owner;
	    this->opp=sp;
		attk=1;
		defence=3;
		maxDefence=3;
		name="Bone Golem";
		cost = 2;
		initAbilities();
		
	}

	void BoneGolem::initAbilities(){
		GainStat g(owner,"Gain +1/+1 whenever a Minion leaves play.",1,1,0,this);
		std::vector<Ability> trig = {g};
		trigAb[M_out]=trig;
	}

	FireElemental::FireElemental(Player *owner, Player *opp):Minion(owner,opp){
		this->owner=owner;
	    this->opp=sp;
		attk=2;
		defence=2;
		maxDefence=2;
		name="Fire Elemental";
		cost = 2;
		initAbilities();
		
	}

	void FireElemental::initAbilities(){
		SingleDamage sd("Whenever an opponent's minion enters play, deal 1 damage to it.",1,0);
		std::vector<Ability> trig = {sd};
		trigAb[M_in]=trig;
	}

	PotionSeller::PotionSeller(Player *owner, Player *opp):Minion(owner,opp){
		this->owner=owner;
	    this->opp=sp;
		attk=2;
		defence=2;
		maxDefence=2;
		name="Potion Seller";
		cost = 2;
		initAbilities();
		
	}

	void PotionSeller::initAbilities(){
		AoEHealing ah(owner,"At the end of your turn, all your minions gain +0/+1",1,0);
		std::vector<Ability> trig = {ah};
		trigAb[EoT]=trig;
	}

	NovicePyromancer::NovicePyromancer(Player *owner, Player *opp):Minion(owner,opp){
		this->owner=owner;
	    this->opp=sp;
		attk=0;
		defence=1;
		maxDefence=1;
		name="Novice Pyromancer";
		cost = 1;
		initAbilities();
	}

	void NovicePyromancer::initAbilities(){
		SingleDamage sd("Deal 1 damage to target minion.",1,1);
		actAb = {sd};
	}
ApprenticeSummoner::ApprenticeSummoner(Player *owner, Player *opp):Minion(owner,opp){
		this->owner=owner;
	    this->opp=sp;
		attk=1;
		defence=1;
		maxDefence=1;
		name="Apprentice Summoner";
		cost = 1;
		initAbilities();
	}

	void ApprenticeSummoner::initAbilities(){
		std::shared+ptr<Minion>ae = std::make_shared<Minion>(new AirElemental(owner,opp));
		Summon s("Summon a 1/1 air elemental.",ae,1);
		actAb = {s};
	}
MasterSummoner::MasterSummoner(Player *owner, Player *opp):Minion(owner,opp){
		this->owner=owner;
	    this->opp=sp;
		attk=2;
		defence=3;
		maxDefence=3;
		name="Master Summoner";
		cost = 3;
		initAbilities();
	}

	void MasterSummoner::initAbilities(){
		std::shared+ptr<Minion>ae = std::make_shared<Minion>(new AirElemental(owner,opp));
		Summon s("Summon up to 3 1/1 air elementals.",ae,3);
		actAb = {s};
	}