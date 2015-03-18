#include "Classifier.hpp"

extern "C" {
	#include "lua.hpp"
	#include "luaT.h"
	#include "TH/TH.h"
}

class FacesClassifier : public Classifier {
public:
	FacesClassifier();

    virtual Result Classify(cv::Mat& img);

    virtual ~FacesClassifier();
private:
	void reportLuaErrors(lua_State *L, int status);

	lua_State *L;
};