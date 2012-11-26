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
package magma.agent.connection;

import magma.util.observer.ISubscribe;

public interface IServerConnection extends ISubscribe<String>
{
	/** the default IP of the RoboCup server */
	String SERVER_IP = "127.0.0.1";

	/** the default port of the server */
	int SERVER_PORT = 3100;

	/**
	 * Allows to change the ip and port of the server to connect to
	 * @param ip the ip of the soccer server
	 * @param port the port of the server
	 */
	public abstract void setConnectionAddress(String ip, int port);

	/**
	 * Creates a connection to the server and initializes the input and output
	 * stream
	 * @return true if the connection was successfully established
	 */
	public abstract boolean establishConnection();

	/**
	 * Sends the passed message to the server
	 * @param msg the message to send
	 */
	public abstract void sendMessage(String msg);

	/**
	 * Starts the receive loop that only ends once the socket is shutdown
	 */
	public abstract void startReceiveLoop();

	/**
	 * Stops the loop of receiving messages and notifying observers after
	 * receiving the next message
	 */
	public abstract void stopReceiveLoop();

	/**
	 * @return true if we are currently connected to the server
	 */
	public abstract boolean isConnected();

	/**
	 * @return the currentMessage that was most recently received
	 */
	public abstract String getCurrentMessage();
}