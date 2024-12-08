#include "MyMutex.h"
#include <mutex>

using namespace std;

std::atomic<bool> is_locked{ false };

void MyMutex::LockMyMutex()
{


	bool expected = false;

	while (!is_locked.compare_exchange_strong(expected, true)) // if is_locked is false, put it to true, and return true if succusfull
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		expected = false;
		
	}

	
}

void MyMutex::UnlockMyMutex()
{
	bool expected = true;
	while (!is_locked.compare_exchange_strong(expected, false))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		expected = true;
		
	}
	
	// else throw exception
}


