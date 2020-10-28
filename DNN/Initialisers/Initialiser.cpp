//#include <stdexcept>
//#include <string>
//#include <iostream>
//#include <sstream>
//#include <math.h>
//#include "Initialiser.h"
//#include "..\..\Models\Vector.h"
//#include "..\..\Models\Matrix.h"
//#include "..\..\Models\Exceptions.h"
//
//Initialiser::Initialiser(int inputs, int outputs, bool uniform) 
//	: inputs(inputs), outputs(outputs), uniform(uniform) {}
//
//Matrix* Initialiser::createWeights() 
//{
//	return create(inputs, outputs, uniform);
//}
//
//Matrix* Initialiser::createBiases()
//{
//	return create(inputs, 1, uniform);
//}
//
//Matrix* Initialiser::create(int inputs, int outputs, bool uniform)
//{
//	return new Matrix(inputs, outputs);	// zeros for now
//}