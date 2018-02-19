#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstring>
#include <climits>
#include <queue>
#include "OSLstemmer.h"
#include "getAllFiles.h"
#include "index.h"
#define ull unsigned long long
#define ll long long
#define pb push_back
#define mp make_pair
#define ff first
#define ss second

using namespace std;


struct Node3																	//struct of output node with its relevance
 {	struct Node doc;
 	float docweight;															//docweight= relevance of doc
 }; 
bool compare_nocase (const struct Node& node1,const struct Node& node2)			//boolean compare function to compare two struct Node
{	string first=node1.name;													//based on doc name
	string second=node2.name;
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

bool compare_size(const list<struct Node> &l1,const list<struct Node> &l2){		//boolean compare function to compare two list based 
																				//on their sizes
	return (l1.size()<l2.size());
}

bool weight_compare(const struct Node3& node1,const struct Node3& node2){		//boolean compare function to compare two struct Node3 
	return (node1.docweight < node2.docweight);									//based on relevance
}

int main(){
	int n=getAllFiles();														//calling index function while getting the count of index
	for(auto i: index::myIndex){												//sorting index
		(i.ss).sort(compare_nocase);
	}

	cout<<" hi\n";
	while(1){																	//UI for user
		cout<<"Please enter your query\n";
		string s,out;
    	stringstream st;
    	cin.clear();
    	getline(cin,s);														    // getting query input
    	st<<s;
    	list< list<struct Node> > postings ;
        while(st>>out)
    	{
    		out=OSLstemmer(out);												//stemming each token of query
    		if(index::myIndex[out].size()>0)
                postings.pb(index::myIndex[out]);							    //adding the posting list for further processing
    		cout<<out<<endl;
    	}
        if(postings.size()){
        	postings.sort(compare_size);
        	list<struct Node3> ans;                                             //ans list
            priority_queue <int, vector<int>, greater<int> > pq;                // heap to store top 10 weight values 
            auto node1= (postings.begin());
            auto node2=(*node1).begin();
        	for(;node2!=(*node1).end();node2++)								    //copying shortest posting to ans
        	{	struct Node3 node;
        		node.doc=*node2;
        		node.docweight=(*node2).TF*log10(n/(*node1).size());
        		ans.pb(node);
                pq.push(node.docweight);
                if(pq.size()>10) 
                    pq.pop();
        	}
            int max=pq.top();
        	auto l=(postings.begin());											//l is a list of Node
        	l++;
            																	//first one is allready in ans;
        	for(;l!=postings.end();l++){									    //for each token 
        		auto postNode=(*l).begin();									    //intersecting two list	
        		auto ansNode=ans.begin();
        		while(postNode!=(*l).end()&&ansNode!=ans.end()){
                    float postvalue=(*postNode).TF*log10(n/(*l).size());
                    if(( *postNode).name == (*ansNode).doc.name ) {
        				(*ansNode).docweight+=postvalue;	                    //storing the intersection in ans
        				if(max<(*ansNode).docweight){
                            pq.push((*ansNode).docweight);
                            if(pq.size()>10) 
                                pq.pop();
                            max=pq.top();
                        }
                        postNode++;
        				ansNode++;
                    }
    				else if((*postNode).name<(*ansNode).doc.name){
    					if(max<postvalue){                                      //if current node has value in top ten include it in ans
                            pq.push(postvalue);
                            {struct Node3 node;
                            node.doc=*postNode;
                            node.docweight=postvalue;
                            ans.insert(ansNode,node);
                            }
                            if(pq.size()>10) 
                                pq.pop();
                            max=pq.top();
                        }
                        postNode++;
                    }
    				else{
                        if(max>(*ansNode).docweight)
                            ansNode=ans.erase(ansNode);
                        else ansNode++;
    				}
        		}
                if(postNode==(*l).end()){

                }
            }
        	ans.sort(weight_compare);											//sorting ans on weights
        	int count=0;
            while(!ans.empty()&&11>(count++)){
        		cout<<(ans.back()).doc.name<< "("<<(ans.back()).docweight<<")\n";//output;
        		ans.pop_back();
        	}
            ans.clear();
        }
        postings.clear();
        cout<<"Do you want to continue?(Y/N)\n";
		char c;
		cin.clear();
		cin>>c;
        if(c=='n'||c=='N') return 0;
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return 0;
}
