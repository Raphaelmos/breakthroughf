#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <string>
#include "mybt.h"
#include <algorithm> 
#include <list>
#include <cstddef>


/* Use values already given in mybt.h and not overcomplicate it for nothing, no need to recreate new variables*/

typedef int score_t;
bool isTerminalState(bt_t board);
score_t heuristicEvaluation(bt_t board);  
std::list<bt_move_t> generateLegalMoves(bt_t board);
void makeMove(bt_t& board, bt_move_t move);
void undoMove(bt_t& board, bt_move_t move);

// Data types
typedef struct bt_t board_t; 
typedef struct bt_move move_t;
typedef struct bt_t board_t;
typedef struct bt_move move_t; 
double evaluateBoard(board_t board);
move_t search(board_t board, int depth);
// Use color definitions
#define WHITE 0
#define BLACK 1
const int maxDepth = 10;
// Constants
const int INVALID_SCORE = -99999;

bt_t B;
int boardwidth = 0;
int boardheight = 0;
bool white_turn = true;
int ProximityToWin(bt_t board, int color);
int MobilityScore(bt_t board);

#ifndef VERBOSE_RAND_PLAYER
#define VERBOSE_RAND_PLAYER
bool verbose = true;
bool showboard_at_each_move = false;
#endif

// Heuristic function
int Heuristic(bt_t board) {
bool ControlsCenter(bt_t board, int color);
bool ControlsEdge(bt_t board, int color);
int score = calculate_score();
// score = 0;
printf("Heuristic score: %d\n", score);

return score;

// Material score
score += 10 * (board.nb_white_pieces - board.nb_black_pieces);

// Control center bonus
if(ControlsCenter(board, WHITE))
score += 50;
if(ControlsCenter(board, BLACK))
score -= 50;


// Edge control penalty
if(ControlsEdge(board, BLACK))
score -= 20;

// Proximity to goals
score += ProximityToWin(board, WHITE) * 100;
score -= ProximityToWin(board, BLACK) * 100;

// Mobility
score += MobilityScore(board);
return score;

}

// Helper functions

bool ControlsCenter(bt_t board, int color) {

// Check control of center squares
int centerSquares = 0;

for(int i=1; i<board.nbl-1; i++) {
for(int j=1; j<board.nbc-1; j++) {
    if(board.board[i][j] == color)
    centerSquares++;

}}

return centerSquares > 4;

}

int ProximityToWin(bt_t board, int color) {

int distance = board.nbl;

for(int i=0; i<board.nb_white_pieces; i++) {

    if(board.white_pieces[i].line == 0)
  distance = 0;
else  
  distance = std::min(distance, board.nbl - board.white_pieces[i].line);
  }

return distance;

}

int MobilityScore(bt_t board) {

int whiteMobility = board.nb_moves;

board.update_moves(BLACK);
int blackMobility = board.nb_moves;

return whiteMobility - blackMobility;

}

bool ControlsEdge(bt_t board, int color) {

int edgeSquaresControlled = 0;

// Check top edge
for(int j=0; j<board.nbc; j++) {
if(board.board[0][j] == color)
edgeSquaresControlled++;
}

// Check bottom edge
for(int j=0; j<board.nbc; j++) {
if(board.board[board.nbl-1][j] == color)
edgeSquaresControlled++;
}

// Check left edge
for(int i=1; i<board.nbl-1; i++) {
if(board.board[i][0] == color)
edgeSquaresControlled++;
}

// Check right edge
for(int i=1; i<board.nbl-1; i++) {
if(board.board[i][board.nbc-1] == color)
edgeSquaresControlled++;
}

    return edgeSquaresControlled > 4;

}

bt_move_t heuristic_search(bt_t board) {

  int depth = 1;
  bt_move_t bestMove = null;

  while(depth <= maxDepth) {

    bestMove = recursive_search(board, depth, -INFINITY, INFINITY);

    if(bestMove != null) {
      printf("Found best move at depth %d\n", depth);
      break;
    }

    depth++;

  }

  return bestMove;

}

bt_move_t recursive_search(bt_t board, int depthRemaining, int alpha, int beta) {

  if(isTerminalState(board)) {
    return null; 
  }

  if(depthRemaining == 0) {

    int score = heuristicEvaluation(board);
    printf("Heuristic score at depth 0: %d\n", score);
    return score;

  }

  List<bt_move_t> legalMoves = generateLegalMoves(board);

  for(bt_move_t move : legalMoves) {

    makeMove(board, move);

    int score = -recursive_search(board, depthRemaining-1, -beta, -alpha);

    undoMove(board, move);

    if(score > alpha) {
      alpha = score;
      if(alpha >= beta) {
        return move; 
      }
    }

  }

  return null;

}
/*
move_t recursiveSearch(board_t board, int depth) {

  if(depth == 0 || isTerminal(board)) 
    return calculate_score(board);

  foreach(move in generateMoves(board)) {

    makeMove(board, move);
    score = -recursiveSearch(cloneBoard(board), depth-1);  
    undoMove(board, move);

    if(score > bestScore)
      return move;
  }

  return NULL;
}
*/
bt_move_t heuristic(board_t board){
  return search(board, maxDepth);
}






const int INFINITY = -99999;
// Define bt_move_t struct
struct bt_move_t {
  int line_i, col_i, line_f, col_f;
};

int Heuristic(bt_t board) {

  int score = 0;

  // Material heuristic 
  score += 10 * (board.whitePieces - board.blackPieces);

  // Mobility heuristic
  score += board.whiteMobility - board.blackMobility;

  // Control center
  if (boardControlsCenter(board, WHITE))
    score += 50;

  return score;

}

bt_move_t recursive_search(bt_t board, int depthRemaining, int alpha, int beta) {

  if (depthRemaining == 0 || isTerminal(board)) {
    return Heuristic(board);
  }

  std::list<bt_move_t> moves = GenerateMoves(board);

  bt_move_t best_move;

  for(bt_move_t move : moves) {

    MakeMove(board, move);
    int score = -recursive_search(board, depthRemaining-1, -beta, -alpha);
    UndoMove(board, move); 

    if(score > alpha) {
      alpha = score;
      best_move = move;
      if(alpha >= beta)
        return best_move;
    }

  }

  return best_move;

}

bt_move_t heuristic_search(bt_t board) {

  bt_move_t best_move;  
  int alpha = -INFINITY, beta = INFINITY;

  best_move = recursive_search(board, MAX_DEPTH, alpha, beta);

  return best_move;

}








void help() {
  fprintf(stderr, "  quit\n");
  fprintf(stderr, "  echo ON | OFF\n");
  fprintf(stderr, "  help\n");
  fprintf(stderr, "  name <PLAYER_NAME>\n");
  fprintf(stderr, "  newgame <NBCOL> <NBLINE>\n");
  fprintf(stderr, "  genmove\n");
  fprintf(stderr, "  play <L0C0L1C1>\n");
  fprintf(stderr, "  showboard\n");
}
void name() {
  printf("= rand_player\n\n");
}
void newgame() {
  if((boardheight < 1 || boardheight > 10) && (boardwidth < 1 || boardwidth > 10)) {
    fprintf(stderr, "boardsize is %d %d ???\n", boardheight, boardwidth);
    printf("= \n\n");
    return;
  }
  B.init(boardheight, boardwidth);
  white_turn = true;
  if(verbose) fprintf(stderr, "ready to play on %dx%d board\n", boardheight, boardwidth);
  printf("= \n\n");
}
void showboard() {
  B.print_board(stderr);
  printf("= \n\n");
}
void genmove() {
  int ret = B.endgame();
  if(ret != EMPTY) {
    fprintf(stderr, "game finished\n");
    if(ret == WHITE) fprintf(stderr, "white player wins\n");
    else fprintf(stderr, "black player wins\n");
    printf("= \n\n");
    return;
  }

  bt_move_t best_move = heuristic_search(B);
  B.play(best_move);
 if(verbose) {
    best_move.print(stderr, white_turn, B.nbl);
    fprintf(stderr, "\n"); 
  }
  white_turn = !white_turn;
  printf("=%s\n\n", best_move.tostr(B.nbl).c_str());
  /*
  bt_move_t m = B.get_rand_move();
  B.play(m);
  if(verbose) {
    m.print(stderr, white_turn, B.nbl);
    fprintf(stderr, "\n");
  }
  white_turn = !white_turn;
  printf("= %s\n\n", m.tostr(B.nbl).c_str()); */
}
void play(char a, char b, char c, char d) {
  bt_move_t m;
  m.line_i = boardheight-(a-'0');
  m.col_i = b-'a';
  m.line_f = boardheight-(c-'0');
  m.col_f = d-'a';
  if(B.can_play(m)) {
    B.play(m);
    if(verbose) {
      m.print(stderr, white_turn, B.nbl);
      fprintf(stderr, "\n");
    }
    white_turn = !white_turn;
  } else {
    fprintf(stderr, "CANT play %d %d %d %d ?\n", m.line_i, m.col_i, m.line_f, m.col_f);
  }
  if(showboard_at_each_move) showboard();
  printf("= \n\n");
}
int main(int _ac, char** _av) {
  bool echo_on = false;
  setbuf(stdout, 0);
  setbuf(stderr, 0);
  if(verbose) fprintf(stderr, "rand_player started\n");
  char a,b,c,d; // for play cmd
  for (std::string line; std::getline(std::cin, line);) {
    if(verbose) fprintf(stderr, "rand_player receive %s\n", line.c_str());
    if(echo_on) if(verbose) fprintf(stderr, "%s\n", line.c_str());
    if(line.compare("quit") == 0) { printf("= \n\n"); break; }
    else if(line.compare("echo ON") == 0) echo_on = true;
    else if(line.compare("echo OFF") == 0) echo_on = false;
    else if(line.compare("help") == 0) help();
    else if(line.compare("name") == 0) name();
    else if(sscanf(line.c_str(), "newgame %d %d\n", &boardheight, &boardwidth) == 2) newgame();
    else if(line.compare("genmove") == 0) genmove();
    else if(sscanf(line.c_str(), "play %c%c%c%c\n", &a,&b,&c,&d) == 4) play(a,b,c,d);
    else if(line.compare("showboard") == 0) showboard();
    else if(line.compare(0,2,"//") == 0) ; // just comments
    else fprintf(stderr, "???\n");
    if(echo_on) printf(">");
  }
  if(verbose) fprintf(stderr, "bye.\n");

  return 0;
}




