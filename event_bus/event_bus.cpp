#include "event_bus.h"
#include <functional>
#include <chrono>
#include <iostream>

EventBus::EventBus()
{
	m_exit = false;
	m_pThreadBus = std::make_unique<std::thread>(std::bind(&EventBus::threadHandler, this));
}
/****************************************************************************/

EventBus::~EventBus()
{
	m_exit = true;
	m_pThreadBus->join();
}
/****************************************************************************/
void EventBus::publish(uint16_t eventId, std::string&& eventData)
{
	m_mutexQueueEvent.lock();
	m_qEvent.push(Event(eventId, eventData));
	m_mutexQueueEvent.unlock();

	m_cvEvent.notify_one();
}
/****************************************************************************/

void EventBus::subscribe(uint16_t eventId, EventHandler handler)
{
	std::lock_guard<std::mutex> lg(m_mutexMapHanlder);
	m_mapHandler[eventId].push_back(handler);
}
/****************************************************************************/
void EventBus::threadHandler(void)
{
	while (false == m_exit)
	{
		Event event;
		{
			std::unique_lock<std::mutex> lk(m_mutexQueueEvent);
			m_cvEvent.wait(lk, [&]
						   { return (false == m_qEvent.empty()); });
			event = m_qEvent.front();
			m_qEvent.pop();
		}

		{
			std::lock_guard<std::mutex> lg(m_mutexMapHanlder);

			for (EventHandler handler : m_mapHandler[event.id])
			{
				handler(event);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}