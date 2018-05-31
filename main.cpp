#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>

using std::getline;
using std::ifstream;
using std::string;
using std::map;
using std::istringstream;
using std::remove_if;
using std::ofstream;
using std::endl;


void nuskaityti(ifstream &fd , map<string , size_t> &zodziu_sk , map<string , map<size_t , size_t>> &references) {
    string eilute;
    unsigned int eilNr = 1;

    while (getline(fd, eilute)){
        eilute.erase(remove_if(eilute.begin(), eilute.end(), [](char s) { return s == ',' || s == '-' || s == '.' || s == '!' || s == '?' || s == '(' || s == ')' || s == '„' || s == '“';}),
                     eilute.end());
        istringstream zod(eilute);
        for (string w; zod >> w;) {
            std::transform(w.begin(), w.end(), w.begin(), tolower);
            zodziu_sk[w]++;
            references[w][eilNr]++;
        }
        eilNr++;
    }
    fd.close();
}
void isvesti(ofstream &fr , map<string , size_t> &zodziu_sk , const map<string , map<size_t , size_t>> &references) {
    for (auto &i : zodziu_sk) {
        if (i.second > 1){
            fr << "Zodis:  " << i.first << " pasikartojo " << i.second << " kartus." << endl;
            fr << "Eilutes (eilNr-kartai): ";
            for (auto &j : references.at(i.first)){
                fr << j.first << "-" << j.second << " ";
            }
            fr << endl << endl;
        }
    }
}

int main() {
    map<std::string, size_t> zodziu_sk;
    map<std::string, std::map<size_t, size_t>> references;
    ifstream fd("test.txt");
    ofstream fr("rez.txt");
    nuskaityti(fd , zodziu_sk , references);
    isvesti(fr , zodziu_sk , references);
    return 0;
}