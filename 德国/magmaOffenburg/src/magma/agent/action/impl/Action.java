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
package magma.agent.action.impl;

import java.util.HashMap;

import magma.agent.IServerConfigFilesConstants;
import magma.agent.action.IAction;
import magma.agent.connection.IServerConnection;

/**
 * This class generates server messages from Effector objects.
 */
public class Action implements IAction
{

	protected HashMap<String, UniversalEffector> universalEffectors;

	protected HashMap<String, HingeEffector> hingeEffectors;

	protected final BeamEffector beam;

	protected final InitEffector init;

	protected final SayEffector say;

	protected final String actionScene;

	/** the connection to the server */
	protected final IServerConnection connection;

	/**
	 * Initializes all effectors that occur in the simulation
	 * 
	 * @param connection module for communicating with the server
	 * @param actionScene string for the robot type to use
	 * @param teamname name of the team this player plays in
	 * @param number player number within the team
	 */
	public Action(IServerConnection connection, String actionScene,
			String teamname, int number)
	{
		this.connection = connection;
		this.actionScene = actionScene;
		universalEffectors = new HashMap<String, UniversalEffector>();
		hingeEffectors = new HashMap<String, HingeEffector>();
		init = new InitEffector(teamname, number);
		beam = new BeamEffector();
		say = new SayEffector();

		initUniversalEffectors();
		initHingeEffectors();
	}

	/**
	 * Initializes all known UniversalJoint-Effectors (which are defined in
	 * IServerConfigFilesConstants)
	 */
	protected void initUniversalEffectors()
	{
		for (int i = 0; i < IServerConfigFilesConstants.UNIVERSALJOINT_EFFECTORS.length; i++) {
			universalEffectors.put(
					IServerConfigFilesConstants.UNIVERSALJOINT_EFFECTORS[i],
					new UniversalEffector(
							IServerConfigFilesConstants.UNIVERSALJOINT_EFFECTORS[i]));
		}
	}

	/**
	 * initializes all known HingeJoint-Effectors (which are defined in
	 * IServerConfigFilesConstants)
	 */
	protected void initHingeEffectors()
	{
		for (int i = 0; i < IServerConfigFilesConstants.HINGEJOINT_EFFECTORS.length; i++) {
			hingeEffectors.put(
					IServerConfigFilesConstants.HINGEJOINT_EFFECTORS[i],
					new HingeEffector(
							IServerConfigFilesConstants.HINGEJOINT_EFFECTORS[i]));
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * magma.agent.action.IAction#getUniversalEffectorByName(java.lang.String)
	 */
	public void setUniversalEffectorSpeed(String name, float speed1, float speed2)
	{
		universalEffectors.get(name).setAxis(speed1, speed2);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.action.IAction#getHingeEffectorByName(java.lang.String)
	 */
	public void setHingeEffectorSpeed(String name, float speed)
	{
		hingeEffectors.get(name).setAxisSpeed(speed);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.action.IAction#sendSceneString()
	 */
	public void sendSceneString()
	{
		String message = "(scene " + actionScene + ")";
		connection.sendMessage(message);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.action.IAction#sendInitString()
	 */
	public void sendInitString()
	{
		String message = init.getMessageString();
		connection.sendMessage(message);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.action.IAction#sendBeamString(float, float, float)
	 */
	public void sendBeamString(float x, float y, float rotation)
	{
		beam.setBeam(x, y, rotation);
		connection.sendMessage(beam.getMessageString());
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.action.IAction#sendSayString(java.lang.String)
	 */
	public void sendSayString(String message)
	{
		say.setMessage(message);
		connection.sendMessage(say.getMessageString());
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.action.IAction#sendMotorString()
	 */
	public String sendMotorString()
	{
		String message = getMotorString();
		connection.sendMessage(message);
		return message;
	}

	/**
	 * Returns the string necessary to send to the server to trigger joint motors
	 * @return the string necessary to send to the server to trigger joint motors
	 */
	private String getMotorString()
	{
		StringBuffer buffer = new StringBuffer(200);
		for (UniversalEffector u : universalEffectors.values()) {
			buffer.append(u.getMessageString());
		}

		for (HingeEffector h : hingeEffectors.values()) {
			buffer.append(h.getMessageString());
		}

		return buffer.toString();
	}
}
