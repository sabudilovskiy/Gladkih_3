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
        bool* was = new bool [n]; //������ ������, � ������� ����� �������� �������, ������� ��� ����������� ������
        for (int i = 0; i < n; i++) {
            was[i] = false;
        }
        was[0] = true; //����� � ������, �� ��� �� ����� �����
        Node* root = new Node(vertex[0]->get_value()); //������ �������� ��� ��� ������
        std::vector<Node*> nodes_tree; //������ ���� ������, ����� �� �������� ������ ���
        nodes_tree.push_back(root);
        //���������� ���� ���� ���� ��������������� �������
        while (nodes_tree.size() < n){
            //���� ���������� ����� �� ���, ������� ��������� �����-�� ����� �� ������������� � �� ��������������
            int min_length = INT_MAX;
            //���������� �������������� �������
            int new_point = -1;
            //���������� ��� ������� �� �������������
            int old_point = -1;
            //�������� ��� ������������� �����
            for (int i = 0; i < nodes_tree.size(); i++) {
                //�� ������������� ��� �������� � ��� � ������� ����� ���� �� ��� � ���������� � ���������
                int was_point = nodes_tree[i]->get_value();
                int number_childs_i = vertex[was_point]->get_number_childs();
                for (int j = 0; j < number_childs_i; j++) {
                    //���� ������ ����� �� � ������, ������� � ������������� � ����� ����� ������ ��������
                    if (!was[vertex[was_point]->check_child(j).get_value()] && min_length > vertex[was_point]->get_cost(j)) {
                        //�� ��������� �������
                        min_length = vertex[nodes_tree[i]->get_value()]->get_cost(j);
                        new_point = vertex[nodes_tree[i]->get_value()]->check_child(j).get_value();
                        old_point = i;
                    }
                }
            }
            //���� �� ������ ���-�� ������������
            if (old_point != -1){
                //��������� � ������ �����
                Node* temp = new Node(new_point);
                nodes_tree[old_point]->add_edge(temp, min_length);
                //����������, ��� ������� ������������
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
        //����� ������������ �������� ��������
        if (0 <= index && index <= n) {
            //������ ������, ��� ����� ������� ������� ������
            std::vector<int> marks;
            //��� ����� �� ��������� ����� �������������
            marks.resize(n, INT_MAX);
            //��������, �������� ������� ��� ���
            std::vector<bool> was;
            //�� ��������� ��� �� ��������
            was.resize(n, false);
            //���������� �� ����� ������� �� ����� ������� ����� 0. ��� ������ ���������
            marks[index] = 0;
            int min = -1;
            int min_value = INT_MAX;
            do {
                //���� �������, �������, ������� ���������� � �� ��������
                min_value = INT_MAX;
                min = -1;
                for (int i = 0; i < n; i++) {
                    //���� ������� �� ���� � � ������� ������ ��� �������, �� ��������� ���������
                    if (!was[i] && min_value > marks[i]) {
                        min = i;
                        min_value = marks[i];
                    }
                }
                //���� ����� ������� �������
                if (min != -1){
                    //��������, ��� ��� ��������
                    was[min] = true;
                    //�������� ��� �������� � ��� �� ������� ����� ��������� ��������, �� ���� ����� ����� �������, �� ������� �� ��������� � ���� ����� ������, ��� ����� ������ �������
                    int min_numbers = vertex[min]->get_number_childs();
                    for (int j = 0; j < min_numbers; j++){
                        //�������� ����� ������� � �����
                        int index_j = vertex[min]->check_child(j).get_value();
                        //������� ����� ��������� ����
                        int new_cost = vertex[min]->get_cost(j) + marks[min];
                        //���� �� ������ ������� �����, �� ��������� ���������
                        if (marks[index_j] > new_cost){
                            marks[index_j] = new_cost;
                        }
                    }
                }
            }
            while (min != -1);
            //���� ��� ������� ��������, �� �� �������� �������������� ������
            return marks;
        }

    }
};


#endif //GLADKIH_3_1_GRAPH_H
