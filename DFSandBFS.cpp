#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
using namespace std;
using namespace std::chrono;

int N = 4;
int K = 2;
int i = 0;
int gen =0;
int exp = 0;

vector<bool> tela (N*N,0);
vector<bool> telaAux(N*N,0);
vector<vector<bool>> stack;
deque<vector<bool>> queue;
vector<vector<bool>> visited;

int checkDamas (const vector<bool> telaT){
    int aux =0;
    for(int j=0;j<telaT.size();j++){
        if(telaT[j]==1){
            aux++;
            }
        }
    return aux+1;
}

bool checkVisited(const vector<bool> telaT){
    for(int j=0;j<visited.size();j++){
        if(telaT==visited[j]){

            return true;
        }
    }
    return false;
}

void printTela (){
    int j=0;
    int linhas =0;

    while(j<N*N) {
        if (tela[j]==1){
            cout << "D";
        }else{
            cout << "+";
        }
        j++;
        linhas++;
        if(linhas==N){
            cout << std::endl;
            linhas=0;
        }
    }
    cout << std::endl;
}


bool testLinha(const vector<bool> telaT){
    int aux =0;
    int linhas =0;
    int j=0;

    while (j<N*N){
        if(telaT[j]==1){
            aux++;
        }
        if(aux==K+1){
            return false;
        }
        j++;
        linhas++;
        if(linhas==N){
            linhas=0;
            aux =0;
        }
    }
    return true;
}

bool testColuna(const vector<bool> telaT){
    int aux =0;
    int coluna =0;
    int j=0;

    while (coluna<N) {

        if(telaT[j+coluna]==1){
            aux++;
        }
        if(aux==K+1){
            return false;
        }
        j+=N;
        if(j>=N*N){
            aux=0;
            coluna++;
            j=0;
        }
    }
    return true;
}

bool testDiagonal(const vector<bool> telaT){
    int aux =0;
    int j=0;
    while (j<N*N) {

        if(telaT[j]==1){
            aux++;
        }
        if(aux==K+1){
            return false;
        }
        j= j + N+1;
    }
    j=N-1;
    while (j<N*N) {

        if(telaT[j]==1){
            aux++;
        }
        if(aux==K+1){
            return false;
        }
        j= j + N-1;
    }

    return true;
}


bool expandDFS() {

    if(stack.empty()){
        return 0;
    }
    if (i>N*N){
        i=0;
    }
    if (tela[i] == 1) {
        i++;
        expandDFS();
    } else {
        telaAux = tela;
        telaAux[i] = 1;
        if (!checkVisited(telaAux)) {  //False:Nao foi visitado

            if (telaAux==stack.back()){
                visited.push_back(telaAux);
                exp++;
                i=0;
            }
            if (testLinha(telaAux) && testColuna(telaAux) && testDiagonal(telaAux) ) {

                tela[i] = 1;
                stack.push_back(tela);
                gen++;
                if(checkDamas(tela)==N*K+1){
                    cout << checkDamas(tela)-1 << visited.size() << endl;
                    printTela();
                    return 1;
                }


            } else {
                visited.push_back(telaAux);
                exp++;
                i++;
            }
        }else{              //Encontrou visitado
            stack.pop_back();
            tela=stack.back();

        }
            expandDFS();
    }
}

bool expandBFS(){

    while(!queue.empty()){
        i=0;
        while(i<N*N){
            tela[i]=1;
            if (!checkVisited(tela)){
                if (testLinha(tela) && testColuna(tela) && testDiagonal(tela) ) {
                    queue.push_back(tela);
                    if(checkDamas(tela)==(N*K)+1){
                        cout << "Solucao: " << endl;
                        printTela();
                        return 1;
                    }
                    printTela();
                    tela[i]=0;
                }
                visited.push_back(tela);
            }
            i++;
        }
        queue.pop_front();
        visited.push_back(tela);
        tela = queue.front();
    }
    return 0;
}
int main() {
    auto start = high_resolution_clock::now();
    stack.push_back (tela); //Estado Inicial
    queue.push_front(tela);//Estado Inicial
    expandDFS();
    expandBFS();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Tempo: " << duration.count() << " ms" << endl;
    cout << "Geracoes: " << gen << endl;
    cout << "Expancoes: " << exp << endl;
    return 0;
}
