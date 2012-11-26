#include "socketcomm.ih"

#ifndef BRAMTEST

void SocketComm::receive()
{
//    std::cout << "SocketComm::receive() BRAMTEST is NOT defined." << std::endl;
  unsigned messageLength = 0;

  unsigned len = 0, temp;

  unsigned char *buf = d_buffer;

  while (true)
  {
    temp = d_socket.read(reinterpret_cast<char *>(buf+len),sizeof(d_buffer)-len-(buf-d_buffer));

    _debugLevel4("The Big Read " << temp);

    if (temp) {
      gettimeofday(t0,0);
    } else if (sizeof(d_buffer)-len-(buf-d_buffer)) {
      gettimeofday(t1,0);

      if ((t1 - t0).getRealSeconds() > 5) {
        throw runtime_error("Server seems to have given up");
      }
    }

    len += temp;

    try
    {

      //      if (len)
      //              cerr << "Read! len = " << len << endl;

      /*
      // Find first messageLength (ussually write at the beginning).
      
      // First strategy: use the first of the buffer.

      for (buf = d_buffer; buf < d_buffer+len && *buf; ++buf);
      len -= (buf-d_buffer);
      */

      // Second strategy: use the last of the buffer. (it better
      // to use messagelength to do this)

      for (unsigned char *i = d_buffer; i < d_buffer+len; ++i)
      {
        if (!*i) {
	  _debugLevel4("Message boundary found, length: " << ntohl(*reinterpret_cast<unsigned*>(i)));
          buf = i;
          i += 3;
        }
      }

      len -= (buf-d_buffer);


      if (len >= 4)
      {
        memcpy(reinterpret_cast<char*>(&messageLength),buf,4);
        messageLength = ntohl(messageLength);

        _debugLevel4("Experimental messagelength = " << messageLength);

        len -= 4;
        buf += 4;

        // This works because the only place where the messageLength
        // is a small number is where it is preceded by the zero's.
        // A 16bit number is max 65535 (anything but a zero in front
        // of it and its atleast higher than that), len is max 16384.
        // Note that his means that the buffes should be smaller then 64KB!

        // At the moment we are a little behind (probably about 4 messages,
        // which doesn't have to be a big problem, because they might all
        // be the same anyway.. Although it could be fixed by reading ahead
        // in the buffer to find the last message and then parsing it
        // (of necesary by reading a little bit more data from the socket).

        if (messageLength < 65535 /*&& len <= messageLength*/)
        {

          _debugLevel4("MessageLength = " << messageLength);;

          d_parser.reset();

          while (true)
          {
            // Parse message so far.
            unsigned long plen = d_parser.parse(buf,min(len,messageLength));

	    //            d_dumpStream.write(reinterpret_cast<char *>(buf),plen);
          
            //          if (plen != len)
            //            throw runtime_error("error, this should not happen (plen != len)");

            messageLength -= plen;

            if (messageLength) {
              buf = d_buffer;
              len = d_socket.read(reinterpret_cast<char *>(buf),min(messageLength,static_cast<unsigned>(sizeof(d_buffer))));

	      if (len) {
          gettimeofday(t0,0);
	      } else {
          gettimeofday(t1,0);
	      
          if ((t1 - t0).getRealSeconds() > 5) {
            throw runtime_error("Server seems to have given up");
          }
	      }

	      //	      if (!len)
	      //		throw runtime_error("Received end-of-line");

            } else {
	      //              d_dumpStream << endl;
              d_parser.parse('\n');
              return;
            }
          }
        } else {
          len = 0;
          buf = d_buffer;
        }
      } else
        if (!d_socket)
          throw runtime_error("connection died");
    } catch (std::runtime_error e) {
      
      // This is a big fat hack!! But it should work nonetheless :)

      if (e.what() == "connection died")
        throw e;

      // otherwise start over an try to read the next message.

      messageLength = 0;
      len = 0;
      buf = d_buffer;
    }
  } 
}

#else

void SocketComm::receive()
{
//    std::cout << "SocketComm::receive BRAMTEST is defined." << std::endl;
  static unsigned char buffer[16384];
  static unsigned bufferOffset(0);
  static unsigned messageOffset(0);
  unsigned lastMessageOffset(0), lastMessageLength(0);
  
  if (!d_socket)
    throw runtime_error("connection died");

  //Read as much as we can
  bufferOffset += d_socket.read( reinterpret_cast<char *>(buffer)+bufferOffset, sizeof(buffer) - bufferOffset);//, MSG_DONTWAIT);

  //While the messages fit, pop them
  while(true)
  {
          unsigned messageLength = 0;
          memcpy(reinterpret_cast<char*>(&messageLength), buffer + messageOffset, 4);
          messageLength = ntohl(messageLength);
          
          _debugLevel2("Message length: " << messageLength);
          if(messageLength == 0)
          {
                  break;
          }
          
          messageOffset += 4;
          
          if(messageOffset + messageLength < sizeof(buffer) )
          {
                  //Pop message here
                  lastMessageOffset = messageOffset;
                  lastMessageLength = messageLength;
                  
                  //Try next message
                  messageOffset += messageLength;
                  _debugLevel4("Pop");
          }
          else
          {
                  _debugLevel4("Parse");
                  //Parse last message
                  d_parser.reset();
                  d_parser.parse(buffer + lastMessageOffset, lastMessageLength);
                  d_parser.parse('\n');
                  
                  //End of message popping, next message is not in there yet
                  //Move last read part to beginning of buffer
                  memcpy(buffer, buffer+messageOffset, bufferOffset - messageOffset);
  
                  //And reset write pointers and message pointer
                  bufferOffset = bufferOffset - messageOffset;
                  messageOffset = 0;
                  break;
          }
  }

}



#endif
