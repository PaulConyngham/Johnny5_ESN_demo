/*
 *  Misc.cpp
 *  shape
 *
 *  Created by Russell Webb on 3/02/06.
 *  Copyright 2006 UC. All rights reserved.
 *
 */

#include "Misc.h"

void do_assert_failed(const char *file, int line){
	fprintf(stderr, "Failure at %s : %i\n", file, line);
	throw 3;
}

#ifdef __APPLE__

#if NEED_APP_PATH

#include <Carbon/Carbon.h>

static char gAppPath[800] = "";
static char gResourcePath[800] = "";

static void SetAppPaths(){
	CFURLRef pluginRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
	CFStringRef macPath = CFURLCopyFileSystemPath(pluginRef, 
												  kCFURLPOSIXPathStyle);
	const char *pathPtr = CFStringGetCStringPtr(macPath, 
												CFStringGetSystemEncoding());
	//printf("Path = %s\n", pathPtr);
	strcpy(gAppPath, pathPtr);
	sprintf(gResourcePath, "%s%s", gAppPath, "/Contents/Resources");
	CFRelease(pluginRef);
	CFRelease(macPath);
}

const char *AppPath(){
	if(!gAppPath[0]){
		SetAppPaths();
	}
	return gAppPath;
}

#endif

#else

const char *AppPath(){
		return "";
}

#endif
