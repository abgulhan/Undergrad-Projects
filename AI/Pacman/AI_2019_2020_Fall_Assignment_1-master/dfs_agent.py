import time
import random
from copy import deepcopy
from agent import Agent


#  use whichever data structure you like, or create a custom one
import queue
import heapq
from collections import deque


"""
  you may use the following Node class
  modify it if needed, or create your own
"""
class Node():
    
    def __init__(self, parent_node, player_row, player_column, depth, chosen_dir, visited, apples_left):
        self.parent_node = parent_node
        #self.level_matrix = level_matrix
        self.player_row = player_row
        self.player_col = player_column
        self.depth = depth
        self.chosen_dir = chosen_dir
        self.visited = visited
        self.apples_left = apples_left

        self.seq = ""
        if (self.chosen_dir == "X"):
            pass
        else:
            self.seq = parent_node.seq + self.chosen_dir



class DFSAgent(Agent):

    def __init__(self):
        super().__init__()

    def solve(self, level_matrix, player_row, player_column):
        super().solve(level_matrix, player_row, player_column)
        move_sequence = []

        """
            YOUR CODE STARTS HERE
            fill move_sequence list with directions chars
        """

        initial_level_matrix = [list(row) for row in level_matrix] #deepcopy(level_matrix)
        #s0 = Node(None, initial_level_matrix, player_row, player_column, 0, "X")
    
        s = [] #stack
        rows = len(initial_level_matrix)
        cols = len(initial_level_matrix[0])
        initial_visited = [[False for x in range(cols)] for y in range(rows)] #visited[rows][cols]
        initial_apples = []
        player_row = 0
        player_col = 0
        for row in range(rows):
            for col in range(cols):
                if initial_level_matrix[row][col] == 'A':
                    initial_apples.append((row,col))
                if initial_level_matrix[row][col] == 'P':
                    initial_level_matrix[row][col] = 'F'
                    player_row = row
                    player_col = col
        #print(player_row)
        #print(player_col)
        s0 = Node(None, player_row, player_col, 0, "X", initial_visited, initial_apples)
        self.generated_node_count = 1
        s.append(s0)
        move_dir = ['U', 'D', 'L', 'R']
        finished = False
        expanded = True
        #print('starting DFS ------------')
        #input()
        while (len(s) != 0 and finished == False):
            if expanded:
                self.expanded_node_count += 1
                expanded = False
            node_count = len(s)
            if node_count > self.maximum_node_in_memory_count:
                self.maximum_node_in_memory_count = node_count
            parent_node = s.pop()

            for direction in move_dir:
                if direction == 'D':
                    next_row = parent_node.player_row+1
                    next_col = parent_node.player_col
                elif direction == 'U':
                    next_row = parent_node.player_row-1
                    next_col = parent_node.player_col
                elif direction == 'L':
                    next_row = parent_node.player_row
                    next_col = parent_node.player_col-1
                elif direction == 'R':
                    next_row = parent_node.player_row
                    next_col = parent_node.player_col+1

                visited = parent_node.visited.copy()
                visited[parent_node.player_row][parent_node.player_col] = True
                new_depth = parent_node.depth + 1
                new_apples = parent_node.apples_left.copy()
                if (next_row <= rows and next_col <= cols and next_row >= 0 and next_col >= 0): #check bounds
                    if visited[next_row][next_col] == False: #check if node was visited
                        if initial_level_matrix[next_row][next_col] != 'W': #check for wall
                            expanded = True
                            if initial_level_matrix[next_row][next_col] == 'A': #check for apple
                                for apple in new_apples: #remove collected apple
                                    if apple == (next_row,next_col):
                                        #print('apple coordinates: ' + str(apple))
                                        #print('player coordinates: ' + str(next_row) + ", " + str(next_col))
                                        #print(new_apples)
                                        new_apples.remove(apple)
                                        visited = [[False for x in range(cols)] for y in range(rows)]
                                        #print(new_apples)
                                        #print(parent_node.seq + direction)
                                        #input()
                            child_node = Node(parent_node, next_row, next_col, new_depth, direction, visited, new_apples)
                            self.generated_node_count += 1
                            s.append(child_node)
                            if len(child_node.apples_left) == 0: #check if all apples are collected
                                move_sequence = child_node.seq
                                finished = True
                                test = child_node
                                break
        if not finished:
            print("Solution not found")
        
        """
            YOUR CODE ENDS HERE
            return move_sequence
        """
        return move_sequence
