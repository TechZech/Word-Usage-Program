/*              DRIVER6.CPP
        Ben Zech        Assignment 6
        Mr. Myers       Due Friday, December 4th 11:59pm
*/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cctype>
#include <string>
#include <unordered_map>
using namespace std;

int main()
{
	unordered_map<string, pair<int,int>> sTable;	// string hashTable, with string as key and pair int int refers to count and position, respectively
	unordered_map<string, pair<int,int>> nTable;	// number hashTable, with string as key and pair int int refers to count and position, respectively
	unordered_map<char, int> cTable;	// char hashTable
	char theChar;
	string numString;
	string wordString;
	unsigned int wordCount = 0;	// both of these counts will be used for determining position in document of the inserted word
	unsigned int numCount = 0;	// ^

	while (cin.get(theChar))
	{
		if ( isdigit(theChar) != 0 )	// char is a number
		{
			cTable.insert(make_pair(theChar,0));
			cTable[theChar]++;

			numString.push_back(theChar);

			while ( isdigit((char)(cin.peek())) != 0 )	// while next char is a num
			{
				cin >> theChar;
				numString.push_back(theChar);
				cTable.insert(make_pair(theChar,0));
				cTable[theChar]++;
			}
			numCount++;
			nTable[numString].first++;		// add num string to the table
			if ( nTable[numString].second == 0 )
				nTable[numString].second = numCount;	// add num string count (for positioning in case of tie)
			numString = "";				// reset string for next usage
		}
		else if ( isalpha(theChar) != 0 )	// char is a letter
		{
			cTable.insert(make_pair(theChar,0));
			cTable[theChar]++;
			
			if ( isupper(theChar) != 0 )
				theChar = tolower(theChar);
			
			wordString.push_back(theChar);
			
			while ( isalpha((char)(cin.peek())) != 0 )	// while next char is a letter
			{
				// cin chars, add them to word string and ctable
				cin >> theChar;
				cTable.insert(make_pair(theChar,0));
				cTable[theChar]++;

				if ( isupper(theChar) != 0 )
					theChar = tolower(theChar);
				
				wordString.push_back(theChar);
			}
			wordCount++;				// increment word counter
			sTable[wordString].first++;		// add word string to table and increment
			if ( sTable[wordString].second == 0 )
				sTable[wordString].second = wordCount;	// add word string position to table
			wordString = "";			// clear word string
		}
		else
		{
			// above is special for words and numbers, now below all relates to the char hashTable
			cTable.insert(make_pair(theChar,0));
			cTable[theChar]++;
		}
	}
	
	// Everything below is for printing the tables

	int sloopNum = 10;
	int nloopNum = 10;
	int cloopNum = 10;

	if ( sTable.size() < 10 )
		sloopNum = sTable.size();
	
	if ( nTable.size() < 10 )
		nloopNum = nTable.size();
	
	if ( cTable.size() < 10 )
		cloopNum = cTable.size();
	
	// Print the top 10 chars, use ascii value in case of tie
	cout << "Total " << cTable.size() << " different characters, " << cloopNum << " most used characters:" << endl;
	for (int c = 0; c < cloopNum; c++)	// <-- haha it says c++
	{
		auto max = cTable.begin();

		for ( auto itr = cTable.begin(); itr != cTable.end(); itr++ )
		{
			if (itr->second > max->second)
				max = itr;
			else if (itr->second == max->second)
			{
				if ( ((int)(itr->first)) < ((int)(max->first)) )	// compare ascii values for tie breaker
					max = itr;
			}
		}

		cout << "No. " << c << ": ";
		if ((max->first) == '\n')
			cout << "\\" << "n";
		else if ((max->first) == '\t')
			cout << "\\" << "t";
		else
			cout << max->first;
		
		cout << "	" << max->second << endl;
		cTable.erase(max);
	}

	cout << "\nTotal " << sTable.size() << " different words, " << sloopNum << " most used words:" << endl;
	for (int s = 0; s < sloopNum; s++)
	{
		auto maxS = sTable.begin();

		for ( auto itr = sTable.begin(); itr != sTable.end(); itr++ )
		{
			if (itr->second.first > maxS->second.first)
				maxS = itr;
			else if (itr->second.first == maxS->second.first)
			{
				if ( itr->second.second < maxS->second.second )	// tie breaker: order of appearance
					maxS = itr;
			}
		}

		cout << "No. " << s << ": ";
		cout << maxS->first;
		cout << "	" << maxS->second.first << endl;
		sTable.erase(maxS);
	}

	cout << "\nTotal " << nTable.size() << " different numbers, " << nloopNum << " most used numbers:" << endl;
	for (int n = 0; n < nloopNum; n++)
	{		
		auto maxN = nTable.begin();

		for ( auto itr = nTable.begin(); itr != nTable.end(); itr++ )
		{
			if (itr->second.first > maxN->second.first)
				maxN = itr;
			else if (itr->second.first == maxN->second.first)
			{
				if ( itr->second.second < maxN->second.second )		// tie breaker: order of appearance
					maxN = itr;
			}
		}

		cout << "No. " << n << ": ";
		cout << maxN->first;
		cout << "	" << maxN->second.first << endl;
		nTable.erase(maxN);
	}

	return 0;
}
