class DotsAndBoxes:

    def __init__(self, height = 0, width = 0):
        self.linesy = [[False for i in range(width+1)] for j in range(height)] #[height][width+1] #hold all Vertical lines
        self.linesx = [[False for i in range(width)] for j in range(height+1)]#[height+1][width] #hold all Horizontal lines
        #print(self.linesx)
        #print(self.linesx[0][0])
        #print(self.linesx[1][0])
        #print(self.linesy)
        self.size = (height, width) #change to boxes?
        self.available_moves = []
        self.score = [0, 0] # Player Red (0), Player Blue (1)
    @staticmethod
    def read_file(file_name): #read file and generate board
        fp = open(file_name, "r")
        
        height = int(fp.readline())
        width = int(fp.readline())
        #print(height)
        #print(width)
        if width > 3 and width < 1 and height > 3 and height < 1:
            print("Board dimensions cannot be greater then 3 or smaller then 1")
            return -1

        board = DotsAndBoxes(height, width) 
        empty = 0
        #print("=====")
        #print(board.linesx)
        #print(board.linesy)
        for i in range(width*(height+1)): #read horizontal lines
            x = i // width
            y = i % width
            line = int(fp.readline())
            if line == 0: 
                line = False
                empty += 1
            else:
                line = True
            #print("x,y : " + str(x) + "," + str(y))
            board.linesx[x][y] = line
        #print("=++++==")
        #print(board.linesy)

        for i in range((width+1)*height):#read vertical lines
            x = i // (width+1)
            #print(x)
            y = i % (width+1)
            line = int(fp.readline())
            if line == 0: 
                line = False
                empty += 1
            else:
                line = True
            #print("----y")
            #print("i: " + str(i))
            #print("width: " + str(width))
            #print("x,y = " + str(x) + "," + str(y))
            board.linesy[x][y] = line
        
        board.score[0] = int(fp.readline())
        board.score[1] = int(fp.readline())
        if empty == 0 or empty > 16:
            print("the number of empty edges must be more then 0 and less then or equal to 16")
            return -1
        board.available_moves = board.list_moves() #find all available moves and store them to board.available_moves
        return board

    def check_box(self, loc, player):
        completed = False #did player complete a square
        direction = loc[2]
        x = loc[0]
        y = loc[1]
        height = self.size[0]
        width = self.size[1]
        #print(player)
        if player == True: 
            player = 0 
            player_name = 'red'
        else: 
            player = 1 
            player_name = 'blue'
        if direction == 'x': # horizontal line
            if x >= 1 and self.linesx[x][y] and self.linesx[x-1][y] and self.linesy[x-1][y] and self.linesy[x-1][y+1]: #check square above line
                completed = True
                self.score[player] += 1
            if x < height and self.linesx[x][y] and self.linesx[x+1][y] and self.linesy[x][y] and self.linesy[x][y+1]: #check square below line
                completed = True
                self.score[player] += 1
        else: #vertical line
            if y >= 1 and self.linesy[x][y] and self.linesy[x][y-1] and self.linesx[x][y-1] and self.linesx[x+1][y-1]: #check square left of line
                completed = True
                self.score[player] += 1
            if y < width and self.linesy[x][y] and self.linesy[x][y+1] and self.linesx[x][y] and self.linesx[x+1][y]: #check square right of line
                completed = True
                self.score[player] += 1
        #if completed:
            #print("player " + str(player_name) + " has scored!")
        return completed

    def move(self, loc, player):
        #check if line is empty
        if player: plyr = 'max'
        else: plyr = 'min'        
        #print(plyr + " moved to " +str(loc[2]) + " " + str(loc[0]) + "," + str(loc[1]))
        if loc[2] == 'x' and self.linesx[loc[0]][loc[1]] == True:
            print("Line already occupied")
            return -1
        if loc[2] == 'y' and self.linesy[loc[0]][loc[1]] == True:
            print("Line already occupied")
            return -1
        direction = loc[2]
        x = loc[0]
        y = loc[1]
        #fill in line
        if direction == 'x':
            self.linesx[x][y] =  True
        elif direction == 'y':
            self.linesy[x][y] = True

        self.available_moves.remove(loc)
        #check if line closes a square and return true if closes
        return self.check_box(loc, player)

    def list_moves(self):
        moves = []
        width = self.size[1]
        height = self.size[0]
        #print("height: " + str(height))
        for x in range(height+1): #check horizontal (x axis) lines
            for y in range(width):
                #print("x,y" + str(x) + "," + str(y))
                if self.linesx[x][y] == False:
                    moves.append((x,y,'x'))
        for x in range(height): #check vertical (y axis) lines
            for y in range(width+1):
                if self.linesy[x][y] == False:
                    moves.append((x,y,'y'))
        return moves

    def is_finished(self):
        for row in self.linesx:
            for line in row:
                if line == False:
                   return False 
        for row in self.linesy:
            for line in row:
                if line == False:
                   return False 
        return True

    def copy(self):
        copy = DotsAndBoxes()
        copy.size = self.size
        copy.linesx = [row[:] for row in self.linesx]
        copy.linesy = [row[:] for row in self.linesy]
        copy.available_moves = self.available_moves[:]
        copy.score = self.score[:]
        return copy

    def utility(self):
        return (self.score[0] - self.score[1])

    def get_moves(self):
        return self.available_moves

    def get_score(self):
        return (self.score[0], self.score[1])

    def get_score_from_utility(self, utility):
        max_score = self.size[0] * self.size[1]
        x = (max_score + utility)/2
        y = max_score - x
        return [x,y]
