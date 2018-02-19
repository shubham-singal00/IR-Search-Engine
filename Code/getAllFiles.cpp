#include <iostream>
#include <string>
#include <dirent.h>
#include "getAllFiles.h"
#include "index.h"
int getAllFiles() {
	int count=0;																//Nummber of file indexed
	std::string path_string="./maildir/";										//path to main DataSet
	DIR *dir,*dir2;																//Local variables
	struct dirent *ent,*ent2;
	if ((dir = opendir (path_string.c_str())) != NULL) {						//checking for error in file handelling
	/* get all the files and directories within directory */
		 ent = readdir (dir);		//reading "."
		 ent = readdir (dir);		//reading ".."
		 while((ent = readdir (dir)) != NULL&&count<10000) {						
			std::string path2  = path_string+ent -> d_name + "/all_documents/";		//getting everything inside "/all_documents/"
			if((dir2 = opendir (path2.c_str())) != NULL){
				ent2=readdir (dir2);		//reading "."
				ent2=readdir (dir2);		//reading ".."
					while((ent2=readdir (dir2)) != NULL&&count<10000){
					std::string name = path2 + ent2 -> d_name;
					index::indexing(name);											//calling the indexing function with the file path
					count++;
					}
				path2.clear();
			}
		}
		closedir (dir);
	} 
	else {
	/* could not open directory */
	perror ("");
	return EXIT_FAILURE;
	}
return count;																	//returning the count of indexed docs
}