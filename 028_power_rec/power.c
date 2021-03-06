unsigned power(unsigned x, unsigned y) {
  if (x == 0 && y == 0) {
    return 1;
  }
  if (y == 1) {
    return x;
  }
  if (y != 0) {
    return (x * power(x, y - 1));
  }
  return 0;
}
