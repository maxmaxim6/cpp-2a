#pragma once
#include <iostream>
#include <exception>
using namespace std;


namespace family
{
    class Tree
    {

        public:
        string name;
        Tree* Mother;
        Tree* Father;
        Tree(string rootName);
        Tree(string rootName, Tree* son);
        Tree& addFather(string rName, string fName);
        Tree& addMother(string rName, string mname);
        string relation(string name);
        string find(string relation);
        void remove(string name);
        void display();

        private:
        string relation(Tree* root, string ans, string name);
        string find(Tree* root, string relation);
        void display(Tree* root);
        void remove(Tree** root);
        bool remove(Tree** root, string name);
    };

};

extern string message;
typedef struct myException :public exception
{
    virtual const char* what() const noexcept
    {
        return message.c_str();
    }
}myException;