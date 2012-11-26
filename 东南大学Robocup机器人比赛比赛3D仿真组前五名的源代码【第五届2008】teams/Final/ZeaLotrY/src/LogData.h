/*****************************************************************************************
 *                                      SEU-3D
 *                     -------------------------------------------------
 * Copyright (c) 2005, Yuan XU<xychn15@yahoo.com.cn>,Chang'e SHI<evelinesce@yahoo.com.cn>
 * Copyright (c) 2006, Yuan XU<xuyuan.cn@gmail.com>,Chunlu JIANG<JamAceWatermelon@gmail.com>
 * Southeast University ,China
 * All rights reserved.
 *
 * $Id: LogData.h,v 1.1.1.1 2006/09/15 02:03:06 Administrator Exp $
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

/**
 * \flie           LogData.h
 *
 * \brief the data struct of agent state from agent's log
 *
 */
 
#ifndef _LOGDATA_H
#define _LOGDATA_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef __cplusplus
}
#endif

#include <sexp.h>
#include "Settings.h"
#include <vector>
#include <map>


/************************************
   FORMAT OF AGENT LOG
-------------------------------------
1. L-og
(L time ...)
-------------------------------------
start with 'L', and the time is the 'game time' of log

2. log_name
(L time (log_name1 ...)(log_name2 ...))
-------------------------------------
'log_name' is the log name string
for example:
'WM' -- the log of agent's worldmodel

3. P-rint
(log_name (P str R G B )...)
-------------------------------------
draw a line text in the srceen ( 2D )
str - the text string
RGB - the color of text

4. S-phere
(S x y z r)
(S x y z r R G B)
-------------------------------------
draw a Sphere in the main 3D screen
x y z - the center of sphere
r     - the radius of sphere
R G B - the color of sphere

5. R-ectangle
(R x y z l w)
(R x y z l w xR yR zR)
(R x y z l w xR yR zR R G B)
-------------------------------------
draw a Rectangle in the main 3D screen
x y z - the left_bottom point rectangle
l w   - the length and width of the rectangle
xR    - the rotation by x-axis
yR    - the rotation by y-axis
zR    - the rotation by z-axis
R G B - the color of rectangle

6. C-ircle
(C x y z r)
(C x y z r xR yR zR)
(C x y z r xR yR zR R G B)
-------------------------------------
draw a Circle in the main 3D screen
x y z - the center of the circle
r     - the radius the circle
xR    - the rotation by x-axis
yR    - the rotation by y-axis
zR    - the rotation by z-axis
R G B - the color of circle

7. L-ine
(L x0 y0 z0 x1 y1 z1)
(L x0 y0 z0 x1 y1 z1 R G B)
-------------------------------------
draw a line in the main 3D screen
x0 y0 z0 - the start point of the line
x1 y1 z1 - the end point of the line
R G B    - the color of the line

8. T-ext
(log_name (D T x y z ( str ) R G B)...)
-------------------------------------
draw the text in the (x,y,z) position in 3D srceen
str - the text string
RGB - the color of text

*************************************/

/** basic class of log data */
class LogData
{
public:
	virtual ~LogData(){};

	virtual void print(std::ostream& ost)const{};
		
#ifdef GL_DRAW
	/** draw the log in the monitor
	 * @param[in] pass int indicate that draw way : 2D or 3D, etc.
	 */
	virtual void draw(/*int pass*/)const{};
#endif
};

/* P-rint
(log_name (P str R G B )...)
-------------------------------------
draw a line text in the srceen ( 2D )
str - the text string
RGB - the color of text
*/
class LogPrint: public LogData
{
public:
	LogPrint(const sexp_t* sexp);
	LogPrint(const string& str);
	LogPrint(const string& str, const Vector3f& rgb);
	~LogPrint(){};
	
	void print(std::ostream& ost)const;
	
	const char* getText()const { return _str.c_str(); }
	bool isColored() const { return _colored; }
	const Vector3f& getRGB() const { return _rgb; }
		
#ifdef GL_DRAW
	void draw()const;
#endif
private:
	string   _str;
	bool     _colored;
	Vector3f _rgb;
};

/* T-ext
(log_name (T x y z ( str ) R G B)...)
-------------------------------------
draw the text in the (x,y,z) position in 3D srceen
str - the text string
RGB - the color of text
*/
class LogText: public LogData
{
public:
	LogText(const sexp_t* sexp);
	LogText(const Vector3f& pos,const string& str);
	LogText(const Vector3f& pos,const string& str, const Vector3f& rgb);
	~LogText(){};
	
	void print(std::ostream& ost)const;
	
#ifdef GL_DRAW
	void draw()const;
#endif
private:
	Vector3f _pos;
	string   _str;
	bool     _colored;
	Vector3f _rgb;
};

/*
S-phere
(S x y z r)
(S x y z r R G B)
-------------------------------------
draw a Sphere in the main 3D screen
x y z - the center of sphere
r     - the radius of sphere
R G B - the color of sphere
*/
class LogShpere: public LogData
{
public:
	LogShpere(const sexp_t* sexp);
	LogShpere(const Vector3f& pos,float r);
	LogShpere(const Vector3f& pos,float r, const Vector3f& rgb);
	~LogShpere(){};
	
	void print(std::ostream& ost)const;
	
#ifdef GL_DRAW
	void draw()const;
#endif
private:
	Vector3f _pos;
	float    _r;
	bool     _colored;
	Vector3f _rgb;
};

/* R-ectangle
(R x y z szX szY)
(R x y z szX szY xR yR zR)
(R x y z szX szY xR yR zR R G B)
-------------------------------------
draw a Rectangle in the main 3D screen
x y z   - the left_bottom point of the rectangle
szX szY - the length and width of the rectangle
xR      - the rotation by x-axis
yR      - the rotation by y-axis
zR      - the rotation by z-axis
R G B   - the color of rectangle
*/
class LogRectangle: public LogData
{
public:
	LogRectangle(const sexp_t* sexp);
	LogRectangle(const Vector3f& pos,float szX, float szY);
	LogRectangle(const Vector3f& pos,float szX, float szY, const Vector3f& rotation);
	LogRectangle(const Vector3f& pos,float szX, float szY, const Vector3f& rotation, const Vector3f& rgb);
	~LogRectangle(){};
	
	void print(std::ostream& ost)const;
	
#ifdef GL_DRAW
	void draw()const;
#endif
private:
	Vector3f _pos;
	float    _szX,_szY;
	int      _flag;
	Vector3f _rotation;
	Vector3f _rgb;
};

/* C-ircle
(C x y z r)
(C x y z r xR yR zR)
(C x y z r xR yR zR R G B)
-------------------------------------
draw a Circle in the main 3D screen
x y z - the center of the circle
r     - the radius the circle
xR    - the rotation by x-axis
yR    - the rotation by y-axis
zR    - the rotation by z-axis
R G B - the color of circle
*/
class LogCircle: public LogData
{
public:
	LogCircle(const sexp_t* sexp);
	LogCircle(const Vector3f& pos,float r);
	LogCircle(const Vector3f& pos,float r, const Vector3f& rotation);
	LogCircle(const Vector3f& pos,float r, const Vector3f& rotation, const Vector3f& rgb);
	~LogCircle(){};
	
	void print(std::ostream& ost)const;
	
#ifdef GL_DRAW
	void draw()const;
#endif
private:
	Vector3f _pos;
	float    _r;
	int      _flag;
	Vector3f _rotation;
	Vector3f _rgb;
};

/* L-ine
(D L x0 y0 z0 x1 y1 z1)
(D L x0 y0 z0 x1 y1 z1 R G B)
-------------------------------------
draw a line in the main 3D screen
x0 y0 z0 - the start point of the line
x1 y1 z1 - the end point of the line
R G B    - the color of the line
*/
class LogLine: public LogData
{
public:
	LogLine(const sexp_t* sexp);
	LogLine(const Vector3f& x0,const Vector3f& x1);
	LogLine(const Vector3f& x0,const Vector3f& x1, const Vector3f& rgb);
	~LogLine(){};
	
	void print(std::ostream& ost)const;
	
#ifdef GL_DRAW
	void draw()const;
#endif
private:
	Vector3f _x0,_x1;
	int      _flag;
	Vector3f _rgb;
};

/** class wrap for one agent, one level, one time log message */ 
class LogInfo
{
public:
	LogInfo(){};
	~LogInfo(){};
	
	void add(LogData* data) { _data.push_back(data); }
		
	void parseDraw(const sexp_t* sexp);
	
	friend std::ostream& operator<<(std::ostream& ost, const LogInfo& v);
	
	void clear();
	
#ifdef GL_DRAW
	void draw()const;
#endif
private:
	vector<LogData*> _data;
};

std::ostream& operator<<(std::ostream& ost, const LogInfo& v);

/** class wrap for one agent, one time log message */
class LogLevel
{
public:
	friend std::ostream& operator<<(std::ostream& ost, const LogLevel& v);
	
	int size()const{ return _data.size(); }
	
	const LogInfo& operator[](int i)const;
	LogInfo& operator[](int i);
	
	void insert( int i,const LogInfo& lf) { _data[i] = lf; }
	
	void clear();
	
#ifdef GL_DRAW
	void draw()const;
#endif
	
private:
	map<int, LogInfo>  _data;
};

std::ostream& operator<<(std::ostream& ost, const LogLevel& v);

#endif /* _LOGDATA_H */
