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
	initAbilities();
	public:
		BoneGolem(Player *owner, Player *opp);
};

class FireElemental: public Minion{
	initAbilities();
	public:
		FireElemental(Player *owner, Player *opp);
};

class PotionSeller: public Minion{
	initAbilities();
	public:
		PotionSeller(Player *owner, Player *opp);
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
		trigAb[M_out]=v;
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
		trigAb[M_in]=v;
	}
	PotionSeller::PotionSeller(Player *owner, Player *opp):Minion(owner,opp){
		this->owner=owner;
	    this->opp=sp;
		attk=2;
		defence=2;
		maxDefence=2;
		name="Fire Elemental";
		cost = 2;
		initAbilities();
		
	}
	void PotionSeller::PotionSeller(){
		SingleDamage sd("Whenever an opponent's minion enters play, deal 1 damage to it.",1,0);
		std::vector<Ability> trig = {sd};
		trigAb[M_in]=v;
	}


