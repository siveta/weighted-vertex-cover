
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

struct Briauna {
    int x;
    int y;
    bool paimta = false;
};
struct Denginys {
    vector<int> denginys;
    int svoris = 0;
};

void raskMaziausiaDengini(vector<int> virsunes, vector<Briauna> briaunos) {

    int n = virsunes.size();
    int count = pow(2, n);
    int s = 0;
    Denginys deng;
    vector<int> laikinas;

    for (int i = 0; i < count; i++) {        // surandame poaibius
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) != 0) {
                int a = virsunes[j];
                laikinas.push_back(a);
            }
            for (auto k : laikinas) {
                s = s + k;       // randame poaibio svori           
            }

            if (deng.svoris == 0 || deng.svoris > s) {
                for (auto& k : laikinas) {       // tikriname ar tai denginys, ir ar dar neturime denginio su mazesniu svoriu
                    for (auto& b : briaunos) {
                        if (k == b.x || k == b.y) {
                            if (b.paimta == false) {      //  patikriname ar briauna dar nebuvo neprideta
                                b.paimta = true;
                            }
                        }
                    }
                }
            }
        }
        int m = 0;
        for (auto& b : briaunos) {
            if (b.paimta == true) {
                m = m + 1;
            }
        }
        if (m == briaunos.size()) {        // jei m lygus n, tai reiskia, kad visos briaunos paimtos, t.y. rastas denginys
            deng.svoris = 0;
            deng.denginys.clear();
            for (auto& k : laikinas) {
                deng.denginys.push_back(k);
                deng.svoris = deng.svoris + k;
            }
        }
        laikinas.clear();
        for (auto& b : briaunos) {
            b.paimta = false;
        }
    }
    cout << "Maziausias denginys : ";
    for (auto k : deng.denginys) {
        cout << k << " ";
    }
    cout << endl;
    cout << "Denginio svoris : " << deng.svoris << endl;
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();
    vector<int> virsunes2 = { 1, 2, 3, 4 };        // visos grafo virsunes
    vector<Briauna> briaunos2 = { {1,3}, {1,2}, {2,3}, {3,4}, {1,4} };
    cout << "Grafo su briaunomis {1,3}, {1,2}, {2,3}, {3,4}, {1,4} denginys :" << endl;
    raskMaziausiaDengini(virsunes2, briaunos2);
    std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start;
    cout << "1. Uztruko : " << diff.count() << " s" << std::endl;
    cout << endl;
    auto start2 = std::chrono::high_resolution_clock::now();
    vector<int> virsunes = { 1, 2, 3, 4, 5, 6, 7 };        // visos grafo virsunes
    vector<Briauna> briaunos = { {1,2}, {1,4}, {2,5}, {2,3}, {3,5}, {3,6}, {3,7}, {5,6} };         // visos grafo briaunos
    cout << "Grafo su briaunomis {1,2}, {1,4}, {2,5}, {2,3}, {3,5}, {3,6}, {3,7}, {5,6} denginys :" << endl;
    raskMaziausiaDengini(virsunes, briaunos);
    std::chrono::duration<double> diff2 = std::chrono::high_resolution_clock::now() - start2;
    cout << "2. Uztruko : " << diff2.count() << " s" << std::endl;

    return 0;
}