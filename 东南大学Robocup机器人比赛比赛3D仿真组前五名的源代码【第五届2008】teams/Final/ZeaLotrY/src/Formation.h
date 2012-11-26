/*****************************************************************************************
 *                                      SEU-3D
 *                     -------------------------------------------------
 * Copyright (c) 2005, Yuan XU<xychn15@yahoo.com.cn>,Chang'e SHI<evelinesce@yahoo.com.cn>
 * Copyright (c) 2006, Yuan XU<xuyuan.cn@gmail.com>,Chunlu JIANG<JamAceWatermelon@gmail.com>
 * Southeast University ,China
 * All rights reserved.
 *
 * Additionally,this program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 ****************************************************************************************/

 
#ifndef _FORMATION_H
#define _FORMATION_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include "WorldModel.h"
#include "Logger.h"
#include "Parser.h"

#define FORMATION_MAX_LINE_LENGTH 1024

//# We have the following players types:
//# -----------------------------------
enum PlayerType
{	
	PT_UNKNOWN				= 0,
	PT_GOALKEEPER			= 1,
	PT_DEFENDER_CENTRAL		= 2,
	PT_DEFENDER_SWEEPER		= 3,
	PT_DEFENDER_WING		= 4,
	PT_MIDFIELDER_SWEEPER	= 5,
	PT_MIDFIELDER_CENTER	= 6,
	PT_MIDFIELDER_WING		= 7,
	PT_ATTACKER_WING		= 8,
	PT_ATTACKER_CENTRAL		= 9,
	PT_JOYSTICK				= 10
};


/***********************************************************************/
/*************************** CLASS FORMATION ***************************/
/***********************************************************************/

class Formation : public Singleton<Formation>
{
public:
	Formation();
	~Formation();

	//-* open the formations.conf file
	bool openFile();
	//-* close the opened file
	void closeFile() { _file.close(); }
	//-* load a specify formation
	bool loadFormation( string formationName );

///////////////////// some useful function ////////////////
	Vector3f getInitPosition( unsigned int num );
	PlayerType getPlayerType( unsigned int num ) const;
	PlayerType getMyType() const;
	Vector3f getStrategicPosition( unsigned int num, Vector3f posBall );
	//void test();

//-* data struct of one palyer's formation
struct FormationData
{
	//unsigned int _num;
	PlayerType _PlayerType;
	Vector3f _initPos;
	Vector3f _homePos;
	Vector3f _attraction;
	Vector3f _minPos;
	Vector3f _maxPos;
	bool	_behindBall;
};

protected:
	bool openFile( std::string formations_fn );

private:
	ifstream _file;
	string getLine();
	string getOneFormation();
	string getFormationName( const string strFormation );
	bool loadFormationData( const string strFormation );
	bool loadFormationData();
	void setupPlayerTypeMap();
	bool loadOnePlayerFormation( const sexp_t* sexp );

/////////////////// formation data //////////////////
	string _formationName;
	vector<FormationData> _formationData;

	//-*  mapping from unum to PlayerType
    typedef std::map<string, PlayerType> TPlayerTypeMap;
    TPlayerTypeMap _PlayerTypeMap;

};

#define FM Formation::GetSingletonPtr()

#endif /* _FORMATION_H */
