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

import magma.agent.perception.impl.Perceptor;
import magma.util.observer.IObserver;
import magma.util.observer.IPublishSubscribe;

/**
 * A Server Message Parser receives a String from some interface layer, parses
 * it into a list of Perceptors and informs higher layers about new information.
 * The interfaces are realized through the observer pattern.
 * 
 * @author Simon Raffeiner
 * 
 */
public interface IServerMessageParser extends
		IPublishSubscribe<List<Perceptor>>, IObserver<String>
{
}
