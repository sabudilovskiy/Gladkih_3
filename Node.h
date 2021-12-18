//
// Created by MRV on 18.12.2021.
//

#ifndef GLADKIH_3_1_NODE_H
#define GLADKIH_3_1_NODE_H
class Node{
    int value;
    //потомки нода
    std::vector<Node*> childs;
    //цена связи
    std::vector<int> cost;
public:
    int get_value() const{
        return value;
    }
    //добавить связь с другим нодом
    void add_edge(Node* vertex, int cost){
        childs.push_back(vertex);
        this->cost.push_back(cost);
    }
    int get_number_childs() const{
        return childs.size();
    }
    //посмотреть потомка без права на изменение
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
