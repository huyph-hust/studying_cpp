#include <iostream>
#include "event_bus.h"
#include <chrono>

int main(void)
{
	std::cout << "hello event bus \n";
	EventBus eventBus;
	eventBus.subscribe(1, [](const Event &event){
		std::cout << "subscribe: " << event.getInfor() << std::endl;

	});


	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		eventBus.publish(1, "hello");
	}

	return 0;
}