#ifndef HOD_H
#define HOD_H
#include "Teacher.h"

class HOD : public Teacher
{
private:


public:
	HOD ();
	HOD (int, const char*);
	HOD (const char*, int&, const char*);
	HOD (const HOD&);
	~HOD ();
};

#endif