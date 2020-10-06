/*
 * Program: run_facts.cpp
 * Author: Joshua Petersen 4134 4297
 * Date: 9-29 | 2020
 * Description: A program that opens up a file of states and their respective counties, and gives back data about it
 * Input: Commandline, the directory location of the file to parse through, the number of states to inspect, and then user input at runtime
 * Output: Either console output or output into a file defined during runtime.
 */



#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>

#include "state_facts.h"

using namespace std;
using namespace state_facts;

/*
 * @A program that opens up a file of states and their respective counties, and gives back data about it
 * @param commandline the directory location of the file to parse through, the number of states to inspect, and then user input at runtime
 * @return Either console output or output into a file defined during runtime
 */
int main(int argc, char* argv[]) {
    try{
        string filename = argv[1]; //actually the state_count from cmdline
        int state_count = stoi(filename);
        filename = argv[2]; //then filename is actually the filename
        sta *sfunc = new sta(); //stupid bc the others should really be statics
        try{
            ifstream reader;
            reader.open(filename.c_str()); //open filename
            cout << "Opened " << filename << " successfully" << endl;
            sta::state *allstate [state_count]; //set up our states holder
            for(int i = 0 ; i < state_count; i++){ //for all of our spaces inside
                sta::state *newstate = sfunc->create_states(0); //get an empty pointer
                sfunc->get_state_data(newstate, state_count, reader); //fill that newstate with info
                allstate[i] = newstate;  //assign that newstate to our stateholder
                cout << "Succesfully added state " << allstate[i]->name << " with counties:";
                for(int g = 0; g < allstate[i]->counties; g++){ //print out stuff about or state and counties
                    cout << " " << allstate[i]->c[g].name;
                }
                cout << endl;
            }
            reader.close();

            //now we will do stuff to it
            cout << "Would you like to print data to the console (0) or text file(1)?";
            string s;
            getline(cin, s);
            vector<string> printline = sfunc->splitSpaces(s);
            int a = stoi(printline[0]); //get on if we will use cout or to a file
            ofstream ofs;
            if(a < 1){//to cout
                ofs.copyfmt(cout);
                ofs.clear(std::cout.rdstate());                          //2
                ofs.basic_ios<char>::rdbuf(std::cout.rdbuf());
            }else{ //to a file
                while(true) {
                    try {
                        cout << "Type in filename: ";
                        getline(cin, s);
                        printline = sfunc->splitSpaces(s);
                        ofs.open(printline[0].c_str());
                        if (ofs.is_open()) {
                            break;
                        }
                        cout << "Could not open file somehow, try again: " << endl;
                    }catch(exception e){
                        cout << "Strange error in file input, try again" << endl;
                    }
                }
            }//ofs now points to either cout or a file we defined

            //run our metrics
            sfunc->incomeAboveAmount(allstate[0], &ofs);
            sfunc->largestPopState(allstate, state_count, &ofs);
            sfunc->largestPopCounty(allstate[0], &ofs);
            sfunc->averageHouseholdCost(allstate, state_count, &ofs);

            ofs.close(); //close

            sfunc->delete_info(allstate, state_count); //clear memory
            delete *allstate;
        }catch(exception e){
            cout << "Failed to open file: " << filename << endl;
            return 2;
        }
    }catch(exception e){
        cout << "Failed to use commandline args!";
        return 1;
    }
    cout << "Process Complete" << endl;
    return 0;
}