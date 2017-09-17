#include <stdio.h>

#include "IpNeigh.h"

extern int verbose;

// Constructor
IpNeigh::IpNeigh()
{
   ;
}

// Destructor
IpNeigh::~IpNeigh()
{
   ;
}

// Add entry to map
int IpNeigh::Add(char * ipnst)
{
   InputBuff = string(ipnst);
   
   InputTokens.clear();
   
   Tokenize(InputBuff, InputTokens, " \n");
   
   IpAddr = InputTokens.front();
   IpStateStr = InputTokens.back();
   
   if (IpStateStr == "FAILED")
      IpState = FAILED;
   else if (IpStateStr == "STALE")
      IpState = STALE;
   else if (IpStateStr == "REACHABLE")
      IpState = REACHABLE;
   else 
      IpState = UNKNOWN; 
   
   if (verbose) printf("IP %s is in state %s\n", IpAddr.c_str(), IpStateStr.c_str());
   
   Adresses[IpAddr] = IpState;
   
   return 0;
}

// \brief Look up entry in map
IpStateType IpNeigh::GetState(char * ipst)
{
   InputBuff = string(ipst);
   
   ip_map::const_iterator i = Adresses.find(InputBuff);
   if (i == Adresses.end ())
      return UNKNOWN;
   
   return i->second;
}

char * IpNeigh::GetStateStr(IpStateType ipstate)
{
	switch (ipstate)
	{
	case FAILED :
		return (char*) "FAILED";
		break;
	case STALE :
		return (char*) "STALE";
		break;
	case REACHABLE :
		return (char*) "REACHABLE";
		break;
	case UNKNOWN :
		return (char*) "UNKNOWN";
		break;
	default :
		return (char*) "undefined";
	}
}

// Split string into tokens
void Tokenize(const string& str,
              vector<string>& tokens,
              const string& delimiters)
{
    // Skip delimiters at beginning
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    
    // Find first non-delimiter
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the use of "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next non-delimiter
        pos = str.find_first_of(delimiters, lastPos);
    }
}
