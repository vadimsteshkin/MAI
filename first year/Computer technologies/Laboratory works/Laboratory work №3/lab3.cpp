#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


int main()
{
    int n=0;
    string line;
    vector <int> a;
    vector <int> vec;
    ifstream in("hello.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            a.push_back(stoi( line ));
            n++;
        }
    }
    in.close();     
    for (int i=0; i<vec.size();i++){
        cout<<vec[i]<<endl;
    }  
    return 0;
}