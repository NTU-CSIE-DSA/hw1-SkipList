#include "testlib.h"
#include <climits>
#include <cassert>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {  // gen M k op1 op2 op3 op4 (%)
    registerGen(argc, argv, 1);
    assert(argc == 7);
    int M = atoi(argv[1]);
    int k = atoi(argv[2]);
    int op1 = atoi(argv[3]);
    int op2 = atoi(argv[4]);
    int op3 = atoi(argv[5]);
    int op4 = atoi(argv[6]);
    assert(1 <= M && M <= 1000000);
    assert(0 <= k && k <= 1000000000);
    assert(op1 == 0 && op2 + op3 + op4 == 100); // no slow get => 0%
    cout << M << '\n';

    set<int> numbers;
    for(int i = 1; i <= M; i++){
        if(i == M){ // assert the last op is fast get 0
            cout << "2 0\n";
            break;
        }
        int op = rnd.next(1, 100); // in this case, only 2(fast get) and 3(insert)
        if(op <= op2 || i > M - 100) op = 2; // assert that the last 100 op are fast get a random number
        else if(op > op2 && op <= op2 + op3) op = 3;
        else op = 4;
        int tmp = rnd.next(0, k);
        while(op == 3 && numbers.count(tmp)) tmp = rnd.next(0, k);
        if(op == 3) numbers.insert(tmp);
        if(op == 4){ // since iterator is too slow, only remove the begin or end of unordered set
            if(numbers.empty()) tmp = 0;
            else{
                tmp = tmp % 2;
                if(tmp) tmp = *numbers.begin();
                else tmp = *numbers.rbegin();
                numbers.erase(tmp);
            }
        } 
        cout << op << " " << tmp << "\n";
    }
    return 0;
}
