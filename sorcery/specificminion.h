#include "minion.h"
#include "specificability.h"
class AirElemental: public Minion{
public:
	AirElemental(Player *owner, Player *opp);	
};

class EarthElemental: public Minion{
public:
	EarthElemental(Player *owner, Player *opp);	
};

class BoneGolem: public Minion{
	vector<GainStat> trigAb  = {GainStat g("Gain +1/+1 whenever a Minion leaves play.")};
public:
	BoneGolem(Player *owner, Player *opp);
	void useTriggerAbility(std::shared_ptr<Card> c) override;
	std::string getTriggerDesc() override;
};

namespace Card::Minion{
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

}
}
