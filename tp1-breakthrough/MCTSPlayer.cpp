#include "mybt.h"
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <string>
#include <chrono> 
#include<vector>
#include <math.h>
#include <cstdio> 
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#define FLT_MAX std::numeric_limits<float>::max()
std::string root;
bt_move_t mcts(double time_limit);
MCTSNode* mcts_selection(MCTSNode* node, bt_t& board);  
void mcts_expansion(MCTSNode* node, bt_t& board);
bool mcts_simulation(bt_t& board);
void mcts_backpropagation(MCTSNode* node, bool result);
static MCTSNode* best_child(MCTSNode* node);
bt_move_t bt_t::mcts(bt_t& board, double time_limit) {

  MCTSNode* root = new MCTSNode(*this);

  std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
  MCTSNode* node = mcts_selection(root);
  while(std::chrono::steady_clock::now() - start < 
         std::chrono::duration<double>(time_limit)) {


    mcts_expansion(node);

    bool result = mcts_simulation(board);

    mcts_backpropagation(node, result);

  }

  return best_child(root)->board.moves[0];

}

MCTSNode* bt_t::mcts_selection(MCTSNode* node, bt_t& board) {

  if(endgame() != EMPTY || node->visits == 0) {
    play(node->board);
    return node; 
  }

  MCTSNode* best = nullptr;
  float score = -FLT_MAX;
  bool result = mcts_simulation(board);
  for(MCTSNode* child : node->children) {

    float curr_score = (float)child->wins/child->visits + sqrt(2*log(node->visits)/child->visits);
    if(curr_score > score) {
      best = child;
      score = curr_score;
    }
  }
  board.play(best->board.moves[0]); 
  return mcts_selection(best, board);

}

void bt_t::mcts_expansion(MCTSNode* node, bt_t& board) {

  update_moves();
   for(bt_move_t& move : moves) {
    
    MCTSNode* child = new MCTSNode(board);
    
    child->board = (board); 
    
    node->children.push_back(child);
  }

}

bool bt_t::mcts_simulation(bt_t& board) {

  bt_t copy = board;
  while(copy.endgame() == EMPTY) {

    bt_move_t move = copy.get_rand_move(); 
    while(!copy.can_play(move)) {
      move = copy.get_rand_move();
    }
    copy.play(move);

  }

  return copy.winner(board) == turn;
  
  // randomly play moves until end
  return winner(board) == turn; 

} 

void bt_t::mcts_backpropagation(MCTSNode* node, bool result) {

  while(node != nullptr) {
    node->visits++;  
    if(result) node->wins++;
    node = node->parent;
  }
}

MCTSNode* best_child(MCTSNode* node) {
  
return *std::max_element(node->children.begin(), node->children.end(),
                          [](MCTSNode* a, MCTSNode* b) {
                            return a->visits < b->visits;  
                          });
}

