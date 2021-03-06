#include <bits/stdc++.h>
using namespace std;
#define ROW 9
#define COL 10
typedef pair<int, int> Pair;
typedef pair<double, pair<int, int> > pPair;
struct cell
{
	int parent_i, parent_j;
	double f, g;
};
bool isValid(int row, int col)
{
	return (row >= 0) && (row < ROW) && (col >= 0)
		&& (col < COL);
}
bool isUnBlocked(int grid[][COL], int row, int col)
{
	if (grid[row][col] == 1)
		return (true);
	else
		return (false);
}
bool isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}
double calculateHValue(int row, int col, Pair dest)
{
	return ((double)sqrt(
		(row - dest.first) * (row - dest.first)
		+ (col - dest.second) * (col - dest.second)));
}
void tracePath(cell cellDetails[][COL], Pair dest)
{
	printf("\nThe Path is ");
	int row = dest.first;
	int col = dest.second;
	stack<Pair> Path;
	while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col))
	{
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}
	Path.push(make_pair(row, col));
	while (!Path.empty())
	{
		pair<int, int> p = Path.top();
		Path.pop();
		printf("-> (%d,%d) ", p.first, p.second);
	}
	}
void aStarSearch(int grid[][COL], Pair src, Pair dest)
{
	if (!isValid(src.first, src.second))
	{
		printf("Source is invalid\n");
		return;
	}
	if (!isValid(dest.first, dest.second))
	{
		printf("Destination is invalid\n");
		return;
	}
    if (isUnBlocked(grid, src.first, src.second) && isUnBlocked(grid, dest.first, dest.second)) {
        if (isDestination(src.first, src.second, dest)) {
            printf("We are already at the destination\n");
            return;
        }
        bool closedList[ROW][COL];
        memset(closedList, false, sizeof(closedList));
        cell cellDetails[ROW][COL];
        int i, j;
        for (i = 0; i < ROW; i++) 
        {
            for (j = 0; j < COL; j++) 
            {
                cellDetails[i][j].f = FLT_MAX;
                cellDetails[i][j].g = FLT_MAX;
                cellDetails[i][j].parent_i = -1;
                cellDetails[i][j].parent_j = -1;
            }
        }
        i = src.first, j = src.second;
        cellDetails[i][j].f = 0.0;
        cellDetails[i][j].g = 0.0;
        cellDetails[i][j].parent_i = i;
        cellDetails[i][j].parent_j = j;
        set<pPair> openList;
        openList.insert(make_pair(0.0, make_pair(i, j)));
        while (!openList.empty()) 
        {
            pPair p = *openList.begin();
            openList.erase(openList.begin());
            i = p.second.first;
            j = p.second.second;
            closedList[i][j] = true;
            double gNew, hNew, fNew;
            if (isValid(i - 1, j)) {
                if (isDestination(i - 1, j, dest)) 
                {
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    return;
                } 
                else if (!closedList[i - 1][j] && isUnBlocked(grid, i - 1, j)) 
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i - 1, j, dest);
                    fNew = gNew + hNew;
                    if (cellDetails[i - 1][j].f == FLT_MAX || cellDetails[i - 1][j].f > fNew) 
                    {
                        openList.insert(make_pair(fNew, make_pair(i - 1, j)));
                        cellDetails[i - 1][j].f = fNew;
                        cellDetails[i - 1][j].g = gNew;
                        cellDetails[i - 1][j].parent_i = i;
                        cellDetails[i - 1][j].parent_j = j;
                    }
                }
            }
            if (isValid(i + 1, j)) 
            {
                if (isDestination(i + 1, j, dest)) 
                {
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    return;
                } 
                else if (!closedList[i + 1][j] && isUnBlocked(grid, i + 1, j)) 
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i + 1, j, dest);
                    fNew = gNew + hNew;
                    if (cellDetails[i + 1][j].f == FLT_MAX || cellDetails[i + 1][j].f > fNew) 
                    {
                        openList.insert(make_pair(fNew, make_pair(i + 1, j)));
                        cellDetails[i + 1][j].f = fNew;
                        cellDetails[i + 1][j].g = gNew;
                        cellDetails[i + 1][j].parent_i = i;
                        cellDetails[i + 1][j].parent_j = j;
                    }
                }
            }
            if (isValid(i, j + 1)) 
            {
                if (isDestination(i, j + 1, dest)) 
                {
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    return;
                } 
                else if (!closedList[i][j + 1] && isUnBlocked(grid, i, j + 1)) 
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i, j + 1, dest);
                    fNew = gNew + hNew;
                    if (cellDetails[i][j + 1].f == FLT_MAX || cellDetails[i][j + 1].f > fNew) 
                    {
                        openList.insert(make_pair(fNew, make_pair(i, j + 1)));
                        cellDetails[i][j + 1].f = fNew;
                        cellDetails[i][j + 1].g = gNew;
                        cellDetails[i][j + 1].parent_i = i;
                        cellDetails[i][j + 1].parent_j = j;
                    }
                }
            }
            if (isValid(i, j - 1)) 
            {
                if (isDestination(i, j - 1, dest)) 
                {
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    return;
                } 
                else if (!closedList[i][j - 1] && isUnBlocked(grid, i, j - 1)) 
                {
                    gNew = cellDetails[i][j].g + 1.0;
                    hNew = calculateHValue(i, j - 1, dest);
                    fNew = gNew + hNew;
                    if (cellDetails[i][j - 1].f == FLT_MAX || cellDetails[i][j - 1].f > fNew) 
                    {
                        openList.insert(make_pair(fNew, make_pair(i, j - 1)));
                        cellDetails[i][j - 1].f = fNew;
                        cellDetails[i][j - 1].g = gNew;
                        cellDetails[i][j - 1].parent_i = i;
                        cellDetails[i][j - 1].parent_j = j;
                    }
                }
            }
            if (isValid(i - 1, j + 1)) 
            {
                if (isDestination(i - 1, j + 1, dest)) 
                {
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    return;
                }
                 else if (!closedList[i - 1][j + 1] && isUnBlocked(grid, i - 1, j + 1))
                  {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i - 1, j + 1, dest);
                    fNew = gNew + hNew;
                    if (cellDetails[i - 1][j + 1].f == FLT_MAX || cellDetails[i - 1][j + 1].f > fNew) 
                    {
                        openList.insert(make_pair(fNew, make_pair(i - 1, j + 1)));
                        cellDetails[i - 1][j + 1].f = fNew;
                        cellDetails[i - 1][j + 1].g = gNew;
                        cellDetails[i - 1][j + 1].parent_i = i;
                        cellDetails[i - 1][j + 1].parent_j = j;
                    }
                }
            }
            if (isValid(i - 1, j - 1)) 
            {
                if (isDestination(i - 1, j - 1, dest)) 
                {
                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    return;
                } else if (!closedList[i - 1][j - 1] && isUnBlocked(grid, i - 1, j - 1)) 
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i - 1, j - 1, dest);
                    fNew = gNew + hNew;
                    if (cellDetails[i - 1][j - 1].f == FLT_MAX || cellDetails[i - 1][j - 1].f > fNew) 
                    {
                        openList.insert(make_pair(fNew, make_pair(i - 1, j - 1)));
                        cellDetails[i - 1][j - 1].f = fNew;
                        cellDetails[i - 1][j - 1].g = gNew;
                        cellDetails[i - 1][j - 1].parent_i = i;
                        cellDetails[i - 1][j - 1].parent_j = j;
                    }
                }
            }
            if (isValid(i + 1, j + 1)) 
            {
                if (isDestination(i + 1, j + 1, dest)) 
                {
                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    return;
                }
                else if (!closedList[i + 1][j + 1] && isUnBlocked(grid, i + 1, j + 1)) 
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i + 1, j + 1, dest);
                    fNew = gNew + hNew;
                    if (cellDetails[i + 1][j + 1].f == FLT_MAX || cellDetails[i + 1][j + 1].f > fNew) 
                    {
                        openList.insert(make_pair(fNew, make_pair(i + 1, j + 1)));
                        cellDetails[i + 1][j + 1].f = fNew;
                        cellDetails[i + 1][j + 1].g = gNew;
                        cellDetails[i + 1][j + 1].parent_i = i;
                        cellDetails[i + 1][j + 1].parent_j = j;
                    }
                }
            }
            if (isValid(i + 1, j - 1)) {
                if (isDestination(i + 1, j - 1, dest)) 
                {
                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                    printf("The destination cell is found\n");
                    tracePath(cellDetails, dest);
                    return;
                }
                else if (!closedList[i + 1][j - 1] && isUnBlocked(grid, i + 1, j - 1)) 
                {
                    gNew = cellDetails[i][j].g + 1.414;
                    hNew = calculateHValue(i + 1, j - 1, dest);
                    fNew = gNew + hNew;
                    if (cellDetails[i + 1][j - 1].f == FLT_MAX || cellDetails[i + 1][j - 1].f > fNew) 
                    {
                        openList.insert(make_pair(fNew, make_pair(i + 1, j - 1)));
                        cellDetails[i + 1][j - 1].f = fNew;
                        cellDetails[i + 1][j - 1].g = gNew;
                        cellDetails[i + 1][j - 1].parent_i = i;
                        cellDetails[i + 1][j - 1].parent_j = j;
                    }
                }
            }
        }
        printf("Failed to find the Destination Cell\n");
        return;
    } else 
    {
        printf("Source or the destination is blocked\n");
    }
}

int main()
{
    int input1, input2, output1,output2;
    cout<<"enter source : ";
    cin>>input1;
    cin>>input2;    
    cout<<"enter destination : ";
    cin>>output1;
    cin>>output2;
	 int grid[ROW][COL]= 
        { 
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
			{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
			{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
			{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
			{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
			{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
			{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
			{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } 
        };
	Pair src = make_pair(input1, input2);
	Pair dest = make_pair(output1, output2);
	aStarSearch(grid, src, dest);
	return (0);

}