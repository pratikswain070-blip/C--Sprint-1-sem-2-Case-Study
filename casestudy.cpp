#include<iostream>
#include<vector>
using namespace std;

// voter info
class Voter{
public:
    int id;
    string name;
    string pass;  // password
    bool hasVoted;
};

// candidate info
class Candidate{
public:
    int id;
    string name;
    string party;
    int voteCount;
};

class Election{
public:
    vector<Voter> voters;
    vector<Candidate> cands;   // candidates
    bool isRunning = false;

    void addVoter(){
        Voter v;
        cout << "Voter ID: ";
        cin >> v.id;

        // check if id already exists maybe? TODO later
        cout << "Name: ";
        cin >> v.name;

        cout << "Password: ";
        cin >> v.pass;

        v.hasVoted = false;
        voters.push_back(v);
        cout << "Done. Voter added.\n";
    }

    void addCandidate(){
        Candidate c;
        cout << "Candidate ID: ";
        cin >> c.id;
        cout << "Name: ";
        cin >> c.name;
        cout << "Party: ";
        cin >> c.party;
        c.voteCount = 0;
        cands.push_back(c);
        cout << "Candidate added\n";
    }

    void startElection(){
        if(cands.size() == 0){
            cout << "No candidates added yet!\n";
            return;
        }
        isRunning = true;
        cout << "Election is now live\n";
    }

    void stopElection(){
        isRunning = false;
        cout << "Election stopped\n";
    }

    void listCandidates(){
        if(cands.empty()){
            cout << "no candidates\n";
            return;
        }
        cout << "\n-- Candidates --\n";
        for(int i=0; i<cands.size(); i++){
            cout << cands[i].id << ". " << cands[i].name << "  [" << cands[i].party << "]\n";
        }
    }

    void castVote(){
        if(!isRunning){
            cout << "Voting hasn't started\n";
            return;
        }

        int uid;
        string pwd;
        cout << "Your voter ID: ";
        cin >> uid;
        cout << "Password: ";
        cin >> pwd;

        int idx = -1;
        for(int i=0; i<voters.size(); i++){
            if(voters[i].id == uid && voters[i].pass == pwd){
                idx = i;
                break;
            }
        }

        if(idx == -1){
            cout << "Wrong ID or password\n";
            return;
        }

        if(voters[idx].hasVoted){
            cout << "You've already voted!\n";
            return;
        }

        listCandidates();

        int pick;
        cout << "Enter candidate ID to vote: ";
        cin >> pick;

        // find that candidate
        int cidx = -1;
        for(int j=0; j<cands.size(); j++){
            if(cands[j].id == pick){
                cidx = j;
                break;
            }
        }

        if(cidx == -1){
            cout << "That candidate doesnt exist\n";
            return;
        }

        char ch;
        cout << "Confirm? (y/n): ";
        cin >> ch;

        if(ch != 'y' && ch != 'Y'){
            cout << "Ok vote cancelled\n";
            return;
        }

        cands[cidx].voteCount++;
        voters[idx].hasVoted = true;
        cout << "Vote recorded!\n";
    }

    void showResults(){
        if(cands.empty()){
            cout << "Nothing to show\n";
            return;
        }

        cout << "\n===== Results =====\n";
        int maxV = 0;
        int winnerIdx = 0;

        for(int i=0; i<cands.size(); i++){
            cout << cands[i].name << " (" << cands[i].party << ") - "
                 << cands[i].voteCount << " votes\n";
            if(cands[i].voteCount > maxV){
                maxV = cands[i].voteCount;
                winnerIdx = i;
            }
        }

        // edge case: all zero votes
        if(maxV == 0)
            cout << "No votes cast yet\n";
        else
            cout << "\nWinner: " << cands[winnerIdx].name << " with " << maxV << " votes\n";
    }

    void showVoters(){
        cout << "\nAll voters:\n";
        for(int i=0; i<voters.size(); i++){
            // not showing password obviously
            cout << voters[i].id << " - " << voters[i].name;
            if(voters[i].hasVoted) cout << " (voted)";
            cout << "\n";
        }
    }
};

int main(){
    Election e;
    int ch;

    while(true){
        cout << "\n==== Voting System ====\n";
        cout << "1. Register voter\n";
        cout << "2. Add candidate\n";
        cout << "3. Start election\n";
        cout << "4. Vote\n";
        cout << "5. Stop election\n";
        cout << "6. Results\n";
        cout << "7. View voters\n";
        cout << "8. Exit\n";
        cout << "Choice: ";
        cin >> ch;

        switch(ch){
            case 1: e.addVoter(); break;
            case 2: e.addCandidate(); break;
            case 3: e.startElection(); break;
            case 4: e.castVote(); break;
            case 5: e.stopElection(); break;
            case 6: e.showResults(); break;
            case 7: e.showVoters(); break;
            case 8:
                cout << "Bye\n";
                return 0;
            default:
                cout << "Invalid option, try again\n";
        }
    }
}