#include <iostream>
#include <string>
#include <vector>
#include <chrono> 
using namespace std;
using namespace std::chrono;
void PlotGraph(const char gg[]) {
    FILE * pipe = popen ("gnuplot -persistent", "w");
    fprintf(pipe,"set style data histograms\n");
    fprintf(pipe,"set style fill solid\n");

    fprintf(pipe,"plot 'plot.txt' using 2:xtic(1) title 'FPTree' with lines lt rgb '#0000FF', '' using 3 title 'Apriori' with lines lt rgb '#FF0000'\n");
    fprintf(pipe,"set term png\n");
    fprintf(pipe,"set output '%s'\n",gg);
    fprintf(pipe,"replot\n");
}

int main(int argc, char const *argv[]){
    int thresholds[6];
    thresholds[0]=1;
    thresholds[1]=5;
    thresholds[2]=10;
    thresholds[3]=25;
    thresholds[4]=50;
    thresholds[5]=90;
    FILE * temp = fopen("plot.txt", "w");
    fprintf(temp,"Threshold FPTree Apriori \n");
    for(int i=0;i<6;i++){
        string ar=argv[1];
        string a="./FPTree " + ar + " " + to_string(thresholds[i]) + " plot_fptree";
        string b="./Apriori " + ar + " " + to_string(thresholds[i]) + " plot_apriori";
        auto start = high_resolution_clock::now(); 
        int k2 = system(a.c_str());
        auto stop = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop - start); 
        start = high_resolution_clock::now(); 
        int k = system(b.c_str());
        stop = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop - start); 
        fprintf(temp,"%d %f %f\n",thresholds[i],duration1.count()/1000000.0,duration2.count()/1000000.0);
    }
    PlotGraph("Plot.png");
    return 0;
}