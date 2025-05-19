#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H


#include <string>
#include "Component.h"


class ComponentList {
private:
    //node structure for the doubly-linked list
    struct Node {
        Component* comp;
        Node* next;
        Node* prev;
        Node(Component* c) : comp(c), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;


public:
    //constructor
    ComponentList();

    //destructor
    ~ComponentList();

    //adds a component pointer to the end of the list
    bool add(Component* comp);

    //adds a component pointer at index
    bool add(Component* comp, int index);

    //removes the component with at the given id
    Component* remove(const std::string& id);

    //removes the component at the given index
    Component* remove(int index);

    //getters
    Component* get(const std::string& id) const;
    Component* get(int index) const;
    int getSize() const;
};
#endif
