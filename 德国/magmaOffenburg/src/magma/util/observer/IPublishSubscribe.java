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
package magma.util.observer;

public interface IPublishSubscribe<T> extends ISubscribe<T>
{
	/**
	 * Removes an observer from the list of observers
	 * @param observer the observer that wants to be removed
	 * @return true if the observer has been in the list and was removed
	 */
	boolean detach(IObserver<T> observer);

	/**
	 * Removes all observers from the list of observers
	 */
	void detachAll();

	/**
	 * Called to inform observer about a change in state
	 * @param content the object that contains the changed information
	 */
	void onStateChange(T content);
}