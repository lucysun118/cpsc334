final int N = 128;
final int iter = 16;
final int SCALE = 5;
float t = 0;


int IX(int x, int y) {
  x = constrain(x, 0, N-1);
  y = constrain(y, 0, N-1);
  return x + (y * N);
}

class Fluid {
  int size;
  float dt;
  float diff;
  float visc;
  
  float[] s;
  float[] density;
  
  float[] Vx;
  float[] Vy;
  
  float[] Vx0;
  float[] Vy0;
  
  
  
  Fluid(float dt, float diffusion, float viscosity) {
    this.size = N;
    this.dt = dt;
    this.diff = diffusion;
    this.visc = viscosity;
    
    this.s = new float[N*N];
    this.density = new float[N*N];
    
    this.Vx = new float[N*N];
    this.Vy = new float[N*N];
    
    this.Vx0 = new float[N*N];
    this.Vy0 = new float[N*N];
  }
  
  void decreaseVelocityGeneration() {
    float decreaseFactor = 0.7; // Adjust the decrease factor as needed
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        int index = IX(i, j);
        Vx[index] *= decreaseFactor;
        Vy[index] *= decreaseFactor;
        Vx0[index] *= decreaseFactor;
        Vy0[index] *= decreaseFactor;
      }
    }
  }

  void resetVelocityGeneration() {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        int index = IX(i, j);
        // Reset the velocity generation to its default state
        Vx[index] = 0.0;
        Vy[index] = 0.0;
        Vx0[index] = 0.0;
        Vy0[index] = 0.0;
      }
    }
  }
  
  void setVelocityToZero() {
  int touchValue = extractTouchValue(touchMessage);

  if (touchValue > 75) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        int index = IX(i, j);
        Vx[index] = 0.0;
        Vy[index] = 0.0;
        Vx0[index] = 0.0;
        Vy0[index] = 0.0;
      }
    }
  }
}
  
  void step() {
    int N          = this.size;
    float visc     = this.visc;
    float diff     = this.diff;
    float dt       = this.dt;
    float[] Vx      = this.Vx;
    float[] Vy      = this.Vy;
    float[] Vx0     = this.Vx0;
    float[] Vy0     = this.Vy0;
    float[] s       = this.s;
    float[] density = this.density;
    
    diffuse(1, Vx0, Vx, visc, dt);
    diffuse(2, Vy0, Vy, visc, dt);
    
    project(Vx0, Vy0, Vx, Vy);
    
    advect(1, Vx, Vx0, Vx0, Vy0, dt);
    advect(2, Vy, Vy0, Vx0, Vy0, dt);
    
    project(Vx, Vy, Vx0, Vy0);
    
    diffuse(0, s, density, diff, dt);
    advect(0, density, s, Vx, Vy, dt);
}
  
  void addDensity(int x, int y, float amount) {
    int index = IX(x,y);
    this.density[index] += amount;
  }
  
  void addVelocity(int x, int y, float amountX, float amountY) {
    int index = IX(x,y);
    this.Vx[index] += amountX;
    this.Vy[index] += amountY;
  }
  
  void renderD() {
    colorMode(HSB, 300);
    
     for (int i = 0; i < N; i++) {
       for (int j = 0; j < N; j++) {
         float x = i * SCALE;
         float y = j * SCALE;
         float d = this.density[IX(i,j)];
         //fill(255, 100);
         fill(d, 255, 255);
         noStroke();
         square(x, y, SCALE);
       }
     }         
  }
  
  void fadeD() {
    for (int i = 0; i < this.density.length; i++) {
      float d = density[i];
      density[i] = constrain(d-0.1, 0, 255);
    }
  }
}