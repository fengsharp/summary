#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

/*
1. 传参数，参与运算的参数如果外部会一直改变，则传值拷贝进去
2. 传参数，线程内部变化，而外部在线程执行完毕前不变化的，传引用进去
*/
int main()
{
    std::vector<int> arr;
    arr.reserve(100);
    for (int i = 0; i < 100; ++i)
    {
        arr.push_back(i + 1);
    }

    // int result = 0;
    // result = std::accumulate(arr.begin(), arr.end(), 0);
    // std::cout << result <<std::endl;

    constexpr int threadNum = 5;
    std::vector<std::thread> arrThreads(threadNum);
    std::vector<int> tmp(threadNum);

    std::vector<int>::iterator first = arr.begin();
    std::vector<int>::iterator end = arr.begin();
    int step = arr.size() / threadNum;
    for (int i = 0; i < threadNum; ++i)
    {
        first = end;
        std::advance(end, step);
        arrThreads[i] = std::thread([i, &tmp, &arr, first, end] () {
            tmp[i] = std::accumulate(first, end, 0);
            std::cout << i << " -> " << tmp[i] << std::endl;
        });
    }

    std::for_each(arrThreads.begin(), arrThreads.end(), std::mem_fn(&std::thread::join));
    int result = 0;
    result = std::accumulate(tmp.begin(), tmp.end(), 0);
    std::cout << result << std::endl;

    return 0;
}