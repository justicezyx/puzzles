#include "common/common.h"
using namespace std;

struct endpoint {
    typedef pair<double,int> key_t;

    int building_id;
    double pos;
    double height;
    bool is_begin;
    pair<double,int> get_key() const {
        return make_pair(height, building_id);
    }
};

struct building {
    int id;
    double begin;
    double width;
    double height;
    
    endpoint get_left_end() const {
        endpoint res;
        res.building_id = id;
        res.pos = begin;
        res.height = height;
        res.is_begin = true;
        return res;
    }

    endpoint get_right_end() const {
        endpoint res;
        res.building_id = id;
        res.pos = begin + width;
        res.height = height;
        res.is_begin = false;
        return res;
    }
};

vector<endpoint> get_endpoints(const vector<building>& buildings) {
    vector<endpoint> res;
    if (buildings.empty()) {
        return res;
    }
    
    res.reserve(buildings.size() * 2);
    for (int i = 0; i < buildings.size(); ++i) {
        endpoint left = buildings[i].get_left_end();
        left.building_id = i;
        res.push_back(left);

        endpoint right = buildings[i].get_right_end();
        right.building_id = i;
        res.push_back(right);
    }
    return res;
}

typedef pair<double, double> point_t;
ostream& operator<<(ostream& os, const point_t& p) {
    os<<p.first<<" "<<p.second<<endl;
}
    
struct endpoint_less {
    bool operator() (const endpoint& l, const endpoint& r) const {
        if (l.pos < r.pos) {
            return true;
        } else if (!(r.pos < l.pos) && l.building_id < l.building_id) {
            return true;
        }
        return false;
    }
};

vector<point_t> get_border(const vector<building>& buildings) {
    vector<endpoint> endpoints = get_endpoints(buildings);
    sort(endpoints.begin(), endpoints.end(), endpoint_less());
    cout<<"endpoints:";
    for (int i = 0; i < endpoints.size(); ++i) {
        cout<<" "<<endpoints[i].pos;
    }
    cout<<endl;
    
    map<endpoint::key_t, int> helper;
    vector<point_t> res;

    double height = 0.0;
    for (int i = 0; i < endpoints.size(); ++i) {
        endpoint& cur = endpoints[i];
        if (cur.is_begin) {
            // implicitly insert currentl endpoint.
            helper[cur.get_key()];
            res.push_back(point_t(cur.pos, height));
            height = helper.rbegin()->first.first;
            res.push_back(point_t(cur.pos, height));
        } else {
            res.push_back(point_t(cur.pos, height));
            helper.erase(cur.get_key());
            height = helper.empty() ? 0 : helper.rbegin()->first.first;
            res.push_back(point_t(cur.pos, height));
        }
    }
    return res;
}

int main() {
    building b0;
    b0.begin = 0.1;
    b0.width = 1.1;
    b0.height = 2.1;
    
    building b1;
    b1.begin = 0.4;
    b1.width = 1.1;
    b1.height = 2.1;

    vector<building> buildings;
    buildings.push_back(b0);
    buildings.push_back(b1);

    vector<point_t> res = get_border(buildings);
    cout<<res.size()<<endl;
    for (int i = 0; i < res.size(); ++i) {
        cout<<res[i];
    }
    // print(res.begin(), res.end());
}
