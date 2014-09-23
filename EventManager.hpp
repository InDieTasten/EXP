#ifndef _EventManager_hpp_
#define _EventManager_hpp_

#include <SFML\Graphics.hpp>
#include "DataBank.hpp"
#include "GraphicsEngine.hpp"
#include "PhysicsEngine.hpp"
#include "GUIManager.hpp"
#include "ModModule.hpp"

extern std::list< std::list<std::string> > eventBuffer;

extern DataBank* dLink;
extern GUIManager* guiLink;

extern sf::Thread* gThread;
extern sf::Thread* pThread;
extern sf::Thread* mThread;

extern sf::Mutex GMutex;

class EventManager
{
    //MEMBERS
private:

    //CONSTRUCTORS

    //DESTRUCTORS

    //METHODS
    void handleEvent(sf::Event *_event);
    void handleSoftEvent(std::list<std::string> _args);
    void handleTask(std::list<std::string> _args);
public:
    void SetDataLink(DataBank *_dataLink, GUIManager *_gManager, GraphicsEngine* _gEngine, PhysicsEngine* _pEngine, ModModule *_mModule, int* _level);
    void processEvent(sf::Event *_event);
    void processSoftEvent(std::list<std::string> _args);
    void processTask(std::list<std::string> _args);
};

#endif