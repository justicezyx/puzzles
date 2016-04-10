/**
 * Given a list of jobs, each of which consumes a certain amount of resources.
 * Each job has an interval of running time which specify when it starts and
 * finishes running. Given a list of jobs, find the maximum resources that being
 * used.
 */

#include "common/common.h"

enum type {
    BEGIN,
    END,
};

struct event {
    int idx;
    int time;
    int val;
    type t;
};

struct job {
    int start;
    int duration;
    int val;
    
    event begin_event() const {
        event e;
        e.time = start;
        e.val = val;
        e.t = BEGIN;
        cout<<"event val:"<<val<<endl;
        return e;
    }

    event end_event() const {
        event e;
        e.time = start + duration;
        e.val = val;
        e.t = END;
        return e;
    }
};

bool event_comp(const event& a, const event& b) {
    return a.time > b.time;
}

ostream& operator<<(ostream& os, const event& e) {
    os<<"["<<e.idx<<":"<<e.time<<"]";
}

int max_resource(const vector<job>& jobs) {
    // an event queue holds all the events.
    vector<event> event_queue;
    event_queue.reserve(2 * jobs.size());
    
    for (int i = 0; i < jobs.size(); ++i) {
        event e = jobs[i].begin_event();
        e.idx = i;
        cout<<"event val:"<<e.val<<endl;
        event_queue.push_back(e);
    }
    make_heap(event_queue.begin(), event_queue.end(), event_comp);
    
    int max = 0;
    int val = 0;
    while (!event_queue.empty()) {
        print(event_queue.begin(), event_queue.end());

        pop_heap(event_queue.begin(), event_queue.end(), event_comp);
        event e = event_queue.back();
        event_queue.pop_back();
        if (e.t == BEGIN) {
            cout<<"begin event at idx:"<<e.val<<endl;
            val += e.val;
            int idx = e.idx;
            event_queue.push_back(jobs[idx].end_event());
            push_heap(event_queue.begin(), event_queue.end(), event_comp);
        } else {
            val -= e.val;
        }
        max = std::max(val, max);
    }
    return max;
}

void test() {
    vector<job> jobs;
    job a; a.start = 0; a.duration = 10; a.val = 1;
    job b; b.start = 1; b.duration = 9; b.val = 1;
    job c; c.start = 2; c.duration = 8; c.val = 1;
    jobs.push_back(a);
    jobs.push_back(b);
    jobs.push_back(c);
    
    cout<<max_resource(jobs)<<endl;
}

int main() {
    test();
}
