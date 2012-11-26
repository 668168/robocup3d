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
package magma.agent.connection.impl;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.logging.Level;
import java.util.logging.Logger;

import magma.agent.connection.IServerConnection;
import magma.util.observer.IObserver;
import magma.util.observer.IPublishSubscribe;
import magma.util.observer.Subject;

public class ServerConnection implements IServerConnection
{
	// handle for logging
	private static Logger logger = Logger.getLogger("");

	// the active host name of the server
	private String host;

	// Server TCP Port
	private int port;

	// Network socket
	private Socket socket;

	// Outgoing data stream
	private DataOutputStream out;

	// Incoming data stream
	private DataInputStream in;

	// Observer
	private final IPublishSubscribe<String> observer;

	// Last message received
	private String currentMessage;

	// True if connection is closed (after disconnection/error)
	private boolean shutDown;

	// true if we are currently connected to the server
	private boolean connected;

	/**
	 * Default constructor
	 */
	public ServerConnection()
	{
		this(SERVER_IP, SERVER_PORT);
	}

	/**
	 * Assignment constructor
	 * 
	 * @param host Host address
	 * @param port Port number
	 */
	public ServerConnection(String host, int port)
	{
		this.host = host;
		this.port = port;
		shutDown = false;
		connected = false;
		observer = new Subject<String>();
	}

	/**
	 * Change Server address/port
	 * 
	 * @param ip the ip of the soccer server
	 * @param port the port of the server
	 */
	public void setConnectionAddress(String ip, int port)
	{
		this.host = ip;
		this.port = port;
	}

	/**
	 * Actually connect to the server
	 */
	public boolean establishConnection()
	{
		try {
			socket = new Socket(host, port);
			socket.setTcpNoDelay(true);

			in = new DataInputStream(socket.getInputStream());
			out = new DataOutputStream(socket.getOutputStream());

			// System.out.println("Connection to: " + host + ":" + port);

			connected = true;
		} catch (UnknownHostException e) {
			e.printStackTrace();
			return false;
		} catch (IOException e) {
			e.printStackTrace();
			return false;
		}

		return true;
	}

	/**
	 * Send a message to the server
	 * 
	 * @param msg Message in ASCII form
	 */
	public void sendMessage(String msg)
	{
		logger.log(Level.FINEST, "sending: {0}", msg);
		byte[] body = msg.getBytes();

		// creation of the messages header (4 bytes)
		int len = body.length;
		int byte0 = (len >> 24) & 0xFF;
		int byte1 = (len >> 16) & 0xFF;
		int byte2 = (len >> 8) & 0xFF;
		int byte3 = len & 0xFF;

		try {
			out.writeByte((byte) byte0);
			out.writeByte((byte) byte1);
			out.writeByte((byte) byte2);
			out.writeByte((byte) byte3);
			out.write(body);
			out.flush();
		} catch (IOException e) {
			shutDown = true;
			System.out.println("Error writing to socket, shuting down...");
		}
	}

	/**
	 * Starts the endless loop of receiving messages and notifying observers
	 */
	public void startReceiveLoop()
	{
		while (!shutDown) {
			currentMessage = receiveMessage();

			logger.log(Level.FINER, "Received message from server");
			logger.log(Level.FINEST, "message: {0}", currentMessage);

			observer.onStateChange(currentMessage);

			logger.log(Level.FINER, "Message processed");
		}
		closeConnection();
		shutDown = false;
	}

	/**
	 * Stops the loop of receiving messages and notifying observers after
	 * receiving the next message
	 */
	public void stopReceiveLoop()
	{
		shutDown = true;
	}

	/*
	 * Receive server message
	 */
	private String receiveMessage()
	{
		String msg;
		byte[] result;
		int length;

		try {
			int byte0 = in.read();
			int byte1 = in.read();
			int byte2 = in.read();
			int byte3 = in.read();
			length = byte0 << 24 | byte1 << 16 | byte2 << 8 | byte3; // analyzes
			// the header
			int total = 0;

			if (length < 0) {
				// server was shutdown
				shutDown = true;
				return null;
			}

			result = new byte[length];
			while (total < length) {
				total += in.read(result, total, length - total);
			}

			msg = new String(result, 0, length, "UTF-8");
			System.out.println(msg);

		} catch (IOException e) {
			System.out.println("Error when reading from socket, closing down...");
			shutDown = true;
			return null;
		}
		return msg;
	}

	/*
	 * Close server connection
	 */
	private void closeConnection()
	{
		try {
			in.close();
			out.close();
			socket.close();
			connected = false;
		} catch (IOException e) {
			e.printStackTrace();
		}
		// System.out.println("Connection disconnected");
	}

	/**
	 * Attaches a new observer to this connection
	 * 
	 * @param newObserver the observer that is interested in new messages
	 */
	public void attach(IObserver<String> newObserver)
	{
		observer.attach(newObserver);
	}

	/**
	 * Get the latest incoming server message
	 * 
	 * @return Latest incoming server message
	 */
	public String getCurrentMessage()
	{
		return currentMessage;
	}

	/**
	 * @return true if we are currently connected to the server
	 */
	public boolean isConnected()
	{
		return connected;
	}
}
