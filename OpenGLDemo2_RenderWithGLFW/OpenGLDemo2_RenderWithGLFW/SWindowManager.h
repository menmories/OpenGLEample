
#ifndef __SCARAB_WINDOW_MANAGER_H__
#define __SCARAB_WINDOW_MANAGER_H__

#include "SWindowBase.h"

class SWindowManager
{
public:
	SWindowManager();
	~SWindowManager();
public:
	bool SCreateWindow(SWindowBase** window);
protected:

};

#endif	//__SCARAB_WINDOW_MANAGER_H__