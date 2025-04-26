#include "header.h"
#include "randomGenerator.cpp"
#include "sort.h"

using namespace std;

void showMemUsage() {  
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"Memory Usage Information:" << endl;
    cout<<"Working Set Size: "<<memInfo.WorkingSetSize / 1024 << " KB" << endl;
    cout<<"Peak Working Set Size: "<<memInfo.PeakWorkingSetSize / 1024 << " KB" << endl;
    cout<<"Pagefile Usage: "<<memInfo.PagefileUsage / 1024 << " KB" << endl;
    cout<<"----------------------------------------------------------"<<endl;
}

int main(){
    cout<<sizeof(uint16_t)<<endl;
    uint16_t n=1000,repeat=1000;
    vector <uint16_t> arr(n);
    genWorstCase(arr);
    cout<<"default mem"<<endl;
    showMemUsage();
    cout<<"quick sort (worst case) test=============================="<<endl;
    auto start = std::chrono::high_resolution_clock::now();
    for(uint16_t i=0;i<repeat;i++){
        if(i==0){
            cout<<"quick sort (worst case) default using"<<endl;
            showMemUsage();
        }
        vector <uint16_t> t=arr;
        quickSort(t, 0, arr.size() - 1);
        cout<<sizeof(t)<<endl;
        if(i==0){
            cout<<"quick sort (worst case) first using"<<endl;
            showMemUsage();
        }
    }
    showMemUsage();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout<<"quick sort (worst case) avg using:"<<duration.count()/repeat<<"ms"<<endl;
    cout<<"=========================================================="<<endl;

    cout<<"end mem"<<endl;
    showMemUsage();
    return 0;
}