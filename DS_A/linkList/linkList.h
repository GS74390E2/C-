//
// Created by G.Q on 2019/3/21.
//

#ifndef CLION_CPP_LINKLIST_H
#define CLION_CPP_LINKLIST_H

#include "../LinearList.h"
#include "../MyException.h"
#include <string>
#include <sstream>

namespace LINK {
    struct DATA {
        unsigned int id;
        std::string name;
        DATA *nextNode;

        DATA(unsigned int theId = 0, std::string theName = " ", DATA *theNext = nullptr) :
                id(theId), name(theName), nextNode(theNext) {}

        DATA(const DATA &node) {
            this->id = node.id;
            this->name = node.name;
            this->nextNode = nullptr;
        }

        bool operator==(const DATA &node) {
            return this->id == node.id && this->name == node.name;
        }

        bool operator!=(const DATA &node) {
            return this->id != node.id && this->name != node.name;
        }
    };

    std::ostream &operator<<(std::ostream &out, const LINK::DATA &node) {
        out << "id: " << node.id << ", name: " << node.name << ", nextNode: " << node.nextNode << endl;
        return out;
    }
}

class linkList {
public:

    typedef LINK::DATA linkNode;

    linkList() : head(nullptr), linkSize(0) {}

    linkList(const linkList &link);

    // 1.判断表是否为空
    bool isEmpty() const { return this->linkSize == 0; }

    // 2.返回数组大小
    int size() const { return this->linkSize; };

    // 3.根据index获取元素
    linkNode &get(int theIndex) const;

    // 4.根据元素获取第一次出现的索引
    int indexOf(linkNode &theNode) const;

    // 5.删除索引为index的元素
    bool erase(int theIndex);

    // 6.把元素插入表的index位
    bool insert(int theIndex, linkNode &theNode);

    // 7.追加元素
    void add(linkNode &theNode);

    // 8.显示所有元素
    void output(std::ostream &out) const;

    // 统一工具
    void checkIndex(int theIndex) const;

    // 练习2
    void setSize(int theSize);

    // 析构函数
    ~linkList() {
        while (this->head != nullptr) {
            linkNode *htmp = this->head->nextNode;
            delete this->head;
            this->head = htmp;
        }
    }

private:
    linkNode *head;
    int linkSize;
};

linkList::linkList(const linkList &link) {
    this->linkSize = link.linkSize;

    if (this->linkSize == 0) {
        this->head = nullptr;
        return;
    }

    linkNode *ltmp = link.head;
    this->head = new linkNode(ltmp->id, ltmp->name, ltmp->nextNode);
    ltmp = ltmp->nextNode;
    linkNode *htmp = this->head;
    while (ltmp != nullptr) {
        htmp->nextNode = new linkNode(ltmp->id, ltmp->name, ltmp->nextNode);
        htmp = htmp->nextNode;
        ltmp = ltmp->nextNode;
    }
    htmp->nextNode = nullptr;
}

// 统一工具
void linkList::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex > this->linkSize - 1) {
        std::ostringstream ss;
        ss << "theIndex: " << theIndex << " is Out of Size!!!";
        throw illegalParameterValue(ss.str());
    }
}

linkList::linkNode &linkList::get(int theIndex) const {
    checkIndex(theIndex);

    linkList::linkNode *htmp = this->head;
    for (int i = 0; i != theIndex; ++i)
        htmp = htmp->nextNode;
    return *htmp;
}

int linkList::indexOf(linkList::linkNode &theNode) const {
    linkList::linkNode *htmp = this->head;
    int index = 0;
    while (htmp != nullptr && *htmp != theNode) {
        htmp = htmp->nextNode;
        ++index;
    }
    if (htmp == nullptr)
        return -1;
    else
        return index;
}

bool linkList::erase(int theIndex) {
    checkIndex(theIndex);

    linkList::linkNode *delNode;
    if (theIndex == 0) {
        delNode = this->head;
        this->head = this->head->nextNode;
    } else {
        linkList::linkNode *dtmp = this->head;
        for (int i = 0; i != theIndex - 1; ++i)
            dtmp = dtmp->nextNode;
        delNode = dtmp->nextNode;
        dtmp->nextNode = delNode->nextNode;
    }
    --this->linkSize;
    delete delNode;
    delNode = nullptr;
    return true;
}

bool linkList::insert(int theIndex, linkList::linkNode &theNode) {
    if (theIndex < 0 || theIndex > this->linkSize) {
        std::ostringstream ss;
        ss << "theIndex: " << theIndex << " is Out of Size!!!";
        throw illegalParameterValue(ss.str());
    }

    if (theIndex == 0)
        this->head = new linkList::linkNode(theNode.id, theNode.name, this->head->nextNode);
    else {
        linkList::linkNode *htmp = this->head;
        for (int i = 0; i != theIndex - 1; ++i)
            htmp = htmp->nextNode;
        htmp->nextNode = new linkList::linkNode(theNode.id, theNode.name, htmp->nextNode);
    }
    ++this->linkSize;
    return true;
}

void linkList::add(linkList::linkNode &theNode) {
    if(this->head == nullptr) {
        this->head = new linkList::linkNode(theNode);
        ++this->linkSize;
        return;
    }

    linkList::linkNode *htmp = this->head;
    while (htmp->nextNode != nullptr) {
        htmp = htmp->nextNode;
    }
    htmp->nextNode = new linkList::linkNode(theNode);
    ++this->linkSize;
}

void linkList::output(std::ostream &out) const {
    for (linkList::linkNode *currentNode = this->head;
         currentNode != nullptr;
         currentNode = currentNode->nextNode)
        out << *currentNode << endl;
}

std::ostream &operator<<(std::ostream &out, const linkList &link){
    link.output(out);
    return out;
}

// 练习2
void linkList::setSize(int theSize) {
    if(this->linkSize > theSize){

    }
}

#endif //CLION_CPP_LINKLIST_H
