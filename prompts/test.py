def get_max_island_size(grid):
    """
    Finds the largest body of "land" (connected '1's) in a 2D binary grid.

    Args:
        grid: A list of lists of strings, where '1' represents land and '0' represents water.

    Returns:
        The size of the largest connected body of land.
    """
    if not grid or not grid[0]:
        return 0

    rows = len(grid)
    cols = len(grid[0])
    max_island_size = 0

    # Helper function for DFS traversal
    def dfs(r, c):
        if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] == '0':
            return 0

        # Mark the cell as visited by changing its value to '0'
        # This prevents revisiting and ensures accurate counting for the current island
        grid[r][c] = '0'
        current_island_size = 1

        # Explore all 4 cardinal directions
        current_island_size += dfs(r + 1, c)  # Down
        current_island_size += dfs(r - 1, c)  # Up
        current_island_size += dfs(r, c + 1)  # Right
        current_island_size += dfs(r, c - 1)  # Left

        return current_island_size

    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '1':
                # Found an unvisited land cell, start a new DFS to find its island size
                island_size = dfs(r, c)
                max_island_size = max(max_island_size, island_size)

    return max_island_size

def run_test():
    """
    Runs a simple test case for the get_max_island_size function.
    """
    grid1 = [
        ["1", "1", "1", "1", "0"],
        ["1", "1", "0", "1", "0"],
        ["1", "1", "0", "0", "0"],
        ["1", "1", "1", "1", "1"]
    ]
    expected_output1 = 14
    result1 = get_max_island_size(grid1)

    print(f"Test Case 1 Input:")
    for row in grid1:
        print(row)
    print(f"Expected Output: {expected_output1}")
    print(f"Actual Output: {result1}")
    assert result1 == expected_output1, f"Test Case 1 Failed: Expected {expected_output1}, Got {result1}"
    print("Test Case 1 Passed!\n")

if __name__ == "__main__":
    run_test()