#include "behavior.ih"

XMLNodeSet Behavior::getMyParams() const
{
	WorldModel const &wm = WorldModel::getInstance();
	std::ostringstream xp("");
	xp << "/for[@unum='" << wm.getUnum() << "']/*";
	return getParams(xp.str());
}
