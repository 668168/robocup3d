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
package magma.util.symboltreeparser;

import java.util.ArrayList;
import java.util.List;

/**
 * Represents a Symbol Nodes, containing other child nodes (or leafs).
 * 
 * @author Simon Raffeiner
 */
public class SymbolNode extends SymbolLeaf
{
	private List<SymbolLeaf> children = new ArrayList<SymbolLeaf>(10);

	/**
	 * Constructor
	 */
	public SymbolNode()
	{
	}

	/**
	 * Get child element count
	 * 
	 * @return Number of child elements
	 */
	public int childCount()
	{
		return children.size();
	}

	/**
	 * Add a leaf/node to the list
	 * 
	 * @param leaf Leaf/Node
	 */
	public void add(SymbolLeaf leaf)
	{
		children.add(leaf);
	}

	/**
	 * Get all children
	 * 
	 * @return List with all children nodes/leafs
	 */
	public List<SymbolLeaf> children()
	{
		return children;
	}

	/**
	 * Get child element at specified location
	 * 
	 * @param index Element index
	 * @return Element
	 * @throws IndexOutOfBoundsException
	 */
	public SymbolLeaf getChild(int index) throws IndexOutOfBoundsException
	{
		if (index >= 0 && index < children.size())
			return this.children.get(index);

		throw new IndexOutOfBoundsException();
	}

	/**
	 * Get node content. Always empty for lists as they consists of other nodes.
	 * If you need a textual representation use toString()
	 */
	@Override
	public String content()
	{
		return null;
	}

	/**
	 * Returns a textual representation of the Node. If your Symbol Tree was
	 * parsed from an input string as specified by the RoboCup Server Manual,
	 * this output should always be identic to your input.
	 */
	@Override
	public String toString()
	{
		String ret = "";

		if (children.size() == 0)
			return "";

		for (int i = 0; i < this.children.size(); i++) {
			SymbolLeaf node = this.children.get(i);

			if (i > 0)
				ret += " ";

			if (node instanceof SymbolNode)
				ret += "(" + node.toString() + ")";
			else
				ret += node.toString();
		}

		return ret;
	}
}
