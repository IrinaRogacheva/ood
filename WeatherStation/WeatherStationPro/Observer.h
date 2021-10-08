#pragma once

#include <map>
#include <functional>

template <typename T>
class IObservable;

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, const int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, const int priority) override
	{
		m_observers.emplace(priority, &observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto copyObservers = m_observers;
		for (auto& item : copyObservers)
		{
			item.second->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto& item : m_observers)
		{
			if (item.second == &observer)
			{
				m_observers.erase(item.first);
				break;
			}
		}
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	std::map<int, ObserverType*> m_observers;
};