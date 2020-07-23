#include "FamilyTree.hpp"
using namespace family;
string message;
Tree* findName(Tree*, string);
Tree::Tree(string rootName)   
{
    this->name = rootName;
    this->Father = NULL;
    this->Mother = NULL;
}
Tree::Tree(string rootName, Tree* son)
{
    this->name = rootName;
    this->Father = NULL;
    this->Mother = NULL;
}
Tree* findName(Tree* root, string name)
{
    if(root->name == name)return root;
    Tree* a = NULL, *b = NULL;
    if(root->Mother != NULL)a = findName(root->Mother, name);
    if(root->Father != NULL)b = findName(root->Father, name);
    if(a != NULL)return a;
    if(b != NULL)return b;
    return NULL;
}
Tree& Tree::addFather(string rootName, string fatherName)
{
    Tree* runner = findName(this, rootName);
    if(runner != NULL && runner->Father == NULL)
    {
        runner->Father = new Tree(fatherName, this);
        return *this;
    }
    message = runner == NULL ? "invalid root name\n" : string(rootName + " already got a father");
    throw myException();
}
Tree& Tree::addMother(string rootName, string motherName)
{
    Tree* runner = findName(this, rootName);
    if(runner != NULL && runner->Mother == NULL)
    {
        runner->Mother = new Tree(motherName, this);
        return *this;
    }
    message = runner == NULL ? "invalid root name\n" : string(rootName + " already got a Mother");
    throw myException();
}
string Tree::relation(string name)
{
    if(this->name == name)return string("me");
    string ans = relation(this, string(""), name);
    if(ans == "mother" || ans == "father" || ans == "unrelated")return ans;
    if(ans == "great-mother")return string("grandmother");
    if(ans == "great-father")return string("grandfather");
    size_t i = 0;
    if(ans.find("great-mother") != string::npos)
        ans.replace(ans.size()-12,12,"grandmother");
    else if(ans.find("great-father") != string::npos)
        ans.replace(ans.size()-12,12,"grandfather");
    return ans;
}
string Tree::relation(Tree* root, string ans, string name)
{
    if(root->Mother == NULL && root->Father == NULL)return string("unrelated");
    if(root->Father != NULL && root->Father->name == name)return string(ans+"father");
    if(root->Mother != NULL && root->Mother->name == name)return string(ans+"mother");
    ans = string("great-" + ans);
    string a = root->Mother != NULL ? relation(root->Mother, ans, name) : "unrelated";
    string b = root->Father != NULL ? relation(root->Father, ans, name) : "unrelated";
    if(a != "unrelated")return a;
    else if(b != "unrelated") return b;
    return "unrelated";
}

string Tree::find(string relation)
{
    message = "invalid relation - "+this->name+" does`nt have a "+relation;
    if(relation == "me")return this->name;
    string a =find(this, relation);
    if(a != "")return a;
    throw myException();
}
string Tree::find(Tree* root, string relation)
{
    // cout << root->name+" aaa\t";
    if(relation == "mother")return root->Mother != NULL ? root->Mother->name : throw myException();
    if(relation == "father")return root->Father != NULL ? root->Father->name : throw myException();
    if(relation == "grandmother")
    {
        if(root->Father != NULL && root->Father->Mother != NULL)return root->Father->Mother->name;
        if(root->Mother != NULL && root->Mother->Mother != NULL)return root->Mother->Mother->name;
        return "";
    }
    if(relation == "grandfather")
    {
        if(root->Father != NULL && root->Father->Father != NULL)return root->Father->Father->name;
        if(root->Mother != NULL && root->Mother->Father != NULL)return root->Mother->Father->name;
        return "";
    }
    if(size_t i =relation.find("great-") != string::npos)
    {
        relation.erase(0, 6);
        string a ="";
        if(root->Mother != NULL)
        {
           a = find(root->Mother, relation);
        }
        string b = "";
        if(root->Father != NULL)
        {
           b = find(root->Father, relation);
        }
        if(a.length() > 0 )return a;
        if(b.length() > 0)return b;
        return "";
    }
    message = "The tree cannot handle the '" +relation+ "' relation";
    throw myException();

}
void Tree::display()
{
    if(this->name.length() > 0)
    {   
        cout <<this->name << endl;
        if(this->Father != NULL)
        {
            cout << this->Father->name+"\n";
            display(this->Father);
        }
        if(this->Mother != NULL)
        {
            cout << this->Mother->name+"\n";
            display(this->Mother);
        }
    }
    else
        cout<< "nothing to display\n";
}
void Tree::display(Tree* root)
{
    if(root->Father != NULL)
    {
        cout << root->Father->name+"\n";
        display(root->Father);
    }
    if(root->Mother != NULL)
    {
        cout << root->Mother->name+"\n";
        display(root->Mother);
    }

}
void Tree::remove(string name)
{
    message = "already removed";
    if(this->name == name)
    {
        message = "cant remove root!";
        throw myException();
    }
    else 
    {
        bool a = false, b = false;
        if(this->Mother != NULL)a = remove(&(this->Mother), name);
        if(this->Father != NULL)b = remove(&(this->Father), name);
        if(!b && !a)throw myException();
    }
}
bool Tree::remove(Tree** root, string name)
{
    if((*root)->name == name)
    {
        if((*root)->Mother != NULL)remove(&(*root)->Mother);
        if((*root)->Father != NULL)remove(&(*root)->Father);
        delete *root;
        *root = NULL;
        return true;
    }
    else
    {

        if((*root)->Mother != NULL && (*root)->Father != NULL)return remove(&(*root)->Mother, name) || remove(&(*root)->Father, name);
        if((*root)->Father != NULL)return remove(&(*root)->Father, name);
        if((*root)->Mother != NULL)return remove(&(*root)->Mother, name);
        return false;
    }
    
}
void Tree::remove(Tree** root)
{
    if((*root)->Mother != NULL)remove(&(*root)->Mother);
    if((*root)->Father != NULL)remove(&(*root)->Father);
    delete *root;
    *root = NULL;
}



