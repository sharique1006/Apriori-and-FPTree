#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

using namespace std;

//Input File
ifstream infile;
string input_file;
//Output File
ofstream outfile;
string output_file;
//Total number of Transactions
int numTransactions = 0;
//Threshold Support
float minSupport;
//Size of an itemset
int item_set_size;

//Function to generate frequent itemsets of size = 1
vector<vector<int>> generate_F1() {
	//Map to store items with their frequency
	map <int, int> C1;
	string st;
	//Read DataBase
	infile.open(input_file);
	if(!infile) {
		cout << "File doesn't exist" << endl;
		exit(1);
	}
	while(getline(infile, st)) {
		int len = st.length();
		char str[len+1];
		strcpy(str, st.c_str());
		char *token = strtok(str, " ");
		while (token != NULL) { 
        	int item = atoi(token); 
        	if(C1.find(item) == C1.end()) {
        		C1[item] = 1;
        	}
        	else {
        		C1[item]++;
        	}
        	token = strtok(NULL, " "); 
    	} 
    	//Increase Total Transaction Counter
    	numTransactions++;
	}
	infile.close();
	//Convert Threshold percentage to threshold value
	minSupport = numTransactions*minSupport / 100.0;
	vector <int> f1;
	for (auto itemset : C1) {
		if(itemset.second >= minSupport) {
			f1.push_back(itemset.first);
		}
	}
	sort(f1.begin(), f1.end());
	//F1 is Frequent Itemset of size1
	vector<vector<int>> F1;
	for (int i = 0; i < f1.size(); i++) {
        vector <int> oldVec;
        oldVec.insert(oldVec.begin(), f1[i]);
        F1.insert(F1.begin() + i, oldVec);
	}
	return F1;
}

//Function to generate CandidateSet C(k) from Frequent ItemSet F(k-1).
vector<vector<int>> generateCandidateItemSet(vector<vector<int>> prevF) {
	vector<vector<int>> candidate_item_set;
	//Pick two distinct pairs from F(k-1) and check if they can be merged
	for(int i = 0; i < prevF.size() - 1; i++) {
		for(int j = i+1; j < prevF.size(); j++) {
			bool isMergable = true;
			//Two itemsets can be merged if only their last element is distinct
			for(int k = 0; k < item_set_size - 1; k++) {
				if(prevF[i][k] != prevF[j][k]) {
					isMergable = false;
					break;
				}
			}
			if(!isMergable) {
				break;
			}
			//If Mergable then generate candidate item from F(k-1)[i] and F(k-1)[j] by taking their union
			vector<int> candidate_item = prevF[i];
			candidate_item.push_back(prevF[j][item_set_size - 1]);
			candidate_item_set.push_back(candidate_item);
		}
	}
	return candidate_item_set;
}

bool comp(int a, int b){
	return to_string(a) < to_string(b);
}

void printFrequentItemSet(vector<int> candidateItem) {
	sort(candidateItem.begin(), candidateItem.end(), comp);
	for(int k = 0; k < candidateItem.size(); k++) {
		outfile <<candidateItem[k]<<" ";
	}
	outfile <<endl;
}

//Function to generate All Frequent Itemsets.
void generateFrequentItemSets() {
	outfile.open(output_file);
	//Write all frequent itemsets of size 1
	vector<vector<int>> F1 = generate_F1();	  	
	for(int i = 0; i < F1.size(); i++) {
		outfile <<F1[i][0]<<endl;
	}

	vector<vector<int>> prevF = F1;
	vector <int> support;
	item_set_size = 1;

	//Keep Generating itemsets while the previous frequent itemset is not empty
	while(!prevF.empty()) {
		//Generate Candidate Itemsets from F(k-1)
		vector<vector<int>> candidateItemSet = generateCandidateItemSet(prevF);
		support.clear();
		for(int i = 0; i < candidateItemSet.size(); i++) {
			support.push_back(0);
		}
		string st;
		infile.open(input_file);
		//Scan the database to calculate support of itemset
		while(getline(infile, st)) {
			set<int> transaction;
			int len = st.length();
			char str[len+1];
			strcpy(str, st.c_str());
			char *token = strtok(str, " ");
			while (token != NULL) { 
        		int item = atoi(token); 
        		transaction.insert(item);
        		token = strtok(NULL, " "); 
    		}
    		//Calculate the support of all itemsets in the candidate itemset
    		for(int i = 0; i < candidateItemSet.size(); i++) {
                if(includes(transaction.begin(), transaction.end(), candidateItemSet[i].begin(), candidateItemSet[i].end())) {
                    support[i] = support[i] + 1;
                }
            }
		}
		infile.close();
		prevF.clear();
		//The new frequent itemset will contain an itemset from the candidate itemset if its support is greater than threshold support
		for(int i = 0; i < candidateItemSet.size(); i++) {
			if(support[i] >= minSupport) {
				prevF.push_back(candidateItemSet[i]);
				//Display the frequent itemset
				printFrequentItemSet(candidateItemSet[i]);
			}
		}
		candidateItemSet.clear();
		item_set_size++;
	}
	outfile.close();
}

//Main Function
int main(int argc, char* argv[]) {
	input_file = argv[1];
	output_file = argv[3];
	output_file = "" + output_file + ".txt";
	minSupport = atoi(argv[2]);
	generateFrequentItemSets();
    return 0; 
}