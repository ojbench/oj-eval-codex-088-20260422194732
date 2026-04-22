#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v): val(v), next(nullptr) {}
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long id; 
    unsigned long long n;
    if(!(cin >> id >> n)) return 0;

    if(id == 1){
        if(n==0) return 0;
        // build singly linked queue 1..n
        Node* head = new Node(1);
        Node* tail = head;
        for(unsigned long long i=2;i<=n;i++){
            tail->next = new Node((int)i);
            tail = tail->next;
        }
        // perform n-1 rounds; after each round print new head->val
        // Each round: move first to last, then discard new first
        for(unsigned long long round=1; round<=n-1; ++round){
            // move first to last
            Node* first = head;
            head = head->next; // may become nullptr if n==1, but here n>=1 and we will discard another, so ensure not null
            tail->next = first;
            tail = first;
            tail->next = nullptr;

            // discard new first
            Node* discard = head;
            head = head->next;
            delete discard;

            // print current top
            if(head) cout << head->val << '\n';
            else cout << tail->val << '\n'; // should not happen for round<=n-1
        }

        // clean up remaining nodes to avoid leaks
        // There should be exactly 1 node left (head..tail ring broken)
        Node* cur = head;
        while(cur){
            Node* nx = cur->next;
            delete cur;
            cur = nx;
        }
        // tail already deleted in loop above if distinct
    } else if(id == 2){
        // Predict final remaining card for large n up to 1e15
        // For process: move first to back, then discard new first.
        // Survivor formula: let p be the largest power of two <= n.
        // Answer is 2 * (n - p) + 1. For exact powers of two, this yields 1.
        if(n == 0) {
            cout << 0 << "\n";
        } else {
            unsigned long long p = 1;
            while ((p << 1) && ((p << 1) <= n)) p <<= 1;
            unsigned long long r = n - p;
            unsigned long long ans = r * 2 + 1;
            cout << ans << "\n";
        }
    } else {
        // Unknown subtask id; do nothing or output nothing
    }
    return 0;
}
