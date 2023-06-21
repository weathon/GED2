#include <iostream>
#include <unistd.h>
void printProgressBar(int progress, int total, int barWidth = 40) {
  // GPT
  float ratio = static_cast<float>(progress) / total;
  int filledWidth = static_cast<int>(ratio * barWidth);

  std::cout <<" "<< progress << "/" << total<<" [";
  for (int i = 0; i < barWidth; ++i) {
    if (i < filledWidth)
      std::cout << "=";
    else if (i == filledWidth)
      std::cout << ">";
    else
      std::cout << " ";
  }
  std::cout << "] " << static_cast<int>(ratio * 100.0) << "%\r";
  std::cout.flush();
}

// int main() {

//   for (int i = 0; i < 20; i++) {
//     sleep(1);
//     printProgressBar(i, 20);
//   }

//   return 0;
// }