// 原型模式是一种创建型设计模式， 使你能够复制已有对象
// 而又无需使代码依赖它们所属的类。

#include <iostream>
#include <unordered_map>

using std::cout;
using std::string;
using std::to_string;

class Prototype
{
public:
    virtual ~Prototype() {}
    virtual Prototype* Clone() const = 0;
    virtual void Disp() const = 0;
};

class Shape : public Prototype
{
public:
    Shape(string name, double x = 0.0, double y = 0.0) : m_name_(name),
                                                         m_x_(x),
                                                         m_y_(y)
    {}

    Shape(const Shape& shape)
    {
        m_name_ = shape.m_name_;
        m_x_ = shape.m_x_;
        m_y_ = shape.m_y_;
    }

    virtual ~Shape() {}

    virtual void Disp() const
    {
        cout << m_name_ << ": { " << m_x_ << ", " << m_y_ << "}";
    }
private:
    string m_name_;
    double m_x_;
    double m_y_;
};

class Rect : public Shape
{
public:
    Rect(string name, double x, double y, double w, double h) : Shape(name, x, y),
                                                                m_h_(h),
                                                                m_w_(w)
                                                                {}

    Prototype* Clone() const override
    {
        return new Rect(*this);
    }

    void Disp() const override
    {
        Shape::Disp();
        cout << "{" << m_h_ << ", " << m_w_ << "}\n";
    }
private:
    double m_h_;
    double m_w_;
};

class Circle : public Shape
{
public:
    Circle(string name, double x, double y, double r) : Shape(name, x, y),
                                                        m_radius_(r)
                                                        {}

    Prototype* Clone() const override
    {
        return new Circle(*this);
    }

    void Disp() const override
    {
        Shape::Disp();
        cout << "{" << m_radius_ << "}\n";
    }
private:
    double m_radius_;
};

class ProtoTypeFactory
{
public:
    enum class Type
    {
        CIRCLE,
        RECT,
    };

    ProtoTypeFactory()
    {
        m_map_[Type::CIRCLE] = new Circle("Circle", 0, 0, 2);
        m_map_[Type::RECT] = new Rect("Rect", 0, 0, 20, 30);
    }

    ~ProtoTypeFactory()
    {
        delete m_map_[Type::CIRCLE];
        delete m_map_[Type::RECT];
        m_map_.clear();
    }

    Prototype* CreatePrototype(Type t)
    {
        return m_map_[t]->Clone();
    }

private:
    std::unordered_map<Type, Prototype*> m_map_;
};

void ClientCode(ProtoTypeFactory* factory)
{
    cout << "Create Circle : \n";
    Prototype* rect = factory->CreatePrototype(ProtoTypeFactory::Type::RECT);
    rect->Disp();
    cout << '\n';

    cout << "Create Rect : \n";
    Prototype* circle = factory->CreatePrototype(ProtoTypeFactory::Type::CIRCLE);
    circle->Disp();
    cout << '\n';

    delete rect;
    delete circle;
}

int main()
{
    ProtoTypeFactory* pf = new ProtoTypeFactory;
    ClientCode(pf);
    delete pf;
    return 0;
}