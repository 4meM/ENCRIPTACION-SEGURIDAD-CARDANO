#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pair<int,int>> vp;
typedef pair<int,int> pi;
typedef priority_queue<int> maxHeap;
typedef priority_queue<int, vector<int>, greater<int>> minHeap;

vector<int> seleccionar(int N, int X) {
    vector<int> resultado;
    random_device rd;
    mt19937 gen(rd());
    
    for(int i = 0; i < N; i++) {
        if(resultado.size() < X) {
            resultado.push_back(i);
        } else {
            uniform_int_distribution<int> dis(1, i);
            int j = dis(gen);
            if(j <= X) {
                resultado[j-1] = i;
            }
        }
    }
    return resultado;
}

int cuadradoProximo(int size){
    int raiz = static_cast<int>(ceil(sqrt(size)));
    return (raiz % 2 != 0? raiz + 1 : raiz); 
}

int size_rejilla(string &encriptar){
    string conc = "";
    for(int i = encriptar.size(); i % 4 != 0; i++){
        conc += "X";
    } 
    encriptar += conc;
    return cuadradoProximo(encriptar.size());
}

vector<pair<int,int>> generarRejilla(int sizeRejilla, int holes){
    int cant_sector = pow((sizeRejilla / 2), 2);
    vector<int> elegidos = seleccionar(cant_sector, holes);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 3);
    vector<int> cuadrantes(elegidos.size());
    for(int i = 0; i < elegidos.size(); i ++){
        cuadrantes[i] = dis(gen); 
    } 
    vector<pair<int,int>> rejilla;
    for(int i = 0; i < cuadrantes.size(); i++){
        int fila = elegidos[i] / (sizeRejilla / 2);
        int col = elegidos[i] % (sizeRejilla / 2); 

        if(cuadrantes[i] == 0){
            rejilla.push_back({fila, col});
        } 
        else if(cuadrantes[i] == 1){
            rejilla.push_back({col, sizeRejilla - fila - 1});
        } 
        else if(cuadrantes[i] == 2){
            rejilla.push_back({sizeRejilla - col - 1, fila});
        }
        else if(cuadrantes[i] == 3){
            rejilla.push_back({sizeRejilla - fila - 1, sizeRejilla - col - 1});
        }
    }
    return rejilla;
}

vector<vector<char>> cardanGrip(string &encriptar, vector<pair<int,int>> &rejilla, int sizeRejilla){
    vector<vector<char>> matriz(sizeRejilla, vector<char>(sizeRejilla, ' '));
    int index = 0;
    for(int rotacion = 0; rotacion < 4; rotacion++){
        sort(rejilla.begin(), rejilla.end());
        for(const auto& pos : rejilla){
            if(index < encriptar.size()){
                matriz[pos.first][pos.second] = encriptar[index++];
            }
        }
        for(auto &pos : rejilla){
            int fila = pos.first;
            int col = pos.second;
            pos.first = col;
            pos.second = sizeRejilla - fila - 1;
        }
    }
    return matriz;
}



int main() {
    srand(time(0));
    
    string word = "HOLAA";
    int sizeRejilla = size_rejilla(word);
    int holes = word.size() / 4; 
    vector<pair<int,int>> rejilla = generarRejilla(sizeRejilla, holes);
    for(int i = 0; i < sizeRejilla; i++){
        for(int j = 0; j < sizeRejilla; j++){
            for(int k = 0; k < rejilla.size(); k++){
                if(rejilla[k].first == i && rejilla[k].second == j){
                    cout << "0 ";
                    break;
                }
                if(k == rejilla.size() - 1){
                    cout << "# ";
                }
            }
        }
        cout << endl;
    } 
    cout << endl;
    vector<vector<char>> matriz = cardanGrip(word, rejilla, sizeRejilla);
    for(int i = 0; i < matriz.size(); i++){
        for(int j = 0; j < matriz[i].size(); j++){
            if(matriz[i][j] == ' ')
                cout << "Y ";
            else{
                cout << matriz[i][j] << " ";
            }
        }
        cout << endl;
    }
    
}