#ifndef _FIELD_MANAGER_H_
#define _FIELD_MANAGER_H_

#include "gamedefs.h"

class FieldManagerC
{
public:
	static FieldManagerC	*CreateInstance();
	static FieldManagerC	*GetInstance() {return sInstance;};
	~FieldManagerC(){};

	FieldC* getFieldPtr();
	void init();
	void renderField();
	void shutdown();

	FieldC *border;

private:
	static FieldManagerC *sInstance;
	FieldManagerC(){};
};

#endif