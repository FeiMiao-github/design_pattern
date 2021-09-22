#include <iostream>

using std::cout;
using std::string;

class singleton
{
private:
    singleton()
    {
        char c = i_ + '0';
        m_name_ = new char[10] {'h', 'e', 'l', 'l', 'o', c, 0};
        i_++;
    }

    singleton(const singleton&) = delete;
    singleton& operator=(const singleton&) = delete;

    ~singleton()
    {
        delete[] m_name_;
    }

    class GC
    {
    public:
        ~GC()
        {
            delete inst_;
        }
    };
public:
    static singleton *inst()
    {
        if (inst_ == nullptr)
        {
            inst_ = new singleton();
        }
        return inst_;
    }

    void log()
    {
        int i = 0;
        while (m_name_[i] != 0)
        {
            cout << m_name_[i];
            i++;
        }
        cout << '\n';
    }
private:
    static singleton * inst_;
    static int i_;
    static GC gc_;
    char *m_name_;
};

singleton::GC singleton::gc_;
singleton* singleton::inst_ = nullptr;
int singleton::i_ = 1;

void client()
{
    singleton* s = singleton::inst();
    s->log();

    s = singleton::inst();
    s->log();

    s = singleton::inst();
    s->log();
}

int main()
{
    client();
    return 0;
}