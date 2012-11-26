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

/**
 * The Vision Perceptor represents the visual sub-system. It stores visible
 * objects.
 * 
 * @author Simon Raffeiner
 */
public interface IVisionPerceptor extends IPerceptor
{
	/**
	 * Add a visible object.
	 * 
	 * @param object Object
	 */
	void addObject(IVisibleObjectPerceptor object);

	/**
	 * Get number of visible objects
	 * 
	 * @return Number of visible objects
	 */
	public int childCount();

	/**
	 * Get list of visible objects
	 * 
	 * @return List of visible objects
	 */
	public List<IVisibleObjectPerceptor> getObjects();

	/**
	 * Get a specific object
	 * 
	 * @param index Index
	 * @return Visible object
	 */
	public IVisibleObjectPerceptor getObject(int index);
}