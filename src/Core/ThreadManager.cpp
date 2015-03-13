#include <Core\ThreadManager.hpp>
#include <Level\SolarSystem.hpp>

ThreadManager::ThreadManager(SolarSystem* _parent, EventThread* _eventThread, GraphicsThread* _graphThread)
{
	//pointer
	parent = _parent;
	eventThread = _eventThread;
	graphThread = _graphThread;
	
	//member
	gravThread = new GravityThread(this);

	//init
	looptime = chrono::milliseconds(1000 / 100);
	running = false;

	ug::log("[Info]ThreadManager has been constructed: " + *_parent->getID());
}
ThreadManager::~ThreadManager()
{
	//member
	delete gravThread;
	gravThread = nullptr;

	//pointer
	string tmp = *parent->getID();
	parent = nullptr;
	eventThread = nullptr;

	ug::log("[Info]ThreadManager has been destructed: " + tmp);
}
void ThreadManager::launch()
{
	running = true;
	me = thread(&ThreadManager::run, this);
}
void ThreadManager::terminate()
{
	running = false;
}
void ThreadManager::run()
{
	ug::log("[Info]ThreadManager is running in this thread");
	chrono::steady_clock::time_point last = chrono::steady_clock::now();
	while (running)
	{
		//Thread throttle
		this_thread::sleep_for(looptime - (chrono::steady_clock::now() - last));
		last = chrono::steady_clock::now();

		//Movement(always)
		//Graphics(always)
		//Gravity(on demand)
		//Modding(on demand)

		//Transfer/Import/Removal/Balancing(on demand)
	}
	ug::log("[Info]ThreadManager has stopped running in this thread");
}
SolarSystem* ThreadManager::getParent()
{
	return parent;
}
void ThreadManager::startRender(sf::View _view)
{
	if (graphThread)
	{
		if (graphThread->isRunning())
		{
			ug::log("[Warning]ThreadManager will terminate GraphicsThread to re-launch it");
			stopRender();
			startRender(_view);
		}
		else {
			//WORK set graphThread
			graphThread->launch();
		}
	}
	else {
		ug::log("[Warning]ThreadManager couldn't launch GraphicsThread, because it doesn't know one");
	}
}
void ThreadManager::stopRender()
{
	if (graphThread)
	{
		if (graphThread->isRunning())
		{
			graphThread->terminate();
		}
		else {
			ug::log("[Warning]ThreadManager tried to stop already stopped GraphicsThread");
		}
	}
	else {
		ug::log("[Warning]ThreadManager couldn't terminate GraphicsThread, because it doesn't know one");
	}
}