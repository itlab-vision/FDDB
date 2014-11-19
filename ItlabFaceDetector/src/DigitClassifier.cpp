#include "DigitClassifier.hpp"
#include <iostream>

extern "C" {
	#include "lua.hpp"
}

using namespace cv;
using namespace std;

void report_errors(lua_State *L, int status)
{
  if ( status!=0 ) {
    std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1); // remove error message
  }
}

Result DigitClassifier::Classify(const Mat& img) {
	lua_State *L = lua_open();

    luaL_openlibs(L);

    const char *file = "/home/artem/projects/itlab/itlab-vision-faces-detection/ItlabFaceDetector/scripts/file.lua";

    int s = luaL_dofile(L, file);
    if (s != 0) report_errors(L, s);

    lua_getglobal(L, "main");

    // Push data
    lua_newtable(L);
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            lua_pushinteger(L, i * img.cols + j + 1);
            lua_pushinteger(L, img.at<uchar>(i, j));
            //std::cout << (int)img.at<uchar>(i, j) << " " ;
            lua_settable(L, -3);
        }
    }
    //cout << "s = " << s << endl;
    if ( s==0 ) {
      // execute Lua program
      s = lua_pcall(L, 1, 2, 0);
    } else report_errors(L, s);

    // result
    //std::cout << "File file.lua return " << std::endl;
    Result result;
    while (lua_gettop(L)) {
    	//std::cout << lua_tostring(L, -1) << std::endl;
        result.confidence = lua_tonumber(L, -1);
    	lua_pop(L, 1);
        result.label =  lua_tointeger(L, -1);
        lua_pop(L, 1);
    }
    //cout << result.label << " " << result.confidence << endl;
    lua_close(L);
	return result;
}
