#include <QFileDialog>
#include "base.h"
#include <string>

void cmp_type::quickSort(int *numbers, int left, int right, int size, string* repr)
{
  int pivot;
  int l_hold = left;
  int r_hold = right;
  pivot = numbers[left];
  while (left < right)
  {
    while ((numbers[right] >= pivot) && (left < right))
      right--;
    if (left != right)
    {
      numbers[left] = numbers[right];
      left++;
    }
    while ((numbers[left] <= pivot) && (left < right))
      left++;
    if (left != right)
    {
      numbers[right] = numbers[left];
      right--;
    }
  }
  numbers[left] = pivot;
  pivot = left;
  left = l_hold;

  repr->append("\n[");
  for (int i = 0; i < size; i++) {
      repr->append(to_string(numbers[i])).append(" ");
  }
  repr->append("]\n");

  right = r_hold;
  if (left < pivot)
    cmp_type::quickSort(numbers, left, pivot - 1, size, repr);
  if (right > pivot)
    cmp_type::quickSort(numbers, pivot + 1, right, size, repr);

}



