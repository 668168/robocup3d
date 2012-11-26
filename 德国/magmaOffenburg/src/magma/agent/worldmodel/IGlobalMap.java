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
package magma.agent.worldmodel;

import java.util.Collection;
import java.util.List;

import magma.util.observer.IObserver;
import magma.util.observer.ISubscribe;

import org.apache.commons.math.geometry.Vector3D;

public interface IGlobalMap extends ISubscribe<IGlobalMap>
{

	/**
	 * @return the ball of the game
	 */
	public abstract IMoveableObject getBall();

	/**
	 * @return an unmodifiable collection of the landmarks
	 */
	public abstract Collection<ILandmark> getLandmarks();

	/**
	 * @return an unmodifiable list of the currently visible players
	 */
	public abstract List<IPlayer> getVisiblePlayers();

	/**
	 * @return an unmodifiable list of the own players
	 */
	public abstract List<IPlayer> getOwnPlayers();

	/**
	 * @return this players information of position etc
	 */
	public abstract IThisPlayer getThisPlayer();

	/**
	 * @return the time on the global clock
	 */
	float getGlobalTime();

	/**
	 * @return the time the game is running now
	 */
	float getGameTime();

	/**
	 * @return the current mode of the game as String
	 */
	String getPlaymode();

	/**
	 * @return number of goals scored by us
	 */
	int getGoalsWeScored();

	/**
	 * @return number of goals scored by opponent
	 */
	int getGoalsTheyScored();

	/**
	 * @return position to the middle of opponent Goal as Vector3D
	 */
	Vector3D getOtherGoalPosition();

	/**
	 * @return the average error of known position and calculated position,
	 *         Double.MAX_VALUE if we do not see any flags
	 */
	double getLandmarkError();

	/**
	 * @return direction to the middle of own Goal as Vector3D
	 */
	Vector3D getOwnGoalPosition();

	/**
	 * Detaches the passed observer to this connection
	 * @param observer the observer that is no longer interested in new messages
	 * @return true if the observer was in the list and detached
	 */
	boolean detach(IObserver<IGlobalMap> observer);

	/**
	 * checks if the specified is in the other half or not
	 * @param position position for which to check
	 * @return true if the specified is in the other half
	 */
	boolean isInOtherHalf(Vector3D position);

	/**
	 * checks if the specified is in the own half or not
	 * @param position position for which to check
	 * @return true if the specified is in the own half
	 */
	boolean isInOwnHalf(Vector3D position);

}