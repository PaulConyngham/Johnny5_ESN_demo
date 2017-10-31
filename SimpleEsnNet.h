/*
 *  SimpleEsnNet.h
 *  esn-network
 *
 *  Created by rwebb on 18/09/08.
 *  Copyright 2008 University of Canterbury. All rights reserved.
 *
 */

#include "Misc.h" 
#include "Random.h"
#include <Math.h>
#include <vector>

using namespace std;

template< uint numIn = 2, uint numOut = 2, uint numNeurons = 40, class Value = float >
class Esn{
public:
	Esn(Value learningRate_0 = 0.200, Value ringStrength = 0.95) : ringStrength(ringStrength), learningRate(learningRate_0){	
		learningRate /= Value(numNeurons);
		memset(esnState, 0, sizeof(esnState));
		memset(inWeights, 0, sizeof(inWeights));
		memset(outWeights, 0, sizeof(outWeights));
		memset(output, 0, sizeof(output));
		memset(input, 0, sizeof(input));
		// inputs
		loop(inIndex, 0, numIn){
			loop(i, 0, numNeurons){
				inWeights[inIndex][i] = (inIndex & 1) == (i & 1); // 0.4 * (2.0 * R().Float() - 1);
			}
		}
		RandomSource r(ringStrength * 10000);
		loop(inIndex, 0, numIn){
			if(inIndex == 0){
				loop(i, 0, numNeurons){
					inWeights[inIndex][i] = 2.0 * r.Float() - 1;
				}
			}
			else{
				loop(i, 0, numNeurons){
					int index = (i + inIndex) % numNeurons;
					inWeights[inIndex][i] = inWeights[0][index];
				}
			}
		}
		loop(i, 0, numNeurons){
			shortcut[i] = 1 - (2.0*r.Float() - 1) * (2.0*r.Float() - 1);
			shortcutIndex[i] = r.U32() % numNeurons;
		}
	}
	
	uint NumInputs() const{ return numIn; }
	uint NumOutputs() const{ return numOut; }
	
	void Input(uint inIndex, Value value){
		Assert(inIndex < numIn);
		input[inIndex] = value;
	}
	
	void Update(){
		SaveTrainingState();
		// ring transfer
		loop(i, 0, numNeurons){
			Ring(i) = Ring(i) + shortcut[i]*Ring(shortcutIndex[i]) + 0.5 * Ring((i + 1) % numNeurons);
		}
		// inputs
		loop(inIndex, 0, numIn){
			loop(i, 0, numNeurons){
				Ring(i) += inWeights[inIndex][i] * input[inIndex];
			}
		}
		loop(i, 0, numIn){
			esnState[i] = input[i];
		}
		loop(i, 0, numOut){
			esnState[i + numIn] = output[i];
		}
		loop(i, 0, numNeurons){
			Ring(i) = tanh(Ring(i));
		}
		// output
		loop(outIndex, 0, numOut){
			output[outIndex] = 0;
			loop(i, 0, numNeurons + numIn + numOut){
				output[outIndex] += outWeights[outIndex][i] * esnState[i];
			}
			output[outIndex] = tanh(output[outIndex]);
		}
	}
	
	Value Output(uint outIndex) const{
		Assert(outIndex < numOut);
		return output[outIndex];
	}
	
	void SavePrevious(){ }
	
	Value TrainPrevious(uint outIndex, Value target, Value learningMultiple = 1.0){
		Assert(outIndex < numOut);
		Value result = output_prev[outIndex] - target;

		Assert(output_prev[outIndex] < 1 && output_prev[outIndex] > -1);
		Assert(target < 1 && target > -1);
		Value linearErr = atanh(output_prev[outIndex]) - atanh(target);
		//Value linearErr = output_prev[outIndex] - target;
		loop(i, 0, numNeurons + numIn + numOut){
			outWeights[outIndex][i] -= learningMultiple * learningRate * linearErr * esnState_prev[i];
		}
		
		return result;
	}
	
	void PrintWeights() const{
		cout << "Input:\n";
		loop(inIndex, 0, numIn){
			float sum = 0;
			cout << inIndex << ": ";
			loop(i, 0, numNeurons){
				cout << inWeights[inIndex][i] << ", ";
				sum += inWeights[inIndex][i];
			}
			cout << endl << "avg: " << sum/numNeurons << endl;
		}
		cout << "Output:\n";
		loop(outIndex, 0, numOut){
			cout << outIndex << ": ";
			loop(i, 0, numNeurons + numIn + numOut){
				cout << outWeights[outIndex][i] << ", ";
			}
			cout << endl;
		}		
	}

private:
	Value esnState[numNeurons + numIn + numOut];
	Value inWeights[numIn][numNeurons];
	Value outWeights[numOut][numNeurons + numIn + numOut];
	Value ringStrength;
	Value output[numOut];
	Value input[numIn];
	
	Value shortcut[numNeurons];
	uint shortcutIndex[numNeurons];

	Value learningRate;
	Value esnState_prev[numNeurons + numIn + numOut];
	Value output_prev[numOut];
	
	const Value &Ring(uint index) const{
		uint realIndex = index + numIn + numOut;
		//Confirm(realIndex < numNeurons + numIn + numOut);
		return esnState[realIndex];
	}

	Value &Ring(uint index){
		uint realIndex = index + numIn + numOut;
		//Confirm(realIndex < numNeurons + numIn + numOut);
		return esnState[realIndex];
	}

	void SaveTrainingState(){
		memcpy(esnState_prev, esnState, sizeof(esnState_prev));
		memcpy(output_prev, output, sizeof(output_prev));
	}
};

