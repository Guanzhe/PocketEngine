//
//  FileReader.cpp
//  Android
//
//  Created by Jeppe Nielsen on 05/07/15.
//
//

#include "FileReader.hpp"
#include "WindowAndroid.hpp"
#include <android/asset_manager.h>

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))


using namespace Pocket;

std::string FileReader::GetFile(std::string localFile) {
    return "assets/" + localFile;
}

/*
unsigned char* FileReader::GetData(std::string localFile, size_t* length) {
    AAssetManager* mgr = (AAssetManager*)WindowAndroid::assetManager;
    
    if (!mgr) {
        LOGI("AAssetManager not found");
    }
    
    AAssetDir* dir = AAssetManager_openDir(mgr, "");
    
    while (true) {
        const char* nextFile = AAssetDir_getNextFileName(dir);
        if (!nextFile) break;
        LOGI("Available asset = %s", nextFile);
    }
    AAssetDir_close(dir);
    
    const char* filename = localFile.c_str();
    LOGI("Trying to load file : %s", filename);
    
    AAsset* asset = AAssetManager_open(mgr, filename, AASSET_MODE_BUFFER);
    if (!asset) {
        LOGI("Asset not found %s", filename);
        return 0;
    }
    
     LOGI("GetData 1 : %s", filename);
    
    off_t size = AAsset_getLength(asset);
    
     LOGI("GetData 2 : size = %i", (int)size);
    
    unsigned char* buffer = (unsigned char*)AAsset_getBuffer(asset);
    unsigned char* output = (unsigned char*)malloc(size);
    memcpy(output, buffer, size);
    LOGI("GetData 3 : %s", filename);
    
    AAsset_close(asset);
    *length = (size_t)size;
    return output;
}
*/

std::string FileReader::GetWritablePath() {
    return "";
}
std::string FileReader::GetExecutablePath() {
    return "";
}
std::string FileReader::GetBundlePath() {
    return "";
}
std::string FileReader::GetBundleDir() {
    return "";
}