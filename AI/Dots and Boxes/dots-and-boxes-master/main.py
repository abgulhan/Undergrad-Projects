import sys
from dots_and_boxes import DotsAndBoxes as dab
import dots_and_boxes_ai as ai


if __name__ == "__main__":
    if (len(sys.argv) > 2):
        file = sys.argv[2]
        method = sys.argv[1]

        game = dab.read_file(file)
        if method == "minimax":
            print("method is minimax")
            result = ai.minimax(game)
        else:
            print("method is alpha-beta pruning")
            result = ai.alphabeta(game)
        #print("game finished")
        #print(result[0])
        #print(result[1])
        print(result[1][0]) #player max (red)
        print(result[1][1]) #pleyer min (blue)
    else:
        print("usage: main.py <[method = alphabeta, minimax] , [filename]>")
        exit()
    
    
 
