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
package magma.agent.perception;

import java.util.List;

import magma.agent.perception.impl.PlayerPos;
import magma.util.observer.IObserver;
import magma.util.observer.ISubscribe;

/**
 * The perception represents all input an agent can get from the outside.
 * 
 * @author Simon Raffeiner
 * 
 */
public interface IPerception extends IObserver<String>, ISubscribe<IPerception>
{
	public static final String BALL = "B";

	/**
	 * Get a specific Universal Joint Perceptor
	 * 
	 * @param name Perceptor name
	 * @return perceptor
	 */
	public IUniversalJointPerceptor getUniversalJointPerceptor(String name);

	/**
	 * Get a specific Hinge Joint Perceptor
	 * 
	 * @param name Perceptor name
	 * @return perceptor
	 */
	public IHingeJointPerceptor getHingeJointPerceptor(String name);

	/**
	 * Get a specific Gyro Perceptor
	 * 
	 * @param name Perceptor name
	 * @return perceptor
	 */
	public IGyroPerceptor getGyroRatePerceptor(String name);

	/**
	 * Get a specific Force Resistance Perceptor
	 * 
	 * @param name Perceptor name
	 * @return perceptor
	 */
	public IForceResistancePerceptor getForceResistancePerceptor(String name);

	/**
	 * Get a specific Visible Object
	 * 
	 * @param name Perceptor name
	 * @return perceptor
	 */
	public IVisibleObjectPerceptor getObject(String name);

	/**
	 * Get the gloabl time perceptor
	 * 
	 * @return perceptor
	 */
	public ITimerPerceptor getTime();

	/**
	 * Get the Game State perceptor
	 * 
	 * @return perceptor
	 */
	public IGameStatePerceptor getGameState();

	/**
	 * Get the Hear perceptor
	 * 
	 * @return perceptor
	 */
	public IHearPerceptor getHearPerceptor();

	/**
	 * Get a list of all visible players
	 * 
	 * @return perceptor
	 */
	public List<PlayerPos> getVisiblePlayers();
}
