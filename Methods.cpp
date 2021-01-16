#include "Methods.h"
#include <fstream>      
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;
using std::max;
using std::pair;
using std::string;
using std::vector;

const vector<pair<int, int> > DIRECTION{ {-1,0},{1,0},{0,-1},{0,1} };

vector<vector<int> > Methods::ReadFile(const string name)
{
    vector< vector<int> > matrix;
    ifstream infile(name);

    if (!infile)
    {
        cout << "Unable to open file " << name << endl;
    }
    else
    {
        int m;
        int n;
        infile >> m >> n;

        if (m > 0 && n > 0)
        {
            cout << "Matrix dimensions " << m << "x" << n << endl;
            int data;

            for (int i = 0; i < m; ++i)
            {
                vector<int> row;

                for (int j = 0; j < n; ++j)
                {
                    infile >> data;
                    row.push_back(data);
                }

                matrix.push_back(row);
            }
        }
        else
        {
            cout << "At least one of the dimensions is zero  " << m << "x" << n << endl;
        }
    }

    return matrix;
}
InfoLongestPath Methods::CalculateLongestPath(const vector<vector<int> > matrix)
{
    InfoLongestPath output;

    int m = matrix.size();
    int n = matrix[0].size();

    vector<vector<int> > length(m, vector<int>(n, -1));

    int maxCol = 0;
    int maxRow = 0;
    int maxLength = 0;

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int currentLength = DFS(i, j, matrix, length);
            if (currentLength > maxLength)
            {
                maxRow = i;
                maxCol = j;
                maxLength = currentLength;
            }
        }
    }

    output.maxLength = maxLength;

    return output;
}
int Methods::DFS(int i, int j, const vector<vector<int> >& matrix, vector<vector<int> >& length)
{
    if (length[i][j] == -1)
    {
        int maxLength = 0;

        for (auto p : DIRECTION)
        {
            int x = i + p.first;
            int y = j + p.second;

            if (x < 0 || x >= static_cast<int>(matrix.size()) || y < 0 || y >= static_cast<int>(matrix[0].size())) continue;

            if (matrix[x][y] < matrix[i][j])
            {
                maxLength = max(maxLength, DFS(x, y, matrix, length));
            }
        }

        length[i][j] = maxLength + 1;
    }

    return length[i][j];
}