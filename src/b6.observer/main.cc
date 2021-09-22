// 观察者模式是一种行为设计模式
// 允许你定义一种订阅机制， 可在对象事件发生时通知多个 “观察” 该对象的其他对象。

#include <iostream>
#include <list>
#include <string>

class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void Update(const std::string &messageFromSubject) = 0;
};

class ISubject
{
public:
	virtual ~ISubject() = default;
	virtual void Attach(IObserver *observer) = 0;
	virtual void Detach(IObserver *observer) = 0;
	virtual void Notify() = 0;
};

class Subject : public ISubject
{
private:
	void HowManyObserver()
	{
		std::cout << "There are "
				  << m_list_observer_.size()
				  << " observers in the list.\n";
	}

public:
	void CreateMessage(std::string message = "Empty")
	{
		this->m_message_ = message;
		Notify();
	}

private:
	void SomeBusinessLogic()
	{
		this->m_message_ = "change message";
		Notify();
		std::cout << "I'm about to do something important.\n";
	}

public:
	virtual ~Subject()
	{
		std::cout << "Goodbye, I was Subject.\n";
	}

	void Attach(IObserver *observer) override
	{
		m_list_observer_.push_back(observer);
	}

	void Detach(IObserver *observer) override
	{
		m_list_observer_.remove(observer);
	}

	void Notify() override
	{
		std::list<IObserver *>::iterator iteator = m_list_observer_.begin();
		HowManyObserver();
		while (iteator != m_list_observer_.end())
		{
			(*iteator)->Update(m_message_);
			++iteator;
		}
	}
private:
	std::list<IObserver *> m_list_observer_;
	std::string m_message_;
};

class Observer : public IObserver
{
public:
	Observer(Subject &subject) : m_subject_(subject)
	{
		this->m_subject_.Attach(this);
		std::cout << "Hi, I'm the Observer \"" << ++Observer::s_number_ << "\".\n";
		this->m_number_ = Observer::s_number_;
	}

	~Observer()
	{
		std::cout << "Goodbye, I was the observer \"" << m_number_ << "\".\n";
	}

	void Update(const std::string &message_from_subject) override
	{
		m_message_from_subject_ = message_from_subject;
		PrintInfo();
	}

	void RemoveMeFromTheList()
	{
		m_subject_.Detach(this);
		std::cout << "Observer \"" << m_number_ << "\" removed from the list.\n";
	}

	void PrintInfo()
	{
		std::cout << "Observer \""
				  << m_number_
				  << "\": a new message is available ==>"
				  << m_message_from_subject_
				  << "\n";
	}

private:
	std::string m_message_from_subject_;
	Subject &m_subject_;
	static int s_number_;
	int m_number_;
};

int Observer::s_number_ = 0;

class Client
{
public:
	void code()
	{
		Subject *subject = new Subject;
		Observer *observer1 = new Observer(*subject);
		Observer *observer2 = new Observer(*subject);
		Observer *observer3 = new Observer(*subject);
		Observer *observer4 = new Observer(*subject);
		Observer *observer5;
		Observer *observer6;

		subject->CreateMessage("Hello world! :D");
		observer3->RemoveMeFromTheList();

		subject->CreateMessage("The weather is hot today! :p");
		observer5 = new Observer(*subject);

		observer2->RemoveMeFromTheList();
		observer6 = new Observer(*subject);

		subject->CreateMessage("My new Car is great! ;)");
		observer6->RemoveMeFromTheList();

		observer5->RemoveMeFromTheList();
		observer4->RemoveMeFromTheList();
		observer1->RemoveMeFromTheList();

		delete observer6;
		delete observer5;
		delete observer4;
		delete observer3;
		delete observer2;
		delete observer1;
		delete subject;
	}
};

int main()
{
	Client client;
	client.code();
	return 0;
}