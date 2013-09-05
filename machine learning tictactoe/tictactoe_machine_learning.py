from random import randrange

def learnFromWin(index, move, player):
	playerBook = player
	for x in range (0,10):
		playerBook[index].append(move)

def learnFromLoss(index, move, player):
	playerBook = player
	if playerBook[index].count(move) >= 10: 
		for x in range (0,9):
			playerBook[index].remove(move)

def whoWon(board):
	if board[0] == board[1] == board[2] and board[0] != " ":
		return board[0]

	if board[3] == board[4] == board[5] and board[3] != " ":
		return board[3]
	
	if board[6] == board[7] == board[8] and board[6] != " ":
		return board[6]
	
	if board[0] == board[3] == board[6] and board[0] != " ":
		return board[0]

	if board[1] == board[4] == board[7] and board[1] != " ":
		return board[1]

	if board[2] == board[5] == board[8] and board[2] != " ":
		return board[2]

	if board[0] == board[4] == board[8] and board[0] != " ":
		return board[0]

	if board[2] == board[4] == board[6] and board[2] != " ":
		return board[2]

	for x in range(0,9):
		if board[x] == " ":
			return " "

	return "D"

def generatePossibleMoves(board):
	movesList = []
	for index in range(0,9):
		if board[index]==" ":
			for x in range(0,10):
				movesList.append(index)
	return movesList

def addMark(board, move, mark):
	board[move] = mark
	return board

def getMovePlayer1(board):
	index = getBoardIndex(board, player1BoardStates)

	boardState = ''.join(board)

	if index == -1:
		player1BoardStates.append(boardState)
		player1MovesBook.append(generatePossibleMoves(board))
		index = len(player1MovesBook)-1

	move = player1MovesBook[index][randrange(len(player1MovesBook[index]))]

	player1MovesPlayed.append(move)
	player1BoardsPlayed.append(index)

	return move

def getMovePlayer2(board):
	index = getBoardIndex(board, player2BoardStates)

	boardState = ''.join(board)

	if index == -1:
		player2BoardStates.append(boardState)
		player2MovesBook.append(generatePossibleMoves(board))
		index = len(player2MovesBook)-1

	move = player2MovesBook[index][randrange(len(player2MovesBook[index]))]

	player2MovesPlayed.append(move)
	player2BoardsPlayed.append(index)

	return move

def getBoardIndex(board, playerBoardStates):
	boardState = ''.join(board)
	for index in range (0,len(playerBoardStates)):
		if(playerBoardStates[index]==boardState):
			return index

	return -1

def generateBoard():
	return list("         ")

player1BoardStates = []
player1MovesBook = []
player1MovesPlayed = []
player1BoardsPlayed = []

player2BoardStates = []
player2MovesBook = []
player2MovesPlayed = []
player2BoardsPlayed = []

xWins = 0
oWins = 0
draw = 0

player1Learns = True
player2Learns = True

for x in range (0, 100000):
	board = generateBoard()

	del player1MovesPlayed[:]
	del player1BoardsPlayed[:]
	del player2MovesPlayed[:]
	del player2BoardsPlayed[:]

	if x%2 == 0:
		while True:
			board = addMark(board, getMovePlayer1(board), "X")
			outcome = whoWon(board)
			if outcome != " ":
				break

			board = addMark(board, getMovePlayer2(board), "O")
			outcome = whoWon(board)
			if outcome != " ":
				break

	else:
		while True:
			addMark(board, getMovePlayer2(board), "O")
			outcome = whoWon(board)
			if outcome != " ":
				break

			addMark(board, getMovePlayer1(board), "X")
			outcome = whoWon(board)
			if outcome != " ":
				break
	
	if outcome == "D":
		draw += 1
		if player1Learns == True:
			for x in range (0, len(player1MovesPlayed)):
				learnFromLoss(player1BoardsPlayed[x], player1MovesPlayed[x], player1MovesBook)
		if player2Learns == True:
			for y in range (0, len(player2MovesPlayed)):
				learnFromLoss(player2BoardsPlayed[y], player2MovesPlayed[y], player2MovesBook)

	if outcome =="X":
		xWins += 1
		if player1Learns == True:
			for x in range (0, len(player1MovesPlayed)):
				learnFromWin(player1BoardsPlayed[x], player1MovesPlayed[x], player1MovesBook)
		if player2Learns == True:
			for y in range (0, len(player2MovesPlayed)):
				learnFromLoss(player2BoardsPlayed[y], player2MovesPlayed[y], player2MovesBook)

	if outcome == "O":
		oWins += 1
		if player1Learns == True:
			for x in range (0, len(player1MovesPlayed)):
				learnFromLoss(player1BoardsPlayed[x], player1MovesPlayed[x], player1MovesBook)
		if player2Learns == True:
			for y in range (0, len(player2MovesPlayed)):
				learnFromWin(player2BoardsPlayed[y], player2MovesPlayed[y], player2MovesBook)

print "X wins:"
print xWins
print "O wins:"
print oWins
print "Draws:"
print draw
