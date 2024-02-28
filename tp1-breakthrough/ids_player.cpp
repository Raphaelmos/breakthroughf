#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <string>
#include "mybt.h"
#include <limits>

bt_t B;

int boardwidth = 0;
int boardheight = 0;
bool white_turn = true;

#ifndef VERBOSE_RAND_PLAYER
#define VERBOSE_RAND_PLAYER
bool verbose = true;
bool showboard_at_each_move = false;
#endif

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


  bt_move_t best_move;
double max = -INFINITY;
int maxDepth = 6;
  // Transposition table
TranspositionTable TT;
bt_move_t best_move;
// Alpha-beta search function
int AlphaBeta(bt_t& board, int alpha, int beta, int depth) {

  // Base case
  if(depth == 0 || board.isGameOver()) 
    return board.evaluate();

  // TT lookup  
  Entry* e = TT.lookup(board.hash());

  if(e->depth >= depth)
    return e->score;

  int score = -INFINITY;

  // Generate all moves
  std::vector<Move> moves = board.generateMoves();

  // Search moves
  foreach(Move m : moves) {

    board.makeMove(m);

    int score = -AlphaBeta(board, -beta, -alpha, depth-1);

    board.takeBack(m);

    if(score > alpha) {
      alpha = score;
      if(score >= beta) {
        TT.store(board.hash(), score, depth);
        return score; 
      }
    }
  }

  TT.store(board.hash(), alpha, depth);
  return alpha;

}

// IDs function 
Move IDS(bt_t board) {

  int maxDepth = 6;

  for(int depth=1; depth<=maxDepth; depth++) {

    int score = AlphaBeta(board, -INFINITY, INFINITY, depth);

    if(score > bestScore) {
      bestScore = score;
      best_move = board.lastMove(); 
    }

  }

  return best_move;

}
  
/*
for (int depth = 1; depth <= maxDepth; depth++) {
  bt_t current_B = B;
  current_B.update_moves();
  double currentMax = -INFINITY;
  bt_move_t current_best_move;

  for (int i = 0; i < current_B.nb_moves; i++) {
    bt_move_t m = current_B.moves[i];
    current_B.play(m);
    double eval = current_B.eval();

    if (eval > currentMax) {
      currentMax = eval;
      current_best_move = m;
    }
  }

  if (currentMax > max) {
    max = currentMax;
    best_move = current_best_move;
  }
}
*/
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




double bt_t::eval() {
  int white_score = 0;
  int black_score = 0;
  int value_trade = 1;
  int valce = 2;
  int valcm = 1;

  for (int i = 0; i < nbl; i++) {
    for (int j = 0; j < nbc; j++) {
      if (board[i][j] == WHITE) { 
        white_score += (nbl - i);

        if ((i + 1 < nbl) && (j + 1 < nbc)) { 
          white_score += valcm;
          if (board[i + 1][j + 1] == BLACK) { 
            white_score += valce;
          }
        }

        if ((i + 1 < nbl) && (j - 1 >= 0)) { 
          white_score += valcm;
          if (board[i + 1][j - 1] == BLACK) { 
            white_score += valce;
          }
        }

        if ((i - 1 >= 0) && (j + 1 < nbc)) {
          if (board[i - 1][j + 1] == WHITE) { 
            white_score += value_trade;
          }
        }

        if ((i - 1 >= 0) && (j - 1 >= 0)) { 
          if (board[i - 1][j - 1] == WHITE) { 
            white_score += value_trade;
          }
        }
      } else if (board[i][j] == BLACK) { 
        black_score += (i + 1);

        if ((i - 1 >= 0) && (j + 1 < nbc)) { 
          black_score += valcm;
          if (board[i - 1][j + 1] == WHITE) { 
            black_score += valce;
          }
        }

        if ((i - 1 >= 0) && (j - 1 >= 0)) { 
          black_score += valcm;
          if (board[i - 1][j - 1] == WHITE) { 
            black_score += valce;
          }
        }

        if ((i + 1 < nbl) && (j + 1 < nbc)) {
          if (board[i + 1][j + 1] == BLACK) { 
            black_score += value_trade;
          }
        }

        if ((i + 1 < nbl) && (j - 1 >= 0)) {
          if (board[i + 1][j - 1] == BLACK) { 
            black_score += value_trade;
          }  }   }   } }
  return (white_score > black_score) ? WHITE : BLACK;
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
