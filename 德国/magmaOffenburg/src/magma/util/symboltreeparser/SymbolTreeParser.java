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

/**
 * Parses a symbol string as specified by the RoboCup Server Manual into a
 * Symbol Tree consisting of SymbolNode and SymbolLeaf objects.
 * 
 * 
 * @author Simon Raffeiner
 */
public class SymbolTreeParser
{
	/**
	 * Parse a smybol string as specified by the RoboCup Manual into a Symbol
	 * tree.
	 * 
	 * @param input String formed according to the RoboCup manual
	 * @return Generated Symbol tree
	 * @throws IllegalSymbolInputException
	 */
	public SymbolNode parse(String input) throws IllegalSymbolInputException
	{
		/* Check input rules */
		if (input.length() == 0)
			throw new IllegalSymbolInputException("Empty string");

		if (input.charAt(0) != '(' || input.charAt(input.length() - 1) != ')')
			throw new IllegalSymbolInputException("Input not embedded in braces: "
					+ input);

		return parseReal(input);
	}

	/**
	 * Parse a string into a symbol tree. This routine fetches the
	 * top-level-tokens from the string, converts them to SymbolLeaf entries and
	 * adds them to the actual node. If a list is found the complete content
	 * (regardless how many levels of symbols and sub-lists are found inside the
	 * list)between the highest-level opening and closing braces is parsed
	 * recursively.
	 * 
	 * The following example shows how the tree is formed:
	 * 
	 * Input: (A (B (C C C)) A)
	 * 
	 * 1. Token A is added 2. The function calls itself on the list "(B (C C C))"
	 * 3. Token B is added 4. The function calls itself on the list "(C C C)" 5.
	 * The three "C" tokens are added 6. The function returns from the recursive
	 * calls 7. Token "A" is added
	 * 
	 * @param input String formed according to the RoboCup manual
	 * @return Generated Symbol tree
	 * @except IllegalSymbolInputException
	 */
	private static SymbolNode parseReal(String input)
			throws IllegalSymbolInputException
	{
		/* Generated symbol tree */
		SymbolNode tree = new SymbolNode();

		/* Current character index */
		int index = 0;

		/* The "level" we are on - breaces increase and decrease it */
		int level = 0;

		/* Temporary variables */
		String temp = "";
		char c;

		/*
		 * Repeat until the input string is completely parsed or the level reaches
		 * an illegal value, meaning the number of braces doesn't add up
		 */
		while (index < input.length() && level >= 0) {
			c = input.charAt(index);

			/* If we are on a deeper level just add the characters */
			switch (c) {
			case '(':
				/*
				 * Descending into a deeper level. If we were on the top level and
				 * there are characters in the buffer, add them to the node as a new
				 * Leaf entry
				 */
				if (level == 0 && temp.length() > 0)
					tree.add(new SymbolLeaf(temp));
				if (level > 0)
					temp += c;
				level++;
				break;

			case ')':
				level--;

				/*
				 * Returning from a deeper level. If we hit the top level there
				 * obviously now is a list in the buffer waiting to be parsed
				 */
				if (level == 0) {
					tree.add(parseReal(temp));
					temp = "";
				} else
					temp += c;
				break;

			case ' ':

				/*
				 * If we are on the top level and there are characters in the buffer
				 * we hit the space character in its role as a spacer, add the
				 * buffered characters to the node as a new Leaf entry
				 */
				if (level == 0 && temp.length() > 0) {
					tree.add(new SymbolLeaf(temp));
					temp = "";
				}
				if (level > 0)
					temp += c;
				break;
			default:
				temp += c;
			}

			index++;
		}

		/*
		 * If we are at the end of the string and there are still characters in
		 * the buffer there is another symbol to add
		 */
		if (temp.length() > 0)
			tree.add(new SymbolLeaf(temp));

		/* Check error conditions */
		if (level != 0)
			throw new IllegalSymbolInputException("Missing brackets in input: "
					+ input);

		return tree;
	}
}
