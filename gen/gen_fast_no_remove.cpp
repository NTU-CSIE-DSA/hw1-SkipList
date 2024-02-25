#include "testlib.h"
#include <climits>
#include <cassert>
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {  // gen_fast_no_remove M k op1 op2 op3 op4 (%)
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
    assert(op1 == 0 && op4 == 0 && op2 + op3 == 100); // no slow get and removal => 0%
    cout << M << '\n';

    unordered_set<int> numbers;
    for(int i = 1; i <= M; i++){
        if(i == M){ // assert the last op is fast get 0
            cout << "2 0\n";
            break;
        }
        int op = rnd.next(1, 100); // in this case, only 2(fast get) and 3(insert)
        if(op <= op2 || i > M - 100) op = 2; // assert that the last 100 op are fast get a random number
        else op = 3;
        int tmp = rnd.next(0, k);
        while(op == 3 && numbers.count(tmp)) tmp = rnd.next(0, k);
        if(op == 3) numbers.insert(tmp);
        cout << op << " " << tmp << "\n";
    }
    return 0;
}
