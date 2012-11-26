/*
 *  Little Green BATS (2007), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	July 27, 2007
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */













#ifndef _Talent_HH_INCLUDED_
#define	_Talent_HH_INCLUDED_

#include <cmath>
#include <utility>
#include "worldmodel.hh"

namespace bats
{
  /** General functions giving super power talents to the agent. */
  class Talent
  {
  	public:
  		/** Solve the angle and power that should be used to kick the ball a certain distance
       *
  		 *	Calculate the angle and power pair given a distance and maximum height
       *  @param distance Distance to kick to. At this distance the ball will have a speed of 1 m/s
       *  @param maxHeight The maximum height the ball will get. If -1, 2 times the height of an agent will be used
  		 *  @return A pair defining the angle (in radians) and power to use.
  		 */
  		static std::pair<double, double> kickTo(double distance, double maxHeight = -1);

      /** Predict an object's position
       *
       * Predicts the object's position after a certain time given a starting position and speed, a drive force, drag factor and mass
       * @param startPos The object's starting position
       * @param startSpeed The object's starting speed
       * @param dt Time over which to predict
       * @param driveForce Drive force acting upon the object during the given period
       * @param dragFactor Factor of the drag that acts upon the object. $f F_drag = - c_drag cdot v $f
       * @param m The object's mass
       */
      static std::pair<Vector3D, Vector3D> predictPos(Vector3D startPos, Vector3D startSpeed, double dt, Vector3D driveForce = Vector3D(), double dragFactor = 0.3, double m = 0.43);

      /** Predict position 
      
      	@param dt
  @param driveForce
  @param dragFactor
  @param m

      * @param objid De WorldModel object id
      * @return Een pair met van: <plaats, snelheid> (beide vector 3d)
      */
      static std::pair<Vector3D, Vector3D> predictPos(unsigned objid, double dt, Vector3D driveForce = Vector3D(), double dragFactor = 0.3, double m = 0.43);
      
      static double predictBounceTime(Vector3D startPos, Vector3D startSpeed, double dragFactor = 0.3, double m = 0.43);
      
      static Vector3D predictBouncePos(Vector3D startPos, Vector3D startSpeed, double dragFactor = 0.3, double m = 0.43);
      
      /** Determine best position to intercept the ball
       *
       * Determines the position the agent should go to to intercept the ball as fast as possible.
       * @param targetPos Current position of the ball
       * @param targetSpeed Current speed of the ball
       * @param ownPos Current position of agent
       * @param ownSpeed Current speed of agent
       */
      static Vector3D interceptBall(Vector3D targetPos, Vector3D targetSpeed, Vector3D ownPos, Vector3D ownSpeed);

      /** Caching version of interceptBall using default values */
      static Vector3D interceptBall();

      /// Cached intercept location
      static Vector3D s_currentInterceptLocation;
      
      /// Time of last cache
      static double s_lastInterceptCache;
      
      /** Determine if agent is at the same side of a point as a target point
       *
       * @param pivot Point to use as reference
       * @param target Target point
       * @param me Own location
       * @returns True if \a me is at the same side of \a pivot as \a target
       */
      static bool atSameSideOf(Vector3D pivot, Vector3D target, Vector3D me);
  };
};

#endif
