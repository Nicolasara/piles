#include "game_handler.h"

int main() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  std::cout << "Hello, World!" << std::endl;
  GameHandler gameHandler;
  gameHandler.startGame();
  return 0;
}