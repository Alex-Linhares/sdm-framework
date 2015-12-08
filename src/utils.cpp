#include <sstream>
#include <sys/time.h>
#include <string>
#include <iostream>
#include "utils.h"

// Original code: http://stackoverflow.com/a/21698913/465035
std::string trim(const std::string &s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isspace(*it)) {
		it++;
	}
	std::string::const_reverse_iterator rit = s.rbegin();
	while (rit.base() != it && isspace(*rit)) {
		rit++;
	}
	return std::string(it, rit.base());
}

// Original code: http://stackoverflow.com/a/236803/465035
std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

void TimeMeasure::start() {
	this->ref_time = this->get_time();
}

void TimeMeasure::mark(const std::string &name) {
	this->measures.push_back(std::make_pair(name, this->get_time()));
}

std::string TimeMeasure::str() {
	std::stringstream ss;
	long long last = this->ref_time;
	long long dt1, dt2;
	for(int i=0; i<this->measures.size(); i++) {
		std::pair<std::string, long long> *x = &this->measures[i];
		dt1 = x->second - this->ref_time;
		dt2 = x->second - last;
		ss << dt1 << " " << dt2 << " " << x->first << std::endl;
		last = x->second;
	}
	return ss.str();
}

long long TimeMeasure::get_time() {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long long x = (long long)tp.tv_sec * 1000L + (tp.tv_usec/1000);
	return x;
}

