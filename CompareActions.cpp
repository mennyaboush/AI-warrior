#include "CompareActions.h"


double CompareActions::calculateScore(Action::eType type, Warrior & warrior)
{
	Action::RUN;
	switch (type)
	{
	case Action::RUN:
		calculateScoreRun(warrior);
		break;
	case Action::FIND_AMMO:
		calculateScoreFindAmmo(warrior);
		break;
	case Action::FIND_MED:
		calculateScoreFindMed(warrior);
		break;
	case Action::FIGHT:
		calculateScoreFight(warrior);
		break;
	case Action::HURT:
		calculateScoreHurt(warrior);
		break;
	default:
		break;
	}
}



/*f(w) = (maxGuns - currentGuns + maxGrandes - currentGrandes)/(MaxGuns + MaxGreandes) * 100 */
double CompareActions::calculateScoreFindAmmo(Warrior & w)
{
	double maxGuns = w.getMaxGrandes(), currentGuns = w.getGunsAmmo(),
		maxGrandes = w.getMaxGrandes(), currentGrandes = w.getGrenadeAmmo();
	return (maxGuns - currentGuns + maxGrandes - currentGrandes) / (maxGuns + maxGrandes) * 100;
}

/*f(w) = (MaxLife - currentLife)/MaxLife * 100 */
double CompareActions::calculateScoreFindMed(Warrior & w)
{
	double maxLife = w.getMaxLife(), life = w.getlifePoints();
	return (maxLife - life) / maxLife * 100;
}


/*f(w) = (calculateMedical + calculateAmmo + seftyScore) /(3 *maxScorAction::eType) * 100 */
double CompareActions::calculateScoreRun(Warrior & w)
{
	Maze* m = &Maze::getInstance();
	return (calculateScoreFindMed(w) + calculateScoreFindAmmo(w) + m->getSaftyScore(w.getLocation())) /
		(MAX_SCORE + MAX_SCORE + ConstValue::MAX_SAFTY_SCORE) * 100;
}
/*f(w) = MAX_SCORE - calcualteScoreRun */
double CompareActions::calculateScoreFight(Warrior & w)
{
	return MAX_SCORE - calculateScoreRun(w);
}

/*???*/
double CompareActions::calculateScoreHurt(Warrior & w)
{
	return 0.0;
}


CompareActions::CompareActions()
{
}


CompareActions::~CompareActions()
{
}


/*update the */
bool CompareActions::operator( )(Action* a1, Action* a2)
{
	//1. update Score
		//1.1 get the type and calculate the Score for a1.
		double score = this->calculateScore(a1->getType(), a1->getWarrior());
		a1->updateScore(score);
	
		//1.2 get the type and calculate the Score for a2.
		score = this->calculateScore(a2->getType(), a2->getWarrior());
		a1->updateScore(score);

	//2. compare scores
	return a1->getScore() < a2->getScore();
}