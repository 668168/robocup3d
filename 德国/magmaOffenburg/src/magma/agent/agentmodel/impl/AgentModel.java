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
package magma.agent.agentmodel.impl;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

import magma.agent.IServerConfigFilesConstants;
import magma.agent.agentmodel.IAgentModel;
import magma.agent.perception.IPerception;
import magma.util.observer.IObserver;
import magma.util.observer.IPublishSubscribe;
import magma.util.observer.Subject;

import org.apache.commons.math.geometry.Vector3D;

public abstract class AgentModel implements IObserver<IPerception>,
		IAgentModel, Serializable
{
	private static final long serialVersionUID = 1L;

	/** all sensors of the agent. Use IServerConfigFilesConstants as keys */
	protected Map<String, Sensor> sensores;

	/** observers of agent model */
	private final transient IPublishSubscribe<IAgentModel> observer;

	/**
	 * initializes all known Sensors like: UniversalJoints, HingeJoints,
	 * ForceResistances and GyroRates
	 */
	public AgentModel()
	{
		sensores = new HashMap<String, Sensor>();

		// initialize sensors
		initUniversalJoints();
		initHingeJoints();
		initForceResistance();
		initGyro();

		observer = new Subject<IAgentModel>();
	}

	/**
	 * initializes all known Universaljoints-Sensors (which are defined in
	 * IServerConfigFilesConstants)
	 */
	protected void initUniversalJoints()
	{
		for (int i = 0; i < IServerConfigFilesConstants.UNIVERSALJOINT_NAMES.length; i++) {
			sensores.put(IServerConfigFilesConstants.UNIVERSALJOINT_NAMES[i],
					new UniversalJoint(
							IServerConfigFilesConstants.UNIVERSALJOINT_NAMES[i]));
		}
	}

	/**
	 * initializes all known HingeJoints-Sensors (which are defined in
	 * IServerConfigFilesConstants)
	 */
	protected void initHingeJoints()
	{
		for (int i = 0; i < IServerConfigFilesConstants.HINGEJOINT_NAMES.length; i++) {
			sensores.put(IServerConfigFilesConstants.HINGEJOINT_NAMES[i],
					new HingeJoint(IServerConfigFilesConstants.HINGEJOINT_NAMES[i],
							IServerConfigFilesConstants.HINGEJOINT_EFFECTORS[i],
							IServerConfigFilesConstants.HINGEJOINT_BOUNDS[i][0],
							IServerConfigFilesConstants.HINGEJOINT_BOUNDS[i][1]));
		}
	}

	/**
	 * initializes all known ForceResistances-Sensors (which are defined in
	 * IServerConfigFilesConstants)
	 */
	protected void initForceResistance()
	{
		for (int i = 0; i < IServerConfigFilesConstants.FORCERESISTANCE_NAMES.length; i++) {
			sensores.put(IServerConfigFilesConstants.FORCERESISTANCE_NAMES[i],
					new ForceResistance(
							IServerConfigFilesConstants.FORCERESISTANCE_NAMES[i]));
		}
	}

	/**
	 * initializes all known GyroRate-Sensors (which are defined in
	 * IServerConfigFilesConstants)
	 */
	protected void initGyro()
	{
		for (int i = 0; i < IServerConfigFilesConstants.GYRORATE_NAMES.length; i++) {
			sensores.put(IServerConfigFilesConstants.GYRORATE_NAMES[i],
					new GyroRate(IServerConfigFilesConstants.GYRORATE_NAMES[i]));
		}
	}

	/**
	 * Implementation of the observer called if agent model params might have
	 * changed
	 */
	@Override
	public void update(IPerception perception)
	{

		// update all Sensors
		updateUniversalJoints(perception);
		updateHingeJoints(perception);
		updateForceResistance(perception);
		updateGytoRate(perception);

		// now inform observers about changes
		observer.onStateChange(this);
	}

	public void attach(IObserver<IAgentModel> newObserver)
	{
		observer.attach(newObserver);
	}

	public boolean detach(IObserver<IAgentModel> oldObserver)
	{
		return observer.detach(oldObserver);
	}

	/**
	 * updates all known UniversalJoints from perception
	 * @param perception the result from server message parsing
	 */
	protected void updateUniversalJoints(IPerception perception)
	{
		for (int i = 0; i < IServerConfigFilesConstants.UNIVERSALJOINT_NAMES.length; i++) {
			getUJ(IServerConfigFilesConstants.UNIVERSALJOINT_NAMES[i]).setAx1(
					perception.getUniversalJointPerceptor(
							IServerConfigFilesConstants.UNIVERSALJOINT_PERCEPTORS[i])
							.getAxis1());
			getUJ(IServerConfigFilesConstants.UNIVERSALJOINT_NAMES[i]).setAx2(
					perception.getUniversalJointPerceptor(
							IServerConfigFilesConstants.UNIVERSALJOINT_PERCEPTORS[i])
							.getAxis2());
		}
	}

	/**
	 * updates all known HingeJoints from perception
	 * @param perception the result from server message parsing
	 */
	protected void updateHingeJoints(IPerception perception)
	{
		for (int i = 0; i < IServerConfigFilesConstants.HINGEJOINT_NAMES.length; i++) {
			getHJ(IServerConfigFilesConstants.HINGEJOINT_NAMES[i]).setAxis(
					perception.getHingeJointPerceptor(
							IServerConfigFilesConstants.HINGEJOINT_PERCEPTORS[i])
							.getAxis());
		}
	}

	/**
	 * updates all known ForceResistances from perception
	 * @param perception the result from server message parsing
	 */
	protected void updateForceResistance(IPerception perception)
	{
		Vector3D force;
		Vector3D forceOrigin;

		for (int i = 0; i < IServerConfigFilesConstants.FORCERESISTANCE_NAMES.length; i++) {
			// Fetch new Force Values
			force = perception.getForceResistancePerceptor(
					IServerConfigFilesConstants.FORCERESISTANCE_PERCEPTORS[i])
					.getForce();
			forceOrigin = perception.getForceResistancePerceptor(
					IServerConfigFilesConstants.FORCERESISTANCE_PERCEPTORS[i])
					.getForceOrigin();

			// Set new Force Values
			getForceResistance(
					IServerConfigFilesConstants.FORCERESISTANCE_NAMES[i]).setForce(
					new Vector3D(force.getX(), force.getY(), force.getZ()));
			getForceResistance(
					IServerConfigFilesConstants.FORCERESISTANCE_NAMES[i])
					.setForceOrigin(
							new Vector3D(forceOrigin.getX(), forceOrigin.getY(),
									forceOrigin.getZ()));
		}
	}

	/**
	 * updates all known GyroRates from perception
	 * @param perception the result from server message parsing
	 */
	protected void updateGytoRate(IPerception perception)
	{
		Vector3D rate;

		for (int i = 0; i < IServerConfigFilesConstants.GYRORATE_NAMES.length; i++) {
			rate = perception.getGyroRatePerceptor(
					IServerConfigFilesConstants.GYRORATE_PERCEPTORS[i]).getGyro();
			getGyroRate(IServerConfigFilesConstants.GYRORATE_NAMES[i]).setGyro(
					new Vector3D(rate.getX(), rate.getY(), rate.getZ()));
		}
	}

	public abstract float checkHJTarget(String name, float targetposition,
			float range);

	public abstract boolean checkHJTrigger(String name, float targetposition,
			float range);

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.agentmodel.impl.IAgentModel#getUJ(java.lang.String)
	 */
	public UniversalJoint getUJ(String name)
	{
		return null;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.agentmodel.impl.IAgentModel#getHJ(java.lang.String)
	 */
	public HingeJoint getHJ(String name)
	{
		return (HingeJoint) sensores.get(name);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * magma.agent.agentmodel.impl.IAgentModel#getForceResistance(java.lang.String
	 * )
	 */
	public ForceResistance getForceResistance(String name)
	{
		return (ForceResistance) sensores.get(name);
	}

	/**
	 * checks if the agent stands on both feet
	 * @return
	 */
	public boolean standingStill()
	{
		// ForceResistance rightFoot = (ForceResistance) sensores
		// .get(IServerConfigFilesConstants.FORCERESISTANCE_PERCEPTORS[0]);
		// ForceResistance leftFoot = (ForceResistance) sensores
		// .get(IServerConfigFilesConstants.FORCERESISTANCE_PERCEPTORS[1]);

		// rightFoot.getForce().

		GyroRate gyro = getGyroRate(IServerConfigFilesConstants.GYRORATE_NAMES[0]);
		return (gyro.getTranslation().getZ() > 0.8);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.agentmodel.impl.IAgentModel#getGyroRate(java.lang.String)
	 */
	public GyroRate getGyroRate(String name)
	{
		return (GyroRate) sensores.get(name);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object o)
	{
		if (!(o instanceof AgentModel)) {
			return false;
		}
		AgentModel other = (AgentModel) o;
		if (!sensores.equals(other.sensores)) {
			return false;
		}
		return true;
	}
}
