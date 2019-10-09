#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;



long long int phi(long long int n){			//Euler Totient Function
	long long int result=n,i;			// For finding number of co-primes less than n . T->O(sqrt(n))
	
	for(i=2;i*i<=n;i++){
		if(n%i==0){
			while(n%i==0)
				n /=i;
			result -= result/i;
			
		}
	}
	
	if(n>1)
		result -= result/n;
	return result;
}



int main(){
	long int t;
	cin>>t;
	while(t--){
		long long int n;
		cin>>n;
		cout<<phi(n)<<endl;
	}
}
