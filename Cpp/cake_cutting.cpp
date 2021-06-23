#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

/**
 *  For cuts
 * 
 *  x = 1, y = 1
 *      
 *    x|xxx    
 *    x|xxx
 *    -----
 *    x|xxx
 *
 **/

class Cake
{
public:
  Cake();
  int cutCake();

private:
  int r, c, n;
  vector<int> x1, y1, x2, y2;
  int cutHorizontal(int startY, int startX, int endY, int endX);
  int cutVertical(int startY, int startX, int endY, int endX);
};

Cake::Cake()
{
  scanf("%d%d%d", &r, &c, &n);
  x1.resize(n);
  y1.resize(n);
  x2.resize(n);
  y2.resize(n);
  for (int i = 0; i < n; i++)
  {
    scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
  }
}

int Cake::cutVertical(int startY, int startX, int endY, int endX)
{
  for (int cutX = startX + 1; cutX < endX; cutX++)
  {
    // Check if column can be cut
    bool rightHasTopping, leftHasTopping = false;
    for (int i = 0; i < this->n; i++) // Check every topping
    {
      if (startY <= y1[i] && y2[i] <= endY && startX <= x1[i] && x2[i] <= endX) //topping on subcake
      {
        if (cutX <= x1[i]) // Topping is on right of cut
        {
          rightHasTopping = true;
        }
        else if (x2[i] <= cutX) // Topping on left of cut
        {
          leftHasTopping = true;
        }
        else // Topping in the way of this cut
        {
          rightHasTopping = false;
          break;
        }
      }
    }

    if (rightHasTopping && leftHasTopping) // Column can be cut
    {
      cout << "I have cut col: " << cutX << endl;
      int rightSide = max(cutVertical(startY, cutX, endY, endX), cutHorizontal(startY, cutX, endY, endX));
      int leftSide = max(cutVertical(startY, startX, endY, cutX), cutHorizontal(startY, startX, endY, cutX));
      return rightSide + leftSide;
    }
    else // Column cannot be cut
    {
      continue;
    }
  }

  return 1;
}

int Cake::cutHorizontal(int startY, int startX, int endY, int endX)
{
  for (int cutY = startY + 1; cutY < endY; cutY++)
  {
    // Check if row can be cut
    bool topHasTopping, botHasTopping = false;
    for (int i = 0; i < this->n; i++) // Check every topping
    {
      if (startY <= y1[i] && y2[i] <= endY && startX <= x1[i] && x2[i] <= endX) //topping on subcake
      {
        if (cutY <= y1[i]) // Topping is on top of cut
        {
          topHasTopping = true;
        }
        else if (y2[i] <= cutY) // Topping is on bottom of cut
        {
          botHasTopping = true;
        }
        else // Topping in the way of this cut
        {
          topHasTopping = false;
          break;
        }
      }
    }

    if (topHasTopping && botHasTopping) // Row can be cut
    {
      cout << "I have cut row: " << cutY << endl;
      int topSide = max(cutVertical(cutY, startX, endY, endX), cutHorizontal(cutY, startX, endY, endX));
      int botSide = max(cutVertical(startY, startX, cutY, endX), cutHorizontal(startY, startX, cutY, endX));
      return topSide + botSide;
    }
    else // Row cannot be cut
    {
      continue;
    }
  }

  return 1;
}

int Cake::cutCake()
{
  return max(cutHorizontal(0, 0, r, c), cutVertical(0, 0, r, c));
}

int main(int argc, char const *argv[])
{
  Cake myCake;
  printf("%d\n", myCake.cutCake());
  return 0;
}
