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
int r, c, n;
vector<int> x1, y1, x2, y2;
int cutVertical(int startY, int startX, int endY, int endX, int cutX);
int cutHorizontal(int startY, int startX, int endY, int endX, int cutY);

int cutVertical(int startY, int startX, int endY, int endX, int cutX)
{
  if (endX - startX == 1 || cutX == startX || cutX == endX)
  {
    return 0;
  }
  bool leftHasTopping = false, rightHasTopping = false;
  for (int i = 0; i < n; i++) // Check every topping
  {
    if (startY <= y1[i] && y2[i] <= endY && startX <= x1[i] && x2[i] <= endX) // topping on subcake
    {
      if (x1[i] < cutX && cutX < x2[i]) // Topping in way of cut
      {
        leftHasTopping = false;
        break;
      }
      if (cutX <= x1[i])
      {
        rightHasTopping = true;
      }
      else
      {
        leftHasTopping = true;
      }
    }

    int canCut = (leftHasTopping && rightHasTopping) ? 1 : 0;
    int left, right;
    if (canCut)
    {
      left = max(cutVertical(startY, startX, endY, cutX, (cutX + startX) / 2), cutHorizontal(startY, startX, endY, cutX, (endY + startY) / 2));
      right = max(cutVertical(startY, cutX, endY, endX, (endX + cutX) / 2), cutHorizontal(startY, cutX, endY, endX, (endY + startY) / 2));
    }
    else
    {
      int token = cutX / 2;
      left = cutVertical(startY, startX, endY, endX, cutX - token);
      right = cutVertical(startY, startX, endY, endX, cutX + token);
    }
    return left + right + canCut;
  }
}

int cutHorizontal(int startY, int startX, int endY, int endX, int cutY)
{
  if (endY - startY == 1 || cutY == startY || cutY == endY) // Base case
  {
    return 0;
  }
  bool topHasTopping = false, botHasTopping = false;
  for (int i = 0; i < n; i++) // Check every topping
  {
    if (startY <= y1[i] && y2[i] <= endY && startX <= x1[i] && x2[i] <= endX) // topping on subcake
    {
      if (y1[i] < cutY && cutY < y2[i]) // Topping in way of cut
      {
        topHasTopping = false;
        break;
      }
      if (cutY <= y1[i])
      {
        topHasTopping = true;
      }
      else
      {
        botHasTopping = true;
      }
    }

    int canCut = (topHasTopping && botHasTopping) ? 1 : 0;
    int top, bot;
    if (canCut)
    {
      top = max(cutVertical(cutY, startX, endY, endX, (endX + startX) / 2), cutHorizontal(cutY, startX, endY, endX, (endY + startY) / 2));
      bot = max(cutVertical(startY, startX, cutY, endX, (endX + startX) / 2), cutHorizontal(startY, startX, cutY, endX, (cutY + startY) / 2));
    }
    else
    {
      int token = cutY / 2;
      top = cutHorizontal(startY, startX, endY, endX, cutY + token);
      bot = cutHorizontal(startY, startX, endY, endX, cutY - token);
    }
    return top + bot + canCut;
  }
}

int main(int argc, char const *argv[])
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
  printf("%d\n", max(cutVertical(0, 0, r, c, c / 2), cutHorizontal(0, 0, r, c, r / 2)) + 1);
  return 0;
}
