#include <vector>
#include <memory>
#include <map>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

class EventBus;
class Publisher;
class Subscriber;
class Event;

typedef void (*EventHandler)(const Event&);
typedef uint16_t EventId;

class EventBus
{
public:
	EventBus();
	~EventBus();

	void publish(uint16_t eventId, std::string&& eventData);
	void subscribe(uint16_t eventId, EventHandler handler);

private:
	void threadHandler(void);

private:
	std::map<EventId, std::vector<EventHandler>> m_mapHandler;
	std::queue<Event> m_qEvent;
	std::mutex m_mutexQueueEvent;
	std::mutex m_mutexMapHanlder;
	std::unique_ptr<std::thread> m_pThreadBus;
	std::condition_variable m_cvEvent;
	bool m_exit;
};

class Event
{
public:
	Event()
	 : id(0), data("") {}

	Event(EventId id, const std::string& data)
		: id(id),
		data(data)
	{
	}

	std::string getInfor() const
	{
		return "id: " + std::to_string(id) + ", data: " + data;
	}

public:
	EventId id;
	std::string data;
};

class Publisher
{
public:

private:

};

class Subscriber
{
public:

private:

};
