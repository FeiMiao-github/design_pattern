// 迭代器
//    迭代器是一种行为设计模式，
//    让你能在不暴露复杂数据结构内部细节的情况下遍历其中所有的元素

#include <iostream>
#include <vector>

template <typename T> class concrete_collection;
template <typename Collection, typename Iterator_type, typename T> class concrete_iterator;

template <typename Collection, typename Iterator_type, typename T>
class iterator
{
public:
    typedef iterator<Collection, Iterator_type, T> m_iter_type_;

    iterator(concrete_collection<T> *collection,
             Iterator_type cur) : m_collection_(collection),
                                  m_current_(cur)
    {
    }
    virtual bool is_done() = 0;
    virtual bool equal(const m_iter_type_ & iter)
    {
        return m_current_ == iter.m_current_ && m_collection_ == iter.m_collection_;
    }
    virtual void next()
    {
        m_current_++;
    }
    virtual T val()
    {
        return *m_current_;
    }
    virtual bool operator==(const m_iter_type_ & iter)
    {
        return equal(iter);
    }
    virtual bool operator!=(const m_iter_type_ & iter)
    {
        return !equal(iter);
    }
protected:
    concrete_collection<T> *m_collection_;
    Iterator_type m_current_;
};

template <typename T>
class concrete_collection
{
public:
    typedef typename std::vector<T>::iterator m_Iterator_type;
    typedef concrete_iterator<concrete_collection<T>, m_Iterator_type, T> m_it_concrete_type_;

    virtual m_it_concrete_type_ begin();
    virtual m_it_concrete_type_ end();

    void push_back(T &val)
    {
        m_vector_.push_back(val);
    }

private:
    std::vector<T> m_vector_;
};

template <typename Collection, typename Iterator_type, typename T>
class concrete_iterator : public iterator<Collection, Iterator_type, T>
{
public:
    typedef iterator<Collection, Iterator_type, T> m_iter_type_;
    typedef concrete_iterator<Collection, Iterator_type, T> m_cont_it_type_;

    concrete_iterator(concrete_collection<T> *collection,
                      Iterator_type cur) : m_iter_type_(collection, cur)
    {}
        
    bool equal(m_cont_it_type_ &iter)
    {
        return m_iter_type_::equal(iter);
    }

    bool operator==(m_cont_it_type_ &iter)
    {
        return equal(iter);
    }

    bool is_done() override
    {
        auto begin = m_iter_type_::m_collection_->begin();
        auto end = m_iter_type_::m_collection_->end();
        return begin == end;
    }
};

template <typename T>
typename concrete_collection<T>::m_it_concrete_type_ concrete_collection<T>::begin()
{
    return m_it_concrete_type_(this, m_vector_.begin());
}

template <typename T>
typename concrete_collection<T>::m_it_concrete_type_ concrete_collection<T>::end()
{
    return m_it_concrete_type_(this, m_vector_.end());
}

int main()
{
    concrete_collection<int> cont;
    for (int i = 0; i < 10; i++)
    {
        cont.push_back(i);
    }

    for (auto p = cont.begin(); p != cont.end(); p.next())
    {
        std::cout << p.val() << ',';
    }

    return 0;
}