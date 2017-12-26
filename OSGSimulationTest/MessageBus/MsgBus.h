#pragma once
#include <string>
#include <boost/tuple/tuple.hpp>
#include <boost/utility.hpp>
#include <boost/unordered_map.hpp>
#include <boost/any.hpp>
#include <boost/thread/thread.hpp>
#include <map>


typedef boost::unique_lock<boost::shared_mutex> ReadLock;
typedef boost::shared_lock<boost::shared_mutex> WriteLock;

using namespace std;

template <typename... Args>
struct Impl;

template <typename First, typename... Args>
struct Impl<First, Args...>
{
	static std::string name()
	{
		return std::string(typeid(First).name()) + " " + Impl<Args...>::name();
	}
};

template <>
struct Impl<>
{
	static std::string name()
	{
		return "";
	}
};

template <typename... Args>
std::string type_name()
{
	return Impl<Args...>::name();
}

template <typename R = void>
class MessageBus : boost::noncopyable
{
public:
	//注册消息
	template< class... Args, class F, class = typename std::enable_if<!std::is_member_function_pointer<F>::value>::type>
	void Attach(string& strKey, F && f)
	{
		std::function<R(Args...)> fn = [&](Args... args) {return f(std::forward<Args>(args)...); };
		{
			WriteLock rlock(read_write_mutex);
			m_map.insert(std::make_pair(strKey + type_name < Args...>(), std::move(fn)));
		}
	}

	// non-const member function 
	template<class... Args, class C, class... DArgs, class P>
	void Attach(string& strKey, R(C::*f)(DArgs...), P && p)
	{
		std::function<R(Args...)> fn = [&, f](Args... args) {return (*p.*f)(std::forward<Args>(args)...); };
		{
			WriteLock rlock(read_write_mutex);
			m_map.insert(std::make_pair(strKey + type_name < Args...>(), std::move(fn)));
		}
	}

	template<class... Args, class C, class... DArgs, class P>
	void Attach(string& strKey, R(C::*f)(DArgs...) const, P && p)
	{
		std::function<R(Args...)> fn = [&, f](Args... args) {return (*p.*f)(std::forward<Args>(args)...); };
		{
			WriteLock rlock(read_write_mutex);
			m_map.insert(std::make_pair(strKey + type_name < Args...>(), std::move(fn)));
		}
	}

	//广播消息，主题和参数可以确定一个消息, 所有的消息接收者都将收到并处理该消息
	template<typename... Args>
	void SendReq(string& strTopic, Args... args)
	{
		auto range = m_map.equal_range(strTopic + type_name < Args...>());
		for (auto it = range.first; it != range.second; it++)
		{
			std::function<R(Args...)> f = boost::any_cast<std::function<R(Args...)>>(it->second);
			f(args...);
		}
	}

	//移除消息
	template<typename... Args>
	void Remove(string& strTopic)
	{
		auto range = m_map.equal_range(strTopic + type_name < Args...>());
		{
			WriteLock rlock(read_write_mutex);
			m_map.erase(range.first, range.second);
		}

	}


private:
	std::multimap<string, boost::any> m_map;
	boost::shared_mutex  read_write_mutex;
};