// Compute the weighted Kendall distance (no ties) in O(n lg n)
// By F. Farnoud, July 2914

// Gives the weighted Kendall distance between two rankings. 
// Based on An Axiomatic Approach to Constructing Distances for Rank Comparison and Aggregation,
// F. Farnoud, and O. Milenkovic, IEEE Trans. Information Theory, vol. 60, pp. 6417–6439, Oct. 2014.

#ifndef ____weightedkendall__
#define ____weightedkendall__

double weightedkendall(const int *, const double *,const int );
double weightedkendall(const int *, const int *, const double *,const int );
double dist(const int *, const int *, const double *,const int );
int *getInv(const int *, const int);
int *permMultiply(const int *, const int *, const int);
void mergeAndCount(int *, int *, const int, const int);
void mergeSortAndCount(const int *p, int *invCount, const int n);

double distSlow(const int *, const int *, const double *,const int );
int find(const int *, const int, const int );


#endif /* defined(____weightedkendall__) */