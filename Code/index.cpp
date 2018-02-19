#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
#include <climits>
#include "OSLstemmer.h"
#include "index.h"
#include <fstream>
#include <math.h>
#define ull unsigned long long
#define ll long long
#define pb push_back	
#define mp make_pair
#define ff first
#define ss second
using namespace std;
/*struct Node {
	std::string name;
	int TF,weight;
	weight=(1+log10(TF))*log10(N/myIndex[s].size())
	
};
class index
{public:
	static std::unordered_map<std::string,std::list<struct Node> > myIndex;
	static void indexing(std::string path); 

};
*/
std::unordered_map<std::string,std::list<struct Node> > index::myIndex;			//Static variable deffination
struct Node2{																	//struct for temporary index
	public :int tf;
	int priority;
};
void index::indexing(string path){
	//open file then use tokenizer
	//add the words to the map 
	int flag=0;
	std::unordered_map<string,Node2> docIndex;									//temporary index for the doc
	ifstream inFile;;															//basic file handelling
	inFile.open(path.c_str());
	if(!inFile) return;
	string s;
	if(inFile>>s)																//Tokenization takes place internally 
	while(s!="Subject:"){														//domain specific data manipulation
		if(!(inFile>>s)){goto label;}
	}																			//NOW s="Subject:"
	if(inFile>>s)
		if(s=="RE:")															//replies have high priority than originals as they have original messages
			flag=1;
	while(s!="Mime-Version:"&&s!="Cc:"){
		s=OSLstemmer(s);														//calling stemmer function
		docIndex[s].tf++;
		docIndex[s].priority++;
			if(flag)
				docIndex[s].priority++;
		if(!(inFile>>s)){goto label;}
	}
	while(s!="X-FileName:"){
		if(!(inFile>>s)){goto label;}
	}																			//Now s is "X-FileName:"
	inFile>>s;
	while(s!="Forwarded"){														//forwarded msges must not be counted in TF
		s=OSLstemmer(s);
		if(s=="Thank"||s==""){goto label;}										//most of the emails end with thank you or ----forwarded--msgs 
		docIndex[s].tf++;
		if(!(inFile>>s)){goto label;}
	}
label:	inFile.close();
	
	for(auto i:docIndex){														//merging temp index and myIndex
		struct Node node;														
		node.name=path;
		node.TF=(1+log10((i.ss).tf) + (i.ss).priority);							//domain specific weighting criteria
		index::myIndex[i.ff].pb(node);
	}

}