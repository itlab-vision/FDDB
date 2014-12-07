#include "Classifier.hpp"

extern "C" {
	#include "lua.hpp"
}

class FacesClassifier : public Classifier {
public:
	FacesClassifier();

    virtual Result Classify(const cv::Mat& img);

    virtual ~FacesClassifier();
private:
	void reportLuaErrors(lua_State *L, int status);

	lua_State *L;
};