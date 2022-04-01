inf = float("inf")

def minimax(node, is_max = True, move = (0,0,'v')):
    children = node.get_moves()

    if len(children) == 0:
        #print("utility: " + str(node.utility()))
        #print("score: " + str(node.get_score()))
        return [node.utility(), node.get_score()]

    if is_max:
        best_score = -inf
        player_scores = []
        for child in children: # child = (x,y,direction)
            current = node.copy()
            turn = current.move(child, is_max) #turn is true if player has scored else it is false
            v = minimax(current, turn, child) #if player has scored(turn == true) then do not switch to next player (is_max == true)
            best_score = max(best_score, v[0])
            #keep final score
            if v[0] >= best_score: player_scores = v[1]
        return [best_score, player_scores]
    else:
        worst_score = inf
        player_scores = []
        for child in children:
            current = node.copy()
            turn = current.move(child, is_max) #if player has scored (turn == true) do not switch to next player (is_max == false => is_max == not turn)
            v = minimax(current, not turn, child)
            worst_score = min(worst_score, v[0])
            #keep final score
            if v[0] <= worst_score: player_scores = v[1]
        return [worst_score, player_scores]



def alphabeta(node, alpha = -inf, beta = inf, is_max = True, move = (0,0,'v')):
    children = node.available_moves

    if len(children) == 0:
        return [node.utility(), node.get_score()]

    if is_max:
        player_scores = []
        for child in children: # child = (x,y,direction)
            current = node.copy()
            turn = current.move(child, is_max)
            v = alphabeta(current, alpha, beta, turn, child)
            if v[0] > alpha:#best_score:
                player_scores = v[1]
                alpha = v[0]#max(best_score, alpha)
            if alpha >= beta: #pruning
                break
        return [alpha, player_scores]
    else:
        player_scores = []
        for child in children:
            current = node.copy()
            turn = current.move(child, is_max)
            v = alphabeta(current, alpha, beta, not turn, child)
            if v[0] < beta:
                player_scores = v[1]
                beta =  v[0]#min(beta, worst_score)
            if beta <= alpha:
                break
        return [beta, player_scores]
