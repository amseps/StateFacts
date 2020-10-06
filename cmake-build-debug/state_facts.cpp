/*
 * Program: main.cpp
 * Author: Joshua Petersen 4134 4297
 * Date: 9-29 | 2020
 * Description: All of the functions worked on by run_facts

 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include "state_facts.h"

using namespace std;
using namespace state_facts;

/*
 * @description utility spliterator over spaces
 * @param s, the string to split
 * @return vector of the individual words
 */
vector<string> sta::splitSpaces(string s){
    int spot = 0;
    int last = 0;
    vector<string> toRet;
    while (true) {//iterate to end of line
        if (spot == string::npos) break;
        spot = s.find(" ", last);
        toRet.push_back(s.substr(last, spot-last));
        last = spot+1;
    }
    return toRet;
}

/*
 * @description returns and empty state
 * @param a, does nothing
 * @return returns the new empty state
 */
sta::state* sta::create_states(int a) {
    return new state;
}

/*
 * @description reads the ifstream, and converts it into a single state
 * @param astate pointer holding state info
 * @param state_count the number of states; useless
 * @param &reader, the ifstream
 * @return void
 */
void sta::get_state_data(sta::state * astate, int state_count, std::ifstream &reader) {
    int state_i = 0;
    string s;
    sta *sfunc = new sta();
    getline(reader, s);
    vector<string> this_line = sfunc->splitSpaces(s);
    astate->name = this_line[0];
    astate->population = stoi(this_line[1]);
    astate->counties = stoi(this_line[2]);
    astate->c = new sta::county[stoi(this_line[2])];
    for(int i = 0 ; i < astate->counties; i++){ //go through all counties within the state, and add them to the containing list
        sta::county *this_county = create_counties(0);
        get_county_data(this_county, astate->counties, reader);
        astate->c[i] = *this_county; //assign it to me
    }
}

/*
 * @description returns empty county
 * @param int a is nothing
 * @return the empty county
 */
sta::county* sta::create_counties(int a) {
    return new county;
}

/*
 * @description gets data for a county line within a state
 * @param *this_county is the pointer we edit
 * @param int num_counties is the number of counties; useless
 * @param &reader is the ifstream we are reading the original file from
 * @return
 */
void sta::get_county_data(sta::county *this_county, int num_counties, std::ifstream &reader) {
    sta *sfunc = new sta();
    string s2;
    if (getline(reader, s2)) { //county line
        vector<string> county_line = sfunc->splitSpaces(s2);
        this_county->name = county_line[0];
        this_county->population = stoi(county_line[1]);
        this_county->avg_income = stoi(county_line[2]);
        this_county->avg_house = stoi(county_line[3]);
        this_county->cities = stoi(county_line[4]);
        this_county->city = new string[this_county->cities];
        for (unsigned g = 0; g < this_county->cities; g++) { //for all cities in my county, read from the rest of the line
            this_county->city[g] = county_line[5 + g];
        }
    }//for all counties in state
}
/*
 * @description deletes all of the county info underneath the state**
 * @param **allstates the pointer set we will be cleaning out
 * @param num_states the number of states in allstates
 * @return void, edit allstates
 */
void sta::delete_info(sta::state ** allstates, int num_states) {
    for(int i = 0 ; i < num_states; i++){
        sta::state thisstate = *allstates[i];
        for(int g = 0 ; g < thisstate.counties; g++){
            delete thisstate.c;
        }
    }
}

/*
 * @description finds the state with the largest population
 * @param **states the pointer set we inspect
 * @param num_states the number of states within **states
 * @param *ofs, controls if we print to cout or to a file
 * @return which the index of the highest pop state
 */
int sta::largestPopState(sta::state **states, int num_states, ofstream *ofs) {
    sta::state *ab = states[0];
    int max = INT_MIN;
    int which = -1;
    for(int i = 0; i < num_states; i++){ //go through all states
        if(states[i]->population > max){ //find max
            max = states[i]->population;
            which = i;
        }
    }
    *ofs << "State with Greatest Population: " << states[which]->name << " with " << max << endl;
    return which;
}

/*
 * @description finds which county has the highest pop
 * @param *thisstate is the state we will inspect the counties in
 * @param *ofs controls if we print to cout or to file
 * @return
 */
int sta::largestPopCounty(sta::state * thisstate, ofstream *ofs) {
    int num_counties = thisstate->counties;
    int max = INT_MIN;
    int which = -1;
    for(int i = 0 ; i < num_counties; i++){ // go through all counties
        if(thisstate->c[i].population > max) {
            max = thisstate->c[i].population;
            which = i;
        }
    }
    *ofs << "Largest Pop County in " << thisstate->name << ": " << thisstate->c[which].name << " with " << thisstate->c[which].population << endl;
    return which;
}

/*
 * @description prints all counties in a given state with an income above a given amount
 * @param *thisstate is the state we are inspecting the counties in
 * @param *ofs is the controller of if we look at cout or a file
 * @return void, only prints
 */
void sta::incomeAboveAmount(sta::state * thisstate, ofstream *ofs) {
    cout << "Find counties of state [" << thisstate->name << "] where income is above: ";
    string s;
    getline(cin, s); //prompts user and gets number to be above
    vector<string> line = splitSpaces(s);
    try{
        int typed_income = stoi(line[0]);
        int num_counties = thisstate->counties;
        *ofs << "Counties of " << thisstate->name << " with average income greater than " <<  typed_income << ": " << endl;
        for(int i = 0 ; i < num_counties; i++){ //go through all counties
            if(thisstate->c[i].avg_income > typed_income){
                *ofs << thisstate->c[i].name << ": " << thisstate->c[i].avg_income << endl;
            }
        }
    }catch(exception e){ //should probably be a while or something
        *ofs << "Malformed integer" << endl;
    }
}

/*
 * @description finds the average household cost of all counties in all states
 * @param **allstate the pointer set to all states
 * @param num_state the number of states
 * @param *ofs controls if we look at cout or at a file
 * @return int of the average household cost
 */
int sta::averageHouseholdCost(sta::state **allstate, int num_state, ofstream *ofs) {
    int sum = 0;
    int num_counts = 0;
    for(int i = 0 ; i < num_state; i++){
        state *thisstate = allstate[i];
        for(int g =  0 ; g < thisstate->counties; g++){
            sum += thisstate->c[g].avg_income;
            num_counts++;
        }//through all counties in this state
    }//through all states
    *ofs << "Average Household Cost of all States: " << (sum/num_counts) << endl;
    return (sum/num_counts);
}
