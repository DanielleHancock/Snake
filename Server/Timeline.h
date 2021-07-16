#pragma once
#include <mutex>

class Timeline
{
protected:
	std::mutex _mutex;
	float _tic_size; // how many units of anchor time per 1 unit of this timeline

public:
	Timeline() { _tic_size = 1; };
	virtual int getTime() { return 0; };
	void changeTicSize(float t) {
		std::unique_lock<std::mutex> cv_lock(this->_mutex);
		_tic_size = t;
		//std::cout << "Tic size is now " << t << std::endl;
	};
	float getTicSize() {
		std::unique_lock<std::mutex> cv_lock(this->_mutex);
		return _tic_size;
	}
};

