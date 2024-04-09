#include <iostream>
#include <vector>

using namespace std;

void calculateCellCost(vector<vector<int>>& matrix, int x,int y,int x1,int y1) {
    bool pathExists=false,onMainDiameter=false;
    if (x==y)
        onMainDiameter=true;
    if (matrix[x][y]<1)
        return;
    int min;
    // I should mind x=0 here
    for (int i=x-1 ; i <=x+1 ; i++) {
        for (int j=y-1 ; j<=y+1; j++) {
        //cout << "x: " << x << " y: " << y << " i: " << i << " j: " << j << " min: " << min << endl;
            if ((!onMainDiameter && ((i==x-1 && (j==y-1 || j==y+1)) || (i==x+1 && (j==y-1 || j==y+1)) ) ) || (i==x && j==y) || (i<0 || j<0))
            // skip oribs if on main diameter + the cell (x,y)
                continue;
            if (matrix[i][j]>1) {
                if (pathExists) {
                    if (min > matrix[i][j])
                        min = matrix[i][j];
                } else {
                    min = matrix[i][j];
                    pathExists=true;
                }
            }
            else if (matrix[i][j]==1 && i==x1 && j==y1) {
                if (pathExists)  {
                    if (min > matrix[i][j])
                        min = matrix[i][j];
                } else {
                    min = matrix[i][j];
                    pathExists=true;
                }
            }
        }
    }
    if (pathExists)
        matrix[x][y]=min+1;

}

int main() {
    int m=20,n,x1,y1,x2,y2,r,a,b;

    vector<vector<int>> matrix(m, vector<int>(m));

    cin >> x1 >> y1 >> x2 >> y2 ;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> r >> a >> b;
        for (int j=a ; j <=b ; j++)
            matrix[r][j]=1;
    }


    for (int i=0 ; i < m ; i++) {
        for (int j=0 ; j < m; j++) {
            if (!(i==x1 && j==y1))
                calculateCellCost(matrix,i,j,x1,y1);
        }
    }

/*    cout << "Matrix:" << endl;
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
*/
    if (matrix[x2][y2]>1)
        cout << matrix[x2][y2]-1;
    else cout << -1;
    return 0;
}