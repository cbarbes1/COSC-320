/************************************************************************
 * Author: Cole Barbes and Harrison Colborne
 * Creation Date: 8/30/23
 * Last Update: 8/30/23
 ************************************************************************/
#include <iostream>
#include <chrono>


using namespace std::chrono;
using namespace std;

// templated function to swap 2 values in an array
template<class t>
void swap(t *, int, int);

// templated function to sort an array
template<class t>
void Sort(t, int);

// templated 
template<class t>
bool Sorted(t *, int n);

int main(){

	int ArrSize = 0;

	cout<<"Please input the size of the array "<<endl;
	cin>>ArrSize;

	int *randArray = new int[ArrSize];

	for(int i = 0; i<ArrSize; i++){
		randArray[i] = (rand()%2001)-1000;
	}
         
	auto start = high_resolution_clock::now();
	// Process to be timed.
	Sort(randArray, ArrSize);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time to sort: " << duration.count() / 1000000.0 << " seconds" << endl;

	if(!Sorted(randArray, ArrSize)){
		cout<<"Not Sorted"<<endl;
	}
	else 
	{
		cout<< "Sorted"<<endl;
	}
	/*
	high_resolution_clock::time_point start = high_resolution_clock::now();
	// Process to be timed.
	high_resolution_clock::time_point stop = high_resolution_clock::now();
	duration<double> duration = duration_cast<microseconds>(stop - start);
	cout << "Time to sort: " << duration.count() / 1000000.0 << " seconds" << endl;
	*/
	delete [] randArray;

	return 0;
}

template<class t>
void swap(t *arr, int n1, int n2){
	t temp = arr[n1];
	arr[n1] = arr[n2];
	arr[n2] = temp;
}

template<class t>
void Sort(t arr, int n){
	int i, minIdx = 0;
	
	for(i = 0; i<n; i++){

		minIdx = i;
		for(int j = i; j<n; j++){
			if(arr[j] < arr[minIdx]){
				minIdx = j;
			}
		}
		if(minIdx != i){
			swap(arr, i, minIdx);
		}

	}
}

template<class t>
bool Sorted(t *arr, int n){

	bool checker = true;
	for(int i = 0; i<n-1; i++){
		if(arr[i] > arr[i+1])
			checker = false;
	}

	return checker;
}

