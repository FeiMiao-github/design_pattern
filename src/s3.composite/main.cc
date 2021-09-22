// 组合是一种结构型设计模式，
// 你可以使用它将对象组合成树状结构， 并且能像使用独立对象一样使用它们。

#include <iostream>
#include <list>

using std::string;
using std::cout;

class Component
{
public:
    virtual ~Component() = default;
    virtual string DoWork() const = 0;
    virtual void Add(Component* )
    {
        throw "this object shouldn't add any sub components !";
    }
    virtual void Remove(Component* )
    {
        throw "this object shouldn't add any sub components !";
    }
    virtual bool IsComposite() const
    {
        return false;
    }
    Component(const string& name) : m_name_(name)
    {
    }
protected:
    string m_name_;
};

class Leaf : public Component
{
public:
    Leaf(const string& name) : Component(name)
    {
    }

    virtual string DoWork() const override
    {
        return "Leaf" + m_name_;
    }
};

class Composite : public Component
{
public:
    Composite(const string& name) : Component(name)
    {
    }

    virtual string DoWork() const override
    {
        string ret = m_name_;
        ret += "-Branch(";
        for (auto p = m_children_.begin(); p != m_children_.end();)
        {
            ret += (*p)->DoWork();
            p++;
            if (p != m_children_.end())
            {
                ret += ", ";
            }
        }
        ret += ")";
        return ret;
    }

    virtual void Add(Component* component) override
    {
        m_children_.push_back(component);
    }

    virtual void Remove(Component* component) override
    {
        m_children_.remove(component);
    }

    virtual bool IsComposite() const override
    {
        return true;
    }
private:
    std::list<Component*> m_children_;
};

class Client
{
public:
    void Code(Component* component)
    {
        cout << "Result: " << component->DoWork() << '\n';
    }
};

int main()
{
    Component* tree = new Composite("tree");
    Client* client = new Client;
    Leaf* leaf1 = new Leaf("1");
    Leaf* leaf2 = new Leaf("2");
    Leaf* leaf3 = new Leaf("3");
    Leaf* leaf4 = new Leaf("4");
    Leaf* leaf5 = new Leaf("5");
    Leaf* leaf6 = new Leaf("6");
    Composite* branch1 = new Composite("1");
    Composite* branch2 = new Composite("2");
    branch1->Add(leaf1);
    branch1->Add(leaf2);
    branch1->Add(leaf3);
    branch2->Add(leaf4);
    branch2->Add(leaf5);
    branch2->Add(leaf6);
    tree->Add(branch1);
    tree->Add(branch2);

    client->Code(tree);

    delete branch2;
    delete branch1;
    delete leaf6;
    delete leaf5;
    delete leaf4;
    delete leaf3;
    delete leaf2;
    delete leaf1;
    delete client;
    delete tree;
    return 0;
}