// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 8

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <algorithm>


namespace w8{
	template <typename T>
	class DataTable{
		std::vector <T> X;
		std::vector <T> Y;
		int FW_;
		int ND_;
	public:
		DataTable(std::ifstream& file, int fw, int nd) : FW_(fw), ND_(nd){
			if (file.is_open()){
				T x, y;
				while (file >> x >> y){
					X.push_back(x);
					Y.push_back(y);
				}
			}
			else{
				std::cerr << "File can not be opened." << std::endl;
				exit(3);
			}
			file.close();
		}

		T mean() const{
			return std::accumulate(Y.begin(), Y.end(), (T)0) / Y.size();
		}

		T sigma() const{
			T sigmaTemp = 0;
			T mean_ = mean();
			for (auto e : Y){
				sigmaTemp += pow(e - mean_ , 2);
			}
			if (Y.size() - 1){
				sigmaTemp = sqrt(sigmaTemp / (Y.size() - 1));
			}
			else {
				std::cout << "Cannot divide by 0." << std::endl;
				exit(4);
			}
			return sigmaTemp;
		}

		T median() const{
			T medianTemp =0;
			std::vector <T> Ycopy (Y);
			std::sort(Ycopy.begin(), Ycopy.end());
			int size_ = Ycopy.size();       
	
			if (!(size_ + 1 % 2) ){                  //if # of data is odd - exact median
				int index = ((size_ + 1) / 2) - 1;
				medianTemp = Ycopy.at(index);
			}
			else{                                   
				int index = ((size_ + 1) / 2) - 1;  // if # of data is odd - add 2 medians / 2 
				medianTemp = (Ycopy.at(index) + Ycopy.at(index+1)) / 2;
			}
			return medianTemp;
		}


		void regression(T& slope, T& y_intercept) const{
			T val1 = Y.size() * std::inner_product(X.begin(), X.end(), Y.begin(), (T)0);
			T val2 = std::accumulate(X.begin(), X.end(), (T)0) * 
				std::accumulate(Y.begin(), Y.end(), (T)0);
			T val3 = val1 - val2;

			T val4 = Y.size() * std::accumulate(X.begin(), X.end(), (T)0,
				[](T runningTotal, T current){
				return runningTotal + pow(current, 2);
			}
			);
			T val5 = pow(std::accumulate(X.begin(), X.end(), (T)0), 2);

			T val6 = val4 - val5;
			slope = val3 / val6;

			y_intercept = (std::accumulate(Y.begin(), Y.end(), (T)0) -
				(slope * std::accumulate(X.begin(), X.end(), (T)0))) / Y.size();
		}

		void display(std::ostream& os) const {
			os << std::setw(FW_) << "x" << std::setw(FW_) << "y" << std::endl;
			for (int i = 0; i < (int)X.size() && i < (int)Y.size(); i++){
				os << std::fixed << std::setprecision(ND_);
				os << std::setw(FW_) << X[i]
					<< std::setw(FW_) << Y[i] << std::endl;
			}

		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const DataTable<T>& out){
		out.display(os);
		return os;
	}

}