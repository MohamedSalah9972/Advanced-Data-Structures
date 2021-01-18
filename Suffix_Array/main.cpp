#include <iostream>
using namespace std;

struct Suffix {
public:
    int index, rank, nextRank;
    Suffix& operator=(const Suffix &s){
        this->rank = s.rank;
        this->nextRank = s.nextRank;
        this->index = s.index;
        return *this;
    }
};

bool compare(Suffix s1,Suffix s2) {
    return (s1.rank == s2.rank) ? s1.nextRank < s2.nextRank :
           s1.rank < s2.rank;
}
void merge(Suffix *suffix,int l,int mid,int r) {

    int len1 = mid-l+1;
    int len2 = r - mid;
    Suffix *part1, *part2;
    part1 = new Suffix[len1];
    part2 = new Suffix[len2];
    for (int i = 0; i < len1; ++i) {
        part1[i] = suffix[i + l];
    }

    for (int i = 0; i < len2; ++i) {
        part2[i] = suffix[i + mid + 1];
    }

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2) {
        if (compare(part1[i], part2[j])) {
            suffix[k++] = part1[i++];
        } else {
            suffix[k++] = part2[j++];
        }
    }

    while (i < len1) {
        suffix[k++] = part1[i++];
    }

    while (j < len2) {
        suffix[k++] = part2[j++];
    }
}
void sort(Suffix *suffix,int l,int r){
    if(l>=r)
        return;
    int mid = (l+r-1)/2;
    sort(suffix,l,mid);
    sort(suffix,mid+1,r);
    merge(suffix,l,mid,r);
}
class SuffixArray{
public:
    int length,*suffixArray;
    Suffix *suffix;
    char *s;
    SuffixArray(char *s){
        this->s = s;
        length=0;
        while(s[length]!=NULL){
            length++;
        }
        suffix = new Suffix[length];
        suffixArray = new int[length];
    }
    void ConstructUsingPrefixDoubling() {
        for (int i = 0; i < length; ++i) {
            suffix[i].index = i;
            suffix[i].rank = s[i] - 'a';
            suffix[i].nextRank = i + 1 < length ? s[i+1] - 'a' : -1;
        }
        sort(suffix, 0, length - 1);
        int *mapIndex = new int[length];

        for (int k = 4; k < length*2; k<<=1) {
            int rank = 0,prevRank = suffix[0].rank;
            suffix[0].rank = rank;
            mapIndex[suffix[0].index] = 0;
            for (int i = 1; i < length; ++i) {
                if (suffix[i].rank == prevRank && suffix[i].nextRank == suffix[i - 1].nextRank) {
                    prevRank = suffix[i].rank;
                    suffix[i].rank = rank;
                } else {
                    rank++;
                    prevRank = suffix[i].rank;
                    suffix[i].rank = rank;
                }
                mapIndex[suffix[i].index] = i;
            }

            for (int i = 0; i < length; i++) {
                int nextIndex = suffix[i].index + k/2;
                suffix[i].nextRank = (nextIndex < length) ?
                                     suffix[mapIndex[nextIndex]].rank : -1;
            }
            sort(suffix,0,length-1);
        }
        for (int i = 0; i < length; ++i) {
            suffixArray[i] = suffix[i].index;
        }

    }
    void Print() {
        for (int i = 0; i < this->length; ++i) {
            cout << suffixArray[i] << ' ';
        }
        cout << endl;
    }
};

