// TSPHopfieldEigen.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <iostream>
#include "parameters.h"
#include "Data.h"
#include "Eigen/Core"
using namespace Eigen;

Data data;

auto sigm = [](const double input)
{
	return 1.0 / (1 + exp(-input / U0));
};

VectorXd sigmoid(VectorXd inputs)
{
	return inputs.unaryExpr(sigm);
}


auto inverseActFunc = [](const double input)
{
	return 0.5 * U0 * log((1.0 + input) / (1.0 - input));
};

VectorXd inverseActivationFunc(const VectorXd& inputs)
{
	return inputs.unaryExpr(inverseActFunc);
}


VectorXd calcDeltaU(const VectorXd& state, const VectorXd& innerVal)
{
	const double tau = 1.0;
	VectorXd delta = (-innerVal / tau + data.weight_mtrx * state + data.biases) * DELTA_T;
	return delta;
}

void outputState(const VectorXd& state)
{
	for (int row = 0; row < cities.size(); ++row)
	{
		for (int col = 0; col < cities.size(); ++col)
		{
			int n = static_cast<int>(row * cities.size() + col);
			std::cout << state[n];
			std::cout << ",";
		}
		std::cout << std::endl;
	}
}

void run()
{
	int n = cities.size() * cities.size();
	VectorXd result = NOISE * VectorXd::Random(n) + VectorXd::Constant(n, 0.5);
	VectorXd innerVal = inverseActivationFunc(result);
	//	VectorXd innerVal = NOISE * VectorXd::Random(n);
	//	VectorXd result = sigmoid(innerVal);
	float progress = 0.0;
	const double step = 1.0 / (RECALL_TIME - 1.0);

	for (int i = 0; i < RECALL_TIME; ++i)
	{
		//update innerVal
		innerVal += calcDeltaU(result, innerVal);
		//update state from innerVal
		result = sigmoid(innerVal);
		int barWidth = 70;
		std::cout << "[";
		int pos = barWidth * progress;
		for (int i = 0; i < barWidth; ++i)
		{
			if (i < pos) std::cout << "=";
			else if (i == pos) std::cout << ">";
			else std::cout << " ";
		}
		std::cout << "] " << int(progress * 100.0) << " %\r";
		std::cout.flush();
		progress += step;
	}
	std::cout << std::endl;
	outputState(result);
}

int main(int argc, char* argv[])
{
	data.load();
	run();
	return 0;
}
