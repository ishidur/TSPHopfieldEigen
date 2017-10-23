// TSPHopfieldEigen.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "main.h"

#include <iostream>
#include "parameters.h"
#include "Data.h"
#include "Eigen/Core"
Data data;

auto sigm = [](const double input)
{
	return 1.0 / (1 + exp(-input));
};

Eigen::VectorXd sigmoid(Eigen::VectorXd inputs)
{
	return inputs.unaryExpr(sigm);
}

Eigen::VectorXd calcDeltaU(const Eigen::VectorXd& state, const Eigen::VectorXd& innerVal)
{
	const double tau = 1.0;
	Eigen::VectorXd delta = (-innerVal / tau + data.weight_mtrx * state + data.biases) * DELTA_T;
	return delta;
}

void run()
{
	int n = cities.size() * cities.size();
	Eigen::VectorXd innerVal = NOISE * Eigen::VectorXd::Random(n);
	Eigen::VectorXd result = sigmoid(innerVal);
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

	std::cout << result << std::endl;
}

int main(int argc, char* argv[])
{
	data.load();
	run();
	return 0;
}