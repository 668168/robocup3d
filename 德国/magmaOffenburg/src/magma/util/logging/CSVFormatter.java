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
package magma.util.logging;

import java.util.logging.Formatter;
import java.util.logging.LogRecord;

/**
 * Log file formatter that simplifies writing CSV files
 */
public class CSVFormatter extends Formatter
{
	// Line separator string. This is the value of the line.separator
	// property at the moment that the SimpleFormatter was created.
	private String lineSeparator = java.security.AccessController
			.doPrivileged(new sun.security.action.GetPropertyAction(
					"line.separator"));

	/**
	 * Format the given LogRecord.
	 * @param record the log record to be formatted.
	 * @return a formatted log record
	 */
	@Override
	public synchronized String format(LogRecord record)
	{
		StringBuffer sb = new StringBuffer();
		String message = record.getMessage();
		String newMessage = message.replace('.', ',');
		sb.append(newMessage);
		sb.append(lineSeparator);
		return sb.toString();
	}
}
