#include "utils.h"
void utils::replaceAll(string & str,const string & from,const string & to){
	if(from.empty())
		return;
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != string::npos){
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

void utils::normalize(vector<float> & array){
	float max = 0;
	float scale = 0;
	// find biggest value
	for(int i = 0; i < array.size(); i++){
		float temp = abs(array[i]);
		max = temp > max ? temp : max;
	}
	scale = 1 /(float) max;
	for(int i = 0; i < array.size(); i++){
		array[i] = array[i] * scale;
	}
}
