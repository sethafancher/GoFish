#include <string>
using namespace std;

class player {
public:
	virtual const std::string& get_name() const = 0;
private:
};
