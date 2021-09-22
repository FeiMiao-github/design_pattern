// 桥接模式

#include <iostream>

using std::string;
using std::cout;

class Color
{
public:
    virtual ~Color() = default;
    virtual string name() const = 0;
};

class Shape
{
public:
    virtual ~Shape() = default;
    virtual string name() const = 0;
protected:
    Color  *m_color_;
};

class Rect
    : public Shape
{
public:
    Rect(Color *color)
    {
        m_color_ = color;
    }

    string name() const override
    {
        return m_color_->name() + " Rect";
    }
};

class Circle
    : public Shape
{
public:
    Circle(Color *color)
    {
        m_color_ = color;
    }

    string name() const override
    {
        return m_color_->name() + " Circle";
    }
}; 

class Red
    : public Color
{
public:
    string name() const override
    {
        return "Red";
    }
};

class Blue
    : public Color
{
public:
    string name() const override
    {
        return "Blue";
    }
};

void Client(Shape *shape)
{
    cout << "Client: draw " << shape->name() << "\n"; 
}

int main()
{
    Color *red = new Red;
    Color *blue = new Blue;
    Shape *rrect = new Rect(red);
    Shape *brect = new Rect(blue);
    Shape *rcircle = new Circle(red);
    Shape *bcircle = new Circle(red);

    Client(rrect);
    Client(brect);
    Client(rcircle);
    Client(bcircle);

    delete bcircle;
    delete rcircle;
    delete brect;
    delete rrect;
    delete blue;
    delete red;
    return 0;
}