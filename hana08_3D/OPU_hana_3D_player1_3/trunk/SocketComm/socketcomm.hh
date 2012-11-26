/*
 *  Little Green BATS (2007), AI department, University of Groningen
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
 *  Date: 	July 27, 2007
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
#include "portableparser.hh"
#include "vector3.hh"
#include "socket.hh"
#include <iostream>
#include <fstream>
#include "types.hh"
#include "timeval.hh"

namespace bats {
  /** Interface between agent and simulation server
	 *
   * The SocketComm is used to communicate with the robocup 3D simulation server. It parses and queues predicates recieved from the server and outputs messages to the server. It is used by the WorldModel for input and by the Cerebellum for output.
   *
   */
  class SocketComm {

    mvds::Socket d_socket;
    mvds::SocketAddress d_socketAddress;

  private:
    static std::string s_jointNames[Types::NJOINTS];
    
    unsigned char d_buffer[64 * 1024];

    typedef std::queue<rf<Predicate> > MessageQueue;

    MessageQueue   d_oMessageQueue, d_iMessageQueue;
    PortableParser d_parser;

    rf<Predicate> d_currentPred;

    mvds::TimeVal t0, t1;

    SocketComm(SocketComm const &); // NI
    SocketComm &operator=(SocketComm const &); // NI

    void destroy()
    {
    }
	
    void initConnection();
  
  public:

    /**
     *  Initializes SocketComm and connects to host with port.
     *
     *  @param host Host name/IP address of the server, eg "localhost", "192.168.1.1"
     *  @param port Port number of the server, standard 3001
     */
    SocketComm(std::string host, int port)
      :
      d_socket(PF_INET,SOCK_STREAM,0),
      d_socketAddress(PF_INET,port,host)
    {
      gettimeofday(t0,0);
      Parser::initialize();
    }

    ~SocketComm() { destroy(); }

    /** Open a connection to the server
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
//      std::cout << "len: " << len << ", " << msg.length() << std::endl;
//      std::cout << "  -> [" << reinterpret_cast<const char*>(&len) << "]" << std::endl;
      std::string prefix(reinterpret_cast<const char*>(&len),sizeof(unsigned int));
//	  std::cout << "prefix = [" << prefix << "]" << std::endl;
//      if (msg.length() == 14 || msg.length == 31)
//        prefix = "?";
      std::string data = prefix + msg;
//	  std::cout << "data_before = " << data << ": " << data.length() << std::endl;
//	  std::cout << " -> " << 
	  d_socket.writeExactly(data.c_str(), data.length());
//	   << std::endl;
//	  std::cout << "data_after = " << data << ": " << data.length() << std::endl << std::endl;
    }


    /** Queue a predicate to be sent
     *
     * Queues the messages for sending. It will be sent
     * as soon as the update() method is called and the
     * server is ready to recieve.
     * @param pred The message to be sent
     */
    void send(rf<Predicate> pred) { d_oMessageQueue.push(pred); }


    /** Send initialization message
     *
     * Send an initialization message to the server, identifying the agent's uniformnumber and teamname
     * @param unum Uniform number (0 = auto choose by server)
     * @param team Team name
     */
    void init(unsigned unum, std::string team);
    
    /** Make an initialization message
     *
     * @param unum Uniform number (0 = auto choose by server)
     * @param team Team name
     */
    static rf<Predicate> makeInitMesage(unsigned unum, std::string team);
    
    /** Move a joint
     *
     * Move a joint by a certain angle. The angle will be added to the current angle of the joint. The move command will be sent the next time update() is called.
     * @param joint The joint to move
     * @param deltaAngle The angle to move the joint by in radians
     */
    void moveJoint(Types::Joint joint, double deltaAngle);
    
    /** Make a command predicate for moving a joint
     *
     * @param joint The joint to move
     * @param deltaAngle The angle to move the joint by in radians
     */
    static rf<Predicate> makeMoveJointMessage(Types::Joint joint, double deltaAngle);
    
    
    /** Move a hinge joint
     *
     * Move a hinge joint by a certain angle. A hinge joint has 1 degree of freedom. The move command will be sent the next time update() is called.
     * @param joint The joint effector name
     * @param deltaAngle The angle to move the joint by in radians
     */
    void moveHingeJoint(Types::Joint joint, double deltaAngle);
    
    /** Make a command predicate for moving a hinge joint
     *
     * @param joint The joint effector name
     * @param deltaAngle The angle to move the joint by in radians
     */
    static rf<Predicate> makeMoveHingeJointMessage(Types::Joint joint, double deltaAngle);
    
    /** Move a universal joint
     *
     * Move a universal joint by a certain angle. A universal joint has 2 degrees of freedom. The move command will be sent the next time update() is called.
     * @param joint The joint effector name (the name of the first axis, eg. Types::LARM1 for lae1_2)
     * @param deltaAngle1 The angle to move the joint by along the first axis in radians
     * @param deltaAngle2 The angle to move the joint by along the second axis in radians
     */
    void moveUniversalJoint(Types::Joint joint, double deltaAngle1, double deltaAngle2);

    /** Make a command predicate for moving a universal joint
     *
     * @param joint The joint effector name (the name of the first axis, eg. Types::LARM1 for lae1_2)
     * @param deltaAngle1 The angle to move the joint by along the first axis in radians
     * @param deltaAngle2 The angle to move the joint by along the second axis in radians
     */
    static rf<Predicate> makeMoveUniversalJointMessage(Types::Joint joint, double deltaAngle1, double deltaAngle2);
    
    /** Beam
     *
     * Beam the agent to a certain position. This command can only be used before kickoff and when a goal is scored. The beam command will be sent the next time update() is called.
     * @param pos The position to beam to. This should be on the own half of the field (x < 0)
     */
    void beam(Vector3D const& pos);
    
    /** Make a command predicate for beaming to a certain position
     *
     * @param pos The position to beam to. This should be on the own half of the field (x < 0)
     */
    static rf<Predicate> makeBeamMessage(Vector3D const& pos);
    
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

    /** Update the communication by first sending queued messages and then reading new available input
     * \todo Is this blocking?
     */
    void update()
    {
      send();
      receive();
    }

    /// \todo can this be private?
    rf<Predicate> getPred() const
    {
      return d_parser.getPredicate();
    }
  };
}

#endif // __INC_BATS_SOCKETCOMM_HH_
