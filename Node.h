//
// Created by MRV on 18.12.2021.
//

#ifndef GLADKIH_3_1_NODE_H
#define GLADKIH_3_1_NODE_H
class Node{
    int value;
    std::vector<Node*> childs;
    std::vector<int> cost;
public:
    int get_value() const{
        return value;
    }
    void add_edge(Node* vertex, int cost){
        childs.push_back(vertex);
        this->cost.push_back(cost);
    }
    int get_number_childs() const{
        return childs.size();
    }
    const Node& check_child(int i) const{
        return *childs[i];
    }
    Node& get_child(int i) const {
        return *childs[i];
    }
    int get_cost(int i) const{
        return cost[i];
    }
    Node(int value) : value(value){}
};
#endif //GLADKIH_3_1_NODE_H
