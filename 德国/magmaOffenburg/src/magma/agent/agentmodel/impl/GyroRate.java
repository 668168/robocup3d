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

import java.util.logging.Level;
import java.util.logging.Logger;

import javax.vecmath.Matrix3d;

import magma.agent.agentmodel.IGyroRate;
import magma.util.FuzzyCompare;
import magma.util.geometry.MatrixUtil;

import org.apache.commons.math.geometry.Vector3D;

import static java.lang.Math.cos;
import static java.lang.Math.sin;

/**
 * @author Stefan Glaser, Srinivasa Ragavan
 * 
 */
public class GyroRate extends Sensor implements IGyroRate
{
	// handle for logging
	private static Logger logger = Logger.getLogger("");

	/** id for serialization */
	private static final long serialVersionUID = 6859542740368696037L;

	/** angular change to previous orientation */
	private Vector3D gyro;

	/** 3x3 identity matrix which is rotated */
	Matrix3d identity;

	public GyroRate(String name)
	{
		super(name);
		initialize();
	}

	/**
	 * resets the gyro to upright position
	 */
	public void initialize()
	{
		if (identity != null) {
			logger.log(Level.FINER, "gyro init old: ({0}, {1}, {2})",
					new Object[] { identity.m02, identity.m12, identity.m22 });
		}

		gyro = new Vector3D();
		identity = new Matrix3d(1, 0, 0, 0, 1, 0, 0, 0, 1);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see magma.agent.agentmodel.impl.IGyroRate#getGyro()
	 */
	public Vector3D getGyro()
	{
		return gyro;
	}

	public void setGyro(Vector3D gyro)
	{
		this.gyro = gyro;

		double x, y, z;

		x = Math.toRadians(gyro.getX() * 0.02);
		y = Math.toRadians(gyro.getY() * 0.02);
		z = Math.toRadians(gyro.getZ() * 0.02);

		double[] rotationValues = new double[9];

		rotationValues[0] = cos(y) * cos(z) + sin(x) * sin(y) * sin(z);
		rotationValues[1] = sin(z) * cos(x);
		rotationValues[2] = -sin(y) * cos(z) + sin(x) * cos(y) * sin(z);
		rotationValues[3] = -cos(y) * sin(z) + sin(x) * sin(y) * cos(z);
		rotationValues[4] = cos(x) * cos(z);
		rotationValues[5] = sin(z) * sin(z) + sin(x) * cos(y) * cos(z);
		rotationValues[6] = cos(x) * sin(y);
		rotationValues[7] = -sin(x);
		rotationValues[8] = cos(x) * cos(y);

		Matrix3d M = new Matrix3d(rotationValues);

		M.mul(identity);

		// Error correction
		// N = M / sqrt(MT x M)
		// N - closest rotation result without errors
		// M - with errors
		// MT - transpose of M
		// sqrt of matrix - done by Cholesky Algorithm in MatrixUtil.java

		Matrix3d MT = new Matrix3d(M.m00, M.m10, M.m20, M.m01, M.m11, M.m21,
				M.m02, M.m12, M.m22);

		MT.mul(M);

		// call cholesky for sqrt(matrix)
		Matrix3d sqrt = MatrixUtil.cholesky(MT);

		sqrt.invert();
		M.mul(sqrt);

		// setting identity as result of error correction
		identity = M;

		logger.log(Level.FINER, "gyro update: ({0}, {1}, {2})", new Object[] {
				identity.m02, identity.m12, identity.m22 });
	}

	public Vector3D getTranslation()
	{
		return new Vector3D(identity.m02, identity.m12, identity.m22);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object o)
	{
		if (!(o instanceof GyroRate)) {
			return false;
		}
		GyroRate other = (GyroRate) o;
		if (!super.equals(other)) {
			return false;
		}
		if (!FuzzyCompare.eq(gyro, other.gyro, 0.00001f)) {
			return false;
		}
		return true;
	}

}
