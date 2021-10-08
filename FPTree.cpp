#include <bits/stdc++.h>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <iterator> 
#include <map> 

using namespace std;

class FPnode
{
public:
	int item;
	int freq;
	unordered_map<int,FPnode*> childs;
	FPnode* parent;
	FPnode(int items,int f, FPnode* p){
		item = items;
		freq = f;
		parent = p;
	}
	FPnode(){
		//NULL
		item = 0;
		freq = -1;
	}
};


struct sort_by_freq{
	bool operator()(const pair<int,int> &p1,const pair<int,int> &p2)const{
		if(p1.second != p2.second){
			return p1.second > p2.second;
		}
		return p1.first > p2.first;
	}
};
unordered_map<int, int> freq_item;
int T;
float min_sup;
FPnode* root = new FPnode ;
unordered_map<int,vector<FPnode*>> headerTable; 
vector<int> answer;

ofstream outfile;
string output_file;

bool comp(int a,int b){
	return to_string(a)<to_string(b);
}

void print_ans(vector<int> ans){
	sort(ans.begin(),ans.end(),comp);
	for(int i=0;i<ans.size();i++){
		outfile<<ans[i]<<" ";
	}
	outfile<<""<<endl;
}


void fpgrowth(vector<FPnode*> v,vector<int> ans){
	
	int supp=0;
	for (int i = 0; i < v.size(); i++)
	{
		supp = supp + v[i]->freq;
	}

		if(supp>=min_sup){

			ans.emplace_back(v[0]->item);
			print_ans(ans);
			unordered_map<int,int> new_freq_item;

			for (int i = 0; i < v.size(); i++)
			{
				FPnode* par_of_curr = v[i]->parent;
				while(par_of_curr->item !=0){
					new_freq_item[par_of_curr->item]+=v[i]->freq;
					par_of_curr=par_of_curr->parent;
				}
			}
			
			unordered_map<int, int>::iterator it; 
		    for (it = new_freq_item.begin(); it!=new_freq_item.end();)
		    {
		    	int item_sup = it->second;
		    	if(item_sup<min_sup){
		    		new_freq_item.erase(it++);
		    	}else{
		    		++it;
		    	}
		    }
			set<pair<int,int>,sort_by_freq> set_in_freq(new_freq_item.begin(),new_freq_item.end());

			FPnode* cond_tree=new FPnode;
			unordered_map<int,vector<FPnode*>> cond_headerTable;
			for (int i = 0; i < v.size(); i++)
			{

				unordered_map<int,int> curr_transc;
				FPnode* curr_nodes = v[i]->parent;
				while(curr_nodes->item !=0){
					if(new_freq_item[curr_nodes->item]>=min_sup){
						curr_transc[curr_nodes->item]=v[i]->freq;
					}
					curr_nodes = curr_nodes->parent;
				}
				
				FPnode* curr_node = cond_tree;
			    for(auto &pair : set_in_freq){ 
			        int citem = pair.first;
			        if(curr_transc.find(citem)!=curr_transc.end()){

			        	auto &childss = curr_node->childs;

			        	FPnode *newNode;
			        	auto cit = childss.find(citem);
			        	if(cit==childss.end()){
			        		newNode = new FPnode(citem,curr_transc[citem],curr_node);
			        		childss[citem] = newNode;
			        		cond_headerTable[citem].emplace_back(newNode);
			        		
			       		}else{
				   			newNode = cit->second;
			       			newNode->freq +=curr_transc[citem];
			       		}

			       		curr_node = newNode;
			       	}
			        	
			    }	

			}
			set<pair<int,int>>::reverse_iterator revIt = set_in_freq.rbegin();
			while (revIt != set_in_freq.rend())
			{
			    fpgrowth(cond_headerTable[(*revIt).first],ans);
			    revIt++;
			}
		}

}


bool make_freq_item(FILE* input_file, unordered_map<int, int> &freqitem) {
    int n = 0;
    bool space = false;
    register int last_c;
    register int c = fgetc_unlocked(input_file);
    if (c == EOF) {
        return false;
    }else{
    	while (c!='\n' && c!=EOF) {
	    	if (c > 47 && c < 58) {
	            n = n*10 + c - 48;
	            space = false;
	        }else if (!space) {
	            freqitem[n]++;
		        n = 0;
		        space = true;
	        }

	        last_c = c;
	        c = fgetc_unlocked(input_file);
		 }

	    if(last_c!=' ')
	       freqitem[n]++;
    }
	
	return true;
}


bool make_transc(FILE* input_file, vector<int> &transc) {
	int n = 0;
    bool space = false;
    register int last_c;
    register int c = fgetc_unlocked(input_file);
    if (c == EOF) {
        return false;
    }else{
    	while (c!='\n' && c!=EOF) {
	    	if (c > 47 && c < 58) {
	            n = n*10 + c - 48;
	            space = false;
	        }else if (!space) {
	            transc.emplace_back(n);
		        n = 0;
		        space = true;
	        }

	        last_c = c;
	        c = fgetc_unlocked(input_file);
		 }

	    if(last_c!=' ')
	       transc.emplace_back(n);
    }
	
	return true;
}



int main(int argc, char const *argv[])
{
	T = 0;
	string input_file = argv[1];
	output_file = argv[3];
	output_file = "" + output_file + ".txt";
	ifstream infile;
	min_sup = atof(argv[2]);
	string sts;
    infile.open(input_file);
	if(!infile) {
		cout << "File doesn't exist" << endl;
		exit(1);
	}
	infile.close();

	// clock_t start, end, end2, end3;
	// start = clock();

	
	FILE* inputStream = fopen(input_file.c_str(), "r");
    while (1){
    	if(!(make_freq_item(inputStream, freq_item)))
    		break;
        T++;
    }

    fclose(inputStream);

    unordered_map<int, int>::iterator itx; 
	min_sup = (T*min_sup)/100.0;
    unordered_map<int, int>::iterator it; 
    for (it = freq_item.begin(); it!=freq_item.end();)
    {
    	int item_sup = it->second;
    	if(item_sup<min_sup){
    		freq_item.erase(it++);
    	}else{
    		++it;
    	}
    }
    set<pair<int,int>,sort_by_freq> set_in_freq(freq_item.begin(),freq_item.end());
	FILE* inputStream2 = fopen(input_file.c_str(), "r");
    vector<int> curr_transc;
    while (true) {
    	if(!(make_transc(inputStream2, curr_transc)))
    		break;

    	FPnode* curr_node = root;
		for(auto &pair : set_in_freq){ 
	        int citem = pair.first;
	        if(find (curr_transc.begin(), curr_transc.end(), citem)!=curr_transc.end()){
	        	auto &childss = curr_node->childs;
	        	FPnode *newNode;
	        	auto cit = childss.find(citem);
	        	if(cit==childss.end()){
	        		newNode = new FPnode(citem,1,curr_node);
	        		childss[citem] = newNode;
	        		headerTable[citem].emplace_back(newNode);
	       		}else{
		   			newNode = cit->second;
	       			newNode->freq +=1;
	       		}
	       		curr_node = newNode;
	       	}
	        	
	    }
	    curr_transc.clear();
	}

	fclose(inputStream2);

	set<pair<int,int>>::reverse_iterator revIt = set_in_freq.rbegin();

	outfile.open(output_file);

	while (revIt != set_in_freq.rend())
	{
	    vector<int> ans;
	    fpgrowth(headerTable[(*revIt).first],ans);
	    revIt++;
	}
	// end2 = clock();
	// double time_taken2 = double(end2 - start)/double(CLOCKS_PER_SEC);
	// cout <<"Time Taken = "<<time_taken2<<setprecision(5)<<endl;

	return 0;
}