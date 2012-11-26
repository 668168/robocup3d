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

import magma.util.observer.IObserver;

/**
 * Provides read only access to the agent model including universal joints,
 * hinge joints, force resistance and gyro rate sensors
 * @author dorer
 */
public interface IAgentModel
{
	/**
	 * Returns a specified universal joint of the agent
	 * @param name the name of the joint as specified in
	 *        IServerConfigFilesConstants.UNIVERSALJOINT_NAMES
	 * @return read only version of the universal joint specified by name
	 */
	IUniversalJoint getUJ(String name);

	/**
	 * Returns a specified hinge joint of the agent
	 * @param name the name of the joint as specified in
	 *        IServerConfigFilesConstants.HINGEJOINT_NAMES
	 * @return read only version of the hinge joint specified by name
	 */
	IHingeJoint getHJ(String name);

	/**
	 * Returns a specified force resistance sensor of the agent
	 * @param name the name of the sensor as specified in
	 *        IServerConfigFilesConstants.FORCERESISTANCE_NAMES
	 * @return read only version of the force sensor specified by name
	 */
	IForceResistance getForceResistance(String name);

	/**
	 * checks if the agent stands on both feet
	 * @return
	 */
	boolean standingStill();

	/**
	 * Returns a specified gyro sensor of the agent
	 * @param name the name of the sensor as specified in
	 *        IServerConfigFilesConstants.GYRORATE_NAMES
	 * @return read only version of the gyro sensor specified by name
	 */
	IGyroRate getGyroRate(String name);

	void attach(IObserver<IAgentModel> newObserver);

	boolean detach(IObserver<IAgentModel> oldObserver);

}