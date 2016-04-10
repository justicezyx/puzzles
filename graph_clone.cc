#include <list>
#include <cstdio>
#include <map>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>

struct node {
    node() : uuid_(node_count++), id_(0), neighbor_list_() {}

    node(int id) : uuid_(node_count++), id_(id), neighbor_list_() {}

    std::string idToString() {
        std::ostringstream oss;
        oss << uuid_ << "-";
        oss << id_;
        return oss.str();
    }

    std::string toString() {
        std::string repr;
        repr += idToString();
        repr += ":";

        for( std::list<node*>::iterator i = neighbor_list_.begin();
                i != neighbor_list_.end();
                ++i ) {
            repr += (*i)->idToString();
            repr += ",";
        }

        return repr;
    }

    static int node_count;

    int uuid_;
    int id_;
    std::list<node*> neighbor_list_;
};

int node::node_count = 0;

node* recursive_clone(node* src, std::map<node*, node*>& node_map);

std::list<node*> clone_graph(std::list<node*> original) {
    // call the recursive implementation to do a DFS to clone
    typedef std::list<node*>::const_iterator itor;
    std::list<node*> res;
    
    std::map<node*, node*> node_map;
    for(itor i = original.begin(); i != original.end(); ++i) {
        recursive_clone(*i, node_map);
        res.push_back(node_map[*i]);
    }
    return res;
}

node* recursive_clone(node* src, std::map<node*, node*>& node_map) {
    typedef std::list<node*>::const_iterator itor;
    node* res = NULL;

    if( node_map.find(src) == node_map.end() ) {
        node* copy = new node(src->id_);
        node_map[src] = copy;
        
        for( itor i = src->neighbor_list_.begin();
                  i != src->neighbor_list_.end();
                  ++i ) {
            node* neighbor_copy = recursive_clone(*i, node_map);
            if( neighbor_copy != NULL ) {
                copy->neighbor_list_.push_back(neighbor_copy);
            } else {
                copy->neighbor_list_.push_back(node_map[*i]);
            }
        }
        res = copy;
    }
    return res;
}

int main() {
    std::list<node*> graph;
    node* n0 = new node(0);
    node* n1 = new node(1);
    node* n2 = new node(2);
    node* n3 = new node(3);

    n0->neighbor_list_.push_back(n1);
    n0->neighbor_list_.push_back(n3);
    n1->neighbor_list_.push_back(n2);
    n2->neighbor_list_.push_back(n0);

    graph.push_back(n0);
    graph.push_back(n1);
    graph.push_back(n2);
    graph.push_back(n3);

    std::list<node*> cloned_graph = clone_graph( graph );
    
    for(std::list<node*>::iterator i = graph.begin();
            i != graph.end();
            ++i) {
        std::cout<<(*i)->toString()<<std::endl;
    }

    for(std::list<node*>::iterator i = cloned_graph.begin();
            i != cloned_graph.end();
            ++i) {
        std::cout<<(*i)->toString()<<std::endl;
    }
}
