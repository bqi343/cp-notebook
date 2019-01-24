/**
* Description: maintains minimum of deque while adding 
    elements to back or deleting elements from front
* Source: own
* Verification: Jan 18 Lifeguards
*/

template<class T> struct MinDeque { 
    int lo = 0, hi = -1;
    deque<pair<T,int>> d;
    
    void ins(T x) { // add to back
        while (sz(d) && d.back().f >= x) d.pop_back();
        d.pb({x,++hi});
    }
    
    void del() { // delete from front
        if (d.front().s == lo++) d.pop_front();
    }
    
    T get() { 
        return sz(d) ? d.front().f : MOD; // change based on T
    }
};
