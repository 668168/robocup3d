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
package magma.agent.perception.impl;

import java.util.ArrayList;
import java.util.List;

import magma.agent.perception.IPerceptor;
import magma.agent.perception.IVisibleObjectPerceptor;
import magma.agent.perception.IVisionPerceptor;

/**
 * Vision Perceptor, contains a list of Visible Objects
 * 
 * @author Simon Raffeiner *
 */
public class VisionPerceptor extends Perceptor implements IVisionPerceptor
{
	// List of visible objects
	private List<IVisibleObjectPerceptor> objects;

	/**
	 * Default constructor
	 * 
	 * @param name Perceptor name
	 */
	public VisionPerceptor(String name)
	{
		this(name, new ArrayList<IVisibleObjectPerceptor>(10));
	}

	/**
	 * Assignment constructor
	 * 
	 * @param name Perceptor name
	 * @param objects List of visible objects
	 */
	public VisionPerceptor(String name, List<IVisibleObjectPerceptor> objects)
	{
		super(name);

		if (objects != null)
			this.objects = objects;
	}

	@Override
	public void addObject(IVisibleObjectPerceptor object)
	{
		this.objects.add(object);
	}

	@Override
	public int childCount()
	{
		return this.objects.size();
	}

	@Override
	public List<IVisibleObjectPerceptor> getObjects()
	{
		return this.objects;
	}

	@Override
	public IVisibleObjectPerceptor getObject(int index)
	{
		if (index >= 0 && index < objects.size())
			return this.objects.get(index);

		throw new IndexOutOfBoundsException();
	}

	@Override
	public void assign(IPerceptor source)
	{
		if (source instanceof VisionPerceptor) {
			VisionPerceptor input = (VisionPerceptor) source;

			objects = input.objects;
		}
	}
}
