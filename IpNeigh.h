#ifndef IPNEIGH_H
#define IPNEIGH_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum IpStateEnum { UNKNOWN=0, FAILED, STALE, REACHABLE };

typedef enum IpStateEnum IpStateType;

void Tokenize(const string& str,
              vector<string>& tokens,
              const string& delimiters = " ");

typedef map<string, IpStateType> ip_map;

class IpNeigh
{
public:
	IpNeigh();
	~IpNeigh();
	int Add(char * ipnst);
	IpStateType GetState(char * ipst);
	char * GetStateStr(IpStateType ipstate);
private:
	string InputBuff;
	string IpAddr;
	string IpStateStr;
	IpStateType IpState;
	vector <string> InputTokens;
	ip_map Adresses;
};

#endif
