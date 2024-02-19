#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <string>
#include "mybt.h"
#include <algorithm> 
#include <list>
#include <cstddef>
// #include "constants.h"

bt_t B;
int boardwidth = 0;
int boardheight = 0;
bool white_turn = true;

#ifndef VERBOSE_RAND_PLAYER
#define VERBOSE_RAND_PLAYER
bool verbose = true;
bool showboard_at_each_move = false;
#endif
const int MAX_DEPTH = 10;
const int INFINITY = 999;
std::list<bt_move_t> GenerateMoves(bt_t board);
void MakeMove(bt_t& board, bt_move_t move);
void UndoMove(bt_t& board, bt_move_t move);
bool isTerminal(bt_t board);
std::list<bt_move_t> moves;
int numMoves = GenerateMoves(board, moves);
bool boardControlsCenter(bt_t, int);
int GenerateMoves(bt_t, std::list<bt_move_t>&);
// Define bt_move_t struct 
/*
struct bt_move_t {
  int line_i, col_i, line_f, col_f;
};
*/

std::list<bt_move_t> GenerateMoves(bt_t& board) {

  std::list<bt_move_t> moves;

  // Loop through pieces
  for(int i=0; i<board.nb_white_pieces; i++) {

    // Generate all legal moves for this piece
    // Check can_move functions
    
    // Add valid moves to list
    bt_move_t move;
    // Set move details
    moves.push_back(move); 
  }

  // Similarly for black pieces

  return moves;

}

bool isTerminal(bt_t& board) {

  // Check if game ended 
  if(board.endgame() != EMPTY) 
    return true;

  // Check for insufficient material
  if(board.nb_white_pieces < 2 && board.nb_black_pieces < 2)
     return true;

  // No legal moves 
  if(GenerateMoves(board).empty())
     return true;

  return false;

}
/*
int Heuristic(bt_t board) {

  int score = 0;

  // Material 
  score += 10 * (board.nb_white_pieces - board.nb_black_pieces);

  // Mobility
  std::list<bt_move_t> moves; 
  int whiteMoves = GenerateMoves(board).size();
  score += whiteMoves;  

  // Control center
  if(boardControlsCenter(board, WHITE))
    score += 50;

  return score;

}


*/

int Heuristic(bt_t board) {

  int score = 0;

  // Material heuristic 
  score += 10 * (board.nb_white_pieces - board.nb_black_pieces);

  // Mobility heuristic
  // score += board.whiteMobility - board.blackMobility;
    score += B.nb_white_moves - B.nb_black_moves;

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
    int score = recursive_search(board, depth-1, alpha, beta);
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
  printf("= %s\n\n", best_move.tostr(B.nbl).c_str());
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