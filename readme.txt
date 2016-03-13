Compute the weighted Kendall distance (no ties) in O(n lg n)
By F. Farnoud, July 2014

Gives the weighted Kendall distance between two rankings. 
Based on An Axiomatic Approach to Constructing Distances for Rank Comparison and Aggregation, F. Farnoud, and O. Milenkovic, IEEE Trans. Information Theory, Oct. 2014.

Use -h fol help.

NAME
        weightedkendall

DESCRIPTION
        Gives the weighted Kendall distance between two rankings.
        Based on An Axiomatic Approach to Constructing Distances
        for Rank Comparison and Aggregation, F. Farnoud,
        and O. Milenkovic, IEEE Trans. Information Theory, Oct. 2014.
USAGE 1:
        WeightedKendallDistance -f input-file
NOTES:
        With -f input, the first line is n (the length of the rankings), the second line is p1,
        the third line is p2, the fourth line is w.
