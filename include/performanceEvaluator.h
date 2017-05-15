// Copyright(c) 2016 - 2017 Costantino Grana, Federico Bolelli, Lorenzo Baraldi and Roberto Vezzani
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
// 
// *Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and / or other materials provided with the distribution.
// 
// * Neither the name of YACCLAB nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once
#include <opencv2/core.hpp>
#include <map> 

class PerformanceEvaluator {
	struct elapsed {
		double _last;
		double _total;

		elapsed() : _last(0),_total(0) {}
	};

public:
	PerformanceEvaluator() {
		_tickFrequency = cv::getTickFrequency();
	}
	void start() {
		_counter._last = (double)cv::getTickCount();
	}
	double stop() {
		double t = cv::getTickCount() - _counter._last;
		_counter._last = t;
		_counter._total += t;
		return _counter._last*1000./_tickFrequency;
	}
	void reset() {
		_counter._total = 0;
	}
	double last() {
		return _counter._last*1000./_tickFrequency;
	}
	double total() {
		return _counter._total*1000./_tickFrequency;
	}

	void start (const std::string& s) {
		_counters[s]._last = (double)cv::getTickCount();
	}
	double stop (const std::string& s) {
		elapsed& e = _counters[s];
		double t = cv::getTickCount() - e._last;
		e._last = t;
		e._total += t;
		return e._last*1000./_tickFrequency;
	}
	void reset (const std::string& s) {
		_counters[s]._total = 0;
	}
	double last (const std::string& s) {
		return _counters[s]._last*1000./_tickFrequency;
	}
	double total (const std::string& s) {
		return _counters[s]._total*1000./_tickFrequency;
	}

private:
	double _tickFrequency;
	elapsed _counter;
	std::map<std::string,elapsed> _counters;
};