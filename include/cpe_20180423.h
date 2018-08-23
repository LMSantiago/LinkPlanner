# ifndef PROGRAM_INCLUDE_CPE_H_
# define PROGRAM_INCLUDE_CPE_H_


# include "netxpto_20180418.h"

# include <complex>
# include <random>
# include <vector>

class CPE : public Block {

	/* State Variables */


	/* Input Parameters */

	int nTaps{ 12};
	int nTestPhase{ 64 };
	double phiInt{ 3.14159265358979323846 / 2 };
	string methodType = "VV";
	double samplingPeriod{ 0.0 };
	double symbolPeriod{ 0.0 };

public:

	/* Methods */
	CPE() {};
	CPE(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setSamplingPeriod(double sPeriod) { samplingPeriod = sPeriod; }
	void setSymbolPeriod(double sPeriod) { symbolPeriod = sPeriod; }

	void setnTaps(int ntaps) { nTaps = ntaps; }
	double getnTaps() { return nTaps; }

	void setTestPhase(int nTphase) { nTestPhase = nTphase; }
	double getTestPhase() { return nTestPhase; }

	void setmethodType(string mType) { methodType = mType; }
	string getmethodType() { return methodType; }

};

#endif 
