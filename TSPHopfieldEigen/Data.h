#pragma once
#include "parameters.h"
#include "stdafx.h"

class Data
{
public:
	Eigen::MatrixXd weight_mtrx;
	Eigen::VectorXd biases;
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	Data();
	void load();
};