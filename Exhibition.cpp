#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
using namespace std;

int main(){
    int K;
    int N, M, A;
    set<int> stamps;
    vector<set<int>> vet;
    map<int,int> mapStampCount;
    int countUnique = 0, countUniqueByFriend = 0;

    //Setar casas decimais
    std::cout << std::fixed;
    std::cout << std::setprecision(6);

    while (!cin.eof())
    {
        cin >> K;
        for(int k = 0; k < K; k++){
            cin >> N;
            mapStampCount.clear();
            vet.clear();
            for(int n = 0; n < N; n++){
                cin >> M;
                stamps.clear();
                for(int m = 0; m < M; m++){
                    cin >> A;
                    if(stamps.find(A) == stamps.end())
                        mapStampCount[A]++;
                    stamps.insert(A);
                }
                vet.push_back(stamps);
            }
            countUnique=0;
            //Quantas cartas são unicas
            for(auto msc: mapStampCount)
                if(msc.second == 1)
                    countUnique++;

            cout << "Case " << k+1 << ":";
            for(auto v: vet){
                countUniqueByFriend = 0;
                for(auto stamp: v){
                    if(mapStampCount[stamp] == 1)
                        countUniqueByFriend++;
                }
                cout << " " << (countUniqueByFriend*100.0)/(double)countUnique << "%";
            }
            cout << endl;
        }
        return 0;
    }
}
