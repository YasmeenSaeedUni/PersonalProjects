#include "ComponentList.h"

//constructor
ComponentList::ComponentList() : head(nullptr), tail(nullptr), size(0) {}


//destructor(makes sure all nodes are properly deleted)
ComponentList::~ComponentList() {
    Node* current = head;
    while (current!=nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

//adds a component to the end of the list
bool ComponentList::add(Component* comp) {
    if (!comp){
        return false;
    }
    Node* newNode = new Node(comp);
    if (!head) { //list is empty.
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
    return true;
}


//adds a component at index
bool ComponentList::add(Component* comp, int index) {
    if (!comp || index < 0 || index > size){
        return false;
    }
    //inserting at the end
    if (index == size){
        return add(comp);
    }
    Node* newNode = new Node(comp);
    //inserting at the head
    if (index == 0) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    //inserting at specific index
    } else {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        newNode->prev = current->prev;
        newNode->next = current;
        if (current->prev) {
            current->prev->next = newNode;
        }
        current->prev = newNode;
    }
    size++;
    return true;
}

//removes the component at the given id
Component* ComponentList::remove(const std::string& id) {
    Node* current = head;
    while (current!=nullptr) {
        if (current->comp && current->comp->getId() == id) {
            if (current->prev){
                current->prev->next = current->next;
            }else {
                head = current->next;
            }
            if (current->next){
                current->next->prev = current->prev;
            }else {
                tail = current->prev; 
            }
            Component* removedComp = current->comp;
            delete current;
            size--;
            return removedComp;
        }
        current = current->next;
    }
    return nullptr;
}

//removes the component at the given index
Component* ComponentList::remove(int index) {
    if (index < 0 || index >= size){
        return nullptr;
    }
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    if (current->prev){
        current->prev->next = current->next;
    } else {
        head = current->next; //removes the head
    }
    if (current->next){
        current->next->prev = current->prev;
    } else {
        tail = current->prev; //removes the tail
    }
    Component* removedComp = current->comp;
    delete current;
    size--;
    return removedComp;
}

//Getters
//gets the component with the specified id
Component* ComponentList::get(const std::string& id) const {
    Node* current = head;
    while (current) {
        if (current->comp && current->comp->getId() == id){
            return current->comp;
        }        
        current = current->next;
    }
    return nullptr;
}

//get the component at the specified index
Component* ComponentList::get(int index) const {
    if (index < 0 || index >= size)
        return nullptr;
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->comp;
}

//returns the number of components stored in the list
int ComponentList::getSize() const {
    return size;
}
