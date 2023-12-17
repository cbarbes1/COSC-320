### Definitions
**Definition 1:** f(n) is O(g(n)) if there exists numbers c and N such that f(n)<=cg(n) for all n>=N

**Definition 2:** The function f(n) is big-Omega(g(n)) if there exists numbers c and N such that f(n) >=cg(n) for all n>=N
**Definition 3:** The function f(n) is big-theta(g(n)) if there exists numbers c1, c2 and N such that c1g(n)<=f(n)<=c2g(n) for all n>=N

**Properties of Big-O**


**Proof of big-Oh**
```
Prove that f(n) = 2^sqrt(lg(n)) is O(n^a) for any positive number a 

if f(n) is O(g(n)) if there exists numbers c and N such that f(n)<=cg(n) for all N>=N

if 2^sqrt(lg(n)) is O(n^a) ... 2^sqrt(lg(n)) <= cn^a 
log2(2^sqrt(lg(n))) <= log2(cn^a)
sqrt(lg(n)) <= a\*log2(cn)
lg(n) <= a^2 \* (log2(cn))^2
lg(n) <= a^2 \* cn
is in fact less than a^2\*cn for any positive number a

```
### Program Analysis
This section was to analyze programs to find a closed expression for each
for example 
```c++
/* simple sum of numbers program */
for (i = sum = 0; i<n; i++)
	sum += a[i]
```

We first see that this loop will run n times to find the sum of numbers in the array
Additionally we see that i and sum are initialized once and two assignments occur in every iteration which are i and the sum.
We can now express this as 2+2n iterations which is O(n)

**The complexity can get more complex with nested loops**
```c++
for (i = 0; i < n; i++){
	for(j = 1, sum = a[0]; j<=i; j++)
		sum += a[j];
	cout<<"sum for subarray 0 through "<<i<<" is "<<sum<<endl;
}
```

As we begin, i is initialized to 0 and assigned each time then we see that this outer loop will run atmost n times.
The inner loop has 2 initializations and two assignments then will run i times each iteration



Data Structures And Algorithms