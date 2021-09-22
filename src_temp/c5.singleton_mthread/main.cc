#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using std::cout;
using std::string;
using std::vector;
using namespace std::chrono_literals;

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
        std::lock_guard<std::mutex> lg(mutex_);
        if (inst_ == nullptr)
        {
            std::this_thread::sleep_for(100ms);
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
    static std::mutex mutex_;
    char *m_name_;
};

singleton* singleton::inst_ = nullptr;
int singleton::i_ = 1;
singleton::GC singleton::gc_;
std::mutex singleton::mutex_;

void client(int thread_no)
{
    std::this_thread::sleep_for(10ms);
    cout << "Thread-" << thread_no << ":";
    singleton* s = singleton::inst();
    s->log();

    s = singleton::inst();
    s->log();

    s = singleton::inst();
    s->log();
}

int main()
{
    const int TN = 5;
    vector<std::thread> arr(TN);
    for (int i = 0; i < TN; i++)
    {
        arr[i] = std::thread(client, i+1);
    }
    for (auto &&t : arr)
    {
        t.join();
    }
    return 0;
}