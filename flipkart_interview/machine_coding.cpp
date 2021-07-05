#include<bits/stdc++.h>
#define all(v) v.begin(),v.end()
using namespace std;

const int SUCCESS = true;
const int FAILURE = false;

const int COVISHIELD = 0;
const int COVAXIN = 1;

unordered_map<int,string> vaccineName;
vaccineName[0] = "COVISHIELD";
vaccineName[1] = "COVAXIN";

struct centre {
    string centreId;
    unordered_map<int,int> vaccineInventory;
    centre(string centreId, unordered_map<int,int>& vaccineInventory) : centreId(centreId), vaccineInventory(vaccineInventory) {};
    vector<user*> bookedUsers;
};

struct user {
    string name;
    char gender;
    int prefferedVaccineType;
    string centreId = "";
    string userId;
    user(string name, char gender, int prefferedVaccineType) : name(name), gender(gender), prefferedVaccineType(prefferedVaccineType) {};
};

class CoFlipHelpers {
    public:
      void displayCentreDetails(centre* c, int vaccineType = -1) {
          cout << "Centre Id: " << c->centreId << "\n";
          if(vaccineType == -1) {
              cout << "INVALID VACCINE TYPE";
              assert(false); // Will throw error.
          }
          else {
              cout << vaccineName[vaccineType] << ": " << c->vaccineInventory[vaccineType] << "\n";
          }
      }
      void iterateAndPrintOverVectorOfCentres(vector<centre*>& v, int vaccineType = -1) {
          if(vaccineType == -1) {
              cout << "INVALID VACCINE TYPE" << endl;
              assert(false); // Will throw error.
          }

          sort(all(v), [&](centre* a, centre* b) {
              if(a->vaccineInventory[vaccineType] != b->vaccineInventory[vaccineType]) {
                  return a->vaccineInventory[vaccineType] > b->vaccineInventory[vaccineType];
              }
              else if(a->bookedUsers.size() != b->bookedUsers.size()) {
                  return a->bookedUsers.size() > b->bookedUsers.size();
              }
              return false;
          });

          for(auto c : v) {
              displayCentreDetails(c, vaccineType);
          }
      }
};

class CoFlipApp : private CoFlipHelpers {

    unordered_map<string, user*> users_database;
    unordered_map<string, centre*> centres_database;

    // Centres with available vaccines by vaccine-types
    unordered_map<int, vector<centre*>> centres;

    bool updateDatabaseAfterBooking(string& userId, string& centreId) {

    }

    void printCentreDetails(centre* c) {
      cout << "Centre Id : " << c->centreId << "\n";
      for(auto vaccine : c->vaccineInventory) {
          cout << vaccineName[vaccine.first] << ": " << vaccine.second << "\n";
      }
      for(auto user : c->bookedUsers) {
          cout << user->userId << "\n";
      }
      cout << "\n";
    }

    public:
      void register_user(string& name, char& gender, int& prefferedVaccineType) {
        /*

        Currently assuming all the names in the input are different

        */

          string userId = name; // Need to assign a unique userId for same names
          user *newUser = new user(name, gender, prefferedVaccineType);
          users_database[userId] = newUser;
      }

      void register_centre(string& centreId, unordered_map<int,int>& vaccineInventory) {
          // sanity check for centreId already existing
          centre *newCentre = new centre(centreId, vaccineInventory);
          centres_database[centreId] = newCentre; // when we need to find centre details by centreId
          for(auto inventory : vaccineInventory) {
              if(inventory.second > 0) {
                  centres[inventory.first].push_back(newCentre);
              }
          }
      }

      void getCentres(string& userId) {
          user *userDetails = users_database[userId];
          int vaccineType = userDetails->prefferedVaccineType;
          iterateAndPrintOverVectorOfCentres(centres[vaccineType], vaccineType);
      }

      bool bookslot(string& userId, string& centreId) {
          user *userDetails = users_database[userId];
          int vaccineType = userDetails->prefferedVaccineType;
          centre *centreDetails = centres_database[centreId];
          if(centreDetails->vaccineInventory[vaccineType] == 0) {
              return FAILURE;
          }
          updateDatabaseAfterBooking(userId, centreId); // this one is left
          return SUCCESS;
      }

      void getStats() {
          for(auto c : centres_database) {
              printCentreDetails(c.second);
          }
      }
};

void solve() {

}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    solve();
}
