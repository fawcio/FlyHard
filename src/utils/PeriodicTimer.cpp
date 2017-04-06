/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Sławomir Cielepak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "PeriodicTimer.hpp"

namespace fly_hard
{

PeriodicTimer::PeriodicTimer(SceneNode* const updateable, const unsigned int milliseconds)
	: mNode(updateable), mIoService(), mMilliseconds(milliseconds)
{
	mAsioTimer = new boost::asio::deadline_timer(mIoService, boost::posix_time::milliseconds(mMilliseconds));
}

PeriodicTimer::~PeriodicTimer()
{
}

bool PeriodicTimer::start()
{
	mAsioTimer->async_wait(boost::bind(&PeriodicTimer::periodicEvent, this));
	mWorker = std::thread([this]()->void {
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
	mNode->update();
	mAsioTimer->expires_at(mAsioTimer->expires_at() + boost::posix_time::milliseconds(mMilliseconds));
	mAsioTimer->async_wait(boost::bind(&PeriodicTimer::periodicEvent, this));
}

}
