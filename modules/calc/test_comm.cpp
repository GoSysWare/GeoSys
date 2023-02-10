
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <iostream>



#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int>values{1,2,3,4,5,6};
    cout << "values 容器首个元素的地址：" << values.data() << endl;

    auto iter = values.begin();
    for (; iter != values.end();) {
        if(*iter ==  3) {
            iter = values.erase(iter);
        cout << *iter <<endl;

        }
        else{
        cout << *iter <<endl;

         ++iter;
        }

    }
    return 0;
}