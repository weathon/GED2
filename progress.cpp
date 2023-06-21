#include <iostream>
#include <time.h>
#include <unistd.h>

bool firstTime = true;
int startedTime;
int ETL;
void printProgressBar(int progress, int total, int barWidth = 40) {
  // GPT
  if (firstTime) {
    startedTime = time(0);
    firstTime = false;
  }
  if (progress % 50 != 0 && progress != total)
    return;

  float ratio = static_cast<float>(progress) / total;
  int filledWidth = static_cast<int>(ratio * barWidth);
  ETL =  (time(0)-startedTime)/(progress+0.001)*(total-progress);
  std::cout << " " << progress << "/" << total << " [";
  for (int i = 0; i < barWidth; ++i) {
    if (i < filledWidth)
      std::cout << "=";
    else if (i == filledWidth)
      std::cout << ">";
    else
      std::cout << " ";
  }
  std::cout << "] " << static_cast<int>(ratio * 100.0) << "% "<< "Estimated Time Left: " << ETL/60 <<" min"<<ETL%60<< "sec \r";
  std::cout.flush();
}

// int main() {

//   for (int i = 0; i < 20; i++) {
//     sleep(1);
//     printProgressBar(i, 20);
//   }

//   return 0;
// }