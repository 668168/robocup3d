#!/usr/bin/perl -w

$header = <<EOF
#ifndef _BATS_%NAME%_HH_
#define _BATS_%NAME%_HH_

#include "behavior.hh"

namespace bats
{
  class %Name% : public Behavior
  {

    virtual rf<Goal> generateGoal(unsigned step, unsigned slot);
    virtual rf<State> getCurrentState();
    virtual ConfidenceInterval getCapability(rf<State> s, rf<Goal> g);
  
  public:
    %Name%(std::string const &id, std::string const &playerClass);
  };
};

#endif
EOF
;

######################################################

$iheader = <<EOF
#include "%name%.hh"

#include "worldmodel.hh"

#define DEBUGLEVEL 0
#include "debug.hh"

using namespace bats;
using namespace std;
EOF
;

######################################################

$constructor = <<EOF
#include "%name%.ih"

%Name%::%Name%(string const &id, string const &playerClass)
  : Behavior("%Name%", id, playerClass)
{
  d_tree = new AST::Node(sequenceType);
  d_tree->addChild(new AST::Node(andType));
  d_tree->getChild(0)->addChild(new AST::Node(orType));
}
EOF
;

######################################################

$generategoal = <<EOF
#include "%name%.ih"

rf<Behavior::Goal> %Name%::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  
  // con->addVar("Var", 0, 1);
  
  return goal;
}
EOF
;

######################################################

$getcurrentstate = <<EOF
#include "%name%.ih"

rf<Behavior::State> %Name%::getCurrentState()
{
  rf<State> state = new State();
  rf<OrNode> dis = state->addDisjunct();
  rf<AndNode> con = dis->addConjunct();

  // con->addVar("Var", 0, 1);
  return state;
}
EOF
;

######################################################

$getcapability = <<EOF
#include "%name%.ih"

Behavior::ConfidenceInterval %Name%::getCapability(rf<State> s, rf<Goal> g)
{
  return ConfidenceInterval(0.5, 0.2);
}
EOF
;

print "Behavior name: ";
$name = <>;
chomp $name;
$nameLower = lc $name;
$nameUpper = uc $name;

$header =~ s/\%Name\%/$name/g;
$header =~ s/\%NAME\%/$nameUpper/g;

$iheader =~ s/\%name\%/$nameLower/g;

$constructor =~ s/\%name\%/$nameLower/g;
$constructor =~ s/\%Name\%/$name/g;

$generategoal =~ s/\%name\%/$nameLower/g;
$generategoal =~ s/\%Name\%/$name/g;

$getcurrentstate =~ s/\%name\%/$nameLower/g;
$getcurrentstate =~ s/\%Name\%/$name/g;

$getcapability =~ s/\%name\%/$nameLower/g;
$getcapability =~ s/\%Name\%/$name/g;

$dir = "../Behavior/$name";

mkdir $dir or die "Couldn't create $dir!\n";

open(HEADER, ">$dir/$nameLower.hh");
print HEADER $header;
close(HEADER);

open(IHEADER, ">$dir/$nameLower.ih");
print IHEADER $iheader;
close(IHEADER);

open(CONSTRUCTOR, ">$dir/$name.cc");
print CONSTRUCTOR $constructor;
close(CONSTRUCTOR);

open(GENERATEGOAL, ">$dir/generateGoal.cc");
print GENERATEGOAL $generategoal;
close(GENERATEGOAL);

open(GETCURRENTSTATE, ">$dir/getCurrentState.cc");
print GETCURRENTSTATE $getcurrentstate;
close(GETCURRENTSTATE);

open(GETCAPABILITY, ">$dir/getCapability.cc");
print GETCAPABILITY $getcapability;
close(GETCAPABILITY);

print "Behavior $name created!\n";

