/************************************************************************
 * Author: Cole Barbes 
 * Creation Date: 9/03/23
 * Last Update: 9/03/23
 ************************************************************************/
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std::chrono;
using namespace std;

// templated function to swap 2 values in an array
template<class t>
void swap(t *, int, int);

// templated function to sort an array
template<class t>
void Sort(t *, int);

// templated function to check if an array is sorted
template<class t>
bool Sorted(t *, int n);

int main(){

	srand(time(0));
	int ArrSize = 0; // init the array size

	// take input from the user
	cout<<"Please input the size of the array "<<endl;
	cin>>ArrSize;

	// initialize the array dynamically
	double *randArray = new double[ArrSize];

	// loop through array and initialize all values to random number between [0, 1)
	for(int i = 0; i<ArrSize; i++){
		randArray[i] = (static_cast<double>(rand())/static_cast<double>(RAND_MAX));
	}

	// time a the sorting process
	auto start = high_resolution_clock::now();
	// Process to be timed.
	Sort(randArray, ArrSize);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time to sort: " << duration.count() / 1000000.0 << " seconds" << endl;

	if(!Sorted(randArray, ArrSize)){
		cout<<"Array is Not Sorted"<<endl;
	}
	else 
	{
		cout<< "Array is Sorted"<<endl;
	}	
	
	delete [] randArray;

	return 0;
}

/***************************************************************
*  Description: This function swaps 2 values in an array
*  Parameters: The array, The first index, The second index
***************************************************************/
template<class t>
void swap(t *arr, int n1, int n2){
	t temp = arr[n1];
	arr[n1] = arr[n2];
	arr[n2] = temp;
}

/**********************************************************************
 *  Description: This function sorts a given array in ascending order
 *  Parameters: the array and the size
 *********************************************************************/
template<class t>
void Sort(t *arr, int n){
	int i, minIdx = 0;
	
	for(i = 0; i<n; i++){

		minIdx = i; // set the target 
		for(int j = i; j<n; j++){
			if(arr[j] < arr[minIdx]){
				minIdx = j;// find the swap
			}
		}
		if(minIdx != i){ // complete the swap as long as the number is different
			swap(arr, i, minIdx);
		}

	}
}

/**********************************************************************
 * Description: This function Checks whether an array is sorted
 * Parameters: the array and the size
 **********************************************************************/
template<class t>
bool Sorted(t *arr, int n){

	bool checker = true;
	for(int i = 0; i<n-1; i++){
		if(arr[i] > arr[i+1])
			checker = false;
	}

	return checker;
}

