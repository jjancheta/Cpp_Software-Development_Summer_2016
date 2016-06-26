// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 4

#include <iostream>

template <typename K, typename V, int N>
class KVList {
	K* kkey[N];
	V* vvalue[N];
	/*struct{
		K kkey;
		V vvalue;
	}data[N];*/
	int count;
public:
	KVList() {
		count = 0; 
		*kkey = nullptr;
		*vvalue = nullptr;
	}
	
	int size() const{
		return count;
	}
	
	const K& key(int i) const {
		if (i < count)
			//return data[i].kkey;
			return *kkey[i];
	}
	
	const V& value(int i) const{
		if (i < count)
			//return data[i].vvalue;
			return *vvalue[i];
	}
	
	KVList& add(const K& kk, const V& vv){
		if (count < N){
			/*data[count].kkey = kk;
			data[count].vvalue = vv;*/
			kkey[count] = new K;
			*kkey[count] = kk;
			vvalue[count] = new V;
			*vvalue[count] = vv;
			++count;
		}
		return *this;
	}

	int find(const K& k) const{
		int index = 0;
		for (int i = 0; i < count; i++){
			if (*kkey[i] == k){
				index = i;
			}
		}
		return index;
	}

	KVList& replace(int i, const K& k, const V& v){
		if (i < count){
			*kkey[i] = k;
			*vvalue[i] = v;
		}
		return *this;
	}

	~KVList(){
		std::cout << "Deleting....." << std::endl;
		for (int i = 0; i < count; i++){
			delete kkey[i];
			delete vvalue[i];
		}
	}
};