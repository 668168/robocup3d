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
package magma.agent.behavior.coordinator;

import magma.agent.action.IAction;
import magma.agent.agentmodel.IAgentModel;
import magma.agent.agentmodel.IHingeJoint;
import magma.agent.behavior.ICoordinator;
import magma.agent.worldmodel.IGlobalMap;

/**
 * the coordinator encapsulates and coordinates the access to the
 * action-interface.<br>
 * <br>
 * 
 * Every message-circle the coordinator sends a Motor-String, given by the
 * Axis-Speed-Maps, which should be filled during the circle by the active
 * behaviors<br>
 * 
 * It also provides the initialization- and beam-Message, which both suppresses
 * sending the motor-String for the given circle<br>
 * 
 * 
 * @author Mathias Ehret, Ingo Schindler, Stefan Glaser
 * 
 */
public class Coordinator implements ICoordinator
{

	protected IAgentModel agentModel;

	protected IGlobalMap worldModel;

	/** action processing of the agent */
	protected IAction action;

	protected boolean performInit = false;

	/**
	 * @param action
	 * @param agentModel
	 * @param worldModel
	 */
	public Coordinator(IAction action, IAgentModel agentModel,
			IGlobalMap worldModel)
	{
		this.agentModel = agentModel;
		this.worldModel = worldModel;
		this.action = action;
	}

	@Override
	public void update(IGlobalMap model)
	{
		if (!performInit) {
			// Send Motor String
			action.sendMotorString();
		} else {
			performInit = false;
		}
	}

	/**
	 * performAxisSpeed - performs a speed for the given Axis in this circle<br>
	 * <br>
	 * 
	 * @param hjName Name of the HingeJoint
	 * @param speed AxisSpeed
	 * 
	 */
	@Override
	public void performAxisSpeed(String hjName, float speed)
	{
		IHingeJoint hj;
		if (hjName != null && (hj = agentModel.getHJ(hjName)) != null) {
			action.setHingeEffectorSpeed(hj.getEffectorName(), speed);
		}
	}

	/**
	 * sends the Init-Message to the Server<br>
	 * (sending of the Motor-String will be suppressed for this circle)
	 */
	@Override
	public void performInit()
	{
		action.sendInitString();
		performInit = true;
	}

	/**
	 * sends a Beam-Message to the Server<br>
	 * (sending the Motor-String will be suppressed for this circle)
	 * 
	 * @param x
	 * @param y
	 * @param rotation
	 */
	@Override
	public void performBeam(float x, float y, float rotation)
	{
		action.sendBeamString(x, y, rotation);
	}

	@Override
	public void performSay(String message)
	{
		action.sendSayString(message);
	}

}
