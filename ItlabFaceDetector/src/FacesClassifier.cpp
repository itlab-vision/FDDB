#include "FacesClassifier.hpp"
#include <iostream>

using namespace cv;
using namespace std;

FacesClassifier::FacesClassifier()
{
    L = lua_open();
    luaL_openlibs(L);

    const char *filename = "/scripts/faces.lua";
    int s = luaL_dofile (L, filename);
    if (s != 0) reportLuaErrors(L, s);

    lua_getglobal(L, "loadNetModel");
    lua_pushstring(L, "/net/CNN-face-preproc.net");
    s = lua_pcall(L, 1, 0, 0);
    if (s != 0) reportLuaErrors(L, s);
}

FacesClassifier::~FacesClassifier()
{
    lua_close(L);
}

void FacesClassifier::reportLuaErrors(lua_State *L, int status)
{
    if ( status!=0 ) 
    {
        cerr << "-- " << lua_tostring(L, -1) << endl;
        lua_pop(L, 1);
    }
}

Result FacesClassifier::Classify(const Mat& img) 
{    
    lua_getglobal(L, "predict");
    // Push data
    lua_newtable(L);
    int countChannel = 3;
    int countPixels = img.cols * img.rows;
    //cout << "asd" << img.cols << " " << img.rows << endl;
    //for (int k = 0; k < countChannel; ++k)
    //{
    //    for (int i = 0; i < img.rows; ++i) 
    //    {
    //        for (int j = 0; j < img.cols; ++j) 
    //        {
    //            lua_pushinteger(L, k * countPixels + i * img.cols + j + 1);
    //            lua_pushinteger(L, img.at<Vec3b>(i, j)[2-k]);
    //            lua_settable(L, -3);
    //        }
    //    }
    //}
    for (int k = 0; k < countChannel; ++k)
    {
        for (int i = 0; i < img.rows; ++i) 
        {
            for (int j = 0; j < img.cols; ++j) 
            {
                lua_pushinteger(L, k * countPixels + i * img.cols + j + 1);
                lua_pushinteger(L, img.at<Vec3b>(i, j)[2-k]);
                lua_settable(L, -3);
            }
        }
    }
    //cout << "asdasd" << flush;
    //call function
    int s = lua_pcall(L, 1, 2, 0);
    if (s != 0) reportLuaErrors(L, s);

    Result result;
    while (lua_gettop(L)) {
        //result.confidence2 = lua_tonumber(L, -1);
        //lua_pop(L, 1);
        result.confidence = lua_tonumber(L, -1);
    	lua_pop(L, 1);
        result.label =  lua_tointeger(L, -1);
        lua_pop(L, 1);
    }

	return result;
}
