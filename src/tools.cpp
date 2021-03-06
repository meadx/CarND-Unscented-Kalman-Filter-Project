#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  VectorXd rmse(4);
	rmse << 0, 0, 0, 0;

	//  the estimation vector size should not be zero
	if (estimations.size() == 0) {
		cout << "Error: estimation vector size is zero in CalculateRMSE()";
		return rmse;
	}

	//  the estimation vector size should equal ground truth vector size
	if (estimations.size() != ground_truth.size()) {
		cout << "Error: estimation vector size is not equal ground truth vector size in CalculateRMSE()";
		return rmse;
	}

	//accumulate squared residuals
	for (unsigned int i = 0; i < estimations.size(); ++i) {
		
		VectorXd residual = estimations[i] - ground_truth[i];

		//coefficient-wise multiplication
		residual = residual.array()*residual.array();
		rmse += residual;
	}

	//calculate the mean
	rmse /= estimations.size();

	//calculate the squared root
	rmse = rmse.array().sqrt();

	//return the result
	return rmse;
}
