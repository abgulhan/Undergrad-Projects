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
    
    def __init__(self, parent_node, player_row, player_column, depth, chosen_dir, h_value, visited, apples_left):
        self.parent_node = parent_node
        self.player_row = player_row
        self.player_col = player_column
        self.depth = depth
        self.chosen_dir = chosen_dir
        self.h = h_value
        self.visited = visited
        self.apples_left = apples_left
        
        self.seq = ""
        if (self.chosen_dir == "X"):
            pass
        else:
            self.seq = parent_node.seq + self.chosen_dir
    
    def __lt__(self, other):
        return self.depth + self.h < other.depth + other.h
       

class PriorityQueue: 
    def __init__(self):
        self.elements = []
    
    def empty(self):
        return len(self.elements) == 0
    
    def put(self, item, priority):
        heapq.heappush(self.elements, (priority, item))
    
    def get(self):
        return heapq.heappop(self.elements)[1]
    def size(self):
        return len(self.elements)


class AStarAgent(Agent):

    def __init__(self):
        super().__init__()

    def solve(self, level_matrix, player_row, player_column):
        super().solve(level_matrix, player_row, player_column)
        move_sequence = []

        """
            YOUR CODE STARTS HERE
            fill move_sequence list with directions chars
        """

        def calculate_farthest_pair(apples): #get pair of apples with biggest real distance, used as part of heuristic
            if len(apples) <= 0:
                return[(0,0),(0,0)]
            if len(apples) == 1:
                return [(apples[0][0],apples[0][1]), (apples[0][0],apples[0][1])]
            max_dist = 0
            result = [apples[0],apples[0]]
            for i in range(len(apples)-1):
                for j in range(i,len(apples)):
                    dist = self.real_distance(apples[i][0],apples[i][1],apples[j][0],apples[j][1])
                    if dist > max_dist:
                        max_dist = dist
                        result[0],result[1] = apples[i],apples[j]
            return result
        def distance_to_closest_apple_in_pair(player_row, player_col, farthest_pair, apple_list, real_dist=False): #calculate distance of player to closest apple in pair tuple.  real_dist 
            if not real_dist: #use manhattan distance
                dist0 = abs(player_row- farthest_pair[0][0]) +abs(player_col-farthest_pair[0][1]) #manhattan distance to first apple
                dist1 = abs(player_row- farthest_pair[1][0]) +abs(player_col-farthest_pair[1][1]) #manhattan distance to second apple
            else: # use real distance.  This is currently inefficient however if you precalculate the distances for each node this will be much faster.  This method is a better heuristic compared to using manhattan distance.  It gives about a 30% lower generated node count for level 4 but takes about 50-100x longer to run
                dist0 = self.real_distance(player_row, player_col, farthest_pair[0][0], farthest_pair[0][1]) #real distance to first apple
                dist1 = self.real_distance(player_row, player_col, farthest_pair[1][0], farthest_pair[1][1]) #real distance to second apple
            if dist0<dist1: return dist0;
            elif dist1<dist0: return dist1;
            elif len(apple_list)==1: #only one apple left, both pairs are the same apple
                return dist0
            elif dist1==dist0:  #tie breaker
                nearest0 = 0
                nearest1 = 0
                for apple in apple_list: #calculate manhattan distance of all apples to the two apples in the farthest pair
                    nearest0 += abs(farthest_pair[0][0]-apple[0]) + abs(farthest_pair[0][1]-apple[1])
                    nearest1 += abs(farthest_pair[1][0]-apple[0]) + abs(farthest_pair[1][1]-apple[1])
                if nearest0>nearest1: return dist1 #return apple from pair that has the most apples closer to it
                else: return dist0

        initial_level_matrix = [list(row) for row in level_matrix] #deepcopy(level_matrix)

        q = PriorityQueue()
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

        farthest_pair = calculate_farthest_pair(initial_apples) #two apples with furthest real distance
        distance_between_farthest_pair = self.real_distance(farthest_pair[0][0],farthest_pair[0][1],farthest_pair[1][0],farthest_pair[1][1])
        distance_to_farthest_pair = distance_to_closest_apple_in_pair(player_row, player_col, farthest_pair, initial_apples)

        #heuristic = real distance of two farthest apples + real distance of player to the closest of these two apples
        initial_h = distance_between_farthest_pair + distance_to_farthest_pair + len(initial_apples)

        s0 = Node(None, player_row, player_col, 0, "X", initial_h, initial_visited, initial_apples)
        self.generated_node_count = 1
        q.put(s0, initial_h)
        move_dir = ['U', 'D', 'L', 'R']
        finished = False
        expanded = True
        while (q.empty() == False and finished == False):
            if expanded:
                self.expanded_node_count += 1
                expanded = False
            node_count = q.size()
            if node_count > self.maximum_node_in_memory_count:
                self.maximum_node_in_memory_count = node_count
            parent_node = q.get()
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
                                        #check heuristic######
                                        if apple in farthest_pair: #apple in farthest pair has been collected
                                            pass

                                            farthest_pair = calculate_farthest_pair(new_apples) #recalculate farthest pair
                                            distance_between_farthest_pair = self.real_distance(farthest_pair[0][0],farthest_pair[0][1],farthest_pair[1][0],farthest_pair[1][1])
                                            #print('--Farthest pair collected')
                                            #print('New pair: ' + str(farthest_pair) + " distance: " + str(distance_between_farthest_pair))
                                        #print(new_apples)
                                        #print(parent_node.seq + direction)
                                        #input()
                            distance_to_farthest_pair = distance_to_closest_apple_in_pair(next_row, next_col, farthest_pair, new_apples)
                            h = distance_between_farthest_pair +distance_to_farthest_pair + len(new_apples)

                            child_node = Node(parent_node, next_row, next_col, new_depth, direction, h, visited, new_apples)
                            self.generated_node_count += 1
                            q.put(child_node,h+new_depth)
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
