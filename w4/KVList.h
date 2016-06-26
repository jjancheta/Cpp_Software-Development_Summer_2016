// Author: ANCHETA, JESUS JR
// ID #: 017 433 152
// Email: jjancheta@myseneca.ca
// Workshop: 4


template <typename K, typename V, int N>
class KVList {
	K k[N];
	V v[N];
	int count;
public:
	KVList() :count(0) {}
	size_t size() const{ 
		return count;
	}
	
	const K& key(int i) const{ 
		return k[i];
	}
	
	const V& value(int i) const{ 
		return v[i];
	}                              
	
	KVList& add(const K& kk, const V& vv){
		if (count < N){
			k[count] = kk;
			v[count] = vv;
			count++;
		}
		return *this;
	}

	int find(const K& kk) const{
		int index = -1;
		for (int i = 0; i < count; i++){
			if (k[i] == kk){
				index = i;
			}
		}
		return index;
	}

	KVList& replace(int i, const K& kk, const V& vv){
		if (i < count){
			k[i] = kk;
			v[i] = vv;
		}
		return *this;
	}
};