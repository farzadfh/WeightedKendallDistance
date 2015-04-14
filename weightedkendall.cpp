// Compute the weighted Kendall distance (no ties) in O(n lg n)
// By F. Farnoud, July 2914

// Gives the weighted Kendall distance between two rankings. 
// Based on An Axiomatic Approach to Constructing Distances for Rank Comparison and Aggregation,
// F. Farnoud, and O. Milenkovic, IEEE Trans. Information Theory, vol. 60, pp. 6417–6439, Oct. 2014.

#include "weightedkendall.h"
#include<iostream>
using namespace std;
#include <algorithm>	// std::random_shuffle
#include <cstdlib>      // std::rand, std::srand
#include <stdint.h>

double weightedkendall(const int * p, const double * w, const int n)
{
	int *id = new int[n];
	for (int i = 0; i<n; ++i) {id[i] = i;}
    return dist(p,id,w,n);
	delete id;
}

double weightedkendall(const int * p, const int * q, const double * w, const int n)
{
    // To do: p-value, correlation coefficient
    return dist(p,q,w,n);
}


double dist(const int *p, const int *q, const double *w, const int n)
// Compute the distance between p and q (of length n) according to w: O(n lg n)
{	double *W = new double[n]; 	// The sum weight function. w[1], w[2], ..., w[n-1]
    W[0] = 0;
    int i;
    for ( i = 1; i < n; ++i){
        W[i] = W[i-1] + w[i-1];
    }
    
    double d = 0;	// distance
    int L_newq_i;
    int *invp = getInv(p,n);
    int *newq = permMultiply(invp,q,n);
    int *invCount = new int[n];
    for (i = 0; i<n; ++i) invCount[i] = 0;
    
    mergeSortAndCount(newq, invCount, n);
    for ( i = 0; i<n; ++i){
        L_newq_i = (newq[i] + i + invCount[newq[i]]) / 2;
        d += ( 2.0 * W[L_newq_i] - W[i] - W[newq[i]]) / 2.0;
    }
    
    delete newq;
    delete invCount;
	delete W;
    delete invp;
    return d;
}

int *getInv(const int *p, const int n)
// compute the inverse of permutation p of length n
{
    int *inv = new int[n];
    for ( int i = 0; i<n; i++){
        if(p[i]>=n || p[i]<0){
			throw std::invalid_argument("Out of range. Elements of input should be between 0 and n-1.\n");
		}
		inv[p[i]] = i;
	}
    return inv;
}


int *permMultiply(const int *p, const int *s, const int n)
// multiply p and s: i --> p[s[i]]
{
    int *q = new int[n];
    for (int i = 0; i < n; i++){
        q[i] = p[s[i]];
    }
    return q;
}


void mergeSortAndCount_(int *, int *, const int);
void mergeSortAndCount(const int *p, int *invCount, const int n)
{
    int *p_copy = new int[n];
    for (int i = 0; i<n; ++i) p_copy[i] = p[i];
    mergeSortAndCount_(p_copy, invCount, n);
    delete p_copy;
    
}

void mergeSortAndCount_(int *p, int *invCount, const int n)
{
    if ( n == 1 ) return;
    mergeSortAndCount_(p, invCount, n/2);
    mergeSortAndCount_(p+n/2, invCount, n-n/2);
    mergeAndCount(p, invCount, n/2,n);
}

void mergeAndCount(int *p, int *invCount, const int n1, const int n2)
// merge two lists pn[0..n1-1] and p[n1..n2-1] and add to count the number of inversions for each element caused by merging
{
    int i1 = 0;
    int i2 = n1;
    int i = 0;
    int j;
    int *tmp = new int[n2];
    while ( (i1 < n1) && (i2 < n2) ){
        if ( p[i1] < p[i2] ) {
            j = p[i1];
            invCount[j] += i2 - n1;   // how many have we had from the second list
            i1++;
        } else {
            j = p[i2];
            invCount[j] += n1 - i1;	 // how many are left in the first list
            i2++;
        }
        tmp[i++] = j;
    }
    while (i1 < n1) {
        j = p[i1];
        invCount[j] += n2 - n1;   // how many have we had from the second list
        tmp[i] = j;
        i++; i1++;
    }
    while (i2 < n2) {
        j = p[i2];
        tmp[i] = j;
        i++; i2++;
    }
    for (int i = 0; i < n2; ++i)
        p[i] = tmp[i];
    delete tmp;
}


// Simple implementation for checking dist()
double distSlow(const int *p1, const int *p2, const double *w, const int n)
// Compute the distance between p1 and p2 (of length n) according to w: O(n^2)
{
    double d = 0;	// distance
    int *q = new int [n];	// copy of p2
    for (int i = 0; i<n; ++i){
        q[i] = p2[i];
    }
    
    for (int i = 0; i<n; ++i) {
        // starting from i=0, each p1[i] is pushed to its proper position
        int pos = find(q, p1[i], n);	// find current position of p1[i] in q
        for (int j = pos; j>i; j--) {	// push it to its correct position
            swap(q[j], q[j-1]);	// swap elements in positions j and j-1
            d = d + w[j-1];		// add the cost to distance
        }
    }
	delete q;
    return d;
}

int find(const int *a, const int v, const int n)
// Find element v in an array a of length n
{
    int i = 0;
    for ( ; i<n; i++) {
        if (a[i] == v)
            break;
    }
    return i;
}

