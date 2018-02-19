#ifndef INDEX_H
#define INDEX_H
#include <iostream>
#include <unordered_map>
#include <map>
#include <list>
#include <string>
struct Node {																	// main struct to store name of indexed doc and its TF value
	std::string name;
	float TF;

};
class index
{public:
	static std::unordered_map<std::string,std::list<struct Node> > myIndex;		//static index
	static void indexing(std::string path); 

};
#endif
