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
// Structure to represent a cell in the matrix
struct Cell {
    int row;
    int col;
};

// Function to check if a cell is valid or not
bool isValid(int row, int col, int numRows, int numCols, int direction, vector<vector<int>>& matrix, bool passFlag) {
    if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
        switch (direction) {
            case 0:
            case 2:
            case 5:
            case 7:
                if (matrix[row][col]==-1 || passFlag)
                    return true;
                else return false;
                break;
            default:
                return true;
                break;
        }
    } else return false;
}

void processCell(int i, int j, vector<vector<int>>& matrix, int dr[] , int dc[], vector<vector<bool>>& processed) {
    queue<Cell> q;
    int numRows = matrix.size();
    int numCols = matrix[0].size();
    bool passFlag=false;
    int minNeighbour;

    if (i == 0 && j == 0) {
        matrix[i][j]=0;
        processed[i][j]=true;
        return;
    }
    if (matrix[i][j] == -1)
        passFlag=true;

    for (int m = 0; m < 8; m++) {
        int newRow = i + dr[m];
        int newCol = j + dc[m];
        if (isValid(newRow, newCol, numRows, numCols, m, matrix, passFlag) && processed[newRow][newCol]) {
            Cell neighborCell = {newRow, newCol};
            q.push(neighborCell);
            minNeighbour=matrix[newRow][newCol]; // just let it have a value before processing all neighbours' values
        }
    }
    while (!q.empty()) {
        Cell currentCell = q.front();
        q.pop();
        
        int currentRow = currentCell.row;
        int currentCol = currentCell.col;

        //cout << "Visiting neighbours (" << currentRow << ", " << currentCol << "): " << matrix[currentRow][currentCol] << endl;

        if (minNeighbour > matrix[currentRow][currentCol])
            minNeighbour = matrix[currentRow][currentCol];
    }
    matrix[i][j]=minNeighbour+1;
    processed[i][j]=true;
}

// Function to perform breadth-first search
void bfs(vector<vector<int>>& matrix) {
    int numRows = matrix.size();
    int numCols = matrix[0].size();
    vector<vector<bool>> visited(numRows, vector<bool>(numCols, false));
    vector<vector<bool>> processed(numRows, vector<bool>(numCols, false));

    // Define the 8 possible movements: up, down, left, right, and diagonals
    int dr[] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1,-1, 1,-1, 0, 1};

    // Queue to store the cells to be visited
    queue<Cell> q;

    // Start BFS from the top-left cell
    Cell startCell = {0, 0};
    q.push(startCell);
    visited[startCell.row][startCell.col] = true;

    while (!q.empty()) {
        Cell currentCell = q.front();
        q.pop();

        int currentRow = currentCell.row;
        int currentCol = currentCell.col;

        // Process the current cell
        processCell(currentRow,  currentCol, matrix, dr, dc, processed);
        //cout << "Visiting cell (" << currentRow << ", " << currentCol << "): " << matrix[currentRow][currentCol] << endl;

        // Explore the neighbors of the current cell
        for (int i = 0; i < 8; i++) {
            int newRow = currentRow + dr[i];
            int newCol = currentCol + dc[i];

            if (isValid(newRow, newCol, numRows, numCols, i, matrix, false) && !visited[newRow][newCol]) {
                // Mark the neighbor as visited and enqueue it
                visited[newRow][newCol] = true;
                Cell neighborCell = {newRow, newCol};
                q.push(neighborCell);
            }
        }
    }
    //cout << "processed: " << endl;
    //printMatrix(processed);

}

int main() {
    int n,j;
    cin >> n;
    vector<vector<int>> matrix(n, vector<int>(n));

    for (int i=0 ; i < n ; i++) {
        cin >> j;
        matrix[i][j-1]=-1;
    }

    bfs(matrix);

    //printMatrix(matrix);
    cout << matrix[n-1][n-1];
    return 0;
}