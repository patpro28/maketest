#include <bits/stdc++.h>
#include "random.h"
#include "../params.h"

using namespace std;

const int MAXN = 1e5 + 10;
const int B = 316;		        // 1/2 of maximum answer for any query
const int L = 600;				// Size of block size of sqrt decomposition

// Question input parameters.
int n, m, a[MAXN];
// Frequency of frequency computation: [block x][block y][frequency_count]
// This is required to be stored will 2 * sqrt(N) only.
int cnt[MAXN / L + 1][MAXN / L + 1][2 * B + 1];
// For left to right processing: [block x][block y][index]
int dp1[MAXN / L + 1][MAXN / L + 1][2 * B + 1];
// For right to left processing: [block x][block y][index]
int dp2[MAXN / L + 1][MAXN / L + 1][2 * B + 1];
// store frequency of array A.
int cntA[MAXN];
// store frequency of frequency.
int cntCnt[MAXN];

map<int, int> compress;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    int n = gen.uniform<int>(1, 1e5);
    int m = gen.uniform<int>(1, 1e5);
    cout << n << " " << m << "\n";
	/*
	Scan the input asn compress the numbers so that they are int he range [1 .. n]
	and we don't need to use map to store the frequency. A normal array can be
	used for future purposes. This eliminates additional log(N) factor as well.
	Note that it can be done here as the frequency of elements matter not the 
	element itself.
	*/
    int val = gen.uniform<int>(1, 1e9);
    for (int i = 1; i <= n; ++i) {
        int e = gen.uniform<int>(-100, 100);
        val += e;
        if (val < 1) val = 1;
        if (val > 1e9) val = 1e9;
        cout << val << (i == n ? "\n" : " ");
        a[i] = val;
        compress[a[i]];
    }

	int tt = 1;
	for(auto &item : compress) {
	    item.second = tt++;
	}
	for(int i = 1; i <= n; i++) {
	    a[i] = compress[a[i]];
	}
	
	/*
	Pre-processing for blocks. Note that blocks are 0-indexed while the array is
	1-indexed in author solution. This is because the block number for a index
	"x" is calculated as "x/L", which essentially starts from 0.
	"r" denotes the maximum number of blocks.
	*/
	int r = n / L + 1;
	for(int i = 0; i < r; i++) {
		// Reset the frequency arrays.
		for(int j = 0; j < MAXN; j++) {
			cntA[j] = 0;
			cntCnt[j] = 0;
		}
		for(int j = i; j < r; j++) {
			/*
			Precompute the answer for given block first.
			The general idea is to remove previous contribution in frequency of
			 frequency table and then update with the new values found.
			*/
			for(int k = j * L; k < (j + 1) * L; k++) {
				if(k < 1 || k > n) continue;
				if(cntA[a[k]] != 0) {
					cntCnt[cntA[a[k]]]--;
				}
				cntA[a[k]]++;
				cntCnt[cntA[a[k]]]++;
				
			}
			/*
			Store the important frequency of frequencies i.e. below 2*sqrt(N)
			across 2 blocks, first starting at block[i] and second ending at
			block[j].
			*/
			for(int k = 1; k < 2 * B + 1; k++) {
				cnt[i][j][k] = cntCnt[k];
			}
			/*
			Store the frequency of number from starting position of block[i] to
			some position in block[j] or block[j-1] in left to right and right
			to left fashion in 2 different tables.
			*/
			for(int k = 1; k <= L; k++) {
				if(i * L - k > 0) {
					dp1[i][j][k] = cntA[a[i * L - k]];
				}
				if((j + 1) * L - 1 + k <= n) {
					dp2[i][j][k] = cntA[a[(j + 1) * L - 1 + k]];
				}
			}
		}
	}
	/*
	Clear the frequency tables.
	*/
	for(int i = 0; i < MAXN; i++) {
		cntCnt[i] = 0;
		cntA[i] = 0;
	}
	
	int prev_ans = 0;
	for(int i = 0; i < m; i++) {
		int l, r;
		l = gen.uniform<int>(1, n);
        r = gen.uniform<int>(l, n);
        l ^= prev_ans; r ^= prev_ans;
        cout << l << " " << r << "\n";
		l ^= prev_ans; r ^= prev_ans;
		int blockL = l / L, blockR = r / L;
		if(blockL == blockR || blockL + 1 == blockR) {
			/*
			Both index belong to same block or adjacent blocks. We can't use
			the block to block information here as no complete blocks are found.
			Since size of each block is upto sqrt(N) (The author choses bit more
			i.e. 600), a brute force solution can be applied here.
			*/
			for(int k = l; k <= r; k++) {
				if(cntA[a[k]] != 0) {
					cntCnt[cntA[a[k]]]--;
				}
				cntA[a[k]]++;
				cntCnt[cntA[a[k]]]++;
			}
			/*
			Find the mex of the frequency. Though the loop looks like an infinite
			one, it will terminate in atmost 2*sqrt(N) steps as explained in the
			editorial.
			*/
			for(int i = 1; ; i++) {
				if(cntCnt[i] == 0) {
					prev_ans = i;
					break;	
				}
			}
			/*
			Bring back the frequency table to initial state i.e. all zeros.
			Instead of clearing the full table using memset or fill, the
			complexity will become O(N) per query. We know here most of the
			elements will be zeros. Only the once updated in this query need to
			be cleared. Thus just reverse the first operation (Just paste code
			in reverse order :P)
			*/
			for(int k = l; k <= r; k++) {
				cntCnt[cntA[a[k]]]--;
				cntA[a[k]]--;
				if(cntA[a[k]] != 0) cntCnt[cntA[a[k]]]++;
			}
		}
		else {
			int x = blockL + 1, y = blockR - 1;
			/*
			The complete blocks are from "x" to "y". For them we had already
			caclulated the frequency of desired elements (i.e. upto 2*sqrt(N))
			in cnt table. We will use this information below and thus avoid
			traversing through these blocks.
			Now in the next 2 loops we add the contribution of remaining elements
			i.e. those lying in not fully covered blocks (x-1 and y+1). We
			traverse each element one by one and we had already stored the
			frequency of elements across blocks in dp1 and dp2. We use this
			information together with cntA and cnt array to calculate the
			updated frequency of the element. As in brute force solution above,
			the idea is to first remove the contribution of frequency in 
			frequency of frequency table, add the elements and then update the
			tables.
			*/
			for(int i = 1; x * L - i >= l; i++) {
				if(dp1[x][y][i] + cntA[a[x * L - i]] > 0) 
					cnt[x][y][dp1[x][y][i] + cntA[a[x * L - i]]]--;
				cntA[a[x * L - i]]++;
				cnt[x][y][dp1[x][y][i] + cntA[a[x * L - i]]]++;
				
			}
			for(int i = 1; (y + 1) * L + i - 1 <= r; i++) {
				if(dp2[x][y][i] + cntA[a[(y + 1) * L + i - 1]] > 0) 
					cnt[x][y][dp2[x][y][i] + cntA[a[(y + 1) * L + i - 1]]]--;
				cntA[a[(y + 1) * L + i - 1]]++;
				cnt[x][y][dp2[x][y][i] + cntA[a[(y + 1) * L + i - 1]]]++;
			}
			
			/*
			Calculate the mex of the frequency. Idea is again same as above brute
			force. See above for details. Just that instead of cntCnt,
			information is stored in cnt.
			*/
			for(int i = 1; ; i++) {
				if(cnt[x][y][i] == 0) {
					prev_ans = i;
					break;	
				}
			}
			
			/*
			Bring back the arrays to original state. Again copy pasting of code
			in reverse order :P. See above brute force for details.
			*/
			for(int i = 1; x * L - i >= l; i++) {
				cnt[x][y][dp1[x][y][i] + cntA[a[x * L - i]]]--;
				cntA[a[x * L - i]]--;
				if(dp1[x][y][i] + cntA[a[x * L - i]] > 0) 
					cnt[x][y][dp1[x][y][i] + cntA[a[x * L - i]]]++;
				
			}
			for(int i = 1; (y + 1) * L + i - 1 <= r; i++) { 
				cnt[x][y][dp2[x][y][i] + cntA[a[(y + 1) * L + i - 1]]]--;
				cntA[a[(y + 1) * L + i - 1]]--;
				if(dp2[x][y][i] + cntA[a[(y + 1) * L + i - 1]] > 0)
					cnt[x][y][dp2[x][y][i] + cntA[a[(y + 1) * L + i - 1]]]++;
			}
		}
		// Print the answer.
		// cout << prev_ans << "\n";
	}
}