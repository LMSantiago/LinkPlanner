# ifndef SUPER_BLOCK_INTERFACE_H_
# define SUPER_BLOCK_INTERFACE_H_

class SuperBlockInterface : public Block {

	/* input parameters */


	/* state variables */


public:

	SuperBlockInterface() :Block() {};
	SuperBlockInterface(vector<Signal *> &inputSignals, vector<Signal *> &outputSignals);

	void initialize(void);

	bool runBlock(void);
		
};

#endif