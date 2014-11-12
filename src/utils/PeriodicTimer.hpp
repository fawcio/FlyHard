/*
 * PeriodicTiner.h
 *
 *  Created on: 11 lis 2014
 *      Author: slawek
 */

#ifndef PERIODICTIMER_HPP_
#define PERIODICTIMER_HPP_

#include <thread>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "IUpdateable.hpp"

namespace sfml_playground
{

class PeriodicTimer
{
public:
	PeriodicTimer(IUpdateable* const updateable, const unsigned int milliseconds);
	virtual ~PeriodicTimer();
	bool start();
	bool stop();

	void periodicEvent();

private:

	IUpdateable*					mUpdateable;

	std::thread						mWorker;

	boost::asio::deadline_timer*	mAsioTimer;
	boost::asio::io_service			mIoService;

	unsigned int					mMilliseconds;

};

} /* namespace sfml_playground */

#endif /* PERIODICTIMER_HPP_ */
