#include "sine.ih"

string Sine::s_lastSineID = "";
vector<vector<Sine::Params> > Sine::s_lastParams;
double Sine::s_lastSineTime = 0;
double Sine::s_transitionTime = 1;
double Sine::s_lastUpdate = -1;
std::vector<rf<Sine> > Sine::s_sines;
