#include<fstream>
#include "Header/Testing.h"

int main(){
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    ///Random generator that generates uniformly n numbers with a specified max value
    ///In the input.txt we specify how many tests for example 10 and we insert in the next lines n and maxValue : 1000 1000, 1000 1000000 etc
    int nrVal;
    in >> nrVal;

    for(int i = 0 ; i < nrVal; i ++) {
        int n, maxValue;
        in >> n >> maxValue;
        runRandomTest<int>(out, n, maxValue);
        std::cout << "Done. N = " << n << " and with max value " << maxValue <<'\n';
    }
    ///Here we have custom made data sets
    ///data_set_1.txt All elements sorted ascending.
    ///data_set_2.txt All elements sorted descending.
    ///data_set_3.txt 70% random, 30% ordered at the end.
    ///data_set_4.txt 70% random, 30% ordered at the beginning.
    ///data_set_5.txt 70% random, 30% ordered in the middle.
    ///data_set_6.txt Highly skewed.
    ///data_set_7.txt Lots of duplicates.
    ///This tester is designed to have on the first line of the .txt the number of numbers and than the numbers (take a look in the give files for examples)
    runTestsFromFiles<float>(out);
}