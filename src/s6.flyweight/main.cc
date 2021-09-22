// 享元模式是一种结构型设计模式
// 它摒弃了在每个对象中保存所有数据的方式， 通过共享多个对象所共有的相同状态，
// 让你能在有限的内存容量中载入更多对象。

#include <iostream>
#include <unordered_map>

class SharedState
{
public:
    std::string m_brand_;
    std::string m_model_;
    std::string m_color_;

    SharedState(const std::string& brand,
                const std::string& model,
                const std::string& color)
                : m_brand_(brand),
                  m_model_(model),
                  m_color_(color)
        {}
    
    SharedState(const SharedState&) = default;

    friend std::ostream &operator<<(std::ostream& os,
                                    const SharedState &ss)
    {
        return os << "["
                  << ss.m_brand_
                  << ", "
                  << ss.m_model_
                  << ", "
                  << ss.m_color_
                  << " ]";
    }
};

class UniqueState
{
public:
    std::string m_owner_;
    std::string m_plates_;

    UniqueState(const std::string& owner,
                const std::string& plates)
                : m_owner_(owner),
                  m_plates_(plates)
        {}

    friend std::ostream &operator<<(std::ostream& os,
                                    const UniqueState& us)
    {
        return os << "[ "
                  << us.m_owner_
                  << ", "
                  << us.m_plates_
                  << " ]";
    }
};

class Flyweight
{
public:
    Flyweight(const SharedState* shared_state)
              : m_shared_state_(new SharedState(*shared_state))
    {}

    Flyweight(const Flyweight &other)
              : m_shared_state_(new SharedState(*other.m_shared_state_))
    {}

    ~Flyweight()
    {
        delete m_shared_state_;
    }

    SharedState *GetSharedState() const
    {
        return m_shared_state_;
    }

    void Operation(const UniqueState& unique_state) const
    {
        std::cout << "Flyweight: Display shared("
                  << *m_shared_state_
                  << ") and unique ("
                  << unique_state
                  << ") state.";
    }
private:
    SharedState *m_shared_state_;
};

class FlyweightFactory
{
public:
    FlyweightFactory(std::initializer_list<SharedState> share_states)
    {
        for (const SharedState& ss : share_states)
        {
            m_flyweights_.insert(std::make_pair<std::string,
                                 Flyweight>(GetKey(ss),
                                 Flyweight(&ss)));
        }
    }

    Flyweight GetFlyweight(const SharedState &sharedState)
    {
        std::string key = GetKey(sharedState);
        if (m_flyweights_.find(key) == m_flyweights_.end())
        {
            std::cout << "FlyweightFactory: can't find a flyweight, creating new one.\n";
            m_flyweights_.insert(std::make_pair(key, Flyweight(&sharedState)));
        }
        else
        {
            std::cout << "FlyweightFactory: Reusing existing flyweight.\n";
        }
        return m_flyweights_.at(key);
    }

    void ListFlyweights() const
    {
        size_t size = m_flyweights_.size();
        std::cout << "\nFlyweightFactory: I have " << size << " flyweights:\n";
        for (std::pair<std::string, Flyweight> pair: m_flyweights_)
        {
            std::cout << pair.first << '\n';
        }
    }
private:
    std::string GetKey(const SharedState &ss) const
    {
        return ss.m_brand_ + "_" + ss.m_model_ + "_" + ss.m_color_;
    }
private:
    std::unordered_map<std::string, Flyweight> m_flyweights_;
};

void AddCarToPoliceDB(FlyweightFactory &ff,
                      const std::string &plates,
                      const std::string &owner,
                      const std::string &brand,
                      const std::string &model,
                      const std::string &color)
{
    std::cout << "\nClient: Adding a car to a database.\n";
    const Flyweight &flyweight = ff.GetFlyweight({brand, model, color});
    flyweight.Operation({owner, plates});
}

int main()
{
    FlyweightFactory *factory = new FlyweightFactory({
        {"Chevrolet", "Camaro2018", "pink"}, 
        {"Mercedes Benz", "C300", "black"}, 
        {"Mercedes Benz", "C500", "red"},
        {"BMW", "M5", "red"},
        {"BMW", "X6", "white"}});
    factory->ListFlyweights();
    
    AddCarToPoliceDB(*factory,
                     "CL234IR",
                     "James Doe",
                     "BMW",
                     "M5",
                     "red");

    AddCarToPoliceDB(*factory,
                     "CL234IR",
                     "James Doe",
                     "BMW",
                     "X1",
                     "red");

    factory->ListFlyweights();

    delete factory;
    return 0;
}