// Compute the weighted Kendall distance (no ties) in O(n lg n)
// By F. Farnoud, July 2914

// Gives the weighted Kendall distance between two rankings. 
// Based on An Axiomatic Approach to Constructing Distances for Rank Comparison and Aggregation,
// F. Farnoud, and O. Milenkovic, IEEE Trans. Information Theory, vol. 60, pp. 6417–6439, Oct. 2014.

#include "weightedkendall.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char **argv){
	ifstream inFile;
	int return_code = 0;
	bool isInputFileGiven = false;
	string inputFile;
	string line;
	string lines;
	int n;
	int * p1, *p2;
	double *w;
	try{
		for (int i = 1; i < argc; ++i){
			string arg = argv[i];
			if ((arg == "-h") || (arg == "--help")){
				cout<<"\nNAME\n";
				cout<<"\tweightedkendall\n";
				cout<<"\nDESCRIPTION\n";
				cout<<"\tGives the weighted Kendall distance between two rankings. \n";
				cout<<"\tBased on An Axiomatic Approach to Constructing Distances\n\tfor Rank Comparison and Aggregation, F. Farnoud,\n";
				cout<<"\tand O. Milenkovic, IEEE Trans. Information Theory, Oct. 2014.\n";
				cout<<"USAGE 1: \n";
				cout<<"\tSTree_LZF -f input-file\n" << flush;
				cout<<"USAGE 2: \n";
				cout<<"\tSTree_LZF n -p1 first_ranking [-p2 second_ranking] -w weight_function (NOT IMPLEMENTED YET)" << flush;
				cout<<"\nNOTES:\n";
				cout<<"\tIf With -f input, the first line is n (the length of the rankings), the second line is p1, \n\tthe third line is p2, the fourth line is w.\n";
				cout<<"\n";
				return 0;
			} else if (arg == "-f") {
				if ( i + 1 < argc) {
					isInputFileGiven = true;
					inputFile.assign(argv[++i]);
				} else {
					throw std::invalid_argument("No argument given for the option -f.\n");
				}
			}

		}
		if (!isInputFileGiven){
			throw std::invalid_argument("No input given.\n");
		}
		inFile.open(inputFile);
		lines.assign("");
		while (getline(inFile, line)){
			lines += " ";
			lines += line;
		}
		stringstream  linestream(lines);
		linestream>>n;
		p1 = new int[n];
		for (int j = 0; j < n; ++j){
			linestream >> p1[j];
		}
		p2 = new int[n];
		for (int j = 0; j < n; ++j){
			linestream >> p2[j];
		}
		w = new double[n-1];
		for (int j = 0; j < n-1; ++j){
			linestream >> w[j];
		}
		cout<<"Distance between rankings: "<< weightedkendall(p1,p2,w,n)<<"\n";
		delete p1,p2,w;

	}
	catch( const std::invalid_argument& e ) {
		cout<<e.what();
		return_code = 1;
	}
	cout<<"Press Enter to exit..."<<flush;
	cin.get();
	cout<<"\n";
	return(return_code);
}