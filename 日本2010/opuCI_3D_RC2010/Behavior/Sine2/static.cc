#include "sine2.ih"

string Sine2::s_lastSine2ID = "";
vector<vector<Sine2::Params> > Sine2::s_lastParams;
double Sine2::s_lastSine2Time = 0;
double Sine2::s_transitionTime = 1;
double Sine2::s_lastUpdate = -1;
std::vector<rf<Sine2> > Sine2::s_sines;
