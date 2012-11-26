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
package magma.util.geometry;

import java.io.Serializable;

/**
 * Represents an angle. Objects are immutable.
 * @author dorer
 */
public class Angle implements Serializable
{
	/** */
	private static final long serialVersionUID = 1L;

	public final static Angle RAD180;

	public final static Angle RAD90;

	private final static double RAD360D;

	private final static double RAD180D;

	private final static double RAD90D;

	/** the angle value (rad) this object represents */
	private double angle;

	static {
		RAD360D = Math.toRadians(360);

		RAD180D = Math.toRadians(180);

		RAD90D = Math.toRadians(90);

		RAD180 = Angle.deg(-180);

		RAD90 = Angle.deg(90);
	}

	/**
	 * Creates a normalized angle [-RAD180 to RAD180[
	 * @param angle angle in radians
	 */
	public static Angle rad(double value)
	{
		return new Angle(value);
	}

	/**
	 * Creates a normalized angle [-RAD180 to RAD180[
	 * @param angle angle in degrees
	 */
	public static Angle deg(double value)
	{
		return new Angle(Math.toRadians(value));
	}

	private Angle(double angle)
	{
		this.angle = angle;
		normalize();
	}

	/**
	 * @return the angle value (rad) represented by this object
	 */
	public double radians()
	{
		return angle;
	}

	/**
	 * @return the angle value in degrees represented by this object
	 */
	public double degrees()
	{
		return Math.toDegrees(angle);
	}

	/**
	 * adds another angle
	 * @param other angle object
	 * @return a new Angle object representing the sum of this and other
	 */
	public Angle add(Angle other)
	{
		return new Angle(angle + other.angle);
	}

	/**
	 * adds a angle in rad
	 * @param value angle in rad
	 * @return a new Angle object representing the sum of this and other
	 */
	public Angle add(double value)
	{
		return new Angle(angle + value);
	}

	/**
	 * subtracts an angle object from this angle
	 * @param other angle object to subtract
	 * @return a new Angle object representing the difference of this and other
	 */
	public Angle subtract(Angle other)
	{
		return new Angle(angle - other.angle);
	}

	/**
	 * subtracts a angle in rad from this angle
	 * @param value angle in rad
	 * @return a new Angle object representing the difference of this and other
	 */
	public Angle subtract(double value)
	{
		return new Angle(angle - value);
	}

	/**
	 * @param angle the angle (rad) to normalize
	 * @return the same angle mapped to the range from -RAD180 to +RAD180
	 */
	private void normalize()
	{
		if (angle >= 0) {
			angle += RAD180D;
			angle = angle % RAD360D;
			angle -= RAD180D;
		} else {
			angle = -angle + RAD180D;
			angle = angle % RAD360D;
			angle = -(angle - RAD180D);
			if (angle >= RAD180D) {
				angle = -angle;
			}
		}
	}

	@Override
	public boolean equals(Object obj)
	{
		if (!(obj instanceof Angle)) {
			return false;
		}
		return ((Angle) obj).angle == this.angle;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString()
	{
		return "" + degrees();
	}

	/**
	 * An angle is left of another if it is bigger, but less than 180 degrees
	 * @param angle2 second angle object
	 * @return true if first angle is left of second
	 */
	public boolean isLeftOf(Angle angle2)
	{
		if (angle > RAD90D && angle2.angle < -RAD90D) {
			// value on -180 degree border
			return false;
		} else if (angle < -RAD90D && angle2.angle > RAD90D) {
			// value on +180 degree border
			return true;
		}

		double delta = angle2.subtract(angle).radians();
		if (delta < 0 && delta > -RAD180D) {
			return true;
		}

		return false;
	}

	/**
	 * An angle is right of another if it is not left of it
	 * @param angle2 second angle object
	 * @return true if first angle is right of second
	 */
	public boolean isRightOf(Angle angle2)
	{
		return !isLeftOf(angle2);
	}

	public static Angle average(Angle[] angles)
	{
		double average = angles[0].radians();
		for (int i = 1; i < angles.length; i++) {
			double angleToUse = angles[i].radians();
			if (average > RAD90D && angleToUse < -RAD90D) {
				// value on -180 degree border
				angleToUse += RAD360D;
			} else if (average < -RAD90D && angleToUse > RAD90D) {
				// value on +180 degree border
				angleToUse -= RAD360D;
			}
			average = (i * average + angleToUse) / (i + 1);
		}

		return Angle.rad(average);
	}
}
