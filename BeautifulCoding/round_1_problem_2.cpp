#include <iostream>
#include <algorithm>

using namespace std;

bool if_reverse(string inString)
{
	for(int i = 0; i < inString.length() / 2; ++i){
		if (inString[i] != inString[inString.length() - 1 - i]) return false;
	}
	return true;
}

int main(int argc, char const *argv[])
{
	// No matter how, the center of such a string is fixed.
	int T;
	cin >> T;
	string givenString;
	int count;
	int result[1000][1000]; // Designed to be with the void string
	int sum;
	for(int i = 0; i <= T - 1; ++i)
	{
		sum = 0;
		cin >> givenString;
		count = 0;

		// By brutal force first
		// cout << if_reverse(givenString) << endl;

		for (size_t j = 0; j <= givenString.length() - 1; ++j)
		{
			for (size_t k = 0; k <= min(j, givenString.length() - 1 - j); ++k)
			{
				if (givenString[j - k] == givenString[j + k]) ++count;
			}
		}
		// cout << count << endl;

		// We now need to count a strict start...

		// If we are to use recursion, I am afraid that we will encounter stackoverflow...
		// The largest allowed complexity is n^3 for the data size of 1000.
		for (size_t j = 0; j <= givenString.length() - 1; ++j) // j for length;
		{
			// result[j][j] = 2;
			for (size_t k = 0; k <= givenString.length() - 1 - j; ++k) // k for starting point
			{
				if (givenString[k] == givenString[k + j])
				{
					// cout << "Equal!" << endl;
					if (j <= 1)
					{
						result[k][k + j] = 1;
					}
					else
					{
						result[k][k + j] = 1;
						for (size_t l = k + 1; l <= k + j - 1; ++l)
						{
							for(size_t m = l; m <= k + j - 1; ++m)
							{
								// cout << "We are now at " << k << ", " << k + j << ", " << l << ", " << m << endl;
								result[k][k + j] += result[l][m];
							}
						}
						
					}
					
				}
				else
				{
					result[k][k + j] = 0;
				}
				// cout << result[k][k + j] << ". " << k << ", " << k + j << endl;
				sum += result[k][k + j];
			}

		}
		// cout << "The final result is: " << sum << endl;
		cout << "Case #" << i + 1 << ": " << sum << endl;

		// How to optimize the algorithm further?
		// It is now O(n^4) which is too large for the size of 1000. We need to optimize to O(n^3)


	}





	return 0;
}