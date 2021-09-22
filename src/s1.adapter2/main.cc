#include <iostream>

using std::cout;
using std::string;

class Target
{
public:
    virtual ~Target() = default;

    virtual string Request() const 
    {
        return "Target: The Default's Target's behavior.";
    }
};

class Adaptee
{
public:
    std::string SpecificRequest() const
    {
        return "Adaptee: The Adaptee's behavior.";
    }
};

class Adapter: public Target, public Adaptee
{
public:
    Adapter() = default;

    std::string Request() const override
    {
        return "Adapter:" + Adaptee::SpecificRequest();
    }
};

void ClientCode(Target* target)
{
    std::cout << "[ClientCode]" << target->Request() << '\n';
}

int main()
{
    std::cout << "client call Target: \n";
    Target* target = new Target;
    ClientCode(target);
    delete target; 

    std::cout << "\n";
    std::cout << "client call Adaptee:\n";
    Target* adapter = new Adapter;
    ClientCode(adapter);
    delete adapter;
    return 0;
}