/*
 *  Little Green BATS (2008), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	November 1, 2008
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef __INC_BATS_SOCKETCOMM_HH_
#define __INC_BATS_SOCKETCOMM_HH_

#include <queue>
#include <string>
//#include "message.hh"
#include "../PortableParser/portableparser.hh"
#include "../Vector3/vector3.hh"
#include "../Socket/socket.hh"
#include <iostream>
#include <fstream>
#include "../Types/types.hh"
#include "../TimeVal/timeval.hh"

namespace bats {
  /** Interface between agent and simulation server
	 *
   * The SocketComm is used to communicate with the robocup 3D simulation server. It parses and queues predicates recieved from the server and outputs messages to the server. Do not use this class directly, you probably need either AgentSocketComm or TrainerSocketComm
   *
   */
  class SocketComm {

    mvds::Socket d_socket;
    mvds::SocketAddress d_socketAddress;

  protected:
    static std::string s_jointNames[Types::NJOINTS];
    
    unsigned char d_buffer[64 * 1024];

    typedef std::queue<rf<Predicate> > MessageQueue;

    MessageQueue   d_oMessageQueue, d_iMessageQueue;
    PortableParser d_parser;

    rf<Predicate> d_currentPred;

    bool d_parseInput;
    
    mvds::TimeVal t0, t1;

    SocketComm(SocketComm const &); // NI
    SocketComm &operator=(SocketComm const &); // NI

    void destroy()
    {
    }
	
    void initConnection();
  
  public:

    /**
     * Default constructor. Call initSocket() before connecting to the server.
     */
    SocketComm()
    : d_parseInput(true)
    {
      gettimeofday(t0,0);
      Parser::initialize();
    }

    /**
     *  Initializes SocketComm to use @a host at portnumber @a port. Call connect() to actually establish the connection. 
     *
     *  @param host Host name/IP address of the server, eg "localhost", "192.168.1.1"
     *  @param port Port number of the server, standard number is 3001
     */
    SocketComm(std::string host, int port)
      :
      d_socket(PF_INET,SOCK_STREAM,0),
      d_socketAddress(PF_INET,port,host),
      d_parseInput(true)      
    {
      gettimeofday(t0,0);
      Parser::initialize();
    }

    ~SocketComm() { destroy(); }

    /**
     * Turn on/off parsing of input recieved from the server. Set to false to reduce overhead when the SocketComm is only used for sending messages to the server. Messages are still read from the socket to prevent overflows, but are imediatly discarded.
     */
    void parseInput(bool p);
    
    /**
     * Initialize the socket to use @a host at portnumber @a port. Call connect() to actually establish the connection. 
     */
    void initSocket(std::string host, int port)
    {
      d_socket = mvds::Socket(PF_INET,SOCK_STREAM,0);
      d_socketAddress = mvds::SocketAddress(PF_INET,port,host);
    }
    
    /**
     * Get description of the address that is being used.
     */
    mvds::SocketAddress getSocketAddress() { return d_socketAddress; }
    
    /**
     * Open a connection to the server
     *
     * @throws runtime_error when connection failed
     */
    void connect()
    {
      // Connect to the server.
      d_socket.connect(d_socketAddress);

      // Init connection.
      if (d_socket)
        initConnection();
      else
        throw std::runtime_error("error connecting to server");
    }

    /** Directly send a string message to the server
     *
     * @param msg The (string) message to be sent to the server. The message will be length prefixed and sent immediatly.
     */
    void sendMessage(std::string const &msg)
    {
      // This could be more efficient if we used a member buffer...
      unsigned int len = htonl(msg.length());
      std::string prefix(reinterpret_cast<const char*>(&len),sizeof(unsigned int));
      std::string data = prefix + msg;
      d_socket.writeExactly(data.c_str(), data.length());
    }


    /** Queue a predicate to be sent
     *
     * Queues the messages for sending. It will be sent
     * as soon as the update() method is called and the
     * server is ready to recieve.
     * @param pred The message to be sent
     */
    void send(rf<Predicate> pred) { d_oMessageQueue.push(pred); }

    /** Checks whether a new message has arrived from the server
     *
     * @returns true if a new message is queued
     */
    bool hasNextMessage() const
    {
      return !d_iMessageQueue.empty();
    }
    
    /**
     * Gives the next message recieved from the server
     * @returns The first message in the queue
     */
    rf<Predicate> nextMessage();

    /** Receive messages from the server when available */
    void receive();

    /** Send queued messages to the server */
    void send();

    /**
     * Update the communication by first sending queued messages and then reading new available input.
     * This method blocks until at least one message is read from the server.
     */
    void update()
    {
      send();
      receive();
    }

    /**
     * Get the current predicate from the internal parser
     * \todo can this be private/is this deprecated?
     */
    rf<Predicate> getPred() const
    {
      return d_parser.getPredicate();
    }
  };
}

#endif // __INC_BATS_SOCKETCOMM_HH_
