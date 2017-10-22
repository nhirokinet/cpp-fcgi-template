// Only mydaemon.cpp is allowed to include this file, exactly once.

#include <unordered_map>
#include <string>
#include <vector>

#include "Handler.h"

using namespace std;

class KVSHandler : public Handler {
public:
	KVSHandler() {}
	~KVSHandler() {}

protected:
	std::string read(const vector <string> & data) const {
		if (data.size() >= 1) {
			if (_db.count(data[0])) {
				return _db.at(data[0]);
			} else {
				return "";
			}
		}

		// error, not in production
		return "";
	}

	void write(const vector <string> & data) {
		if (data.size() >= 2) {
			_db[data[0]] = data[1];
		}
	}

private:
	unordered_map <string, string> _db;

};
