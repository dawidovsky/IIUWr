void Spiral( int X, int Y){
    int x,y,dx,dy;
    x = y = dx =0;
    dy = -1;
    int t = std::max(X,Y);
    int maxI = t*t;
    for(int i =0; i < maxI; i++){
        if ((-X/2 <= x) && (x <= X/2) && (-Y/2 <= y) && (y <= Y/2)){
            // DO STUFF...
        }
        if( (x == y) || ((x < 0) && (x == -y)) || ((x > 0) && (x == 1-y))){
            t = dx;
            dx = -dy;
            dy = t;
        }
        x += dx;
        y += dy;
    }
}
