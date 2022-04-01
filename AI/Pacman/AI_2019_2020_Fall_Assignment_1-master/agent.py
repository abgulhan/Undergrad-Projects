import time

import queue

class Agent:

    """
        initialize some member variables
    """
    def __init__(self):
        self.player_row = 0
        self.player_col = 0
        self.level_matrix = None
        self.elapsed_solve_time = 0

        """
            please use these variables for statistics
        """
        self.expanded_node_count = 0
        self.generated_node_count = 0
        self.maximum_node_in_memory_count = 0

        #  not implemented, not necessary
        self.real_distance_matrix = []
        self.manhattan_distance_matrix = []
    


    """
        returns REAL manhattan distance between two points in the level.
    it is the amount of steps required from going point 1 to point 2, 
    so it also consider walls.
    row_1 and col_1 is the position of first point
    row_2 and col_2 is the position of second point 

        this function is not necessary, you may leave it empty
    """
    def real_distance(self, row_1, col_1, row_2, col_2):
        if (row_1,col_1) == (row_2,col_2):
            return 0
        distance_matrix = [list(row) for row in self.level_matrix] #deepcopy(level_matrix)
        q = queue.Queue()
        rows = len(distance_matrix)
        cols = len(distance_matrix[0])
        distance_matrix[row_1][col_1] = 0
        s0 = (row_1, col_1)
        q.put(s0)
        move_dir = ['U', 'D', 'L', 'R']
        while (q.empty() == False):
            coord = q.get()
            distance = distance_matrix[coord[0]][coord[1]]
            for direction in move_dir:
                if direction == 'D':
                    next_row = coord[0]+1
                    next_col = coord[1]
                elif direction == 'U':
                    next_row = coord[0]-1
                    next_col = coord[1]
                elif direction == 'L':
                    next_row = coord[0]
                    next_col = coord[1]-1
                elif direction == 'R':
                    next_row = coord[0]
                    next_col = coord[1]+1
                if (next_row <= rows and next_col <= cols and next_row >= 0 and next_col >= 0): #check bounds
                    if (distance_matrix[next_row][next_col] == 'F' or distance_matrix[next_row][next_col] == 'A' or distance_matrix[next_row][next_col] == 'P'): #check if node is accessible
                        distance_matrix[next_row][next_col] = distance+1
                        if (next_row,next_col) == (row_2,col_2): #found distance
                            return (distance+1)
                        q.put((next_row,next_col))
        print('Distance not found')
        print("coordinates: " + str(row_1) + ', ' + str(col_1) + ' | ' + str(row_2) + ', ' + str(col_2))
        return(-1)
    


    """
        level_matrix is list of lists (like 2d array)
    that contains whether a particular cell is
    -A (apple)
    -F (floor)
    -P (player)
    -W (wall)

    level_matrix[0][0] is top left corner
    level_matrix[height-1][0] is bottom left corner
    level_matrix[height-1][width-1] is bottom right corner

        player_row and player_column are current position
    of the player, eg:
    level_matrix[player_row][player_column] supposed to be P
      
        returns a character list, list of moves
    that needs to be played in order to solve
    given level
    valid letters are R, U, L, D corresponds to:
    Right, Up, Left, Down
    an example return value:
    L = ["U", "U", "U", "L", "R", "R"]...
    """
    def solve(self, level_matrix, player_row, player_column):
        self.player_row = player_row
        self.player_col = player_column
        self.level_matrix = level_matrix

        #  you may precompute distances between pairs of points here

