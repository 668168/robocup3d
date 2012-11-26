#XuYuan <xychn15@yahoo.com.cn> 2006-12-05

#$Id: Makefile.am,v 1.6 2006/02/23 02:23:54 xy Exp $

AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = seu-3d-player

if DEBUG
seu_3d_player_CXXFLAGS = -O -W -Wall
else
seu_3d_player_CXXFLAGS = -O3 -Wall
endif


# set CXXFLAGS = NULL to disable -g -O2
CXXFLAGS = 

seu_3d_player_CPPFLAGS = -I/usr/local/include -I/usr/local/include/rcssserver3d -I../utility/sexpr 
seu_3d_player_LDFLAGS = -L../utility/sexpr
seu_3d_player_LDADD = -lsexp
		

seu_3d_player_SOURCES = \
	main.cpp \
	Settings.h \
	Singleton.h \
	Geometry.h Geometry.cpp \
	Parser.h Parser.cpp \
	Object.h Object.cpp \
	commserver.h commserver.cpp ReadBuffFD.h ReadBuffFD.cpp\
	LogData.h LogData.cpp Logger.h Logger.cpp \
	Agent.h Agent.cpp \
	BasicPlayer.h BasicPlayer.cpp PlayerTraining.cpp\
	Player.h Player.cpp \
	Action.h Action.cpp \
	Skill.h Skill.cpp \
	BasicWorldModel.h BasicWorldModel.cpp \
	WorldModel.h WorldModel.cpp \
	Formation.h Formation.cpp

EXTRA_DIST = agentdb.xml formations.conf README-PLAYER
