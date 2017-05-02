class MomentumAverage {
  float adapt;
  float avg;
  MomentumAverage(float adapt) { // Initializes a MomentumAverage object with this.adapt = ADAPT
    this.adapt = adapt;
    reset();
  }
  void note(float x) { //Unless x = inf, the average is a moving average (adapt determines how much the new data x impacts the average)
    if(x == Float.POSITIVE_INFINITY)
      return;
    else
      avg = (avg * (1 - adapt)) + (x * adapt);
  }
  void reset() { //Sets the average to 0.
    avg = 0;
  }
}
