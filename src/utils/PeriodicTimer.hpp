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

#include "SceneNode.hpp"

namespace sfml_playground
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

#endif /* PERIODICTIMER_HPP_ */
