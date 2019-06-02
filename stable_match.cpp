/*
Problem: There are n students and n bikes, each student is differently far away from each bike.
Now we want each of the students to find a bike and the overall distance students walk to the their bikes
could be minimized.
*/
#include <iostream>
#include <map>
#include <vector>
using namespace std;

void stableMatch(vector<vector<int>> graph, int n);

int main() {
  /*
    Input: 2d array {{s1,b1,d1},{s1,b2,d2}....} in which, s1 is the student1, b1 is the bike1 and d1 is
    the distance between student1 and bike1.
    It is ensured that the numbers of students and bikes are equal.
  */

  vector<vector<int>> g = {{0,0,2},{0,1,4},{0,2,5},{1,0,1},{1,1,3},{1,2,2},{2,0,6},{2,1,2},{2,2,4}};

  stableMatch(g, 3);

  return 0;
}

void stableMatch(vector<vector<int>> graph, int n){
  map<int, vector<int>> b2s_map;
  map<int, int> match_map;
  vector<int> std_in_need;

  //Firstly we create a map from bike to studnet regarding to their distances,
  //b2s_map is a map that maps from integers to vectors.
  //Let's say we have student s1 and bike b1, the distance is d1, then we store it in the
  //b2s_map in the way that b2s_map[b1][s1] = d1.
  for(vector<int> pair : graph){
    if(b2s_map[pair[1]].size() == 0)
      b2s_map[pair[1]] = vector<int>(n);
    b2s_map[pair[1]][pair[0]] = pair[2];
  }

//Initially we push all the students in std_in_need queue since none of the students has been assigned a bike
  for(int i = 0; i < n; i++){
    std_in_need.push_back(i);
  }


  while(std_in_need.size() > 0){
    int std = std_in_need[0];

    //For each student in the std_in_need queue, we iterate all the bikes, if a bike is not matched with
    //any other student, we have this student match with this bike, if a bike is already matched with
    //another student, who is the bike holder, we compare the distances of these two students and
    //if the current student is closer to the bike than the bike holder studnet is, then we replace the
    //bike holder student with the current studnet, and we add the bike holder student back to the std_in_need queue.
    for(int b = 0; b < n; b++){
      if(!match_map.count(b)){
        match_map[b] = std;
        std_in_need.erase(std_in_need.begin());
        break;
      }else{
        int occ_std = match_map[b];
        cout<<std<<":"<<b2s_map[b][std]<<","<<occ_std<<":"<<b2s_map[b][occ_std]<<"\n"<<endl;
        if(b2s_map[b][std] < b2s_map[b][occ_std]){
          match_map[b] = std;
          std_in_need.erase(std_in_need.begin());
          std_in_need.push_back(occ_std);
          break;
        }
      }
    }

  }

  int total_dist = 0;

  for(int i = 0; i < n; i++){
    cout << "bike " << i << ": student " << match_map[i] <<endl;
    total_dist += b2s_map[i][match_map[i]];
  }

  cout<<"Todal distance:"<<total_dist<<endl;
}
