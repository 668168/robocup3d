/* Copyright 2009 Hochschule Offenburg
 * Klaus Dorer, Mathias Ehret, Stefan Glaser, Thomas Huber,
 * Simon Raffeiner, Srinivasa Ragavan, Thomas Rinklin,
 * Joachim Schilling, Ingo Schindler, Rajit Shahi
 *
 * This file is part of magmaOffenburg.
 *
 * magmaOffenburg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * magmaOffenburg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with magmaOffenburg. If not, see <http://www.gnu.org/licenses/>.
 */
package magma.agent.agentmodel;

/**
 * Provides read only access to hinge joints
 * @author dorer
 */
public interface IHingeJoint
{
	/**
	 * @return angle of the joint in degrees
	 */
	float getAxis();

	/**
	 * @return previous time step angle of the joint in degrees
	 */
	float getLastAxis();

	/**
	 * @return the minimal angle that can be reached by the joint
	 */
	float getMin();

	/**
	 * @return the maximal angle that can be reached by the joint
	 */
	float getMax();

	/**
	 * @return the name of the corresponding effector
	 */
	public String getEffectorName();

	/**
	 * @param targetposition angle to get to
	 * @param range precision with which to check the angles
	 * @return 0 if the axis position is reached, -1 if axis is > target
	 *         position, 1 if <
	 */
	public float checkTarget(float targetposition, float range);

	/**
	 * @param targetposition angle to get to
	 * @param range precision with which to check the angles
	 * @return true if the target position was reached
	 */
	public boolean checkTrigger(float targetposition, float range);

}