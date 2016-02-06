#pragma once

#include <thread>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "entities/SceneNode.hpp"

namespace SFGame
{

class PeriodicTimer
{
public:
    PeriodicTimer(SceneNode* const node, const unsigned int milliseconds);
    virtual ~PeriodicTimer();
    bool start();
    bool stop();

    void periodicEvent();

private:

    SceneNode*						mNode;

    std::thread						mWorker;

    boost::asio::deadline_timer*	mAsioTimer;
    boost::asio::io_service			mIoService;

    unsigned int					mMilliseconds;

};

} /* namespace sfml_playground */
