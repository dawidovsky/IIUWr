import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def randomGrid(N):
    return np.random.choice([100, 0], N*N).reshape(N, N)

def update(frameNum, img, grid, N):

    newGrid = grid.copy()
    for i in range(N):
        for j in range(N):

            total = (grid[i, (j-1)%N] + grid[i, (j+1)%N] + grid[(i-1)%N, j] + grid[(i+1)%N, j] +
                    grid[(i-1)%N, (j-1)%N] + grid[(i-1)%N, (j+1)%N] + grid[(i+1)%N,
                    (j-1)%N] + grid[(i+1)%N, (j+1)%N])/100

            if grid[i, j]  == 100:
                if (total < 2) or (total > 3):
                    newGrid[i, j] = 0
            else:
                if total == 3:
                    newGrid[i, j] = 100

    img.set_data(newGrid)
    grid[:] = newGrid[:]
    return img,

grid = randomGrid(100)
fig, ax = plt.subplots()
cmap = cm.seismic
img = ax.imshow(grid, cmap)
ani = animation.FuncAnimation(fig, update, fargs=(img, grid, 100),
                                frames = 10,
                                interval=50)
plt.show()

# 100 and < 2 -> 0
# 100 and 2 | 3 -> 100
# 100 and > 3 -> 0
# 0 and 3 -> 100
