//
// Created by MRV on 18.12.2021.
//

#ifndef GLADKIH_3_1_TREE_H
#define GLADKIH_3_1_TREE_H
#include "Node.h"
#include <vector>
class Tree{
protected:
    Node* root;
    //рекурсивная функция удаления нода и его потомков
    static void delete_node(Node* node){
        if (node){
            //если есть потомки, то их удаляем
            if (node->get_number_childs() > 0){
                for (int i = 0; i < node->get_number_childs(); i++) delete_node(&(node->get_child(i)));
            }
            delete node;
        }
    }
public:
    Tree(Node* root) : root(root){}
    Node& get_root(){
        return *root;
    }
    void clear(){
        //запускаем удаление с первого нода
        delete_node(root);
        root = nullptr;
    }
    void left_depth(std::vector<int> & answer, Node* cur_node = nullptr){
        //левосторонний обход в глубину
        if (cur_node == nullptr){
            cur_node = root;
        }
        //заносим значение нода в результирующий вектор
        answer.push_back(cur_node->get_value());
        //запускаем слева направа обход потомков
        for (int i = 0; i < cur_node->get_number_childs(); i++){
            left_depth(answer, &(cur_node->get_child(i)));
        }
    }
    double avg_inc_left_breadth(){
        //создаём очередь для обхода
        std::vector<Node*> que;
        //добавляем в очередь корневой нод
        que.push_back(root);
        //считаем количество нодов
        int count = 0;
        //считаем суммарное количество инцидентных вершин
        double sum = 0;
        //если очередь не пуста
        while (!que.empty()){
            //обходим первый нод в ней
            Node* cur_node = que[0];
            //увеличиваем количество обойдённых вершин
            count++;
            //увеличиваем количество рёбер
            sum+=cur_node->get_number_childs();
            //добавляем в очередь всех потомков
            for (int i = 0; i < cur_node->get_number_childs(); i++) que.push_back(&(cur_node->get_child(i)));
            //удаляем из очереди первый нод
            que.erase(que.begin());
        }
        //возвращаем среднее арифметическое
        return sum/count;
    }
    ~Tree(){
        clear();
    }
};


#endif //GLADKIH_3_1_TREE_H
