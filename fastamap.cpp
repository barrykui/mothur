/*
 *  fastamap.cpp
 *  mothur
 *
 *  Created by Sarah Westcott on 1/16/09.
 *  Copyright 2009 Schloss Lab UMASS AMherst. All rights reserved.
 *
 */

#include "fastamap.h"

/*******************************************************************************/
void FastaMap::readFastaFile(ifstream& in) {
	try {
		string name, sequence, line;
		sequence = "";
	
		getline(in, line);
		name = line.substr(1, line.length());  //rips off '>'
	
		//read through file
		while (getline(in, line)) {
			if (isalnum(line.at(0))){  //if it's a sequence line
				sequence += line;
			}
			else{
				//input sequence info into map
				it = data.find(sequence);
				if (it == data.end()) { 	//it's unique.
					data[sequence].groupname = name;  //group name will be the name of the first duplicate sequence found.
					data[sequence].groupnumber = 1;
					data[sequence].names = name;
				}else { // its a duplicate.
					data[sequence].names += "," + name;
					data[sequence].groupnumber++;
				}
				name = (line.substr(1, (line.npos))); //The line you just read is a new name so rip off '>'
				sequence = "";
			}
		}
	
		//store last sequence and name info.
		it = data.find(sequence);
		if (it == data.end()) { 	//it's unique.
			data[sequence].groupname = name;  //group name will be the name of the first duplicate sequence found.
			data[sequence].groupnumber = 1;
			data[sequence].names = name;
		}else { // its a duplicate.
			data[sequence].names += "," + name;
			data[sequence].groupnumber++;
		}	
	}
	catch(exception& e) {
		cout << "Standard Error: " << e.what() << " has occurred in the FastaMap class Function readFastaFile. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}
	catch(...) {
		cout << "An unknown error has occurred in the FastaMap class function readFastaFile. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}
}
/*******************************************************************************/
string FastaMap::getGroupName(string seq) {  //pass a sequence name get its group
	return data[seq].groupname;
}
/*******************************************************************************/
string FastaMap::getNames(string seq) {	//pass a sequence get the string of names in the group separated by ','s.
	return data[seq].names;
}
/*******************************************************************************/
int FastaMap::getGroupNumber(string seq) {	//pass a sequence get the number of identical sequences.
	return data[seq].groupnumber;
}
/*******************************************************************************/
void FastaMap::push_back(string seq, string Name) {//sequencename, name
	data[seq].groupname = Name;
	data[seq].names = Name;
}
/*******************************************************************************/
void FastaMap::set(string seq, string groupName, string Names) {
	data[seq].groupname = groupName;
	data[seq].names = Names;
}
/*******************************************************************************/
void FastaMap::clear() { //clears out data
	data.clear();
}
/*******************************************************************************/
int FastaMap::size(){ //returns datas size which is the number of unique sequences
	return data.size();
}
/*******************************************************************************/
void FastaMap::print(ostream& out){ //prints data
	try {
		// two column file created with groupname and them list of identical sequence names
		for (it = data.begin(); it != data.end(); it++) {
			out << it->second.groupname << '\t' << it->second.names << endl;
		}
	}
	catch(exception& e) {
		cout << "Standard Error: " << e.what() << " has occurred in the FastaMap class Function print. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}
	catch(...) {
		cout << "An unknown error has occurred in the FastaMap class function print. Please contact Pat Schloss at pschloss@microbio.umass.edu." << "\n";
		exit(1);
	}
}
/*******************************************************************************/