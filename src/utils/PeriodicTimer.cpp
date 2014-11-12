/*
 * PeriodicTiner.cpp
 *
 *  Created on: 11 lis 2014
 *      Author: slawek
 */
#include <iostream>

#include "PeriodicTimer.hpp"

namespace sfml_playground
{

PeriodicTimer::PeriodicTimer(IUpdateable* const updateable, const unsigned int milliseconds)
	: mUpdateable(updateable), mIoService(), mMilliseconds(milliseconds)
{
	mAsioTimer = new boost::asio::deadline_timer(mIoService, boost::posix_time::milliseconds(mMilliseconds));
}

PeriodicTimer::~PeriodicTimer()
{
}

bool PeriodicTimer::start()
{
	mAsioTimer->async_wait(boost::bind(&PeriodicTimer::periodicEvent, this));
	mWorker = std::thread([this]()->void{
		this->mIoService.run();
	});

	return true;
}

bool PeriodicTimer::stop()
{
	mIoService.stop();
	mWorker.join();

	return true;
}

void PeriodicTimer::periodicEvent()
{
	mUpdateable->update();
	mAsioTimer->expires_at(mAsioTimer->expires_at() + boost::posix_time::milliseconds(mMilliseconds));
	mAsioTimer->async_wait(boost::bind(&PeriodicTimer::periodicEvent, this));
}

} /* namespace sfml_playground */
