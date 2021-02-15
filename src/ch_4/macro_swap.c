// Swaps two variables (`x` and `y`) of type `t`.
#define swap(t, x, y) \
    { x = (t) x + (t) y; \
      y = (t) x - (t) y; \
      x = (t) x - (t) y; }