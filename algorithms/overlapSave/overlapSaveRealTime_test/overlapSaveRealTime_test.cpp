# include "netxpto.h"
# include "binary_source.h"
# include "m_qam_mapper.h"	
# include "discrete_to_continuous_time.h"
# include "sink.h"
# include "fork.h"
# include "overlap_save_20180208.h"
# include "pulse_shaper.h"
# include "pulse_shaper_fd_20180306.h"

int main() {

	// #######################################################################
	// ###################### System Input Parameters ########################
	// #######################################################################

	BinarySourceMode sourceMode{ PseudoRandom };
	int patternLength{ 5 };
	double bitPeriod{ 1.0 / 2.5e9 };
	vector<t_iqValues> iqAmplitudes{ { { 0,0 },{ 1,0 },{ 2,0 },{ 3,0 } } };
	int numberOfBits{ 1000 };		  // -1 will generate long bit sequence.
	int numberOfSamplesPerSymbol{ 16 };
	double BTs{ 0.25 };
	int impulseResponseTimeLength{ 16 };
	int transferFunctionFrequencyLength{ 16 };
	
	// ########################################################################
	// ################ Signals Declaration and Inicialization ################
	// ########################################################################

	Binary S1{ "S1.sgn" };							 // Binary Sequence
	TimeDiscreteAmplitudeDiscreteReal S2{"S2.sgn"};	 // MPAM Signal
	TimeDiscreteAmplitudeDiscreteReal S2b{"S2b.sgn"};// Not used (Q signal)
	TimeContinuousAmplitudeDiscreteReal S3{"S3.sgn"};// Discrete to continious time
	TimeContinuousAmplitudeContinuousReal S4{"S4.sgn"};// Fork
	TimeContinuousAmplitudeContinuousReal S5{"S5.sgn"};// Fork
	TimeContinuousAmplitudeContinuousReal S6{"S6.sgn"};// Pulse Shaper TIME
	TimeContinuousAmplitudeContinuousReal S7{"S7.sgn"};// Pulse Shaper FREQUENCY

	// #########################################################################
	// ############### Blocks Declaration and Inicialization ###################
	// #########################################################################

	BinarySource B1{ vector<Signal*> {}, vector<Signal*> { &S1} };
	B1.setMode(sourceMode);
	B1.setPatternLength(patternLength);
	B1.setBitPeriod(bitPeriod);
	B1.setNumberOfBits(numberOfBits);

	MQamMapper B2{ vector<Signal*> { &S1 }, vector<Signal*> { &S2, &S2b } };
	B2.setIqAmplitudes(iqAmplitudes);

	Sink B3{ vector<Signal*> { &S2b }, vector<Signal*> {} };

	DiscreteToContinuousTime B4{ vector<Signal*> { &S2 }, vector<Signal*> { &S3 } };
	B4.setNumberOfSamplesPerSymbol(numberOfSamplesPerSymbol);

	Fork B5{ vector<Signal*> { &S3 }, vector<Signal*> { &S4, &S5 } };

	PulseShaper B6{ vector<Signal*> { &S4 }, vector<Signal*> { &S6 } };
	B6.setBTs(BTs);
	B6.setImpulseResponseTimeLength(impulseResponseTimeLength);
	B6.setSeeBeginningOfImpulseResponse(false);
	B6.setFilterType(Gaussian);

	PulseShaperFd B7{ vector<Signal*> { &S5 }, vector<Signal*> { &S7 } };
	B7.setBTs(BTs);
	B7.setTransferFunctionFrequencyLength(transferFunctionFrequencyLength);
	B7.setSeeBeginningOfTransferFunction(false);
	B7.setFilterType(GaussianTF);

	Sink B8{ vector<Signal*> { &S6 }, vector<Signal*> {} };
	Sink B9{ vector<Signal*> { &S7 }, vector<Signal*> {} };

	// ############################################################################
	// ################ System Declaration and Inicialization #####################
	// ############################################################################

	System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B4, &B5, &B6, &B7, &B8, &B9} };

	// ############################################################################
	// ############################# System Run ###################################
	// ############################################################################

	MainSystem.run();
	cout << "\nExecution Finished, Please hit Enter to exit!";
	getchar();
	return 0;
}