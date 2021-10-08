Team Members:-
2018CS10349- Kartikeya Gupta
2018CS10388- Sharique Shamim
2018CS10387- Seshank 
######################################################################################
Homework1

Part(a) :- Implementation of Apriori & FPTree Algorithm.

Part(b) :- Performance comparison of Apriori & FPTree

####################################INSTRUCTIONS#######################################

To compile: sh compile.sh
(a) To run Apriori algorithm: sh 2018CS10349.sh data.dat X -apriori output_apriori 
(b) To run FPTree algorithm: sh 2018CS10349.sh data.dat X -fptree output_fptree 
(c) To generate plot comparing runtimes of Apriori and FPTree Algorithm: sh 2018CS10349.sh data.dat -plot
###################################IMPLEMENTATION AND EXPLANATION######################################

Implementation of Apriori Algorithm:(apriori.cpp) (a) vector<vector> generate_F1() : In this function, the whole database is scanned and the number of times each item occurs is updated in a map. From this we can generate the number of itemsets of size 1 are frequent.

(b) vector<vector> generateCandidateItemSet(vector<vector> prevF) : In this function we generate the number of itemsets of size n+1 from the the set of frequent itemsets of size n. Since each of the itemsets are sorted in lexicographical order, for a new candidate to be generated the first n-1 items of the itemsets are supposed to be the same and the last element differs. So after this condition is checked, the new candidate is generated and added to the new candidate set.

(c) void generateFrequentItemSets() : In this function the support of each element in the candidate set of size n+1 is checked, and if it is greater than the threshold, it is added to the frequent itemset of size n+1.

(d) bool comp(int a, int b) : Compares 2 integers in the ASCII order.

(e) void printFrequentItemSet(vector candidateItem) : This prints the Frequent Itemsets into the output file.

Implementation of FPTree Algorithm:(fptree.cpp) (a) bool make_freq_item(FILE* input_file, unordered_map<int, int> &freqitem): This function creates a map which maps an item and its frequency. It is created by a database scan.

(b) bool make_transc(FILE* input_file, vector &transc): This function creates a vector of transactions. It is also created by a database scan.

(c) bool comp(int a,int b): Compares 2 integers in the ASCII order.

(d) void print_ans(vector ans): Sorts the answer in the ASCII order and prints it into the output file.

(e) void fpgrowth(vector<FPnode*> v,vector ans): In this function, the support of each element in the vector is checked. If it is greater than the minimum support, then it is added to the answer file. Now, a header table and a conditional tree are generated and for each element in the table with support greater than min_support, fpgrowth is called. It is called in the reverse order of support.

Plotting the graph comparing the times of FPTree and Apriori:(plot.cpp) In this file, FPTree and Apriori algorithms are called for support thresholds of 1,5,10,25,50,90 and the runtime of both the algorithms is plotted using gnuplot for these thresholds.

#################################COMPARISON BETWEEN APRIORI AND FPTREE#####################################

FPTree Execution Time(seconds) for different values of X over webdocs.dat X = 90 : 17.51 X = 50 : 17.55 X = 25 : 31.5 X = 10 : 720

Apriori Execution Time(seconds) for different values of X over webdocs.dat X = 90 : 139.61 X = 50 : 251.95 X = 25 : 1020

FPtree works better than Apriori due to following reasons:-
- In apriori algorithm it joins the candidate set then prunes while in FPTree constructs conditional tree and conditional header table for itemset whose support is greater than minimum support

- Apriori scans database multiple times for generating candidate sets while FPTree scans only two times

- As there s no candidate generation and hence it requires less memory in FPTree so it requires less memory compared to Apriori

- In FPTree it only searches in possible sapce unlike Apriori which generates a large number of candidates and checks for all of them. 

With increase in minimum support, the running time of both algorithm decrease. However, decrease in Apriori is greater than FPTree

