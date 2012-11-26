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
package magma.util;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

/**
 * Utils for serialization tests
 * @author dorer
 */
public class SerializationUtil
{
	/**
	 * Serializes the passed object to a byte array and deserializes it again
	 * @param testee the object to serialize
	 * @return the double serialized object
	 * @throws IOException should never happen
	 * @throws ClassNotFoundException if a class may not be desirialized
	 */
	public static Object doubleSerialize(Object testee) throws IOException,
			ClassNotFoundException
	{
		// write object to byte array (memory)
		ByteArrayOutputStream byteout = new ByteArrayOutputStream();
		ObjectOutputStream oos = new ObjectOutputStream(byteout);
		oos.writeObject(testee);

		// read object from byte array (memory)
		ByteArrayInputStream bytein = new ByteArrayInputStream(byteout
				.toByteArray());
		ObjectInputStream ois = new ObjectInputStream(bytein);
		Object result = ois.readObject();
		return result;
	}
}
