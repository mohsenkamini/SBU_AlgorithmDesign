// C++ program to demonstrate the implementation of List
#include <iostream>
#include <iterator>
#include <list>
using namespace std;

void showlist(list<long> l)
{
	list<long>::iterator it;
	for (it = l.begin(); it != l.end(); ++it)
		cout << ' ' << *it;
	cout << '\n';
}

int main()
{
	list<long> evenList, evenIndex, oddList, oddIndex ;
    long n,modifiedN;

    cin >> n;

    modifiedN=n;
	for (long i = 0; i < n; ++i) {
        long input;
        cin >> input;
        if (input >= 0) {
            if (input%2==0){
                evenList.push_back(input);
                evenIndex.push_back(i);
            } else {
                oddList.push_back(input);
                oddIndex.push_back(i);
            }
            //showlist(evenList);
        } else {
            modifiedN--;
            switch (input) {
                case -1:
                    if (!evenList.empty()){
                        evenList.pop_front();
                        evenIndex.pop_front();
                    }
                    break;
                case -2:
                    if (!oddList.empty()){
                        oddList.pop_front();
                        oddIndex.pop_front();
                    }
                    break;
                case -3:
                    if (!evenList.empty()){
                        evenList.pop_back();
                        evenIndex.pop_back();
                    }
                    break;
                case -4:
                    if (!oddList.empty()){
                        oddList.pop_back();
                        oddIndex.pop_back();
                    }
                    break;
                default:
                    break;
            }
        }
	}

    for (long i=0 ; i < modifiedN ; i++) {
        long eCandidate=0;
        long eCandidateIndex=-1;
        long oCandidate=0;
        long oCandidateIndex=-1;
        if (!oddList.empty()){
            oCandidate=oddList.front();
            oCandidateIndex=oddIndex.front();
        }
        if (!evenList.empty()){
            eCandidate=evenList.front();
            eCandidateIndex=evenIndex.front();
        }
        if (oCandidateIndex == -1 && eCandidateIndex != -1 || ( eCandidateIndex != -1 && oCandidateIndex > eCandidateIndex) ) {
            cout << eCandidate;
            evenList.pop_front();
            evenIndex.pop_front();
        }
        if (eCandidateIndex == -1 && oCandidateIndex != -1 || ( oCandidateIndex != -1 && oCandidateIndex < eCandidateIndex) ) {
            cout << oCandidate;
            oddList.pop_front();
            oddIndex.pop_front();
        }
        cout << " ";
    }

	//showlist(evenList);
	//showlist(evenIndex);
	//showlist(oddList);
	//showlist(oddIndex);

	return 0;
}
