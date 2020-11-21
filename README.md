# Filler
Hive Helsinki school project called filler.

Filler is an algorithmic game which consists in filling a grid of a known size in advance with pieces of random size and shapes, without the pieces being stacked more than one square above each other and without them exceeding the grid. If one of these conditionsis not met, the game stops. Each successfully placed piece yields a number of points, and has only one player, the goal of the game could be to get the best score possible. However, it is with two players that the filler takes all his interest. Each player has for the purpose of placing as many pieces as possible while attempting to prevent his opponent from doing the same. At the end of the game, the one with the most points wins the match.

# Usage
Clone the repository and compile the program:
> make 

To get rid of the object files, use:
> make clean

To run the program, go into the resources folder and run:
> ./filler_vm -p1 [user1] -p2 [user2] -f maps/map(00/01/02)

The users are programs that are formatted as "*.filler". \
The files inside resources folder were provided by the school for the project and are not my work.

# The algorithm
I approached the problem by trying to understand what is the most efficient way of eliminating possible moves by the opponent while maximizing the efficient use of space from my point of view. In the end there was a clear winning strategy; always place a piece as close as possible to the opponent. There is a point to be made that this is not always the best solution. The algorithm could be even better if we use this strategy, but also check the boardstate which we could use to decide between two equally close positions and choose the best one.

I achieved the desired result by creating a heatmap of the board, which gave values to each position acending the further we get from the opponents pieces. This way we can check the lowest combined value of each position on the board and place the piece to a position with the lowest sum. This method turned out to be really good and it ended up beating all opponents given in the subject with extremely high probability. My algorithm was also able to beat most other algorithms created by my fellow students at the school. It is also one of the faster ones.

# The subject

- In this game, two players fight each other. They play one after the other.
- The goal is to collect as many points as possible by placing the highest number of pieces on the the game board.
- The board is defined by X columns and N lines, it will then become X*N cells.
- At the beginning of each turn, you will receive your game piece.
- A game piece is defined by X columns and N lines, so it will be X*N cells. Insidee ach game piece, will be included a shape of one or many cells.
- To be able to place a piece on the board, it is mandatory that one, and only onec ell of the shape (in your piece) covers the cell of a shape placed previously (your territory).
- The shape must not exceed the dimensions of the board.
- When the game starts, the board already contains one shape.
- The game stops at the first error: either when a game piece cannot be placedanymore or it has been wrongly placed.

**The Board** \
A board is a two-dimensional grid with an arbitrary number of rows and columns. To launch the game an initial board must be passed as an argument to the VM. This initial board must have a starting form for each player.
>Plateau 14 30: \
    012345678901234567890123456789 \
000 .............................. \
001 .............................. \
002 ..X........................... \
003 .............................. \
004 .............................. \
005 .............................. \
006 .............................. \
007 .............................. \
008 .............................. \
009 .............................. \
010 .............................. \
011 ...........................O.. \
012 .............................. \
013 ..............................

**The tokens** \
The tokens are managed randomly by the VM. You can’t predict their size or shape untilthe VM transmits them to your program. Here are some arbitrary examples of possibletokens to give you an idea:
>Piece 4 7 \
..\*\*... \
..\*\*... \
.\*\*\*... \
..\*\*\*..

>Piece 3 3 \
.\*\* \
.\*. \
...

**The player** 
- The executable that will enable you to play the filler is attached to this subject.
- For this project, you will have to create a filler player. Your goal is to win:
  - It will read the board and the game pieces placed on the standard output.
  - Each turn the filler rewrites the board map and includes a new piece to be placed.
  - In order to place the game piece on the board, the player will have to write it’s coordinates on the standard ouput.
  - The following format must be used “Y X\n”.
  - You will collect points each time you place a piece.

**Multiplayers** 
- Player number:
  - The first two lines of the filler must be in the following format: $$$ exec pPLAYER_NUMBER : [PLAYER_NAME]
  - The filler will only send the line that concerns your program. You’ll have to get your player number.
  - If you are Player 1 your program will be represented by “o” and “O”. If you are Player 2, your program will be represented by “x” and “X”. The first step will be to get your player number.
  - The lowercases (“x” or “o”) will highlight the piece last placed on the board. At the following turns, that same piece will be represented by the uppercase letters (“X” or “O”), as it won’t be the piece last placed anymore.
  - You will collect points each time you place a piece.
- How the game works:
  - At each turn, the filler will send the updated map and a new token to the player concerned.
  - The player concerned will write on the standard output his or her piece’s coordinates to place it on the board.
  - The filler will send the map and a new piece to the other player.

