#include <stdio.h>
int main(int argc, char const *argv[]) {
  int s[6] = [-1, 0, 1, 2, -1, -4];
  int numsSize=6;
  int *returnSize=3;
  threeSum(s,numsSize,returnSize);
  return 0;
}
int** threeSum(int* nums, int numsSize, int* returnSize) {
  if (*returnSize<1||*returnSize>numsSize) {
    return NULL;
  }

}
