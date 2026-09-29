class Solution {
    vector<vector<vector<int>>> memo;

    bool searchPath(vector<vector<char>>& grid, int row, int col, int balance) {
        if (grid[row][col] == '(') {
            balance++;
        } else {
            balance--;
        }

        if (balance < 0) {
            return false;
        }

        int rows = grid.size();
        int cols = grid[0].size();

        if (row == rows - 1 && col == cols - 1) {
            return balance == 0;
        }

        if (memo[row][col][balance] != -1) {
            return memo[row][col][balance];
        }

        bool validPath = false;

        if (row + 1 < rows) {
            validPath = searchPath(grid, row + 1, col, balance);
        }

        if (!validPath && col + 1 < cols) {
            validPath = searchPath(grid, row, col + 1, balance);
        }

        return memo[row][col][balance] = validPath;
    }

public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        if (grid[0][0] == ')' || grid[rows - 1][cols - 1] == '(') {
            return false;
        }

        if ((rows + cols - 1) % 2 != 0) {
            return false;
        }

        memo.assign(rows, vector<vector<int>>(
            cols, vector<int>(rows + cols, -1)
        ));

        return searchPath(grid, 0, 0, 0);
    }
};