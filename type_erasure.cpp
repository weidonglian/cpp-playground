//
// Created by lian on 10/16/17.
//
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class A {
public:
    A(int id_) : m_id(id_) {
        cout << "Ctor:A with " << id_ << endl;
    }

    ~A() {
        cout << "Dtor:A with " << m_id << endl;
    }

private:
    int m_id;
};

class B {
public:
    B(int id_) : m_id(id_) {
        cout << "Ctor:B with " << id_ << endl;
    }

    ~B() {
        cout << "Dtor:B with " << m_id << endl;
    }

private:
    int m_id;
};

int main() {
    // shared_ptr void trick is a simple and easy solution. You should consider std::variant and std::any first. 
    vector<shared_ptr<void>> sps;
    sps.push_back(make_shared<A>(1));
    sps.push_back(make_shared<A>(2));
    sps.push_back(make_shared<A>(3));
    sps.push_back(make_shared<B>(1));
    sps.push_back(make_shared<B>(2));
    sps.push_back(make_shared<B>(3));
    sps.push_back(make_shared<A>(4));
    return 0;
}