#include <iostream>
#include <future>
#include "functions/functions.h"
#include "spaceship/spaceship.h"
#include "enemy/enemy.h"
#include "player.h"
using namespace std;


int main()
{
  const int size = 100;
  // Allocate memory to the display frame (2D Array).
  char **frame = new char *[size];
  for (int i = 0; i < size; i++)
  {
    frame[i] = new char [size];
  }

  // Free memory allocated to the array.
  for (int i = 0; i < size; i++)
  {
    delete[] frame[i];
  }
  delete[] frame;

  return 0;
}
