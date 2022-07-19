#include <iostream>
#include "PandasDataFrame.h"

double szTest[] = {1000, 1100, 1200, 1300, 1400, 1500,1600, 1700, 1800, 1900, 2000};
using namespace std;
int main() {


    double test[] = {1502, 1501, 1503, 1501, 1502, 1502, 1503, 1503, 1503, 1503, 1503, 1504, 1504, 1504, 1504, 1504, 1504, 1503, 1504, 1504, 1503, 1503, 1502, 1501, 1499, 1501, 1498, 1500, 1500, 1498};
    PandasDataFrame pands = PandasDataFrame();
    double i_emw;
    for(int i = 1;i<31;i++)
    {
        i_emw = pands.ewm_mean(test,i,10,1);
        printf("%d ,%lf, %lf\n",i-1,test[i-1],i_emw);
    }

    return 0;
//    PandasDataFrame* obj = new PandasDataFrame();
//    double param_1 = obj->ewm_mean(szTest, 5, 4, 1);
//    cout<<param_1<<endl;
//    auto cc = obj->ewm_mean(szTest, 6, 4, 1, param_1);
//    cout<<cc<<endl;
//
//    cc = obj->rolling_max(szTest, 6, 4, 1);
//    cout<<cc<<endl;
//
//    cc = obj->rolling_min(szTest, 5, 4, 1);
//    cout<<cc<<endl;
//
//    cc = obj->rolling_mean(szTest, 6, 4, 1);
//    cout<<cc<<endl;
//
//    cc = obj->rolling_std(szTest, 7, 4, 1);
//    cout<<cc<<endl;
//
//    double * szRet = obj->sz_rolling_std(szTest, 7, 4, 1);
//
//
//    double * szRet1 = obj->sz_rolling_min(szTest, 6, 4, 1);
//    szRet1 = obj->sz_rolling_mean(szTest, 6, 4, 1);
//
//    double * szRet2 = obj->sz_rolling_max(szTest, 6, 4, 1);
//    szRet2 = obj->sz_rolling_mean(szTest, 6, 4, 1);
    return 0;
}