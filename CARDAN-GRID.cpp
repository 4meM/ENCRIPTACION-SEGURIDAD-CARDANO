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

int calculateNextEvenSquareSize(int minSize){
    int raiz = static_cast<int>(ceil(sqrt(minSize)));
    return (raiz % 2 != 0? raiz + 1 : raiz); 
}

string padTextToMultipleOfFour(string text){
    string padding = "";
    for(int i = text.size(); i % 4 != 0; i++){
        padding += "X";
    }
    return text + padding;
}


vector<int> selectRandomPositionsWithReservoir(int totalPositions, int selectCount) {
    vector<int> resultado;
    random_device rd;
    mt19937 gen(rd());
    
    for(int i = 0; i < totalPositions; i++) {
        if(resultado.size() < selectCount) {
            resultado.push_back(i);
        } else {
            uniform_int_distribution<int> dis(1, i);
            int j = dis(gen);
            if(j <= selectCount) {
                resultado[j-1] = i;
            }
        }
    }
    return resultado;
}

vector<int> assignRandomQuadrants(int positionCount){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 3);
    vector<int> cuadrantes(positionCount);
    for(int i = 0; i < positionCount; i ++){
        cuadrantes[i] = dis(gen); 
    }
    return cuadrantes;
}

vector<pair<int,int>> convertToGrilleCoordinates(const vector<int>& positions, const vector<int>& quadrants, int gridSize){
    vector<pair<int,int>> rejilla;
    for(int i = 0; i < quadrants.size(); i++){
        int fila = positions[i] / (gridSize / 2);
        int col = positions[i] % (gridSize / 2); 

        if(quadrants[i] == 0){
            rejilla.push_back({fila, col});
        } 
        else if(quadrants[i] == 1){
            rejilla.push_back({col, gridSize - fila - 1});
        } 
        else if(quadrants[i] == 2){
            rejilla.push_back({gridSize - col - 1, fila});
        }
        else if(quadrants[i] == 3){
            rejilla.push_back({gridSize - fila - 1, gridSize - col - 1});
        }
    }
    return rejilla;
}

vector<pair<int,int>> generateCardanGrillePattern(int gridSize, int holeCount){
    int sectorsPerQuadrant = pow((gridSize / 2), 2);
    vector<int> selectedPositions = selectRandomPositionsWithReservoir(sectorsPerQuadrant, holeCount);
    vector<int> quadrants = assignRandomQuadrants(selectedPositions.size());
    return convertToGrilleCoordinates(selectedPositions, quadrants, gridSize);
}

void rotateGrille90Degrees(vector<pair<int,int>>& grille, int gridSize){
    for(auto &pos : grille){
        int fila = pos.first;
        int col = pos.second;
        pos.first = col;
        pos.second = gridSize - fila - 1;
    }
}

void fillMatrixWithRotatedGrille(vector<vector<char>>& matrix, const string& text, const vector<pair<int,int>>& grille, int& textIndex){
    vector<pair<int,int>> sortedGrille = grille;
    sort(sortedGrille.begin(), sortedGrille.end());
    for(const auto& pos : sortedGrille){
        if(textIndex < text.size()){
            matrix[pos.first][pos.second] = text[textIndex++];
        }
    }
}

vector<vector<char>> encryptWithCardanGrille(string text, vector<pair<int,int>> grille, int gridSize){
    vector<vector<char>> matriz(gridSize, vector<char>(gridSize, ' '));
    int index = 0;
    for(int rotacion = 0; rotacion < 4; rotacion++){
        fillMatrixWithRotatedGrille(matriz, text, grille, index);
        rotateGrille90Degrees(grille, gridSize);
    }
    return matriz;
}


void fillRemainingWithRandomLetters(vector<vector<char>>& matrix) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 25);

    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) {
            if(matrix[i][j] == ' ') {
                char randomChar = 'A' + dis(gen);
                matrix[i][j] = randomChar;
            }
        }
    }
}

int main() {
    srand(time(0));
    
    string word; cin >> word;
    word = padTextToMultipleOfFour(word);
    int sizeRejilla = calculateNextEvenSquareSize(word.size());
    int holes = word.size() / 4; 
    vector<pair<int,int>> rejilla = generateCardanGrillePattern(sizeRejilla, holes);
    
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
    
    vector<vector<char>> matriz = encryptWithCardanGrille(word, rejilla, sizeRejilla);
    fillRemainingWithRandomLetters(matriz);
    for(int i = 0; i < matriz.size(); i++){
        for(int j = 0; j < matriz[i].size(); j++){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    
}