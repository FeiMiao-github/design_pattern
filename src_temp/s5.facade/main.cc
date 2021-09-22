/**
 * 外观模式提供一个高层的接口并且对客户屏蔽这些子系统的类。外观模式可方便大多数程序员
 * 使用，同时对少数懂得如何使用底层的人,它并不隐藏这些功能
 *      以下情况适用于外观模式:
 *      a) 为复杂子系统提供一个简单接口
 *      b) 客户程序与抽象类的使用部分存在很大的依赖性.引入子系统与客户程序解耦
 *      c) 需要构建一个层次的子系统时,使用Facade模式定义子系统中每层的入口点。如果
 *  子系统之间相互依赖，可以让它们仅仅通过Facade通信
 * 
 */

#include <iostream>

using std::cout;

class subsystem1
{
public:
    void init()
    {
        cout << "[subsystem1] init" << "\n";
    }

    void dosth1()
    {
        cout << "[subsystem1] doSth1" << "\n";
    }

    void dosth2()
    {
        cout << "[subsystem1] doSth2" << "\n";
    }

    void dowork()
    {
        cout << "[subsystem1] dowork" << "\n";
    }
};

class subsystem2
{
public:
    void init()
    {
        cout << "[subsystem2] init" << "\n";
    }

    void dowork1()
    {
        cout << "[subsystem2] dowork1" << "\n";
    }

    void dowork2(subsystem1 &s1)
    {
        cout << "[subsystem2] dowork2" << "\n";
        s1.dowork();
    }
};

class facade
{
public:
    void run()
    {
        subsystem1 s1;
        subsystem2 s2;
        s1.init();
        s2.init();
        s1.dosth1();
        s2.dowork1();
        s1.dosth2();
        s2.dowork2(s1);
    }
};

void client(facade &f)
{
    f.run();
}

int main(void)
{
    facade f;
    client(f);
    return 0;
}