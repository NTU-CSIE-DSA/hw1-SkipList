#include "testlib.h"
#include <assert.h>
#include <unordered_set>
using namespace std;

int main() {
    registerValidation();
    int M = inf.readInt(1, 100000);
    inf.readEoln();
    unordered_set<long long> numbers;
    for(int i = 1; i <= M; i++){
        int op = inf.readInt(2, 4);
        inf.readSpace();
        long long k = inf.readLong((long long)0, 1000000000000000000);
        if(op == 3){
            ensure(!numbers.count(k));
            numbers.insert(k);
        }
        if(op == 4) numbers.erase(k);
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
