#include "score.ih"

Behavior::ConfidenceInterval Score::getCapability(rf<State> s, rf<Goal> g)
{
  WorldModel& wm = WorldModel::getInstance();
  
//  return wm.onMyBack() || wm.onMyBelly() || wm.onMySide() ? ConfidenceInterval(0.0, 0.0) : ConfidenceInterval(0.5, 0.2);

  if( wm.onMyBack() || wm.onMyBelly() || wm.onMySide() ){
//	std::cout << "Score:(0.0, 0.0)" << std::endl;
	return ConfidenceInterval(0.0, 0.0);
  }
  else{
	if( fabs(wm.getDistToField()) < 0.2){
		return ConfidenceInterval(0.0, 0.0);
//		std::cout << "Score:(0.0, 0.0)" << std::endl;
	}
	else{
		return ConfidenceInterval(0.5, 0.2);
//		std::cout << "Score:(0.5, 0.2)" << std::endl;
	}
  }
}
