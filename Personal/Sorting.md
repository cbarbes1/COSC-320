
### Fundamental Sorting Algorithms (slow)
- Bubble sort
- Insertion sort
- Selection sort

## nlgn sorting
### QuickSort slow on occasion
`The fundamental idea is using binary search like algorithm`

```
save i as the left value
save j as the right value
get the mid point between the two numbers

save the number at the center as the pivot
loop while i is less than or equal to j
each loop loop while number at i is less than pivot iterate i if true
each loop loop while number at j is greater than pivot iterate j if true
if the i is less than or equal to j then swap the numbers and iterate the counts

after the loop terminates 
check if the left side is less than j
then recursively call the function from left to j

check if the i is less than the right 
then recursively call the funtion from i to right
```

```c++

template<class T>
void quickSort(T A[i], int size){
	quickSort(A, 0, size-1);
}
template<class T>
void quickSort(T A[], int left, int right)
	int i = left;
	int j = right;
	int mid = (left + right)/2;

	T pivot = A[mid];

	while( i <= j){
		while(A[i] < pivot)
			i++;

		while(A[j] > pivot)
			j--;

		if(i <= j){
			T tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
			i++;
			j--;
		}
	}

	if(left < j)
		quickSort(A, left, j);

	if(i < right)
		quickSort(A, left, i);
}
```

### Merge sort
divide the array into subarrays and then merge back together

```c++
// setup function
template<class T>
void mergeSort(T A[], int size){
	T *temp = new T[size];
	mergeSort(A, temp, 0, size-1);
	delete[] temp;
}

// recursive function
template<class T>
void mergeSort(T A[], T temp[], int start, int end){
	if(start < end){
		int mid = (start+end)/2;
		mergeSort(A, temp, start, mid);
		mergeSort(A, temp, mid+1, end);
		merge(A, temp, start, mid+1, end);
	}
}

// merging two array function
template<class T>
void merge(T A[], T temp[], int startA, int startB, int end){
	int aptr = startA;
	int bptr = startB;
	int i = startA;

	while(aptr < startB && bptr <= end){
		if (A[aptr]<A[bptr])
			temp[i++] = A[aptr++];
		else
			temp[i++] = A[bptr++];
	}

	while(aptr < startB)
		Temp[i++] = A[aptr++];

	while(bptr <= end)
		Temp[i++] = A[bptr++];

	for(i = startA; i<= end; i++)
		A[i] = Temp[i];
	
}
```
## Non comparison sorts with more restriction
### Comb Sort
```c++
template<class T>
void combsort(T data[], const int n){
	 int step = n, j, k;
	 //phase 1
	 while((step=int(step/1.3))>1)
		 for(j = n-1, j>= step; j++){
			 k = j-step;
			 if(data[j]<data[k])
				 swap(data[j], data[k]);
		 }

	// phase 2
	bool again = true;
	for(int i = 0; i<n-1 && again; i++)
		 for(j = n-1, again = false; j>i; --j)
			if(data[j]<data[j-1]){
				swap(data[j], data[j-1]);
				again = true;
			}
}
```

### Shell sort


### heap sort


### radix sort


### count sort

### bucket sort

Data Structures And Algorithms