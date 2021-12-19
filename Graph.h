//
// Created by MRV on 17.12.2021.
//

#ifndef GLADKIH_3_1_GRAPH_H
#define GLADKIH_3_1_GRAPH_H

#include <vector>
#include "Pair.h"
#include "Node.h"
#include "Support.h"
#include "Tree.h"

class Graph {
protected:
    std::vector<Node*> vertex;
    int n;
public:
    Graph(int **arr, const int &n) : n(n){
        vertex.resize(n);
        for (int i = 0; i < n; i++) {
            vertex[i] = new Node(i);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (arr[i][j] != 0) {
                    vertex[i]->add_edge(vertex[j], arr[i][j]);
                }
            }
        }
    }
    template<int n>
    Graph(int (&arr)[n][n]) : n(n){
        vertex.resize(n);
        for (int i = 0; i < n; i++) {
            vertex[i] = new Node(i);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (arr[i][j] != 0) {
                    vertex[i]->add_edge(vertex[j], arr[i][j]);
                }
            }
        }
    }
    Tree find_MST() {
        bool* was = new bool [n]; //создаём массив, в котором будем отмечать вершины, которые уже принадлежат дереву
        for (int i = 0; i < n; i++) {
            was[i] = false;
        }
        was[0] = true; //начнём с первой, но это не столь важно
        Node* root = new Node(vertex[0]->get_value()); //создаём корневой нод для дерева
        std::vector<Node*> nodes_tree; //храним ноды дерева, чтобы не обходить лишний раз
        nodes_tree.push_back(root);
        //продолжаем цикл пока есть неприсоединённые вершины
        while (nodes_tree.size() < n){
            //ищем наименьшее ребро из тех, которые соединяют какую-то точку из присоединённых с не присоединёнными
            int min_length = INT_MAX;
            //запоминаем присоединяемую вершину
            int new_point = -1;
            //запоминаем нод вершины из присоединённых
            int old_point = -1;
            //проходим все присоединённые точки
            for (int i = 0; i < nodes_tree.size(); i++) {
                //то просматриваем все соседние с ней и смотрим длину ребёр от них и сравниваем с минимумом
                int was_point = nodes_tree[i]->get_value();
                int number_childs_i = vertex[was_point]->get_number_childs();
                for (int j = 0; j < number_childs_i; j++) {
                    //если вторая точка не в дереве, связана с присоединённое и длина ребра меньше минимума
                    if (!was[vertex[was_point]->check_child(j).get_value()] && min_length > vertex[was_point]->get_cost(j)) {
                        //то обновляем минимум
                        min_length = vertex[nodes_tree[i]->get_value()]->get_cost(j);
                        new_point = vertex[nodes_tree[i]->get_value()]->check_child(j).get_value();
                        old_point = i;
                    }
                }
            }
            //если мы смогли что-то присоединить
            if (old_point != -1){
                //добавляем в дерево ребро
                Node* temp = new Node(new_point);
                nodes_tree[old_point]->add_edge(temp, min_length);
                //запоминаем, что вершина присоединена
                nodes_tree.push_back(temp);
                was[new_point] = true;
            }
            else{
                Tree buffer = Tree(root);
                buffer.clear();
            }
        }
        return Tree(root);
    }
    std::vector<int> find_shortest_ways(int index){
        //будем использовать алгоритм дейкстры
        if (0 <= index && index <= n) {
            //создаём вектор, где будем хранить пометки вершин
            std::vector<int> marks;
            //все метки по умолчанию равны бесконечности
            marks.resize(n, INT_MAX);
            //отмечаем, пройдена вершина или нет
            std::vector<bool> was;
            //по умолчанию все не пройдены
            was.resize(n, false);
            //расстояние от нашей вершины до нашей вершины равно 0. Это начало алгоритма
            marks[index] = 0;
            int min = -1;
            int min_value = INT_MAX;
            do {
                //ищем вершину, пометка, которая наименьшая и не пройдена
                min_value = INT_MAX;
                min = -1;
                for (int i = 0; i < n; i++) {
                    //если вершина не была и её пометка меньше чем минимум, то обновляем последний
                    if (!was[i] && min_value > marks[i]) {
                        min = i;
                        min_value = marks[i];
                    }
                }
                //если такая вершина нашлась
                if (min != -1){
                    //отмечаем, что она пройдена
                    was[min] = true;
                    //проходим все соседние с ней на предмет более короткого маршрута, то есть сумма метки вершины, на которой мы находимся и цена ребра меньше, чем метка другой вершины
                    int min_numbers = vertex[min]->get_number_childs();
                    for (int j = 0; j < min_numbers; j++){
                        //получаем номер вершины в графе
                        int index_j = vertex[min]->check_child(j).get_value();
                        //считаем новую стоимость пути
                        int new_cost = vertex[min]->get_cost(j) + marks[min];
                        //если он меньше текущей метки, то обновляем последнюю
                        if (marks[index_j] > new_cost){
                            marks[index_j] = new_cost;
                        }
                    }
                }
            }
            while (min != -1);
            //если все вершины пройдены, то мы получили результирующий вектор
            return marks;
        }

    }
    //Алгоритм Эдмондса — Карпа
    int max_flow_problem(int index_source, int index_runoff){
        if (index_source != index_runoff && 0 <= index_source && index_source < n && 0 <= index_runoff && index_runoff < n){
            std::vector<std::vector<int>> flow;
            //заводим вектор из векторов. В нём будем хранить текущие потоки. Значения максимальных потоков останутся в изначальном графе.
            flow.resize(n);
            for (int i = 0; i < n; i++){
                // для каждой вершины заводим вектор, в котором будет описан текущий поток
                flow[i].resize(vertex[i]->get_number_childs());
            }
            std::vector<int> min_route; //наикратчайший путь
            do {
                std::vector<bool> was; //создаём вектор, в котором будем отмечать, пройдена ли вершина(во время обхода)
                was.resize(n);
                std::vector<Node *> que; //создаём очередь для обхода в ширину. Она будет использоваться для нахождения кратчайшего незаполненного максимально пути из источника в сток
                std::vector<std::vector<int>> que_route; //тут будем запоминать для каждой вершины путь в неё(записываться будет индекс потомка в родительском ноде)
                que.push_back(vertex[index_source]); //начинаем цикл с добавления источника
                que_route.emplace_back(); //путь до него пуст, так как он начало
                bool found = false; //если найдём кратчайший путь, то цикл завершаем
                while (!found && !que.empty()) {
                    min_route.clear();
                    //берём из очереди первую вершину
                    Node *cur = que[0];
                    //отмечаем вершину пройденной
                    was[cur->get_value()] = true;
                    //проходим всех непройденных детей
                    for (int i = 0; !found && i < cur->get_number_childs(); i++) {
                        //если i потомок не пройден и поток по соответствующему ребру не забит полностью
                        if (!was[cur->check_child(i).get_value()] && flow[cur->get_value()][i] < cur->get_cost(i)) {
                            //если это не сток, то добавляем его в конец очереди, его путь - это путь родителя + его номер
                            if (cur->check_child(i).get_value() != index_runoff) {
                                //добавляем в очередь вершин потомка
                                que.push_back(&(cur->get_child(i)));
                                //в очередь с путями добавляем путь до вершины + её номер
                                que_route.push_back(que_route[0]);
                                (que_route.end() - 1)->push_back(i);
                            }
                            else {
                                //если это сток, то это минимальный путь по определению(до него мы добрались первым)
                                min_route = que_route[0];
                                min_route.push_back(i);
                                found = true;
                            }
                        }
                    }
                    //удаляем из очереди обработанную вершину
                    que.erase(que.begin());
                    //и путь к ней тоже
                    que_route.erase(que_route.begin());
                }
                //если путь был найден
                if (!min_route.empty()){
                    //теперь нам надо установить наименьшую разницу между вместимостью на ребре и текущим потоком: именно на эту величину будет увеличен текущий поток по всему пути
                    Node *cur_node = vertex[index_source];
                    int min_value = INT_MAX;
                    for (int i = 0; i < min_route.size(); i++) {
                        //если минимум больше разницы между максимальным потоком и текущим, то обновляем последний
                        if (min_value > cur_node->get_cost(min_route[i]) - flow[cur_node->get_value()][min_route[i]]) {
                            min_value = cur_node->get_cost(min_route[i]);
                        }
                        //сдвигаем текущий указатель
                        cur_node = &(cur_node->get_child(min_route[i]));
                    }
                    //теперь проходим ещё раз и увеличиваем поток
                    cur_node = vertex[index_source];
                    for (int i = 0; i < min_route.size(); i++) {
                        //увеличиваем поток по нужной нам вершине
                        flow[cur_node->get_value()][min_route[i]] += min_value;
                        //сдвигаем текущий указатель
                        cur_node = &(cur_node->get_child(min_route[i]));
                    }
                }
            }
            while (!min_route.empty()); //пока находятся пути
            int sum = 0; //считаем итоговый поток
            //проходим все вершины
            for (int i = 0; i < n; i++){
                //проходим всех потомков
                for (int j = 0; j < vertex[i]->get_number_childs(); j++){
                    //если вершина связана со стоком
                    if (vertex[i]->check_child(j).get_value() == index_runoff){
                        //то поток из неё в него суммируем
                        sum+=flow[i][j];
                    }
                }
            }
            //возвращаем суммарный поток
            return sum;
        }
    }
};


#endif //GLADKIH_3_1_GRAPH_H
