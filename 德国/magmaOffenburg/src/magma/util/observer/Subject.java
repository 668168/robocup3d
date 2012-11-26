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

import java.util.ArrayList;
import java.util.List;

/**
 * Base class for all Observer notification classes. This implementation uses a
 * simplified design. Model classes would not inherit from this class but use a
 * mediator. The name was chosen to comply with Gamma et all's book, but is a
 * rather general name
 */
public class Subject<T> implements IPublishSubscribe<T>
{
	/** the list of observers that are notified */
	private List<IObserver<T>> observers;

	/**
	 * Default constructor creating the observer list
	 */
	public Subject()
	{
		super();
		this.observers = new ArrayList<IObserver<T>>();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * magma.util.observer.IPublishSubscribe#attach(magma.util.observer.IObserver
	 * )
	 */
	public void attach(IObserver<T> observer)
	{
		if (!observers.contains(observer)) {
			observers.add(observer);
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * magma.util.observer.IPublishSubscribe#detach(magma.util.observer.IObserver
	 * )
	 */
	public boolean detach(IObserver<T> observer)
	{
		return observers.remove(observer);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.util.observer.IPublishSubscribe#detachAll()
	 */
	public void detachAll()
	{
		observers.clear();
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.util.observer.IPublishSubscribe#onStateChange()
	 */
	public void onStateChange(T content)
	{
		for (IObserver<T> observer : observers) {
			observer.update(content);
		}
	}
}
