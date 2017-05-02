boolean linear = true;
float minDistance = 1, maxDistance = 4;

class Normalize {
  float min, max;
  Normalize() { // Initializes a Normalize object with min and max set to + and - INF
    reset();
  }
  void note(float x) { // If x exceeds the min and max boundaries, readjust min and max.
    if(x < min)
      min = x;
    if(x > max)
      max = x;
  }
  float normalize(float x) { // Map x between the values 0 and 1 and return that value
    if(min == max || min == Float.POSITIVE_INFINITY)
      return 0;
    float n = map(x, min, max, 0, 1);
    return constrain(n, 0, 1);
  }
  float linear(float x) { // Normalize x, take the square root of the inverse, and map the result between 0 and 1 bssed on min and max dist
    float normalized = normalize(x);
    if(normalized == 0)
      return 1;
    float linear = sqrt(1 / normalized);
    linear = map(linear, minDistance, maxDistance, 0, 1);
    //println(linear);
    return constrain(linear, 0, 1);
  }
  float choose(float x) { //Return normalize(X) or linear(x) depending on preference set by linear var.
    return linear ? linear(x) : normalize(x);
  }
  void reset() { //Expands boiunds to everything
    min = Float.POSITIVE_INFINITY;
    max = Float.NEGATIVE_INFINITY;  
  }
}
