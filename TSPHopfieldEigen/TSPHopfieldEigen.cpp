// TSPHopfieldEigen.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <iostream>
#include "parameters.h"
#include "Data.h"
#include "Eigen/Core"
using namespace Eigen;

Data data;

auto relu = [](const double input)
{
	if (input + 0.5 > 1.0)
	{
		return 1.0;
	}
	else if (input + 0.5 < 0.0)
	{
		return 0.0;
	}
	return input + 0.5;
};

VectorXd sigmoid(VectorXd inputs)
{
	return inputs.unaryExpr(relu);
}

VectorXd calcDeltaU(const VectorXd& state)
{
	VectorXd delta = (data.weight_mtrx * state + data.biases) * DELTA_T;
	return delta;
}

void outputState(const VectorXd& state)
{
	for (int row = 0; row < cities.size(); ++row)
	{
		for (int col = 0; col < cities.size(); ++col)
		{
			int n = row * cities.size() + col;
			std::cout << state[n];
			std::cout << ",";
		}
		std::cout << std::endl;
	}
}

void run()
{
	int n = cities.size() * cities.size();
	VectorXd innerVal = NOISE * VectorXd::Random(n);
	VectorXd result = sigmoid(innerVal);
	float progress = 0.0;
	const double step = 1.0 / (RECALL_TIME - 1.0);

	for (int i = 0; i < RECALL_TIME; ++i)
	{
		//update innerVal
		innerVal += calcDeltaU(result);
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
