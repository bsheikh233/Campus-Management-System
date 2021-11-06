#ifndef ASSESSMENT_H
#define ASSESSMENT_H

class Assessment
{
private:
	char *name;
	float totalMarks;
	float obtainedMarks;
	float weightage;
	float obtainedWeightage;

public:
	Assessment (const char*, float, float, float, float, int&, int&);
	Assessment ();
	Assessment (int&, int&);
	~Assessment ();
	void showAssesment () const;
	char* getName () const;
	float getTotalMarks () const;
	float getObtainedMarks () const;
	float getWeightage () const;
	float getObtainedWeightage () const;
};


#endif