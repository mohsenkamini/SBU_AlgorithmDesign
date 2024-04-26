#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template<typename T>
void printMatrix(const vector<vector<T>>& matrix) {
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

template<typename T>
void printVector(const vector<T>& vec) {
    // Print vector elements separated by space
    for (int i = 0; i < vec.size(); i++) 
        cout << vec[i] << " ";
    cout << endl;
}

// Structure to represent a cell in the matrix
struct Cell {
    int row;
    int col;
};

// Function to check if a cell is valid or not
bool isValid(int row, int col, int numRows, int numCols, int direction, vector<vector<int>>* matrix, bool passFlag) {
    if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
        switch (direction) {
            case 0:
                if ((*matrix)[row][col] == -1 || passFlag)
                    return true;
                else
                    return false;
                break;
            default:
                return true;
                break;
        }
    } else {
        return false;
    }
}

void processCell(int i, int j, vector<vector<int>>* matrix, int dr[], int dc[]) {
    queue<Cell> q;
    int numRows = matrix->size();
    int numCols = (*matrix)[0].size();
    bool passFlag = false;
    int minNeighbour;

    if (i == 0 && j == 0) {
        (*matrix)[i][j] = 0;
        return;
    }
    if ((*matrix)[i][j] == -1)
        passFlag = true;

    for (int m = 0; m < 3; m++) {
        int newRow = i + dr[m];
        int newCol = j + dc[m];
        if (isValid(newRow, newCol, numRows, numCols, m, matrix, passFlag)) {
            Cell neighborCell = { newRow, newCol };
            q.push(neighborCell);
            minNeighbour = (*matrix)[newRow][newCol]; // just let it have a value before processing all neighbors' values
            cout << "validated: " << newRow <<", "<< newCol << endl;
        }
    }
    while (!q.empty()) {
        Cell currentCell = q.front();
        q.pop();

        int currentRow = currentCell.row;
        int currentCol = currentCell.col;

        //cout << "Visiting neighbours (" << currentRow << ", " << currentCol << "): " << (*matrix)[currentRow][currentCol] << endl;

        if (minNeighbour > (*matrix)[currentRow][currentCol])
            minNeighbour = (*matrix)[currentRow][currentCol];
    }
    cout << "Decided for: " << i <<", "<< j << " minNeighbour: " << minNeighbour<< endl;

    (*matrix)[i][j] = minNeighbour + 1;
    cout << (*matrix)[i][j] << endl;

}

void processMatrix(vector<vector<int>>& matrix, bool firstRow) {
    int n = matrix[0].size();
    vector<int> tempRow(n,0);
    //vector<vector<bool>> processed(numRows, vector<bool>(numCols, true));

    // Define the 3 possible movements
    int dr[] = { -1, -1, 0 };
    int dc[] = { -1, 0, -1 };
    if (firstRow) for (int i = 0; i < n; ++i) {
        processCell(0, i, &matrix, dr, dc);
    } else for (int i = 0; i < n; ++i) {
        processCell(1, i, &matrix, dr, dc);
    }

    // Update matrix[1] with the values from matrix[0]
    matrix[0] = matrix[1];

    // Assign the processed values from the temporary vector to matrix[0]
    matrix[1] = tempRow;
}

int main() {
    int n, j;
    cin >> n;
    vector<vector<int>> matrix(2, vector<int>(n,0));
    bool firstRow=true;

    for (int i = 0; i < n; i++) {
        cin >> j;
        if (!firstRow) matrix[1][j - 1] = -1;
        processMatrix(matrix,firstRow);
        printVector(matrix[0]);

        firstRow=false;
        //printMatrix(matrix);
    }



    //bfs(&matrix);

    //printMatrix(matrix);
    //cout << matrix[n - 1][n - 1];
    return 0;
}