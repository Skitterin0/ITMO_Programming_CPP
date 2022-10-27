#ifndef LAB5_LINKEDLIST_H
#define LAB5_LINKEDLIST_H

template<class T>
class linkedlist {
public: //values
    struct node {
        T data;
        node* next;
    };

    node* head_;

public: //methods
    linkedlist() = default;

    void insert(node* prevNode, node* newNode) {
        if (prevNode == nullptr) {
            if (head_ != nullptr) {
                newNode->next = head_;
            }
            else {
                newNode->next = nullptr;
            }
            head_ = newNode;
        }
        else {
            if (prevNode->next == nullptr) {
                prevNode->next = newNode;
                newNode->next = nullptr;
            }
            else {
                newNode->next = prevNode->next;
                prevNode->next = newNode;
            }
        }
    }

    void remove(node* prevNode, node* remNode) {
        if (prevNode == nullptr) {
            if (remNode->next == nullptr) {
                head_ = nullptr;
            }
            else {
                head_ = remNode->next;
            }
        }
        else {
            prevNode->next = remNode->next;
        }
    }
};

#endif
