#include "Classifier.hpp"

extern "C" {
	#include "lua.hpp"
}

class DigitClassifier : public Classifier {
public:
	DigitClassifier();

    virtual Result Classify(cv::Mat& img);

    virtual ~DigitClassifier();
private:
	void reportLuaErrors(lua_State *L, int status);

	lua_State *L;
};