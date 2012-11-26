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
import java.util.logging.Level;
import java.util.logging.Logger;

import magma.agent.IMagmaConstants;
import magma.agent.perception.IServerMessageParser;
import magma.util.observer.Subject;
import magma.util.symboltreeparser.IllegalSymbolInputException;
import magma.util.symboltreeparser.SymbolLeaf;
import magma.util.symboltreeparser.SymbolNode;
import magma.util.symboltreeparser.SymbolTreeParser;

import org.apache.commons.math.geometry.Vector3D;

/**
 * Parses incoming server messages, converts them into single Perceptor messages
 * and delivers them to all observers
 * 
 * @author Simon Raffeiner
 * 
 */
public class ServerMessageParser extends Subject<List<Perceptor>> implements
		IServerMessageParser
{
	// handle for logging
	protected static Logger logger = Logger.getLogger("");

	// Internal tree parser
	private SymbolTreeParser treeparser;

	/**
	 * Default constructor
	 */
	public ServerMessageParser()
	{
		treeparser = new SymbolTreeParser();
	}

	@Override
	public void update(String message)
	{
		// Just parse the message and ignore all errors
		try {
			parse(message);
		} catch (Exception e) {
			logger.log(Level.SEVERE,
					"Parsing problem message: " + message + "{0}", e);
		}
	}

	/**
	 * Parse server messages, convert symbol tree nodes into Perception objects
	 * and inform the observers for every found object
	 * 
	 * @param message Input message
	 * @return List of perceptors
	 */
	public List<Perceptor> parse(String message)
			throws PerceptorConversionException
	{
		if (message.length() == 0)
			return new ArrayList<Perceptor>();

		try {
			List<Perceptor> list = parseString(message);

			if (list != null) {
				onStateChange(list);
			}
			return list;

		} catch (Exception e) {
			logger.log(Level.SEVERE,
					"Parsing problem message: " + message + "{0}", e);
		}
		return null;
	}

	/**
	 * Parse a string into a list of Perceptor objects
	 * 
	 * @param message Message string
	 */
	public List<Perceptor> parseString(String message)
			throws PerceptorConversionException
	{
		SymbolNode root;

		// Generate the symbol tree
		try {
			root = treeparser.parse(message);
		} catch (IllegalSymbolInputException e) {
			throw new PerceptorConversionException("Parsing error: "
					+ e.getMessage());
		}

		ArrayList<Perceptor> list = new ArrayList<Perceptor>(root.childCount());

		// Parse all top-level nodes into messages
		for (SymbolLeaf node : root.children()) {
			/*
			 * The tree may contain top-level leaves, ATM they are not specified
			 * and therefore not parsed
			 */
			if (node instanceof SymbolNode) {
				Perceptor perceptor = parseNode((SymbolNode) node);
				list.add(perceptor);
			}
		}

		return list;
	}

	/**
	 * Parse a symbol tree node into a Perceptor object (if possible)
	 * 
	 * @param node Symbol tree node
	 * @return Perceptor object
	 * @throws PerceptorConversionException
	 */
	private Perceptor parseNode(SymbolNode node)
			throws PerceptorConversionException
	{
		/* Check message type */
		SymbolLeaf type = node.getChild(0);

		if (type == null || type instanceof SymbolNode)
			throw new PerceptorConversionException("Malformed node: "
					+ node.toString());

		/* Gyro */
		if (type.content().equals("GYR"))
			return parseGyro(node);

		/* Hinge Joint */
		if (type.content().equals("HJ"))
			return parseHingeJoint(node);

		/* Universal Joint */
		if (type.content().equals("UJ"))
			return parseUniversalJoint(node);

		/* Force resistance perceptor */
		if (type.content().equals("FRP"))
			return parseForceResistance(node);

		/* Touch perceptor */
		if (type.content().equals("TCH"))
			return parseTouch(node);

		/* Vision perceptor */
		if (type.content().equals("See"))
			return parseVision(node);

		/* GameState perceptor */
		if (type.content().equals("GS"))
			return parseGameState(node);

		/* AgentState perceptor */
		if (type.content().equals("AgentState"))
			return parseAgentState(node);

		/* Hear perceptor */
		if (type.content().equals("hear"))
			return parseHear(node);

		/* Time perceptor */
		if (type.content().equals("time"))
			return parseTime(node);

		return null;
	}

	/**
	 * Parse a symbol tree node into a Gyro Perceptor object
	 * 
	 * @param node Symbol tree node
	 * @return Gyro Perceptor object
	 */
	private GyroPerceptor parseGyro(SymbolNode node)
			throws PerceptorConversionException
	{
		if (!(node.getChild(1) instanceof SymbolNode)
				|| !(node.getChild(2) instanceof SymbolNode))
			throw new PerceptorConversionException("Malformed Message: "
					+ node.toString());

		try {
			/* Check content */
			SymbolNode nameNode = (SymbolNode) node.getChild(1);
			SymbolNode rotationNode = (SymbolNode) node.getChild(2);

			if (!nameNode.getChild(0).content().equals("n"))
				throw new PerceptorConversionException("name expected: "
						+ node.toString());

			if (!rotationNode.getChild(0).content().equals("rt"))
				throw new PerceptorConversionException("rotation expected: "
						+ node.toString());

			return new GyroPerceptor(nameNode.getChild(1).content(), Float
					.valueOf(rotationNode.getChild(1).content()), Float
					.valueOf(rotationNode.getChild(2).content()), Float
					.valueOf(rotationNode.getChild(3).content()));
		} catch (IndexOutOfBoundsException e) {
			throw new PerceptorConversionException("Malformed node: "
					+ node.toString());
		}
	}

	/**
	 * Parse a symbol tree node into a Hinge Joint Perceptor object
	 * 
	 * @param node Symbol tree node
	 * @return Hinge Joint Perceptor object
	 * @throws PerceptorConversionException
	 */
	private HingeJointPerceptor parseHingeJoint(SymbolNode node)
			throws PerceptorConversionException
	{
		try {
			if (!(node.getChild(1) instanceof SymbolNode)
					|| !(node.getChild(2) instanceof SymbolNode))
				throw new PerceptorConversionException("Malformed Message: "
						+ node.toString());

			/* Check content */
			SymbolNode nameNode = (SymbolNode) node.getChild(1);
			SymbolNode rotationNode = (SymbolNode) node.getChild(2);

			if (!nameNode.getChild(0).content().equals("n"))
				throw new PerceptorConversionException("Malformed Message: "
						+ node.toString() + ": name expected");

			if (!rotationNode.getChild(0).content().equals("ax"))
				throw new PerceptorConversionException("Malformed Message: "
						+ node.toString() + ": axis expected");

			return new HingeJointPerceptor(nameNode.getChild(1).content(), Float
					.valueOf(rotationNode.getChild(1).content()));
		} catch (IndexOutOfBoundsException e) {
			throw new PerceptorConversionException("Malformed node: "
					+ node.toString());
		}
	}

	/**
	 * Parse a symbol tree node into a Universal Joint Perceptor object
	 * 
	 * @param node Symbol tree node
	 * @return Universal Joint Perceptor object
	 * @throws PerceptorConversionException
	 */
	private UniversalJointPerceptor parseUniversalJoint(SymbolNode node)
			throws PerceptorConversionException
	{
		try {
			// Sanity checks
			assert node.getChild(1) instanceof SymbolNode : "Malformed Message: "
					+ node.toString();
			assert node.getChild(2) instanceof SymbolNode : "Malformed Message: "
					+ node.toString();
			assert node.getChild(3) instanceof SymbolNode : "Malformed Message: "
					+ node.toString();

			/* Check content */
			SymbolNode nameNode = (SymbolNode) node.getChild(1);
			SymbolNode axis1Node = (SymbolNode) node.getChild(2);
			SymbolNode axis2Node = (SymbolNode) node.getChild(3);

			assert nameNode.getChild(0).content().equals("n") : "name expected: "
					+ node.toString();
			assert axis1Node.getChild(0).content().equals("ax1") : "axis expected: "
					+ node.toString();
			assert axis2Node.getChild(0).content().equals("ax2") : "axis expected: "
					+ node.toString();

			return new UniversalJointPerceptor(nameNode.getChild(1).content(),
					Float.valueOf(axis1Node.getChild(1).content()), Float
							.valueOf(axis2Node.getChild(1).content()));
		} catch (IndexOutOfBoundsException e) {
			throw new PerceptorConversionException("Malformed node: "
					+ node.toString());
		}
	}

	/**
	 * Parse a symbol tree node into a Force Resistance Perceptor object
	 * 
	 * @param node Symbol tree node
	 * @return Force Resistance Perceptor object
	 * @throws PerceptorConversionException
	 */
	private ForceResistancePerceptor parseForceResistance(SymbolNode node)
			throws PerceptorConversionException
	{
		try {
			// Sanity checks
			assert node.getChild(1) instanceof SymbolNode : "Malformed Message: "
					+ node.toString();
			assert node.getChild(2) instanceof SymbolNode : "Malformed Message: "
					+ node.toString();
			assert node.getChild(3) instanceof SymbolNode : "Malformed Message: "
					+ node.toString();

			/* Check content */
			SymbolNode nameNode = (SymbolNode) node.getChild(1);
			SymbolNode originNode = (SymbolNode) node.getChild(2);
			SymbolNode forceNode = (SymbolNode) node.getChild(3);

			assert nameNode.getChild(0).content().equals("n") : "name expected: "
					+ node.toString();
			assert originNode.getChild(0).content().equals("c") : "origin expected: "
					+ node.toString();
			assert forceNode.getChild(0).content().equals("f") : "force expected: "
					+ node.toString();

			return new ForceResistancePerceptor(nameNode.getChild(1).content(),
					Float.valueOf(originNode.getChild(1).content()), Float
							.valueOf(originNode.getChild(2).content()), Float
							.valueOf(originNode.getChild(3).content()), Float
							.valueOf(forceNode.getChild(1).content()), Float
							.valueOf(forceNode.getChild(2).content()), Float
							.valueOf(forceNode.getChild(3).content()));
		} catch (IndexOutOfBoundsException e) {
			throw new PerceptorConversionException("Malformed node: "
					+ node.toString());
		}
	}

	/**
	 * Parse a symbol tree node into a Touch Perceptor object
	 * 
	 * @param node Symbol tree node
	 * @return Touch Perceptor object
	 * @throws PerceptorConversionException
	 */
	private TouchPerceptor parseTouch(SymbolNode node)
			throws PerceptorConversionException
	{
		if (node.childCount() != 5 || !node.getChild(1).content().equals("n")
				|| !node.getChild(3).content().equals("val"))
			throw new PerceptorConversionException("Malformed node: "
					+ node.toString());

		try {
			String name = node.getChild(2).content();

			boolean value = false;
			if (node.getChild(4).content().equals("1"))
				value = true;

			return new TouchPerceptor(name, value);
		} catch (IndexOutOfBoundsException e) {
			throw new PerceptorConversionException("Malformed node: "
					+ node.toString());
		}
	}

	/**
	 * Parse a symbol tree vision node into a list of Perceptor objects
	 * 
	 * @param node Symbol tree vision node
	 * @return List of Perceptor objects
	 * @throws PerceptorConversionException
	 */
	private VisionPerceptor parseVision(SymbolNode node)
			throws PerceptorConversionException
	{
		// Sanity checks
		if (node.childCount() == 0)
			throw new PerceptorConversionException("Malformed Node: "
					+ node.toString());

		try {
			VisionPerceptor vision = new VisionPerceptor("See");

			// Parse visible objects
			for (int i = 1; i < node.childCount(); i++) {
				SymbolLeaf subitem = node.getChild(i);

				if (subitem instanceof SymbolNode) {
					SymbolNode subnode = (SymbolNode) subitem;

					// Player object?
					if (subnode.getChild(0) instanceof SymbolNode) {
						// this if is only required for compatibility with 0.6.0
						// version protocol which left out P in some cases
						vision.addObject(parsePlayer(subnode));

					} else if (subnode.getChild(0).content().equals("P"))
						vision.addObject(parsePlayer(subnode));

					else
						vision.addObject(parseVisibleObject(subnode));
				}
			}

			return vision;
		} catch (IndexOutOfBoundsException e) {
			throw new PerceptorConversionException("Malformed node: "
					+ node.toString());
		}
	}

	/**
	 * Parse a symbol tree node into a Player object
	 * 
	 * @param node Symbol tree node
	 * @return Player object
	 * @throws PerceptorConversionException
	 */
	private PlayerPos parsePlayer(SymbolNode node)
			throws PerceptorConversionException
	{
		try {
			/* Parse content */
			String teamName = IMagmaConstants.UNKNOWN_PLAYER_TEAMNAME;
			int id = IMagmaConstants.UNKNOWN_PLAYER_NUMBER;
			Vector3D pol = new Vector3D();
			boolean parsedPol = false;

			for (int i = 1; i < node.childCount(); i++) {
				if (!(node.getChild(i) instanceof SymbolNode))
					throw new PerceptorConversionException("Malformed node: "
							+ node.toString());

				SymbolNode param = (SymbolNode) node.getChild(i);

				if (param.getChild(0).content().equals("team"))
					teamName = param.getChild(1).content();
				else if (param.getChild(0).content().equals("id"))
					id = Integer.parseInt(param.getChild(1).content());

				// in case of seeing parts of opponent, we have to look into them
				else if (!parsedPol
						&& (param.getChild(0).content().equals("head")
								|| param.getChild(0).content().equals("rlowerarm")
								|| param.getChild(0).content().equals("llowerarm")
								|| param.getChild(0).content().equals("rfoot") || param
								.getChild(0).content().equals("lfoot"))) {
					param = (SymbolNode) param.getChild(1);
				}

				if (param.getChild(0).content().equals("pol")) {
					pol = parsePol(param);
					parsedPol = true;
				}
			}

			return new PlayerPos(pol, id, teamName);
		} catch (IndexOutOfBoundsException e) {
			throw new PerceptorConversionException("Malformed node: "
					+ node.toString());
		}
	}

	/**
	 * Parse a symbol tree node into a Player object
	 * 
	 * @param node Symbol tree node
	 * @return Player object
	 * @throws PerceptorConversionException
	 */
	private VisibleObjectPerceptor parseVisibleObject(SymbolNode node)
			throws PerceptorConversionException
	{
		try {
			assert node.childCount() == 2 : "Malformed node";
			assert node.getChild(0) instanceof SymbolLeaf : "Malformed node: "
					+ node.toString();
			assert node.getChild(1) instanceof SymbolNode : "Malformed node: "
					+ node.toString();

			String name = node.getChild(0).content();
			Vector3D pol = parsePol((SymbolNode) node.getChild(1));

			return new VisibleObjectPerceptor(name, pol);
		} catch (IndexOutOfBoundsException e) {
			throw new PerceptorConversionException("Malformed node: "
					+ node.toString());
		}
	}

	/**
	 * Parse object coordinates
	 * 
	 * @param node
	 * @return
	 * @throws PerceptorConversionException
	 */
	private Vector3D parsePol(SymbolNode node)
			throws PerceptorConversionException
	{
		try {
			assert node.childCount() == 4 : "Malformed node: " + node.toString();
			assert node.getChild(0).content().equals("pol") : "Expecting a pol object: "
					+ node.toString();

			float val1 = Float.parseFloat(node.getChild(1).content());
			float val2 = Float.parseFloat(node.getChild(2).content());
			float val3 = Float.parseFloat(node.getChild(3).content());

			return new Vector3D(val1, new Vector3D(Math.toRadians(val2), Math
					.toRadians(val3)));
		} catch (IndexOutOfBoundsException e) {
			throw new PerceptorConversionException("Malformed node: "
					+ node.toString());
		}
	}

	/**
	 * Parse a symbol tree node into a Game State Perceptor object
	 * 
	 * @param node Symbol tree node
	 * @return Game State Perceptor object
	 * @throws PerceptorConversionException
	 */
	private GameStatePerceptor parseGameState(SymbolNode node)
			throws PerceptorConversionException
	{
		float time = 0.0f;
		String playmode = "", team = "";
		int unum = 0;

		SymbolNode child = null;

		// Evaluate content
		try {
			for (int i = 1; i < node.childCount(); i++) {
				child = (SymbolNode) node.getChild(i);

				String type = child.getChild(0).content();

				// Check sub-node type
				if (type.equals("t")) {
					time = Float.parseFloat(child.getChild(1).content());
				} else if (type.equals("pm")) {
					playmode = child.getChild(1).content();
				} else if (type.equals("unum")) {
					unum = Integer.parseInt(child.getChild(1).content());
				} else if (type.equals("team")) {
					team = child.getChild(1).content();
				} else
					throw new PerceptorConversionException(
							"Malformed GameState node, unknown sub-node: "
									+ child.toString());
			}
		} catch (Exception e) {
			throw new PerceptorConversionException(
					"Malformed GameState node, conversion error: "
							+ child.toString());
		}

		return new GameStatePerceptor(time, playmode, team, unum);
	}

	/**
	 * Parse a symbol tree node into an Agent State Perceptor object
	 * 
	 * @param node Symbol tree node
	 * @return Agent State Perceptor object
	 * @throws PerceptorConversionException
	 */
	private AgentStatePerceptor parseAgentState(SymbolNode node)
			throws PerceptorConversionException
	{
		try {
			// Sanity checks
			assert node.getChild(1) instanceof SymbolNode : "Malformed Message: "
					+ node.toString();
			assert node.getChild(2) instanceof SymbolNode : "Malformed Message: "
					+ node.toString();

			/* Check content */
			SymbolNode temperatureNode = (SymbolNode) node.getChild(1);
			SymbolNode batteryNode = (SymbolNode) node.getChild(2);

			assert temperatureNode.getChild(0).content().equals("temp") : "temperature expected: "
					+ node.toString();
			assert batteryNode.getChild(0).content().equals("battery") : "battery level expected: "
					+ node.toString();

			return new AgentStatePerceptor(Integer.parseInt(temperatureNode
					.getChild(1).content()), Integer.parseInt(batteryNode
					.getChild(1).content()));
		} catch (IndexOutOfBoundsException e) {
			throw new PerceptorConversionException("Malformed node: "
					+ node.toString());
		}
	}

	/**
	 * Parse a symbol tree node into a Hear Perceptor object
	 * 
	 * @param node Symbol tree node
	 * @return Hear Perceptor object
	 * @throws PerceptorConversionException
	 */
	private HearPerceptor parseHear(SymbolNode node)
			throws PerceptorConversionException
	{
		float time = 0.0f;
		String message = "", target = "";

		// Sanity checks
		if (node.childCount() < 4)
			throw new PerceptorConversionException("Malformed hear node: "
					+ node.toString());

		try {
			time = Float.parseFloat(node.getChild(1).content());
			target = node.getChild(2).content();

			// Concatenate following nodes
			for (int i = 3; i < node.childCount(); i++) {
				if (i > 3)
					message += " " + node.getChild(i);
				else
					message += node.getChild(i);
			}
		} catch (Exception e) {
			throw new PerceptorConversionException(
					"Malformed hear node, conversion error: " + node.toString());
		}

		return new HearPerceptor(time, target, message);
	}

	/**
	 * Parse a symbol tree node into a Time Perceptor object
	 * 
	 * @param node Symbol tree node
	 * @return Time Perceptor object
	 * @throws PerceptorConversionException
	 */
	private TimePerceptor parseTime(SymbolNode node)
			throws PerceptorConversionException
	{
		// Sanity check
		if (node.childCount() != 2 || !(node.getChild(0) instanceof SymbolLeaf)
				|| !(node.getChild(1) instanceof SymbolNode))
			throw new PerceptorConversionException("Malformed time node: "
					+ node.toString());

		// Sub-node sanity check
		SymbolNode timeNode = (SymbolNode) node.getChild(1);
		if (timeNode.childCount() != 2
				|| timeNode.getChild(1).content().equals("now"))
			throw new PerceptorConversionException("Malformed time sub-node: "
					+ timeNode.toString());

		try {
			// Sanity checks
			float time = Float.parseFloat(timeNode.getChild(1).content());

			return new TimePerceptor(time);
		} catch (Exception e) {
			throw new PerceptorConversionException(
					"Malformed time node, conversion error: " + node.toString());
		}
	}
}
