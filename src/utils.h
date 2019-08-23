#ifndef utils_h
#define utils_h
#include "ofMain.h"
class utils{
public:
	static void replaceAll(string & str,const string & from,const string & to);
	static void normalize(vector<float> & array);
};
	
#endif
