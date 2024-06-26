#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class SquareMatrix{
    private:
        int **matrix;
        int size;
    public:
        SquareMatrix() : matrix(nullptr),size(0){}
        void scan(){
            cin >> size;
            matrix = new int*[size];
            for (int i = 0; i < size; ++i) {
                matrix[i] = new int[size];
            }
            for(int i=0;i<size;i++)
                for(int j=0;j<size;j++){
                    cin >> matrix[i][j];
                }
        }
        void RotateRight(){
            if (matrix == nullptr || matrix[0] == nullptr) {
                cout << "No element in matrix can be rotated."<<endl;
                return;
            }
            int row = size;
            int col = size;
            //transpose
            for(int r=0;r<row;r++)
                for(int c=r;c<col;c++){
                    swap(matrix[r][c],matrix[c][r]);
                }
            //reverse elements on row order
            for(int r=0;r<row;r++)
                for(int c=0;c<col/2;c++){
                    swap(matrix[r][c],matrix[r][col-c-1]);
                }
        }
        void RotateLeft(){
            if (matrix == nullptr || matrix[0] == nullptr) {
                cout << "No element in matrix can be rotated.\n";
                return;
            }
            int row = size;
            int col = size;
            //transpose
            for(int r=0;r<row;r++)
                for(int c=r;c<col;c++){
                    swap(matrix[r][c],matrix[c][r]);
                }
            //reverse elements on colunm order
            for(int c=0;c<col;c++)
                for(int r=0;r<row/2;r++){
                    swap(matrix[r][c],matrix[row-r-1][c]);
                }
        }
        void print(){
            if (matrix == nullptr || matrix[0] == nullptr) {
                cout << "No element in matrix can be printed.\n";
                return;
            }
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    cout << matrix[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        void Delete(){
            for (int i = 0; i < size; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
};

int main(){
    SquareMatrix s;
    string ins;
    while(getline(cin,ins) && ins!="stop"){
        if(ins == "scan"){
            s.scan();
            cin.ignore();
        }else if(ins == "rotate right"){
           s.RotateRight();
        }else if(ins == "rotate left"){
            s.RotateLeft();
        }
        else if(ins == "print"){
            s.print();
        }else{
            cout << "unknown\n";
        }
    }
    s.Delete();
    return 0;
}