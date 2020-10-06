/*
 * Program: state_facts.h
 * Author: Joshua Petersen 4134 4297
 * Date: 9-29 | 2020
 * Description: The header file of state_facts.cpp
 */

#include <string>
#include <fstream>

#ifndef COOL_MAINFUNC_H
#define COOL_MAINFUNC_H
#endif //COOL_MAINFUNC_H

using namespace std;

namespace state_facts {
    class sta{
    public:
        struct county {
            std::string name; //name of county
            std::string *city; // array of city names in county
            int cities; //number of cities in county
            int population; //total population of county
            float avg_income; //avg household income
            float avg_house; //avg household price
        };

        struct state {
            std::string name; //name of state
            struct county *c; //array of counties
            int counties; //number of counties in state
            int population; //total population of state
        };

        vector<string> splitSpaces(string);

        state *create_states(int);

        void get_state_data(state *, int, std::ifstream &);

        county *create_counties(int);

        void get_county_data(county *, int, std::ifstream &);

        void delete_info(state **, int);

        int largestPopState(state **, int, ofstream*);

        int largestPopCounty(state *, ofstream*);

        void incomeAboveAmount(state *, ofstream*);

        int averageHouseholdCost(state **, int, ofstream*);
    };
}



