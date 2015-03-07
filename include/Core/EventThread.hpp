#ifndef _EventThread_hpp_
#define _EventThread_hpp_

#include <string>

using namespace std;
extern void ug::log(string);

class ThreadManager;

class EventThread
{
private:
	ThreadManager* parent;
public:
	EventThread();
	~EventThread();

	void Run();
	void Stop();
};

#endif // !_EventThread_hpp_